/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:14:17 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_env_var(char *s, t_all *all)
{
	int		i;
	char	*trim_wp;
	t_env	*lst;

	i = 1;
	while (s[i] && !is_whitespaces(s[i])
	&& ft_strlchr("\'\"$\\", s[i]) < 0)
		i++;
	trim_wp = ft_strdupl(s, i);
	if (!ft_strcmp("$?", trim_wp))
		return (ft_itoa(all->status));
	lst = all->env_list;
	while (lst)
	{
		if (!ft_strcmp(lst->var, trim_wp + 1))
		{
			trim_wp = free_safe(trim_wp);
			return (ft_strdup(lst->value));
		}
		lst = lst->next;
	}
	trim_wp = free_safe(trim_wp);
	return (ft_strdup(""));
}

int		to_expand(char *cmd, int *i, t_all *all)
{
	if ((all->parse->quo && (!all->parse->dquo || all->parse->dquo == 2)))
		return (0);
	else if (!all->parse->quo && !all->parse->dquo && (!cmd[*i + 1]
	|| is_whitespaces(cmd[*i + 1])))
		return (0);
	else if (all->parse->dquo && (!cmd[*i + 1] || cmd[*i + 1] == '\"'
	|| is_whitespaces(cmd[*i + 1])))
		return (0);
	return (1);
}

int		to_dollar(char *cmd, char **trim, int *i, t_all *all)
{
	char	*s1;
	char	*s2;
	int		len_var;

	if (!to_expand(cmd, i, all))
	{
		add_chr(trim, '$');
		(*i)++;
	}
	else
	{
		s1 = expand_env_var(cmd + *i, all);
		s2 = *trim;
		*trim = ft_strjmod(*trim, s1);
		s1 = free_safe(s1);
		s2 = free_safe(s2);
		len_var = 1;
		while (cmd[*i + len_var] && !is_whitespaces(cmd[*i + len_var])
		&& ft_strlchr("\'\"$\\", cmd[*i + len_var]) < 0)
			len_var++;
		*i += len_var;
	}
	return (0);
}
