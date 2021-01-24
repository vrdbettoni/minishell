/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_cmd.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 20:45:43 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:39:08 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		print_n_set_error(t_all *all, char *token, char *str, int errcode)
{
	all->status = errcode;
	ft_putstr_fd("minishell: ", 2);
	if (token)
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int		is_builtin(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "env") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

int		is_valid_assignment(t_list *args)
{
	int		i;
	char	*str;

	if (ft_strlchr(args->content, '=') <= 0)
		return (0);
	if (!args->assignable || ft_isdigit(((char*)args->content)[0]))
		return (0);
	i = 0;
	str = args->content;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	find_builtin(int *ret, t_all *all)
{
	char	*tmp;

	tmp = all->args->content;
	!(*ret) && !ft_strcmp(tmp, "pwd") ? (*ret = ft_pwd(all)) : 0;
	!(*ret) && !ft_strcmp(tmp, "cd") ? (*ret = ft_chdir(all)) : 0;
	!(*ret) && !ft_strcmp(tmp, "echo") ? (*ret = ft_echo(all)) : 0;
	!(*ret) && !ft_strcmp(tmp, "env") ? (*ret = ft_env(all)) : 0;
	!(*ret) && !ft_strcmp(tmp, "export") ? (*ret = ft_export(all)) : 0;
	!(*ret) && !ft_strcmp(tmp, "unset") ? (*ret = ft_unset(all)) : 0;
	all->status = !(*ret);
}

int		find_command(t_all *all)
{
	int		fk;
	int		ret;

	ret = 0;
	if (!all->args)
		return (0);
	check_cmd(all->args);
	wildcards(&(all->args));
	is_valid_assignment(all->args) ? (ret = ft_setenv(all)) : 0;
	if (all->args && all->args->subsh && !ret)
	{
		ret = run_subshell(all->args, all);
		return (all->status);
	}
	if (all->args && is_builtin(all->args->content))
		find_builtin(&ret, all);
	else if (all->args)
	{
		!ft_strcmp(all->args->content, "exit") ? ft_exit(all) : 0;
		!ret ? (ret = ft_exec(all)) : 0;
		!ret ? print_n_set_error(all, all->args->content,
		"unknown command", 127) : 0;
	}
	return (all->status);
}
