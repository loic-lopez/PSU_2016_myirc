/*
** str_to_wordtab.c for PSU_2016_myftp in /home/lopez_i/PSU_2016_myftp/str_to_wordtab.c
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  dim. mai 14 17:52:58 2017 Loïc Lopez
** Last update dim. mai 14 17:52:58 2017 Loïc Lopez
*/

#include "myirc.h"

int	countword(const char *str, char c)
{
  int	i;
  int	n;

  i = 0;
  n = 0;
  while (str[i])
    {
      while (str[i] == c)
	i++;
      if (str[i])
	n++;
      while (str[i] != c && str[i] != 0)
	i++;
    }
  return (n);
}

int	current(const char *str, char c)
{
  int	i;

  i = 0;
  while (str[i] != c && str[i] != '\0')
    i++;
  return (i);
}

char	**str_to_wordtab(char *str, char c)
{
  int	i;
  int	l;
  int	t;
  char	**tab;

  i = 0;
  l = 0;
  if (str == NULL || countword(str, c) == 0)
    return (NULL);
  if ((tab = malloc((countword(str, c) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  while (str[i] != 0)
    {
      if ((tab[l] = malloc((current(&str[i], c) + 1) * sizeof(char))) == NULL)
	return (NULL);
      t = 0;
      while (str[i] != c && str[i] != '\0')
	tab[l][t++] = str[i++];
      tab[l++][t] = '\0';
      while (str[i] == c )
	i++;
    }
  tab[l] = NULL;
  return (tab);
}
