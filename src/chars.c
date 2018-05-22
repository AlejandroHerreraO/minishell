/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:48:52 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 12:24:30 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ch_add(t_chars **cs, char c)
{
	t_chars	*tmp;

	if (!*cs)
	{
		*cs = (t_chars *)malloc(sizeof(t_chars));
		(*cs)->c = c;
		(*cs)->next = NULL;
		return ;
	}
	tmp = *cs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_chars *)malloc(sizeof(t_chars));
	tmp = tmp->next;
	tmp->c = c;
	tmp->next = NULL;
}

char	*ch_put(t_chars *cs)
{
	t_chars	*tmp;
	char	*s;
	int		i;

	i = 0;
	tmp = cs;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	s = (char *)malloc((i + 1) * sizeof(char));
	s[i] = '\0';
	tmp = cs;
	i = 0;
	while (tmp)
	{
		s[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	return (s);
}

void	ch_dst(t_chars **cs)
{
	if (!*cs)
		return ;
	if ((*cs)->next)
		ch_dst(&((*cs)->next));
	free(*cs);
	cs = NULL;
}

int		env_c(void)
{
	int i;

	i = 0;
	while (g_environ[i])
	{
		ft_putendl(g_environ[i]);
		i++;
	}
	return (1);
}
