/*
** execute_quit.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/execute_quit.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. mai 25 15:56:31 2017 Loïc Lopez
** Last update Sat Jun 10 14:36:04 2017 Loïc Dupil
*/

#include "server.h"

void	execute_quit_print_msg_clients(t_irc_server *irc_server,
				       int current_client, char
				       **actions, int i)
{
  int 	k;
  int 	l;

  k = -1;
  if (!actions[1])
    return;
  while (++k < irc_server->channels[i].nbr_clients)
    {
      if (irc_server->channels[i].clients[k].id !=
	  irc_server->clients[current_client].id)
	{
	  l = 0;
	  dprintf(irc_server->channels[i].clients[k].sd, "%s "
		  "quit: ",
		  irc_server->clients[current_client].pseudo);
	  while (actions[++l])
	    dprintf(irc_server->channels[i].clients[k].sd, "%s ",
		    actions[l][0] == ':' ? &actions[l][1]:
		    &actions[l][0]);
	  dprintf(irc_server->channels[i].clients[k].sd, "\r\n");
	}
    }
}

void	execute_quit_reset_client(t_irc_server *irc_server,
				  int current_client)
{
  memset(irc_server->clients[current_client].channels_id, 0, 10);
  memset(irc_server->clients[current_client].pseudo, 0, 9);
  irc_server->clients[current_client].current_channel = 0;
  irc_server->clients[current_client].cmd = STANDBY;
  close(irc_server->clients[current_client].sd);
  irc_server->clients[current_client].sd = 0;
}

void	execute_quit(t_irc_server *irc_server, int current_client,
		     char **actions)
{
  int 	i;
  int 	j;

  i = -1;
  while (++i < irc_server->max_channel)
    {
      j = -1;
      while (++j < irc_server->channels[i].nbr_clients)
	{
	  if (irc_server->channels[i].clients[j].id ==
	      irc_server->clients[current_client].id)
	    {
	      execute_quit_print_msg_clients(irc_server, current_client,
					     actions, i);
	      irc_server->channels[i].clients[j] = (t_clients){0};
	      irc_server->channels[i].nbr_clients--;
	      break;
	    }
	}
    }
  execute_quit_reset_client(irc_server, current_client);
}
