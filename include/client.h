/*
** client.h for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/client.h
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 13:22:47 2017 Loïc Lopez
** Last update lun. mai 22 13:22:47 2017 Loïc Lopez
*/

#ifndef PSU_2016_MYIRC_CLIENT_H
#define PSU_2016_MYIRC_CLIENT_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <netdb.h>
# include <fcntl.h>
# include <pthread.h>
# include "myirc.h"

typedef enum 		e_client_cmd
{
  FILE_SEND,
  ACCEPT_FILE,
  OTHER,
  WRONG_COMMAND
}			e_client_cmd;

typedef	struct		s_irc_client
{
  int 			sockfd;
  struct sockaddr_in 	serv_addr;
  struct hostent 	*server;
  pthread_t		thread_socket_reader;
}			t_irc_client;

void	free_array(char **array);
int 	get_array_size(char **array);
bool	execute_send_file_client(char **parsed_command,
				     int fd, int sockfile_transfer);
bool	send_file(t_irc_client *irc_client, char **parsed_command);
void	*thread_socket_reader(void *data);

#endif /* PSU_2016_MYIRC_CLIENT_H */
