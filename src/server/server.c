/*
** server.c for PSU_2016_myirc in /home/dupil_l/PSU_2016_myirc/server.c
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Mon May 22 14:27:30 2017 Loïc Dupil
** Last update Sat Jun 10 14:36:53 2017 Loïc Dupil
*/

#include "server.h"
#include "myirc.h"

void    init(t_irc_server *irc_server, int port)
{
  int 	i;

  irc_server->max_clients = 50;
  irc_server->opt = 1;
  i = -1;
  while (++i < irc_server->max_clients)
    {
      irc_server->clients[i] = (t_clients){0};
      irc_server->clients[i].id = (short)(i + 1);
      irc_server->clients[i].cmd = STANDBY;
    }
  if ((irc_server->serv_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    error();
  if (setsockopt(irc_server->serv_socket, SOL_SOCKET,
		 SO_REUSEADDR, (char *)&irc_server->opt, sizeof(int)) < 0)
    error();
  irc_server->address.sin_family = AF_INET;
  irc_server->address.sin_addr.s_addr = INADDR_ANY;
  irc_server->address.sin_port = htons(port);
  if (bind(irc_server->serv_socket, (struct sockaddr *) &irc_server->address,
	   sizeof(irc_server->address)) < 0)
    error();
  if (listen(irc_server->serv_socket, 3) < 0)
    error();
  irc_server->addrlen = sizeof(irc_server->address);
}

void			init_channel(t_irc_server *irc_server)
{
  int 			i;
  int 			j;

  irc_server->max_channel = 10;
  irc_server->nbr_clients = 0;
  i = 0;
  while (i < irc_server->max_channel)
    {
      sprintf(irc_server->channels[i].channel_name,
	      "%s%d", "#channel", i + 1);
      irc_server->channels[i].chan_id = i + 1;
      irc_server->channels[i].nbr_clients = 0;
      j = -1;
      while (++j < irc_server->max_clients)
	irc_server->channels[i].clients[j] = (t_clients){0};
      i++;
    }
}

void	incomming_connection(t_irc_server *irc_server)
{
  int 	i;
  if (FD_ISSET(irc_server->serv_socket, &irc_server->readded))
    {
      i = -1;
      if ((irc_server->new_client =
	   accept(irc_server->serv_socket,
		  (struct sockaddr *)&irc_server->address,
		  (socklen_t*)&irc_server->addrlen)) < 0)
	error();
      while (++i < irc_server->max_clients)
	if (irc_server->clients[i].sd == 0)
	  {
	    irc_server->clients[i].sd = irc_server->new_client;
	    irc_server->nbr_clients++;
	    break;
	  }
    }
}

void			clients_actions(t_irc_server *irc_server)
{
  int 	i;

  i = -1;
  while (++i < irc_server->max_clients)
    {
      if (FD_ISSET(irc_server->clients[i].sd, &irc_server->readded))
	{
	  irc_server->client_cmd = get_next_line(irc_server->clients[i].sd);
	  if (irc_server->client_cmd != NULL)
	    launch_client_demand(irc_server, i);
	  free(irc_server->client_cmd);
	}
    }
}

void    		server(int port)
{
  t_irc_server      	irc_server;
  int 			i;

  init(&irc_server, port);
  init_channel(&irc_server);
  while (1)
    {
      FD_ZERO(&irc_server.readded);
      FD_SET(irc_server.serv_socket, &irc_server.readded);
      irc_server.max_sd = irc_server.serv_socket;
      i = -1;
      while (++i < irc_server.max_clients)
        {
          if (irc_server.clients[i].sd > 0)
            FD_SET(irc_server.clients[i].sd, &irc_server.readded);
          if (irc_server.clients[i].sd > irc_server.max_sd)
            irc_server.max_sd = irc_server.clients[i].sd;
        }
      irc_server.activity = select(irc_server.max_sd + 1,
				   &irc_server.readded, NULL, NULL, NULL);
      irc_server.activity >= 0 && errno != EINTR ?
	(incomming_connection(&irc_server), clients_actions(&irc_server)) : 0;
    }
}
