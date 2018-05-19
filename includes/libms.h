/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:04:14 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 02:34:08 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H
# include "libft.h"
# include "libpf.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

extern char			**environ;

typedef struct		s_chars
{
	char			c;
	struct s_chars	*next;
}					t_chars;

int					echo(char *s);
int					cd(char *s, char **prev);
int					pwd(char *s);
int					setenv_c(char *s);
int					unsetenv_c(char *s);
void				ch_add(t_chars **cs, char c);
char				*ch_put(t_chars *cs);
void				ch_dst(t_chars **cs);
void				ch_get(char *s, char **s2, int n);
char				*ev_find(char *var);
void				dst_av(char **st);
int					ft_iswhitespace(char c);
int					ft_iswhitespacestr(char *s);
void				ev_make(void);
void				ev_modi(char *var, char *val);
void				ev_addn(char *var, char *val);
void				ev_remv(char *var);
void				ev_dst(void);

#endif
