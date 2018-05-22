/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:50:20 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 13:03:53 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void		dst_av(char **st)
{
	int i;

	i = 0;
	while (st[i])
	{
		ft_strdel(&st[i]);
		i++;
	}
}

char		*ev_find(char *var)
{
	int i;
	int j;

	i = 0;
	while (g_environ[i] && ft_strncmp(g_environ[i], var, ft_strlen(var)))
		i++;
	if (!g_environ[i])
		return (ft_strdup(""));
	j = 0;
	while (g_environ[i][j] != '=')
		j++;
	return (ft_strdup(&g_environ[i][j + 1]));
}

static void	helper(char *aux, char **l, int *i, int j)
{
	char	*new_l;
	char	*aux2;
	int		k;

	aux2 = ev_find(aux);
	if (!aux)
		return ;
	k = ft_strlen(aux2);
	new_l = ft_strnew(ft_strlen(*l) - j + k);
	ft_strncpy(new_l, l[0], *i);
	ft_strncpy(&new_l[*i], aux2, k);
	ft_strncpy(&new_l[*i + k], &l[0][*i + j], ft_strlen(&l[0][j]));
	ft_strdel(l);
	*l = new_l;
	ft_strdel(&aux2);
	*i = -1;
}

void		check_env(char **l, int i, int j)
{
	char	*aux;

	while (l[0][i])
	{
		if (l[0][i] == '$' && ft_isalnum(l[0][i + 1]))
		{
			j = 1;
			while (ft_isalnum(l[0][i + j]))
				j++;
			aux = ft_strnew(j);
			ft_strncpy(aux, &l[0][i + 1], j - 1);
			helper(aux, l, &i, j);
			ft_strdel(&aux);
		}
		i++;
	}
}
