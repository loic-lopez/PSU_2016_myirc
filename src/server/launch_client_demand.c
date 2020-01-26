/*
** launch_client_demand.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/launch_client_demand.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 16:39:57 2017 Loïc Lopez
** Last update Sat Jun 10 15:01:13 2017 Loïc Dupil
*/

#include "server.h"
#include "myirc.h"

char 	**change_first_action_block(char **actions)
{
  int 	i;
  char 	*tmp_action;

  if (actions[0][0] == '/' && actions[0][1] && islower(actions[0][1]))
    return (actions);
  else
    {
      i = 0;
      if (actions[0][0] != '/')
	{
	  if ((tmp_action =
	       malloc(sizeof(char) * strlen(actions[0]) + 2)) == NULL)
	    return (NULL);
	  tmp_action[0] = '/';
	  tmp_action[1] = 0;
	  strcat(tmp_action, actions[0]);
	  free(actions[0]);
	  actions[0] = strdup(tmp_action);
	  free(tmp_action);
	}
      while (actions[0][++i])
	actions[0][i] = (char)tolower(actions[0][i]);
    }
  return (actions);
}

void	check_entry(t_irc_server *server, char **actions, int current_client)
{
  if (actions[1][0] == '&' || actions[1][0] == '#')
    server->clients[current_client].cmd = SEND_FILE;
  else
    server->clients[current_client].cmd = MSG_SPECIFIC_USER;
}

void	find_command(t_irc_server *irc_server, char **actions,
		     int current_client, bool *is_valid_command)
{
  size_t i;
  const 		char	*available_commands[] =
    {
      "/nick", "/list", "/join", "/part", "/users",
      "/names", "/accept_file", "/user", "/quit"
    };

  i = 0;
  while (i < sizeof(available_commands) / sizeof(available_commands[0]))
    {
      if (strcmp(available_commands[i], actions[0]) == 0)
	{
	  irc_server->clients[current_client].cmd = (e_command)i;
	  *is_valid_command = true;
	}
      i++;
    }
}

bool	parse_client_demand(t_irc_server *irc_server, char **actions,
			    int current_client)
{
  bool	is_valid_command;

  is_valid_command = false;
  if ((actions[0][0] != '/' && islower(actions[0][0]))
      || (actions[0][0] != '/' && isupper(actions[0][0])
	  && islower(actions[0][1])))
    {
      is_valid_command = true;
      irc_server->clients[current_client].cmd = MSG_TO_CHANNEL;
    }
  else
    {
      actions = change_first_action_block(actions);
      if (strcmp(actions[0], "/msg") == 0)
	{
	  is_valid_command = true;
	  check_entry(irc_server, actions, current_client);
	}
      else
	find_command(irc_server, actions, current_client, &is_valid_command);
    }
  return (is_valid_command);
}

void	launch_client_demand(t_irc_server *irc_server, int current_client)
{
  char 	**actions;
  int 	i;

  fprintf(stderr, "%s\n", irc_server->client_cmd);
  irc_server->client_cmd = remove_backslash_r(irc_server->client_cmd);
  actions = str_to_wordtab(irc_server->client_cmd, ' ');
  if (!actions)
    return;
  else
    {
      actions[0] = remove_backslash_r(actions[0]);
      if (parse_client_demand(irc_server, actions, current_client))
	execute_client_demand(irc_server, current_client, actions);
      else
	{
	  send(irc_server->clients[current_client].sd,
	       "Command not found!\r\n", strlen("Command not found!\r\n"), 0);
	}
      i = -1;
      while (actions[++i])
	free(actions[i]);
      free(actions);
    }
}
