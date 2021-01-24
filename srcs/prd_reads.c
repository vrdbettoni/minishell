/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prd_reads.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 20:58:14 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:59:23 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		read_prd_loop(char **trim, char *cmd, int *i, t_all *all)
{
	if (trim_cmd(cmd, trim, i, all))
	{
		*trim = free_safe(*trim);
		return (1);
	}
	if (*trim)
		ft_lstadd_back(&(all->args), ft_lstnew(ft_strdup(*trim)));
	check_if_redir_oplog(cmd, &(all->args), i, all);
	check_if_parenthesis(cmd, &(all->args), i);
	if (check_prd_syntax(all))
		return (1);
	*trim = free_safe(*trim);
	while (cmd[*i] && is_whitespaces(cmd[*i]))
		(*i)++;
	return (0);
}

int		complete_read(t_list *lst, t_all *all)
{
	t_list	*last;

	while ((last = ft_lstlast(all->args))
	&& which_prd(last) == 3 && !last->next)
		if (read_prd(all))
			return (1);
	!all->args_pipe ? all->args_pipe = lst : 0;
	if (check_prd_syntax(all))
		return (1);
	return (0);
}

int		read_prd(t_all *all)
{
	char	*cmd;
	char	*trim;
	int		i;

	i = 0;
	trim = NULL;
	ft_printf("> ");
	if (gnl(0, &cmd, 3, all) == -1)
		return (1);
	while (cmd[i] && is_whitespaces(cmd[i]))
		i++;
	while (cmd[i])
		if (read_prd_loop(&trim, cmd, &i, all))
			return (1);
	cmd = free_safe(cmd);
	return (0);
}

char	*expand_str(char *str, char *exp, int len_var, t_all *all)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			s1 = expand_env_var(str + i, all);
			s2 = exp;
			exp = ft_strjmod(exp, s1);
			s1 = free_safe(s1);
			s2 = free_safe(s2);
			while (str[i + len_var] && !is_whitespaces(str[i + len_var])
			&& ft_strlchr("\'\"$\\", str[i + len_var]) < 0)
				len_var++;
			i += len_var;
		}
		else
			add_chr(&exp, str[i++]);
	}
	str = free_safe(str);
	return (exp);
}

int		read_heredoc(char *eofsig, char **heredoc, int ret, t_all *all)
{
	char	*tmp;
	char	*line;

	*heredoc = NULL;
	while (!ret)
	{
		ft_printf("> ");
		if ((ret = gnl(0, &line, 3, all)) == -1)
			return (1);
		if (!ft_strcmp(line, eofsig))
		{
			line = free_safe(line);
			break ;
		}
		if (*heredoc)
		{
			tmp = *heredoc;
			*heredoc = ft_strjsep(*heredoc, line, '\n');
			tmp = free_safe(tmp);
		}
		else
			*heredoc = ft_strdup(line);
		line = free_safe(line);
	}
	return (0);
}
