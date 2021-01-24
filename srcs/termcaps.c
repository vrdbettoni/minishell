/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:39:19 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:41:49 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_term(t_env *env, char **term_name)
{
	while (ft_strcmp("TERM", env->var))
		env = env->next;
	if (!env)
		*term_name = NULL;
	else
		*term_name = ft_strdup(env->value);
}

int		init_termcap(t_termcap *tc_cmd, t_all *all, int ret)
{
	char	*term_name;

	get_term(all->env_list, &term_name);
	if (term_name == NULL)
	{
		ft_printf("Specify a terminal type with 'TERM=<type>'.\n");
		return (0);
	}
	ret = tgetent(NULL, term_name);
	term_name = free_safe(term_name);
	if (ret == -1 || ret == 0)
	{
		ft_printf("Termcaps can't start, check env <TERM>.\n");
		return (0);
	}
	tc_cmd->cl = tgetstr("cl", NULL);
	tc_cmd->nd = tgetstr("nd", NULL);
	tc_cmd->le = tgetstr("le", NULL);
	tc_cmd->ed = tgetstr("ed", NULL);
	tc_cmd->dm = tgetstr("dm", NULL);
	tc_cmd->ei = tgetstr("ei", NULL);
	tc_cmd->im = tgetstr("im", NULL);
	tc_cmd->dc = tgetstr("dc", NULL);
	tc_cmd->reset = tgetstr("me", NULL);
	return (1);
}

int		delete(t_all *all, char **buffer, char **res, int len)
{
	char	*save;

	if (all->index == 0)
		return (0);
	ft_bzero(*buffer, 3);
	(*buffer)[0] = 127;
	tputs(all->term->le, 1, ft_putchar);
	tputs(all->term->dc, 1, ft_putchar);
	if (all->index > len)
		(*res)[ft_strlen(*res) - 1] = 0;
	else
	{
		save = ft_strdup(&((*res)[all->index]));
		(*res)[all->index - 1] = '\0';
		*res = ft_strjoin_mod(*res, save);
		free(save);
	}
	all->index--;
	return (0);
}

void	prompt(t_all *all, char **buffer, char **res, int len)
{
	if ((*buffer)[2] == 67 && all->index < len)
	{
		all->index++;
		tputs(all->term->nd, 1, ft_putchar);
	}
	if ((*buffer)[2] == 68 && all->index > 0 && len > 0)
	{
		all->index--;
		tputs(all->term->le, 1, ft_putchar);
	}
}

char	**set_line(t_all *all, char **res, char *buffer, int *ret)
{
	char	*save;

	if (buffer[0] == 10)
	{
		*ret = 0;
		return (res);
	}
	if (all->index >= ft_strlen(*res))
	{
		*res = ft_strjoin_mod(*res, buffer);
		return (res);
	}
	save = ft_strdup(&((*res)[all->index]));
	(*res)[all->index] = buffer[0];
	(*res)[all->index + 1] = '\0';
	*res = ft_strjoin_mod(*res, save);
	free(save);
	return (res);
}
