/*
** main.c for PSU_2016_myirc in /home/dupil_l/PSU_2016_myirc/main.c
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Mon May 22 13:28:54 2017 Loïc Dupil
** Last update Mon May 22 13:28:54 2017 Loïc Dupil
*/

# include "server.h"

int main(int ac, char **av)
{
  if (ac == 2)
    server(atoi(av[1]));
  else
    printf("Usage: %s port", av[0]);
  return (0);
}
