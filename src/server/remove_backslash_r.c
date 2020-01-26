/*
** remove_backslash_r.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/remove_backslash_r.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 24 15:37:54 2017 Loïc Lopez
** Last update mer. mai 24 15:37:54 2017 Loïc Lopez
*/

#include "server.h"

char	*remove_backslash_r(char *str)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == '\r')
      str[i] = ' ';
  return (str);
}
