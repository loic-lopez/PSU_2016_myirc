/*
** execute_list_users.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/execute_list_users.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 24 13:16:45 2017 Loïc Lopez
** Last update Sat Jun 10 15:08:13 2017 Loïc Dupil
*/

#include "server.h"

void 	execute_users(t_irc_server *irc_server, int current_client,
		      char **actions)
{
  int 	i;

  (void)actions;
  i = -1;
  while (++i < irc_server->nbr_clients)
    dprintf(irc_server->clients[current_client].sd,
	    "%s\r\n", irc_server->clients[i].pseudo);
}

void 	execute_names(t_irc_server *server, int curr,
		      char **act)
{
  int 	i;
  int 	j;

  if (act[1] && act[1][0] != '#')
    dprintf(server->clients[curr].sd,
	    "Invalid channel name: %s\r\n", act[1]);
  else if (act[1])
    {
      i = -1;
      while (++i < server->max_channel)
	{
	  if (strcmp(server->channels[i].channel_name, act[1]) == 0)
	    {
	      j = -1;
	      while (++j < server->channels[i].nbr_clients)
		dprintf(server->clients[curr].sd,
			"%s\r\n", server->channels[i].clients[j].pseudo);
	      return;
	    }
	}
      dprintf(server->clients[curr].sd, "No channel found: %s\r\n", act[1]);
    }
  else
    dprintf(server->clients[curr].sd,
	    "Provide channel name: \"/names [chan_name]\"\r\n");
}

void 	execute_list(t_irc_server *irc_server, int current_client,
		     char **actions)
{
  int 	i;

  i = 0;
  while (i < irc_server->max_channel)
    {
      dprintf(irc_server->clients[current_client].sd, "%s\r\n",
	      irc_server->channels[i].channel_name);
      i++;
    }
  (void)actions;
}

void 	execute_user(t_irc_server *irc_server, int current_client,
		     char **actions)
{
  (void)actions;
  dprintf(irc_server->clients[current_client].sd, "001 %s: User registered"
	  ".\r\n", irc_server->clients[current_client].pseudo);
}
