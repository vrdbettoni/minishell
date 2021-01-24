/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:19:25 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 19:03:18 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		arg_list2array(t_all *all)
{
	int		i;
	int		lstlen;
	t_list	*lst;

	lstlen = len_to_pipe(all->args);
	all->args_array = (char**)malloc((lstlen + 1) * sizeof(char*));
	if (!all->args_array)
		exit_err();
	lst = all->args;
	i = -1;
	while (++i < lstlen)
	{
		all->args_array[i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	all->args_array[i] = NULL;
	return (0);
}

char	*ft_find_path_next(char **argv, t_env *env_list, int fd)
{
	char	*s;
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	if (!(s = malloc(1)))
		return (NULL);
	path = ft_split(env_list->value, ':');
	while (path[i] && fd < 0)
	{
		tmp = s;
		s = ft_strjoin(path[i], *argv);
		tmp = free_safe(tmp);
		fd = open(s, O_RDONLY);
		i++;
	}
	tmp = free_safe(tmp);
	i = -1;
	while (path[++i])
		free(path[i]);
	path = free_safe(path);
	*argv = free_safe(*argv);
	fd < 0 ? s = free_safe(s) : 0;
	return (s);
}

char	*ft_find_path(char *argv, t_env *env_list)
{
	int		fd;

	fd = -1;
	if (!ft_strncmp("./", argv, 2) || !ft_strncmp("../", argv, 3))
		return (ft_strdup(argv));
	while (env_list && ft_strcmp(env_list->var, "PATH"))
		env_list = env_list->next;
	if (!(env_list))
		return (NULL);
	argv = ft_strjoin("/", argv);
	return (ft_find_path_next(&argv, env_list, fd));
}

int		exec_cmd(t_all *all, char *path)
{
	pid_t	p;

	p = fork();
	tcsetattr(0, TCSANOW, all->old_term);
	if (p == 0)
		if (execve(path, all->args_array, all->env_array) == -1)
		{
			tcsetattr(0, TCSANOW, all->new_termios);
			return (0);
		}
	wait(&(all->status));
	tcsetattr(0, TCSANOW, all->new_termios);
	return (1);
}

int		ft_exec(t_all *all)
{
	char	*path;
	int		i;
	t_stat	info;
	pid_t	p;

	path = ft_find_path(all->args->content, all->env_list);
	if (!path || (!ft_strncmp(".", path, 1) && (stat(path, &info))))
		return (0);
	arg_list2array(all);
	env_list2array(all);
	exec_cmd(all, path);
	i = -1;
	while (all->args_array[++i])
		all->args_array[i] = free_safe(all->args_array[i]);
	all->args_array = free_safe(all->args_array);
	i = -1;
	while (all->env_array[++i])
		all->env_array[i] = free_safe(all->env_array[i]);
	all->env_array = free_safe(all->env_array);
	free(path);
	return (1);
}
