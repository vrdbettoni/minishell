/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_loop.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:11:31 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		parse_loop(char *cmd, char **trim, int *i, t_all *all)
{
	if (cmd[*i] == '\'')
		to_quote(trim, i, all);
	else if (cmd[*i] == '\"')
		to_dquote(trim, i, all);
	else if (cmd[*i] == '$')
		to_dollar(cmd, trim, i, all);
	else if (cmd[*i] == '\\' && !all->parse->quo)
	{
		if (to_bslash(cmd, trim, i, all))
			return (1);
	}
	else if (cmd[*i] == '=')
		to_equal(cmd, trim, i, all);
	else
		add_chr(trim, cmd[(*i)++]);
	return (0);
}

int		trim_cmd(char *cmd, char **trim, int *i, t_all *all)
{
	char	*s1;
	char	*s2;
	t_parse	p;

	p.quo = 0;
	p.dquo = 0;
	p.unassignable = 0;
	all->parse = &p;
	while (cmd[*i] && ((!is_whitespaces(cmd[*i]) &&
	!is_redir_oplog(cmd, *i) && cmd[*i] != ';' && cmd[*i] != '(')
	|| p.quo || p.dquo))
		parse_loop(cmd, trim, i, all);
	if ((p.quo || p.dquo) && !is_redir_oplog(cmd, *i))
		read_quotes(p.quo == 1 ? '\'' : '\"', 0, trim, all);
	return (0);
}
