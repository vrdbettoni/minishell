/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:24:46 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:25:21 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	load_history(t_hist **history)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	*(history) = NULL;
	fd = open("history_log", O_RDONLY);
	if (fd == -1)
		return ;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line, 100);
		ft_add_hist(history, ft_new_hist(line));
	}
	free(line);
	close(fd);
}

void	save_history(t_hist **history)
{
	int		fd;
	t_hist	*tmp;

	tmp = *history;
	fd = open("history_log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't save history log.\n", 2);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		write(fd, tmp->line, ft_strlen((const char*)tmp->line));
		write(fd, "\n", 1);
		tmp = tmp->previous;
	}
}

void	ft_copy(t_all *all, char **res)
{
	char	*taille;
	int		i;
	int		len;
	int		j;

	i = -1;
	j = 0;
	get_next_line(0, &taille, 10);
	while (taille[++i])
		if (!ft_isdigit(taille[i]))
		{
			ft_bzero((*res), ft_strlen(*res));
			return (ft_putstr_fd("\nError: bad copy.\n", 2));
		}
	ft_bzero(all->copy, 200);
	len = ft_atoi(taille);
	i = all->index;
	while ((*res)[i] && len--)
		all->copy[j++] = (*res)[i++];
	free(taille);
	all->copy[j] = '\0';
}

void	ft_paste_2(t_all *all, char **res, int len)
{
	while (all->index < len)
	{
		tputs(all->term->nd, 1, ft_putchar);
		all->index++;
	}
	while (len > 0)
	{
		tputs(all->term->le, 1, ft_putchar);
		tputs(all->term->dc, 1, ft_putchar);
		len--;
	}
}

void	ft_paste(t_all *all, char **res, int len)
{
	char	*save;
	int		save_index;

	if (!(all->copy[0]))
		return ;
	save_index = all->index;
	ft_paste_2(all, res, len);
	all->index = save_index;
	save = ft_strdup(&((*res)[all->index]));
	(*res)[all->index] = '\0';
	save_index = ft_strlen(save);
	(*res) = ft_strjoin_mod(*res, all->copy);
	*res = ft_strjoin_mod(*res, save);
	all->index += ft_strlen(all->copy);
	free(save);
	ft_printf("%s", *res);
	while (save_index--)
		tputs(all->term->le, 1, ft_putchar);
}
