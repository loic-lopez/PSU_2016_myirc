/*
** execut_send_file.c for PSU_2016_myirc in /home/dupil_l/PSU_2016_myirc/execut_send_file.c
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Fri May 26 16:16:35 2017 Loïc Dupil
** Last update Sat Jun 10 15:36:30 2017 Loïc Dupil
*/

# include "server.h"
# include "myirc.h"

void 	execute_accept(t_irc_server *irc_server, int current_client,
			   char **actions)
{
  struct stat 	st;
  int 		fp;
  char 		*buffer;

  stat(irc_server->channels[irc_server->clients[current_client]
	  .current_channel].file, &st);
  buffer = malloc(sizeof(char) * st.st_size);
  fp = open(irc_server->channels[irc_server->clients[current_client]
	  .current_channel].file, O_RDONLY);
  read(fp, buffer, st.st_size);
  dprintf(2, "%s\n", buffer);
  close(fp);
  (void)actions;
}

void	pray_for_norme(t_irc_server *irc_server, int current_client,
		       int peer_socket)
{
  int 		to_read;
  FILE 		*fp;
  char 		*readded;
  char 		number;
  size_t 	i;
  char 		file_lenght[4096];

  i = 0;
  while (recv(peer_socket, &number, 1, 0) > 0)
    if (number >= '0' && number <= '9')
      file_lenght[i++] = number;
    else
      break;
  file_lenght[i] = 0;
  if ((fp = fopen(irc_server->channels[irc_server->clients[current_client]
	  .current_channel].file, "w")) == NULL)
    return;
  to_read = atoi(file_lenght);
  readded = malloc(sizeof(char) * to_read + 1);
  recv(peer_socket, readded, to_read, 0);
  readded[to_read] = 0;
  fprintf(fp, "%s", readded);
  free(readded);
  fclose(fp);
  dprintf(irc_server->clients[current_client].sd, "Waiting for acceptation\n");
}

void 	execute_send_file(t_irc_server *irc_server, int current_client,
			  char **actions)
{
  size_t 	i;
  int		peer_socket;

  if ((peer_socket = check_request_validity_and_create_subconnection
	  (irc_server, current_client, actions)) == -1)
      return;
  i = strlen(actions[3]);
  while (actions[3][i] != '/' && i > 0)
    i--;
  strcpy(irc_server->channels[irc_server->clients[current_client]
			      .current_channel].file, "/tmp/");
  strcat(irc_server->channels[irc_server->clients[current_client]
			      .current_channel].file, &actions[3][i]);
  pray_for_norme(irc_server, current_client, peer_socket);
  close(peer_socket);
}
