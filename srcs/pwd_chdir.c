/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pwd_chdir.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 19:29:02 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 19:47:46 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	next_args(t_list **args)
{
	*args = (*args)->next;
}

int		skip_args(t_list *args)
{
	if (!args)
		return (1);
	if (!ft_strcmp(args->content, ">") && args->prd)
		return (2);
	if ((!ft_strcmp(args->content, "<")
	|| !ft_strcmp(args->content, ">>")) && args->prd)
		return (2);
	if (!ft_strcmp(args->content, "|") && args->prd)
		return (3);
	if ((!ft_strcmp(args->content, "&&")
	|| !ft_strcmp(args->content, "||")) && args->prd)
		return (4);
	return (0);
}

int		ft_pwd(t_all *all)
{
	char	buffer[512];
	int		ret;

	ret = 0;
	getcwd(buffer, 512);
	while ((ret = skip_args(all->args)) == 0)
		next_args(&(all->args));
	ft_printf("%s\n", buffer);
	return (1);
}

int		ft_chdir(t_all *all)
{
	char		path[100];
	int			i;
	char		*home;

	next_args(&(all->args));
	if (skip_args(all->args))
	{
		home = expand_env_var("$HOME", all);
		if ((chdir(home) == -1))
			ft_printf("%s\n", strerror(errno));
		home = free_safe(home);
	}
	else if ((chdir(all->args->content) == -1))
	{
		ft_printf("minishell: %s\n", strerror(errno));
		all->status = 1;
		return (1);
	}
	if (all->args)
		next_args(&(all->args));
	all->status = 0;
	return (1);
}

void	format_echo_output(t_all *all, char **buffer, int *boolean)
{
	*buffer = malloc(sizeof(1));
	(*buffer)[0] = '\0';
	while (!(skip_args(all->args)))
	{
		*buffer = ft_strjoin_mod(*buffer, all->args->content);
		*buffer = ft_strjoin_mod(*buffer, " ");
		next_args(&(all->args));
	}
	if (**buffer)
		(*buffer)[ft_strlen(*buffer) - 1] = '\0';
	else
		(*buffer)[0] = '\0';
	*boolean == 1 ? *buffer = ft_strjoin_mod(*buffer, "\n") : 0;
}
