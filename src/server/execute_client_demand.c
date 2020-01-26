/*
** execute_client_demand.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/execute_client_demand.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 16:58:28 2017 Loïc Lopez
** Last update Sat Jun 10 14:46:48 2017 Loïc Dupil
*/

#include "server.h"

void	execute_client_demand(t_irc_server *irc_server, int current_client,
			      char **actions)
{
  void	(*server_functions[])(t_irc_server *, int,
			      char **) =
    {
      execute_nick, execute_list, execute_join,
      execute_part, execute_users, execute_names, execute_accept,
      execute_user, execute_quit, execute_msg_specific_user,
      execute_msg_to_channel, execute_send_file
    };

  if ((irc_server->clients[current_client].cmd != NICK &&
       irc_server->clients[current_client].cmd != USER &&
       irc_server->clients[current_client].cmd != QUIT) &&
      irc_server->clients[current_client].pseudo[0] == 0)
    dprintf(irc_server->clients[current_client].sd,
	    "please give us your nickname with \"/nick [nickname]\"\r\n");
  else
    server_functions[irc_server->clients[current_client].cmd]
      (irc_server, current_client, actions);
}
