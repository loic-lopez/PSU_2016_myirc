/*
** utils.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/utils.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. mai 26 16:53:25 2017 Loïc Lopez
** Last update ven. mai 26 16:53:25 2017 Loïc Lopez
*/

#include "client.h"

int 	get_array_size(char **array)
{
  int	i;

  i = 0;
  while (array[i])
    i++;
  return (i);
}
