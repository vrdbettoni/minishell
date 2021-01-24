/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_term.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:36:26 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:37:35 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prepare_history(t_all *all, char **res)
{
	int		len;

	len = ft_strlen(*res);
	while (all->index < len)
	{
		tputs(all->term->nd, 1, ft_putchar);
		all->index++;
	}
}

void	previous_word(t_all *all, char **res, int len)
{
	int		tmp;

	tmp = all->index;
	if (!is_whitespaces((*res)[all->index]))
		while (len && all->index && !is_whitespaces((*res)[all->index]))
			all->index--;
	while (len && all->index && is_whitespaces((*res)[all->index]))
		all->index--;
	while (len && all->index && !is_whitespaces((*res)[all->index]))
		all->index--;
	all->index != 0 ? all->index++ : 0;
	tmp -= all->index;
	while (tmp)
	{
		tputs(all->term->le, 1, ft_putchar);
		tmp--;
	}
}

void	next_word(t_all *all, char **res, int len)
{
	int		tmp;

	tmp = all->index;
	while (len && all->index < len && !is_whitespaces((*res)[all->index]))
		all->index++;
	while (len && all->index < len && is_whitespaces((*res)[all->index]))
		all->index++;
	tmp = all->index - tmp;
	while (tmp)
	{
		tputs(all->term->nd, 1, ft_putchar);
		tmp--;
	}
}

void	s_e_line(t_all *all, int s_e, int len)
{
	while (s_e == 0 && all->index)
	{
		tputs(all->term->le, 1, ft_putchar);
		all->index--;
	}
	while (s_e != 0 && all->index < len)
	{
		tputs(all->term->nd, 1, ft_putchar);
		all->index++;
	}
}
