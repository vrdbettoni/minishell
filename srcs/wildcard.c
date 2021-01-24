/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wildcard.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:41:42 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:42:57 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		add_wildcards(t_list *arg, char *data, char *path)
{
	t_list		*new;

	new = ft_lstnew(ft_strjoin(path, ft_strdup(data)));
	new->next = arg->next;
	arg->next = new;
	return (1);
}

int		check_wildcards(t_list *arg, char *path, char *name)
{
	DIR			*rep;
	t_dirent	*dossier;
	int			i;

	i = 0;
	if (!(rep = opendir(path)))
		return (i);
	while ((dossier = readdir(rep)))
	{
		if (match_n_match(dossier->d_name, name))
			i += add_wildcards(arg, dossier->d_name, path);
	}
	closedir(rep);
	return (i);
}

void	clear_wildcards(t_list **args)
{
	t_list		*tmp;
	t_list		*tmp2;

	while (ft_strchr((*args)->content, '*'))
	{
		tmp2 = *args;
		*args = tmp2->next;
		free(tmp2->content);
		tmp2 = free_safe(tmp);
	}
	tmp = *args;
	while (tmp && tmp->next)
	{
		if (ft_strchr(tmp->next->content, '*')
						|| !ft_strlen(tmp->next->content))
		{
			tmp2 = tmp->next;
			tmp->next = tmp2->next;
			free(tmp2->content);
			tmp2 = free_safe(tmp2);
		}
		else
			tmp = tmp->next;
	}
}

void	get_wild_path(char *content, char **path, char **name)
{
	int			i;

	i = ft_strlen(content);
	while (i >= 0 && content[i] != '/')
		i--;
	*name = ft_strdup(&(content[i + 1]));
	content[i + 1] = 0;
	if (!ft_strlen(content))
		*path = ft_strdup("./");
	else
		*path = ft_strdup(content);
}

void	wildcards(t_list **args)
{
	t_list		*arg;
	char		*path;
	char		*name;
	int			i;

	i = 0;
	arg = *args;
	while (arg)
	{
		if (ft_strchr(arg->content, '*'))
		{
			get_wild_path(arg->content, &path, &name);
			i += check_wildcards(arg, path, name);
		}
		arg = arg->next;
	}
	if (i > 0)
		clear_wildcards(args);
}
