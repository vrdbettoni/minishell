/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quotes.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:13:03 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	flag_quote(char c, t_parse *p)
{
	if (c == '\'')
		p->quo = p->quo ? 0 : p->dquo + 1;
	else if (c == '\"')
		p->dquo = p->dquo ? 0 : p->quo + 1;
	p->unassignable = 1;
}

int		to_quote(char **trim, int *i, t_all *all)
{
	if (all->parse->dquo)
		add_chr(trim, '\'');
	else
		flag_quote('\'', all->parse);
	(*i)++;
	return (0);
}

int		to_dquote(char **trim, int *i, t_all *all)
{
	if (all->parse->quo)
		add_chr(trim, '\"');
	else
		flag_quote('\"', all->parse);
	(*i)++;
	return (0);
}

int		read_quotes(char q, int i, char **trim, t_all *all)
{
	char	*buf;
	char	*tmp;
	char	*cmd;

	i = 0;
	if (!(cmd = malloc(sizeof(char))))
		return (1);
	*cmd = 0;
	while (ft_strlchr(cmd, q) < 0)
	{
		ft_printf("> ");
		if (gnl(0, &buf, 3, all) == -1)
		{
			cmd = free_safe(cmd);
			return (1);
		}
		tmp = cmd;
		cmd = ft_strjsep(cmd, buf, '\n');
		tmp = free_safe(tmp);
		buf = free_safe(buf);
	}
	while (cmd[i] && cmd[i] != q)
		parse_loop(cmd, trim, &i, all);
	cmd = free_safe(cmd);
	return (0);
}
