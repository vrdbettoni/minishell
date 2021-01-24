/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:17:55 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_redir_oplog(char *cmd, int i)
{
	if (cmd[i] == '>')
		return (1);
	else if (cmd[i] == '<')
		return (2);
	else if (cmd[i] == '|')
		return (3);
	else if (!ft_strncmp(cmd + i, "&&", 2))
		return (4);
	return (0);
}

int		free_cmd_args(t_all *all)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*cmds;

	cmds = all->cmds;
	while (cmds)
	{
		lst = cmds->content;
		while (lst)
		{
			tmp = lst->next;
			lst->content = free_safe(lst->content);
			lst = free_safe(lst);
			lst = tmp;
		}
		tmp = cmds->next;
		cmds = free_safe(cmds);
		cmds = tmp;
	}
	all->args_beg = NULL;
	all->args = NULL;
	all->cmds = NULL;
	return (0);
}
