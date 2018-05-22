/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:54:27 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 12:36:07 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void		ev_make(int ac, char **av, char **env)
{
	int		i;
	char	**new_en;

	(void)ac;
	(void)av;
	i = 0;
	while (env[i])
		i++;
	new_en = (char **)malloc((i + 1) * sizeof(char *));
	new_en[i] = NULL;
	i = 0;
	while (env[i])
	{
		new_en[i] = ft_strdup(env[i]);
		i++;
	}
	g_environ = new_en;
}

void		ev_modi(char *var, char *val)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_environ[i])
	{
		if (!ft_strncmp(g_environ[i], var, ft_strlen(var)))
			break ;
		i++;
	}
	if (!g_environ[i])
		ev_addn(var, val);
	else
	{
		tmp = ft_strjoin(var, "=");
		ft_strcomb(&tmp, val, 0, ft_strlen(val));
		ft_strdel(&g_environ[i]);
		g_environ[i] = tmp;
	}
}

void		ev_addn(char *var, char *val)
{
	int		i;
	char	**new_en;
	char	*tmp;

	i = 0;
	while (g_environ[i])
		i++;
	new_en = (char **)malloc((i + 2) * sizeof(char *));
	new_en[i + 1] = NULL;
	i = 0;
	while (g_environ[i])
	{
		new_en[i] = ft_strdup(g_environ[i]);
		i++;
	}
	tmp = ft_strjoin(var, "=");
	ft_strcomb(&tmp, val, 0, ft_strlen(val));
	new_en[i] = tmp;
	dst_av(g_environ);
	free(g_environ);
	g_environ = new_en;
}

void		ev_remv(char *var)
{
	int		i;

	i = 0;
	while (g_environ[i])
	{
		if (!ft_strncmp(g_environ[i], var, ft_strlen(var)))
		{
			ft_strdel(&g_environ[i]);
			while (g_environ[i + 1])
			{
				g_environ[i] = g_environ[i + 1];
				i++;
			}
			g_environ[i] = NULL;
			return ;
		}
		i++;
	}
}

void		ev_dest(void)
{
	int i;

	i = 0;
	while (g_environ[i])
	{
		ft_strdel(&g_environ[i]);
		i++;
	}
	free(g_environ);
}
