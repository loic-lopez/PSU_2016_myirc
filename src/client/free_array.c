/*
** free_array.c for PSU_2016_myirc in /home/lopez_i/PSU_2016_myirc/free_array.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. mai 26 16:03:24 2017 Loïc Lopez
** Last update ven. mai 26 16:03:24 2017 Loïc Lopez
*/

#include "client.h"

void	free_array(char **array)
{
  int	i;

  i = 0;
  while (array[i])
    free(array[i++]);
  free(array);
}
