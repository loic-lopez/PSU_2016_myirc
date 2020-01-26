/*
** main.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/main.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 13:39:29 2017 Loïc Lopez
** Last update lun. mai 22 13:39:29 2017 Loïc Lopez
*/

#include "client.h"

bool	start_connection(t_irc_client *irc_client, char **parsed_command)
{
  char 	**address_info;
  int 	port_number;

  if (!(address_info = str_to_wordtab(parsed_command[1], ':')) ||
      !address_info[1])
    return (fprintf(stderr, "Invalid ip address or port.\n") ? false: true);
  port_number = atoi(address_info[1]);
  irc_client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (irc_client->sockfd < 0)
    error();
  if (!(irc_client->server = gethostbyname(address_info[0])))
    return (fprintf(stderr, "Invalid hostname\r\n") ? false: true);
  bzero((char *) &irc_client->serv_addr, sizeof(irc_client->serv_addr));
  irc_client->serv_addr.sin_family = AF_INET;
  bcopy(irc_client->server->h_addr, (char *)&irc_client->serv_addr.sin_addr
	.s_addr, irc_client->server->h_length);
  irc_client->serv_addr.sin_port = htons(port_number);
  if (connect(irc_client->sockfd, (struct sockaddr *)&irc_client->serv_addr,
	      sizeof(irc_client->serv_addr)) < 0)
    return (fprintf(stderr, "Could not connect to server.\n") ? false: true);
  fprintf(stdout, "Connected to server!\r\n");
  free_array(address_info);
  pthread_create(&irc_client->thread_socket_reader, NULL,
		 &thread_socket_reader, irc_client);
  return (false);
}

bool	parse_first_data_array(t_irc_client *irc_client,
			       char **parsed_command, char
			       *complete_cmd, e_client_cmd client_cmd)
{
  if (strcmp(parsed_command[0], "/server") == 0)
    return (start_connection(irc_client, parsed_command));
  else if (irc_client->sockfd != -1)
    {
      dprintf(irc_client->sockfd, "%s\n", complete_cmd);
      if (strcmp(parsed_command[0], "/quit") == 0)
	return (true);
      else if (client_cmd == FILE_SEND)
	{
	  send_file(irc_client, parsed_command);
	}
      else if (client_cmd == ACCEPT_FILE)
	{

	}
    }
  else
    fprintf(stderr,
	    "First you need to connect on a server : /server $host[:$port]\n");
  return (false);
}

e_client_cmd	is_a_valid_command(char **parsed_command)
{
  size_t 	i;
  const 		char	*available_commands[] =
    {
      "/server", "/nick", "/list", "/join", "/part", "/users",
      "/names", "/accept_file", "/user", "/quit"
    };

  if (parsed_command[0][0] != '/'
      || strcmp(parsed_command[0], "/msg") == 0)
    {
      return (parsed_command[0][0] != '/' ? OTHER :
	      strcmp(parsed_command[0], "/msg") == 0
	      && get_array_size(parsed_command) == 4 ? FILE_SEND : ACCEPT_FILE);
    }
  else
    {
      i = -1;
      while (++i < sizeof(available_commands)
	     / sizeof(available_commands[0]))
	{
	  if (strcmp(parsed_command[0], available_commands[i]) == 0)
	    return (OTHER);
	}
    }
  return (WRONG_COMMAND);
}

void	launch_client(t_irc_client *irc_client,
		      char *cmd, char **parsed_command)
{
  e_client_cmd		is_valid_command;

  while ((cmd = get_next_line(0)))
    {
      if ((parsed_command = str_to_wordtab(cmd, ' ')))
	{
	  is_valid_command = is_a_valid_command(parsed_command);
	  if (is_valid_command != WRONG_COMMAND)
	    {
	      if (parse_first_data_array(irc_client, parsed_command,
					 cmd, is_valid_command))
		break;
	    }
	  else
	    fprintf(stdout, "%s: Command not found.\r\n", parsed_command[0]);
	  free_array(parsed_command);
	  free(cmd);
	  parsed_command = NULL;
	  cmd = NULL;
	}
    }
  if (parsed_command)
    free_array(parsed_command);
  if (cmd)
    free(cmd);
}

int	main()
{
  t_irc_client  	irc_client;
  char 			**parsed_command;
  char 			*cmd;

  irc_client.sockfd = -1;
  parsed_command = NULL;
  cmd = NULL;
  launch_client(&irc_client, cmd, parsed_command);
  dprintf(irc_client.sockfd, "/quit");
  exit(0);
}
