/*
** get_next_line.h for get_next_line.c in /home/dupil_l/Module_UNIXRéseau/PSU_2016_myftp/sources
** 
** Made by Loïc Dupil
** Login   <dupil_l@epitech.net>
** 
** Started on  Wed May 17 16:43:44 2017 Loïc Dupil
** Last update Wed May 17 16:43:46 2017 Loïc Dupil
*/

#ifndef		GET_NEXT_LINE_H_
# define	GET_NEXT_LINE_H_

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "server.h"

# ifndef READ_SIZE
#  define READ_SIZE (8)
# endif /* !READ_SIZE */

# ifndef BUF
#  define BUF (READ_SIZE + 1)
# endif /* !BUF */

char   	*get_next_line(const int fd);

#endif		/* !GET_NEXT_LINE_H_ */
