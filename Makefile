##
## Makefile for makefile in /home/lopez_i/PSU_2016_myirc
##
## Made by Loic Lopez
## Login   <loic.lopez@epitech.eu>
##
## Started on  Mon Mar  6 10:06:57 2017 Loic Lopez
## Last update Tue May 23 15:56:24 2017 Loïc Dupil
##

CC	=	gcc -g

RM	=	rm -rf

SERVER_NAME	=	server

CLIENT_NAME	=	client

ECHO	=	/bin/echo -e

DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[5;31m"

CFLAGS	+=	-Wall -Werror -Wextra
CFLAGS	+=	-I./include/

SRC_SERVER	=	src/server/main.c			\
			src/server/launch_client_demand.c	\
			src/server/execute_client_demand.c	\
			src/server/execute_channel_act.c	\
			src/server/execute_nick.c		\
			src/server/execute_quit.c		\
			src/server/execute_list_users.c		\
			src/server/remove_backslash_r.c		\
			src/server/server.c			\
			src/server/execute_messages.c		\
			src/commun/get_next_line.c		\
			src/commun/str_to_wordtab.c		\
			src/server/execute_send_file.c		\
			src/server/check_execute_send_file.c		\


SRC_CLIENT	=	src/client/main.c			\
			src/client/free_array.c			\
			src/client/thread_socket_reader.c	\
			src/client/utils.c			\
			src/client/send_file.c			\
			src/commun/get_next_line.c		\
                     	src/commun/str_to_wordtab.c		\
                     	src/commun/error.c			\

OBJS_SERVER	=	$(SRC_SERVER:.c=.o)
OBJS_CLIENT	=	$(SRC_CLIENT:.c=.o)

all	:	$(SERVER_NAME)	$(CLIENT_NAME)

$(SERVER_NAME)	:	$(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) $(CFLAGS) -o $(SERVER_NAME) && \
	$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(SERVER_NAME) $(DEFAULT)  || \
	$(ECHO) $(RED) "[ERROR]" $(TEAL) $(SERVER_NAME) $(DEFAULT)

$(CLIENT_NAME)	:	$(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) $(CFLAGS) -pthread -o $(CLIENT_NAME) && \
	$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(CLIENT_NAME) $(DEFAULT)  || \
	$(ECHO) $(RED) "[ERROR]" $(TEAL) $(CLIENT_NAME) $(DEFAULT)

clean	:
	@rm -f $(OBJS_CLIENT) $(OBJS_SERVER) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJS_CLIENT) $(OBJS_SERVER) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJS_CLIENT) $(OBJS_SERVER) $(DEFAULT)

fclean	:	clean
	@rm -f $(SERVER_NAME) $(CLIENT_NAME) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(SERVER_NAME) $(CLIENT_NAME) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(SERVER_NAME) $(CLIENT_NAME) $(DEFAULT)

re	:	fclean all

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $< && \
	$(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)

.PHONY	:	all clean fclean re
