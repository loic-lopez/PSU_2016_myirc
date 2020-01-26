/*
** execute_messages.c for PSU_2016_myirc in /home/dupil_l/PSU_2016_myirc/execute_messages.c
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Tue May 23 15:04:57 2017 Loïc Dupil
** Last update Sat Jun 10 14:48:59 2017 Loïc Dupil
*/

# include "server.h"

void 	execute_msg_specific_user(t_irc_server *server, int current_client,
				  char **actions)
{
  int 	i;
  int 	j;

  i = -1;
  while (++i < server->nbr_clients)
    {
      if (strcmp(actions[1], server->clients[i].pseudo) == 0)
	{
	  dprintf(server->clients[i].sd, "Whisper from %s : ",
		  server->clients[current_client].pseudo);
	  j = 2;
	  while (actions[j])
	    {
	      if (actions[j + 1])
	      	dprintf(server->clients[i].sd, "%s ", actions[j]);
	      else
		dprintf(server->clients[i].sd, "%s\r\n", actions[j]);
	      j++;
	    }
	}
    }
}

void 	write_msg(t_irc_server *irc_server, int current_client,
		  char **acts, int i)
{
  int 	k;
  int 	j;

  j = -1;
  while (++j < irc_server->channels[i].nbr_clients)
    {
      if (irc_server->channels[i].clients[j].id
	  != irc_server->clients[current_client].id)
	{
	  dprintf(irc_server->channels[i].clients[j].sd, "%s : ",
		  irc_server->clients[current_client].pseudo ?
		  irc_server->clients[current_client].pseudo : "\0");
	  k = -1;
	  while (acts[++k])
	    if (acts[k + 1])
	      dprintf(irc_server->channels[i].clients[j].sd, "%s ", acts[k]);
	    else
	      dprintf(irc_server->channels[i].clients[j].sd,
		      "%s\r\n", acts[k]);
	}
    }
}

void 	execute_msg_to_channel(t_irc_server *irc_server, int current_client,
			       char **acts)
{
  int 	i;

  i = -1;
  while (++i < irc_server->max_channel)
    {
      if (irc_server->channels[i].chan_id
	  == irc_server->clients[current_client].current_channel)
	write_msg(irc_server, current_client, acts, i);
    }
}
