/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:55:02 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 02:17:05 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int		echo(char *s)
{
	char *line;

	line = NULL;
	ch_get(s, &line, 4);
	ft_putendl(line);
	ft_strdel(&line);
	return (1);
}

int		cd(char *s, char **prev)
{
	char *line;
	char *home;
	char *aux;

	home = ev_find("HOME");
	line = NULL;
	ch_get(s, &line, 2);
	if (line[0] == '~')
	{
		aux = ft_strjoin(home, &line[1]);
		ft_strdel(&line);
		line = aux;
	}
	aux = *prev;
	*prev = getcwd(NULL, 0);
	if (line[0] == '-')
		chdir(aux);
	else if (line[0] == 0)
		chdir(home);
	else if (chdir(line) == -1)
		ft_printf("cd: could not find directory: <%s>\n", line);
	ft_strdel(&line);
	ft_strdel(&aux);
	ft_strdel(&home);
	return (1);
}

int		pwd(char *s)
{
	int		i;
	char	*line;

	i = 3;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			ft_putendl("pwd: too many arguments");
			return (1);
		}
		i++;
	}
	line = getcwd(NULL, 0);
	ft_putendl(line);
	ft_strdel(&line);
	return (1);
}

int		setenv_c(char *s)
{
	char	**va;

	va = ft_strsplit(s, ' ');
	if (!va[1] || !va[2] || va[3])
		ft_putendl("setenv: incorrect number of arguments");
	else
		ev_modi(va[1], va[2]);
	dst_av(va);
	free(va);
	return (1);
}

int		unsetenv_c(char *s)
{
	char	**va;
	int		i;

	i = 1;
	va = ft_strsplit(s, ' ');
	if (!va[1])
		ft_putendl("unsetenv: no arguments");
	else
		while (va[i])
		{
			ev_remv(va[i]);
			i++;
		}
	dst_av(va);
	free(va);
	return (1);
}
