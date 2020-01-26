/*
** server.h for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/server.h
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 13:22:26 2017 Loïc Lopez
** Last update lun. mai 22 13:22:26 2017 Loïc Lopez
*/

#ifndef PSU_2016_MYIRC_SERVER_H
#define PSU_2016_MYIRC_SERVER_H

# include <stdio.h>
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
# include <dirent.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef enum 	e_command
  {
    NICK = 0,
    LIST = 1,
    JOIN = 2,
    PART = 3,
    USERS = 4,
    NAMES = 5,
    ACCEPT = 6,
    USER	= 7,
    QUIT = 8,
    MSG_SPECIFIC_USER = 9,
    MSG_TO_CHANNEL = 10,
    SEND_FILE = 11,
    STANDBY = 12,
  }		e_command;

typedef struct 		s_clients
{
  short 		id;
  e_command		cmd;
  short 		channels_id[10];
  short			current_channel;
  int 			sd;
  char 			pseudo[9];
  bool			acceptation;
}			t_clients;

typedef struct 		s_channel
{
  int	 		chan_id;
  t_clients		clients[50];
  int 			nbr_clients;
  char 			channel_name[200];
  char 			file[PATH_MAX];
}			t_channel;

typedef struct 		s_irc_server
{
  int 			serv_socket;
  int 			addrlen;
  int 			new_client;
  t_clients		clients[50];
  t_channel 		channels[10];
  int 			max_channel;
  int			max_clients;
  int 			nbr_clients;
  int 			activity;
  int 			max_sd;
  struct sockaddr_in	address;
  fd_set		readded;
  char 			*client_cmd;
  int 			opt;
}			t_irc_server;

void		init_channel(t_irc_server *);
void		launch_client_demand(t_irc_server *irc_server,
				     int current_client);
void    	server(int port);
void		execute_client_demand(t_irc_server *irc_server,
				      int current_client,
				      char **actions);
void 	execute_part(t_irc_server *irc_server, int current_client,
		     char **actions);
void	execute_msg_specific_user(t_irc_server *, int, char **);
void	execute_msg_to_channel(t_irc_server *, int, char **);
void	execute_send_file(t_irc_server *, int, char **);
void	execute_accept(t_irc_server *, int, char **);
void 	execute_nick(t_irc_server *irc_server, int current_client,
		     char **actions);
void 	execute_users(t_irc_server *irc_server, int current_client,
		      char **actions);
void 	execute_names(t_irc_server *irc_server, int current_client,
		      char **actions);
void 	execute_join(t_irc_server *, int, char **);
void	execute_list(t_irc_server *, int, char **);
void 	execute_user(t_irc_server *irc_server, int current_client,
		     char **actions);
char	*remove_backslash_r(char *str);
void	execute_quit(t_irc_server *irc_server, int current_client,
		     char **actions);
bool	current_client_in_channel_requested(t_irc_server
					    *irc_server,
					    int current_client);
bool	client_receiver_in_channel_requested(t_irc_server
					     *irc_server,
					     char *client_receiver);
int 	check_request_validity_and_create_subconnection(t_irc_server
							*irc_server,
							int current_client,
							char **actions);

#endif /* PSU_2016_MYIRC_SERVER_H */
