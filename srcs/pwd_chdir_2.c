/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pwd_chdir_2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 19:16:22 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 19:47:57 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_echo(t_all *all)
{
	int		boolean;
	char	*buffer;

	boolean = 1;
	next_args(&(all->args));
	if (all->args && !ft_strcmp(all->args->content, "-n"))
	{
		boolean = 0;
		next_args(&(all->args));
	}
	format_echo_output(all, &buffer, &boolean);
	ft_printf("%s", buffer);
	buffer = free_safe(buffer);
	all->status = 0;
	return (1);
}

int		ft_env(t_all *all)
{
	print_env(all->env_list);
	while (!skip_args(all->args))
	{
		if (ft_strlchr(all->args->content, '=') > 0)
			ft_printf("%s\n", all->args->content);
		next_args(&(all->args));
	}
	all->status = 0;
	return (1);
}

int		ft_export(t_all *all)
{
	next_args(&(all->args));
	if (skip_args(all->args))
		export_no_arg(all);
	else
	{
		while (!skip_args(all->args))
		{
			export_env(&(all->env_list), all->args->content);
			next_args(&(all->args));
		}
	}
	all->status = 0;
	return (1);
}

int		ft_unset(t_all *all)
{
	next_args(&(all->args));
	while (!skip_args(all->args))
	{
		unset_env(&(all->env_list), all->args->content);
		next_args(&(all->args));
	}
	all->status = 0;
	return (1);
}
