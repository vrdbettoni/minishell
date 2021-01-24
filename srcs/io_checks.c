/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   io_checks.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 20:56:09 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:57:44 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_prd_syntax(t_all *all)
{
	t_list	*lst;
	t_list	*prev;

	lst = all->args;
	prev = NULL;
	while (lst && ft_strcmp(lst->content, "&&")
	&& ft_strcmp(lst->content, "||"))
	{
		if (which_prd(lst) == 3 && (lst == all->args
		|| (lst->next && which_prd(lst->next) == 3)))
			return (print_n_set_error(all, lst->content, "syntax error", 1));
		if (prev && which_prd(prev) && !ft_strcmp(prev->content, lst->content))
			return (print_n_set_error(all, prev->content, "syntax error", 1));
		else if (which_prd(lst) && which_prd(lst) != 3 && !lst->next)
			return (print_n_set_error(all, lst->content, "syntax error", 1));
		prev = lst;
		lst = lst->next;
	}
	return (0);
}

int		parse_pipe(t_all *all)
{
	t_list	*lst;
	int		i;

	i = 0;
	all->args_pipe = NULL;
	lst = all->args;
	while (lst && ft_strcmp(lst->content, "&&")
	&& ft_strcmp(lst->content, "||"))
	{
		if (which_prd(lst) == 3 && lst->next && lst->prd)
		{
			all->args_pipe = lst;
			break ;
		}
		else if (which_prd(lst) == 3 && !lst->next && lst->prd)
		{
			if (complete_read(lst, all))
				return (1);
			break ;
		}
		lst = lst->next;
		i++;
	}
	return (0);
}

int		parse_rd(t_all *all)
{
	t_list	*lst;
	t_list	*last;

	all->args_rd = NULL;
	lst = all->args;
	while (lst && ft_strcmp(lst->content, "&&")
	&& ft_strcmp(lst->content, "||") && ft_strcmp(lst->content, "|"))
	{
		if (is_redirect(lst) && lst->next && !all->args_rd && lst->prd)
			all->args_rd = lst;
		else if (is_redirect(lst) && !lst->next && lst->prd)
		{
			while ((last = ft_lstlast(all->args)) && is_redirect(last)
			&& !last->next)
				if (read_prd(all))
					return (1);
			!all->args_rd ? all->args_rd = lst : 0;
			if (check_prd_syntax(all))
				return (1);
			break ;
		}
		lst = lst->next;
	}
	return (0);
}

int		redirect_io(t_all *all, t_list *prd)
{
	if (which_prd(prd) == 4)
		redir_stdout(all, ">>");
	else if (which_prd(prd) == 5)
		redir_heredoc(all);
	else if (which_prd(prd) == 2)
		redir_stdin(all);
	else if (which_prd(prd) == 1)
		redir_stdout(all, ">");
	else if (which_prd(prd) == 3)
		pipe_stdout(all);
	return (0);
}

int		check_logic(t_all *all)
{
	t_list	*lst;

	lst = all->args;
	while (lst && !((!ft_strcmp("||", lst->content)
	|| !ft_strcmp("&&", lst->content)) && lst->prd))
		lst = lst->next;
	if (!lst)
		return (0);
	else if (lst && (!ft_strcmp("&&", lst->content)
	|| !ft_strcmp("||", lst->content))
	&& lst->prd && !lst->next)
	{
		read_prd(all);
		return (0);
	}
	return (0);
}
