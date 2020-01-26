/*
** myirc.h for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/myirc.h
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  lun. mai 22 13:20:51 2017 Loïc Lopez
** Last update lun. mai 22 13:20:51 2017 Loïc Lopez
*/

#ifndef PSU_2016_MYIRC_MYIRC_H
#define PSU_2016_MYIRC_MYIRC_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

char	**str_to_wordtab(char *str, char c);
void	error();

#endif /* PSU_2016_MYIRC_MYIRC_H */
