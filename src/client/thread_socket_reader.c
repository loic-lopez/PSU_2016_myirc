/*
** thread_socket_reader.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/thread_socket_reader.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  sam. juin 10 15:10:20 2017 Loïc Lopez
** Last update sam. juin 10 15:10:20 2017 Loïc Lopez
*/

#include "client.h"

void	*thread_socket_reader(void *data)
{
  t_irc_client		*irc_client;
  char			line[1024];
  ssize_t		num;

  irc_client = (t_irc_client *)data;
  while (1)
    {
      num = recv(irc_client->sockfd, line, sizeof(line), 0);
      if (num <= 0)
	{
	  fprintf(stderr, "Connection Error\n");
	  break;
	}
      line[num] = '\0';
      write(1, line, strlen(line));
    }
  return (NULL);
}
