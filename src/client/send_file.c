/*
** send_file.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/send_file.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. mai 26 16:42:37 2017 Loïc Lopez
** Last update ven. mai 26 16:42:37 2017 Loïc Lopez
*/

#include "client.h"

bool	execute_send_file_client(char **parsed_command,
				 int fd, int sockfile_transfer)
{
  struct stat	st;
  char 	*buffer;
  char 	*number;
  char  response[3];

  recv(sockfile_transfer, response, 3, 0);
  if (strcmp(response, "500") == 0)
    return (false);
  send(sockfile_transfer, "200", 3, 0);
  stat(parsed_command[3], &st);
  if ((buffer = malloc(sizeof(char) * st.st_size)) == NULL)
    return (false);
  if ((number = malloc(sizeof(char) * st.st_size)) == NULL)
    return (false);
  sprintf(number, "%lu", st.st_size);
  read(fd, buffer, st.st_size);
  strcat(number, "\n");
  send(sockfile_transfer, number, strlen(number), 0);
  send(sockfile_transfer, buffer, strlen(buffer), 0);
  free(buffer);
  close(fd);
  return (true);
}

bool	send_file(t_irc_client *irc_client, char **parsed_command)
{
  int 	fd;
  int 	sockfile_transfer;
  bool	status;

  if ((fd = open(parsed_command[3], O_RDONLY)) < 0)
    {
      send(irc_client->sockfd, "403", 3, 0);
      fprintf(stdout, "%s: File not found\n", parsed_command[3]);
      return (false);
    }
  else
    {
      send(irc_client->sockfd, "200", 3, 0);
      sockfile_transfer = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfile_transfer < 0)
	error();
      if (connect(sockfile_transfer,
		  (struct sockaddr *)&irc_client->serv_addr,
		  sizeof(irc_client->serv_addr)) < 0)
	return (false);
      status = execute_send_file_client(parsed_command, fd, sockfile_transfer);
      return (status);
    }
}
