/*
** check_execute_send_file.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/check_execute_send_file.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. juin 10 18:18:04 2017 Loïc Lopez
** Last update sam. juin 10 18:18:04 2017 Loïc Lopez
*/

#include "server.h"

bool	current_client_in_channel_requested(t_irc_server
					    *irc_server,
					    int current_client)
{
  int 			i;
  int 			j;
  bool			current_client_in_channel_request;

  i = -1;
  current_client_in_channel_request = false;
  while (++i < irc_server->max_channel)
    {
      j = -1;
      while (++j < irc_server->max_clients)
	{
	  if (irc_server->channels[i].clients[j].id ==
	      irc_server->clients[current_client].id)
	    {
	      current_client_in_channel_request = true;
	      break;
	    }
	}
    }
  return (current_client_in_channel_request);
}

bool	client_receiver_in_channel_requested(t_irc_server
					     *irc_server,
					     char *client_receiver)
{
  int 			i;
  int 			j;
  bool			client_receiver_in_channel_request;

  i = -1;
  client_receiver_in_channel_request = false;
  while (++i < irc_server->max_channel)
    {
      j = -1;
      while (++j < irc_server->max_clients)
	{
	  if (strcmp(irc_server->channels[i].clients[j].pseudo,
		     client_receiver) == 0)
	    {
	      client_receiver_in_channel_request = true;
	      break;
	    }
	}
    }
  return (client_receiver_in_channel_request);
}

int 	check_client(t_irc_server *irc_server, int current_client,
		     char **actions, int peer_socket)
{
  if (!current_client_in_channel_requested(irc_server, current_client))
    {
      send(peer_socket, "500", 3, 0);
      dprintf(irc_server->clients[current_client].sd, "You are not in the "
	      "channel: %s\n", actions[1]);
      return (-1);
    }
  else if (!client_receiver_in_channel_requested(irc_server, actions[2]))
    {
      send(peer_socket, "500", 3, 0);
      dprintf(irc_server->clients[current_client].sd, "%s is not in the "
	      "channel: %s\n", actions[2], actions[1]);
      return (-1);
    }
  else
    send(peer_socket, "200", 3, 0);
  return (0);
}

int 	check_request_validity_and_create_subconnection(t_irc_server
							*irc_server,
							int current_client,
							char **actions)
{
  int 			peer_socket;
  socklen_t     	sock_len;
  struct sockaddr_in    peer_addr;
  char          	buffer[4];

  buffer[3] = 0;
  recv(irc_server->clients[current_client].sd, buffer, 3, 0);
  if (strcmp(buffer, "403") == 0)
    {
      dprintf(irc_server->clients[current_client].sd, "Can't upload file.\n");
      return (-1);
    }
  sock_len = sizeof(struct sockaddr_in);
  if ((peer_socket = accept(irc_server->serv_socket,
			    (struct sockaddr *)&peer_addr, &sock_len)) == -1)
    return (peer_socket);
  if (check_client(irc_server, current_client, actions, peer_socket) == -1)
    return (-1);
  return (0);
}
