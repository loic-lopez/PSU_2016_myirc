/*
** execute_channel_act.c for execute_channel_act.c in /home/dupil_l/Module_UNIXRéseau/PSU_2016_myirc/src/server
** 
** Made by Loïc Dupil
** Login   <dupil_l@epitech.net>
** 
** Started on  Wed May 24 10:53:47 2017 Loïc Dupil
** Last update Sat Jun 10 15:37:18 2017 Loïc Dupil
*/

#include "server.h"

void	func_for_norme(t_irc_server *server, int client,
		       int i, int id)
{
  if (id == 1)
    {
      dprintf(server->clients[client].sd,
	      "Switched into the channel : %s\r\n",
	      server->channels[i].channel_name);
      server->clients[client].current_channel =
	(short)server->channels[i].chan_id;
    }
  else if (id == 2)
    {
      server->channels[i].clients[server->channels[i].nbr_clients]
	= server->clients[client];
      server->clients[client].current_channel =
	(short)server->channels[i].chan_id;
      server->channels[i].nbr_clients++;
    }
  else
    return;
}

void	execute_part_verify(t_irc_server *server,
			    int current_client, int i)
{
  int 	j;

  j = -1;
  while (++j < server->channels[i].nbr_clients)
    {
      if (server->channels[i].clients[j].id == server->clients[j].id)
	{
	  server->channels[i].clients[j] = (t_clients){0};
	  dprintf(server->clients[current_client].sd,
		  "%s: channel quit.\r\n",
		  server->channels[i].channel_name);
	  server->clients[current_client].channels_id[j] = 0;
	  server->channels[i].nbr_clients--;
	  while (++j < server->channels[i].nbr_clients)
	    {
	      if (server->channels[i].clients[j].id == server->clients[j].id)
		{
		  func_for_norme(server, current_client, i, 1);
		  return;
		}
	    }
	}
    }
  dprintf(server->clients[current_client].sd,
	  "You are not in the channel.\r\n");
}

void 	execute_part(t_irc_server *irc_server, int current_client,
		     char **actions)
{
  int 	i;

  if (actions[1] && actions[1][0] != '#')
    dprintf(irc_server->clients[current_client].sd, "Unknown channel name\n");
  else if (actions[1])
    {
      i = -1;
      while (++i < irc_server->max_channel)
	{
	  if (strcmp(actions[1], irc_server->channels[i].channel_name) == 0)
	    {
	      execute_part_verify(irc_server, current_client,  i);
	      return;
	    }
	}
    }
  dprintf(irc_server->clients[current_client].sd, "Unknown channel\n");
}

bool 	verify_already_join(t_irc_server *irc_server, int current_client,
			    char **actions)
{
  int 	i;

  i = 0;
  while (i < irc_server->max_channel)
    {
      if (strcmp(irc_server->channels[i].channel_name, actions[1]) == 0
	  && irc_server->clients[current_client].channels_id[i] ==
	  irc_server->channels[i].chan_id)
	{
	  dprintf(irc_server->clients[current_client].sd,
		  "Switched into the channel : %s\r\n", actions[1]);
	  irc_server->clients[current_client].current_channel =
	    (short)irc_server->channels[i].chan_id;
	  return (true);
	}
      i++;
    }
  return (false);
}

void 	execute_join(t_irc_server *server, int current_client,
		     char **actions)
{
  int 	i;

  if (actions[1][0] != '#')
    dprintf(server->clients[current_client].sd,
	    "Unknown channel name\n");
  else
    {
      i = -1;
      while (++i < server->max_channel)
	{
	  if (strcmp(actions[1], server->channels[i].channel_name) == 0)
	    {
	      if (verify_already_join(server, current_client, actions))
		return;
	      dprintf(server->clients[current_client].sd,
		      "Welcome into channel : %s\r\n", actions[1]);
	      server->clients[current_client].channels_id[i] =
		(short)server->channels[i].chan_id;
	      func_for_norme(server, current_client, 0, 2);
	      return;
	    }
	}
      dprintf(server->clients[current_client].sd, "Unknown channel\n");
    }
}
