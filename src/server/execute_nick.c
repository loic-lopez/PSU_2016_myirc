/*
** execute_nick.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/execute_nick.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mar. mai 23 19:12:09 2017 Loïc Lopez
** Last update Sat Jun 10 15:12:27 2017 Loïc Dupil
*/

#include "server.h"

bool	execute_nick_verify_already_used(t_irc_server *irc_server,
					 int current_client,
					 char **actions)
{
  int 	j;

  j = -1;
  while (++j < irc_server->nbr_clients)
    {
      if (strcmp(actions[1], irc_server->clients[j].pseudo) == 0)
	{
	  dprintf(irc_server->clients[current_client].sd,
		  "%s: Already Used.\r\n", actions[1]);
	  return (true);
	}
    }
  return (false);
}

void	execute_nick_search_client_id(t_irc_server *irc_server,
				      int current_client,
				      char **actions, int i)
{
  int 	j;

  j = -1;
  while (++j < irc_server->channels[i].nbr_clients)
    {
      if (irc_server->channels[i].clients[j].id ==
	  irc_server->clients[current_client].id)
	{
	  memset(irc_server->channels[i].clients[j].pseudo, 0, 9);
	  strcpy(irc_server->channels[i].clients[j].pseudo,
		 actions[1]);
	  break;
	}
    }
}

void 	execute_nick(t_irc_server *irc_server, int current_client,
		     char **actions)
{
  int 	i;

  if (actions[1] &&
      execute_nick_verify_already_used(irc_server, current_client, actions))
    return;
  else if (actions[1] && strlen(actions[1]) <= 9)
    {
      i = -1;
      while (++i < irc_server->max_channel)
	{
	  if (irc_server->clients[current_client].current_channel
	      == irc_server->channels[i].chan_id)
	    execute_nick_search_client_id(irc_server,
					  current_client, actions, i);
	}
      memset(irc_server->clients[current_client].pseudo, 0, 9);
      strcpy(irc_server->clients[current_client].pseudo, actions[1]);
      dprintf(irc_server->clients[current_client].sd,
	      "Nice to meet you %s\r\n",
	      irc_server->clients[current_client].pseudo);
    }
  else
    dprintf(irc_server->clients[current_client].sd,
	    "Invalid nickname: nickname must contains"
	    "between 1 and 9 characters.\r\n");
}
