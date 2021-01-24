/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_and_exec.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:09:41 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_if_redir_oplog(char *cmd, t_list **args, int *i, t_all *all)
{
	char	*rd;
	t_list	*new;

	rd = NULL;
	if (is_redir_oplog(cmd, *i))
	{
		add_chr(&rd, cmd[(*i)++]);
		if (cmd[*i - 1] == cmd[*i])
			add_chr(&rd, cmd[(*i)++]);
		new = ft_lstnew(ft_strdup(rd));
		new->prd = 1;
		ft_lstadd_back(args, new);
		rd = free_safe(rd);
	}
	return (0);
}

int		check_if_parenthesis(char *cmd, t_list **args, int *i)
{
	char	*s1;
	int		len;
	t_list	*new;

	if (cmd[*i] == '(')
	{
		len = *i + 1;
		match_parenthesis(cmd, &len);
		len = len - *i;
		s1 = ft_strdupl(cmd + *i + 1, len - 2);
		new = ft_lstnew(s1);
		new->subsh = 1;
		ft_lstadd_back(args, new);
		*i += len;
	}
	return (0);
}

void	exec_command(t_all *all)
{
	if (all->args)
		ft_lstadd_back(&(all->cmds), ft_lstnew(all->args));
	all->args_beg = all->args;
	all->status = parse_logic(all->args, all);
	if (all->status > 255)
		all->status /= 256;
	all->args = NULL;
}

void	push_command(char *command, char **trim, int *i, t_all *all)
{
	t_list	*tmp;

	if (*trim)
	{
		tmp = ft_lstnew(ft_strdup(*trim));
		tmp->assignable = all->assignable;
		if (tmp->assignable && is_valid_assignment(tmp))
			add_env(&(all->env_list), tmp->content, 0, 0);
		all->assignable = 1;
		ft_lstadd_back(&(all->args), tmp);
	}
	check_if_redir_oplog(command, &(all->args), i, all);
	check_if_parenthesis(command, &(all->args), i);
	if (command[*i] == ';')
	{
		(*i)++;
		exec_command(all);
	}
	*trim = free_safe(*trim);
}

int		parse_args_to_lists(char *command, t_all *all, int i, int script)
{
	char	*trim;

	trim = NULL;
	all->args = NULL;
	all->cmds = NULL;
	while (command[i] && is_whitespaces(command[i]))
		i++;
	while (command[i])
	{
		all->assignable = 1;
		if (trim_cmd(command, &trim, &i, all))
		{
			trim = free_safe(trim);
			return (1);
		}
		push_command(command, &trim, &i, all);
		while (command[i] && is_whitespaces(command[i]))
			i++;
		if (command[i] == ';' && all->args == NULL)
			return (print_n_set_error(all, "`;'", "syntax error", 1));
	}
	exec_command(all);
	free_cmd_args(all);
	!script ? command = free_safe(command) : 0;
	return (0);
}
