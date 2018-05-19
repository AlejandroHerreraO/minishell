/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 01:50:20 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 02:34:11 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int			ft_iswhitespace(char c)
{
	if ((c < 9 || c > 13) && c != 32)
		return (0);
	return (1);
}

int			ft_iswhitespacestr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

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
	while (environ[i] && ft_strncmp(environ[i], var, ft_strlen(var)))
		i++;
	if (!environ[i])
		return (ft_strdup(""));
	j = 0;
	while (environ[i][j] != '=')
		j++;
	return (ft_strdup(&environ[i][j + 1]));
}
