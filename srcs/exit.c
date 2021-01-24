/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exit.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:20:46 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:38:48 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_list(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}

void	free_path_auto(char **path)
{
	int		i;

	i = -1;
	while (path[++i])
		free(path[i]);
}

void	free_env_lst(t_all *all)
{
	t_env	*lst;
	t_env	*tmp;

	lst = all->env_list;
	while (lst)
	{
		tmp = lst->next;
		lst->var = free_safe(lst->var);
		lst->value = free_safe(lst->value);
		lst = free_safe(lst);
		lst = tmp;
	}
	all->env_list = NULL;
}

void	ft_exit(t_all *all)
{
	if (!all->depth)
	{
		free_cmd_args(all);
		*(all->full_command) = free_safe(*(all->full_command));
		all->args_array = NULL;
		all->args_beg = NULL;
		all->args_rd = NULL;
		all->args_pipe = NULL;
		all->args = NULL;
		free_path_auto(all->path_auto);
		all->path_auto = free_safe(all->path_auto);
		tputs(all->term->ed, 1, ft_putchar);
		tputs(all->term->ei, 1, ft_putchar);
		tputs(all->term->reset, 1, ft_putchar);
		free_env_lst(all);
		save_history(all->history);
		ft_clear_history(all->history, &free);
		free(all->history);
		tcsetattr(0, TCSANOW, all->old_term);
		free(all);
		all = NULL;
	}
	exit(0);
}
