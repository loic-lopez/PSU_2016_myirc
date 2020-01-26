/*
** error.c for PSU_2016_myirc in /home/dupil_l/PSU_2016_myirc/error.c
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Mon May 22 15:01:59 2017 Loïc Dupil
** Last update Mon May 22 15:01:59 2017 Loïc Dupil
*/

#include "myirc.h"

void 	error()
{
  fprintf(stderr, "%s\n", strerror(errno));
  exit(EXIT_FAILURE);
}
