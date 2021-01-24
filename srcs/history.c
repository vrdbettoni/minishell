/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:22:30 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:23:49 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_hist	*ft_new_hist(void *content)
{
	t_hist	*list;
	int		i;
	char	*line;

	i = -1;
	line = content;
	if (ft_strlen(line) == 0)
		return (NULL);
	while (line[++i])
		if (!ft_isprint(line[i]))
			return (NULL);
	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->line = content;
	list->next = NULL;
	list->previous = NULL;
	return (list);
}

void	ft_add_hist(t_hist **alst, t_hist *new)
{
	t_hist	*list;
	int		i;

	i = 0;
	if (!alst || !new)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		list = *alst;
		list->previous = new;
		new->next = list;
		*alst = new;
	}
}

void	ft_clear_history(t_hist **lst, void (*del)(void*))
{
	t_hist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		tmp->line ? del(tmp->line) : 0;
		free(tmp);
	}
	*lst = NULL;
}

void	next_history(t_all *all, char **res)
{
	int		len;

	if (*(all->history) == NULL || all->current == NULL)
		return ;
	prepare_history(all, res);
	len = ft_strlen(*res);
	free(*res);
	if (all->current->previous)
	{
		all->current = all->current->previous;
		*res = ft_strdup(all->current->line);
	}
	else
		*res = ft_strdup("");
	while (len > 0)
	{
		tputs(all->term->le, 1, ft_putchar);
		tputs(all->term->dc, 1, ft_putchar);
		len--;
	}
	all->index = ft_strlen(*res);
	all->free_command = 0;
	ft_printf("%s", *res);
}

void	previous_history(t_all *all, char **res)
{
	int		len;

	if (all->current == NULL || !all->current->next)
		return ;
	prepare_history(all, res);
	len = ft_strlen(*res);
	free(*res);
	*res = ft_strdup(all->current->line);
	if (all->current->next)
		all->current = all->current->next;
	while (len > 0)
	{
		tputs(all->term->le, 1, ft_putchar);
		tputs(all->term->dc, 1, ft_putchar);
		len--;
	}
	all->index = ft_strlen(*res);
	all->free_command = 0;
	ft_printf("%s", *res);
}
