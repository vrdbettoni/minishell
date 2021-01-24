/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ops.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 18:27:53 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 17:46:17 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../mylib/libft.h"

int		run_subshell(t_list *args, t_all *all)
{
	int	fk;

	if ((fk = fork()) == -1)
		print_n_set_error(all, 0, "fork error", 1);
	else if (!fk)
	{
		all->depth++;
		parse_args_to_lists(args->content, all, 0, 0);
		if (all->status > 255)
			all->status /= 256;
		exit(all->status);
	}
	else
	{
		wait(&(all->status));
		all->depth--;
	}
	if (all->status > 255)
		all->status /= 256;
	return (1);
}

int		eval_logic(t_list *lst, int val, t_all *all)
{
	if (lst && !ft_strcmp("&&", lst->content))
	{
		if (!val)
			return (parse_logic(lst->next, all));
		else
			return (val);
	}
	else if (lst && !ft_strcmp("||", lst->content))
	{
		if (!val)
			return (val);
		else
			return (parse_logic(lst->next, all));
	}
	else
		return (val);
}

int		parse_logic(t_list *args, t_all *all)
{
	t_list	*lst;
	t_list	*prev;
	int		val;

	all->args = args;
	check_logic(all);
	setup_pipes_rd(all);
	val = all->status;
	lst = args;
	while (lst && !((!ft_strcmp("||", lst->content)
	|| !ft_strcmp("&&", lst->content)) && lst->prd))
		lst = lst->next;
	return (eval_logic(lst, val, all));
}

void	match_parenthesis(char *str, int *i)
{
	int	match;

	match = 1;
	while (str[*i] && match)
	{
		if (str[*i] == '(')
			match++;
		else if (str[*i] == ')')
			match--;
		(*i)++;
	}
}
