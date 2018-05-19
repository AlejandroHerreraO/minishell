/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:54:27 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 02:16:43 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void		ev_make(void)
{
	int		i;
	char	**new_en;

	i = 0;
	while (environ[i])
		i++;
	new_en = (char **)malloc((i + 1) * sizeof(char *));
	new_en[i] = NULL;
	i = 0;
	while (environ[i])
	{
		new_en[i] = ft_strdup(environ[i]);
		i++;
	}
	environ = new_en;
}

void		ev_modi(char *var, char *val)
{
	int		i;
	char	*tmp;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var, ft_strlen(var)))
			break ;
		i++;
	}
	if (!environ[i])
		ev_addn(var, val);
	else
	{
		tmp = ft_strjoin(var, "=");
		ft_strcomb(&tmp, val, 0, ft_strlen(val));
		ft_strdel(&environ[i]);
		environ[i] = tmp;
	}
}

void		ev_addn(char *var, char *val)
{
	int		i;
	char	**new_en;
	char	*tmp;

	i = 0;
	while (environ[i])
		i++;
	new_en = (char **)malloc((i + 2) * sizeof(char *));
	new_en[i + 1] = NULL;
	i = 0;
	while (environ[i])
	{
		new_en[i] = ft_strdup(environ[i]);
		i++;
	}
	tmp = ft_strjoin(var, "=");
	ft_strcomb(&tmp, val, 0, ft_strlen(val));
	new_en[i] = tmp;
	dst_av(environ);
	free(environ);
	environ = new_en;
}

void		ev_remv(char *var)
{
	int		i;
	char	*aux;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var, ft_strlen(var)))
		{
			aux = environ[i];
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			ft_strdel(&aux);
			return ;
		}
		i++;
	}
}

void		ev_dest(void)
{
	int i;

	i = 0;
	while (environ[i])
	{
		ft_strdel(&environ[i]);
		i++;
	}
	free(environ);
}
