/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:49:09 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/22 12:44:46 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static void	create_fork(char *path, char **av)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execve(path, av, g_environ);
	else
		wait(&status);
}

static int	try_path(char *path, char **av)
{
	char	**paths;
	int		i;
	int		n;

	n = 0;
	i = 0;
	paths = ft_strsplit(path, ':');
	while (paths[i])
	{
		ft_strcomb(&paths[i], "/", 0, 1);
		ft_strcomb(&paths[i], av[0], 0, ft_strlen(av[0]));
		if (open(paths[i], O_RDONLY) != -1)
		{
			create_fork(paths[i], av);
			n = 1;
			break ;
		}
		i++;
	}
	dst_av(paths);
	free(paths);
	return (n);
}

static int	exec(char *line)
{
	char	**av;
	char	*path;
	int		fd;

	path = ev_find("PATH");
	av = ft_strsplit(line, ' ');
	fd = open(av[0], O_RDONLY);
	if (fd == -1)
	{
		fd = try_path(path, av);
		dst_av(av);
		free(av);
		ft_strdel(&path);
		return (fd);
	}
	else
	{
		create_fork(av[0], av);
		dst_av(av);
		free(av);
		close(fd);
		ft_strdel(&path);
		return (1);
	}
	return (0);
}

static int	command(char *line, char **prev)
{
	if (ft_iswhitespacestr(line))
		return (1);
	if (!ft_strncmp(line, "echo", 4) && (line[4] == ' ' || line[4] == 0))
		return (echo(line));
	if (!ft_strncmp(line, "cd", 2) && (line[2] == ' ' || line[2] == 0))
		return (cd(line, prev));
	if (!ft_strncmp(line, "pwd", 3) && (line[3] == ' ' || line[3] == 0))
		return (pwd(line));
	if (!ft_strncmp(line, "setenv", 6) && (line[6] == ' ' || line[6] == 0))
		return (setenv_c(line));
	if (!ft_strncmp(line, "unsetenv", 8) && (line[8] == ' ' || line[8] == 0))
		return (unsetenv_c(line));
	if (!ft_strncmp(line, "env", 3) && (line[3] == ' ' || line[3] == 0))
		return (env_c());
	return (0);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	char	*prev;

	ev_make(ac, av, env);
	line = NULL;
	prev = getcwd(NULL, 0);
	while (1)
	{
		ft_putstr("miniS:$>");
		if (!get_next_line2(0, &line))
			break ;
		if (!ft_strncmp(line, "exit", 4) && (line[4] == ' ' || line[4] == 0))
			break ;
		if (!command(line, &prev) && !exec(line))
			ft_printf("miniS: command not found: %s\n", line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_strdel(&prev);
	return (0);
}
