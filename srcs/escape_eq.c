/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_eq.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:16:59 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		to_bslash(char *cmd, char **trim, int *i, t_all *all)
{
	if (all->parse->quo ||
	(all->parse->dquo && ft_strlchr("\\\"$", cmd[*i + 1]) < 0 && cmd[*i + 1]))
		add_chr(trim, '\\');
	if (ft_strlchr("\'\"$\\`();", cmd[*i + 1]) >= 0)
	{
		add_chr(trim, cmd[*i + 1]);
		(*i)++;
	}
	else if (!cmd[*i + 1])
		return (1);
	(*i)++;
	return (0);
}

int		to_equal(char *cmd, char **trim, int *i, t_all *all)
{
	if (all->parse->unassignable)
		all->assignable = 0;
	else
		all->assignable = 1;
	add_chr(trim, cmd[(*i)++]);
	return (0);
}
