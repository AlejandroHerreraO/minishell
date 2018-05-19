/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:48:32 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 02:27:32 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static int	check(char c)
{
	if (c == '"' || c == 39 || ft_iswhitespace(c) || c == 0)
		return (0);
	return (1);
}

static void	s_quote(char **line, int *i, t_chars **c)
{
	(*i)++;
	while ((*line)[*i] != 39)
	{
		if (!(*line)[*i])
		{
			ft_strdel(line);
			ft_printf("quote>");
			ch_add(c, '\n');
			get_next_line2(0, line);
			*i = 0;
		}
		if ((*line)[*i] != 39)
			ch_add(c, (*line)[*i]);
		if ((*line)[*i] != 39)
			(*i)++;
	}
	(*i)++;
}

static void	d_quote(char **line, int *i, t_chars **c)
{
	(*i)++;
	while ((*line)[*i] != '"')
	{
		if (!(*line)[*i])
		{
			ft_strdel(line);
			ft_printf("dquote>");
			ch_add(c, '\n');
			get_next_line2(0, line);
			*i = 0;
		}
		if ((*line)[*i] != '"')
			ch_add(c, (*line)[*i]);
		if ((*line)[*i] != '"')
			(*i)++;
	}
	(*i)++;
}

void		ch_get(char *s, char **s2, int n)
{
	char	*line;
	int		i;
	t_chars	*cs;

	i = n;
	cs = NULL;
	line = ft_strdup(s);
	while (ft_iswhitespace(line[i]) && line[i])
		i++;
	while (line[i])
	{
		while (ft_iswhitespace(line[i]) && line[i])
		{
			if (line[i + 1] != ' ')
				ch_add(&cs, ' ');
			i++;
		}
		line[i] == '"' ? d_quote(&line, &i, &cs) : 1;
		line[i] == 39 ? s_quote(&line, &i, &cs) : 1;
		check(line[i]) ? ch_add(&cs, line[i]) : 1;
		check(line[i]) ? i++ : 1;
	}
	*s2 = ch_put(cs);
	ft_strdel(&line);
	ch_dst(&cs);
}
