/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocompletion.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:37:49 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 16:38:28 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**save_path(t_env *env_list)
{
	char		**path;

	while (env_list && ft_strcmp(env_list->var, "PATH"))
		env_list = env_list->next;
	if (!(env_list))
		return (NULL);
	path = ft_split(env_list->value, ':');
	return (path);
}

void		search_cmd(t_all *all, char *res, int len, char **line)
{
	DIR			*rep;
	t_dirent	*dossier;
	int			i;

	i = 1;
	while (all->path_auto[i])
	{
		rep = opendir(all->path_auto[i]);
		if (rep == NULL)
			return (ft_error());
		while ((dossier = readdir(rep)))
		{
			if (dossier == NULL)
				return (ft_error());
			if ((ft_strncmp(res, dossier->d_name, len) == 0))
			{
				(*line) = ft_strdup(dossier->d_name);
				closedir(rep);
				return ;
			}
		}
		if (closedir(rep) == -1)
			return (ft_error());
		i++;
	}
}

void		search_pattern(t_all *all, char *res, int len, char **line)
{
	DIR			*rep;
	t_dirent	*dossier;
	char		buffer[512];
	char		*last_word;

	last_word = ft_last_word(res);
	len = ft_strlen(last_word);
	getcwd(buffer, 512);
	rep = opendir(buffer);
	if (rep == NULL)
		return (ft_error());
	while ((dossier = readdir(rep)))
	{
		if (dossier == NULL)
			return (ft_error());
		if ((ft_strncmp(last_word, dossier->d_name, len) == 0))
		{
			(*line) = ft_strdup(dossier->d_name);
			free(last_word);
			closedir(rep);
			return ;
		}
	}
	free(last_word);
	return (closedir(rep) == -1 ? ft_error() : 0);
}

int			autocompletion_choice(char *res)
{
	int		i;

	i = 0;
	while (res[i] && is_whitespaces(res[i]))
		i++;
	while (res[i] && !is_whitespaces(res[i]))
		i++;
	if (!res[i])
		return (0);
	return (1);
}

void		autocompletion(t_all *all, char **res)
{
	char		*line;
	int			len;

	line = NULL;
	if ((len = ft_strlen(*res)) < 1 || is_whitespaces((*res)[len])
									|| (*res)[all->index] != 0)
		return ;
	autocompletion_choice(*res) == 0 ? search_cmd(all, *res, len, &line)
									: search_pattern(all, *res, len, &line);
	if (!line)
		return ;
	while (len > 0)
	{
		tputs(all->term->le, 1, ft_putchar);
		tputs(all->term->dc, 1, ft_putchar);
		len--;
	}
	len = ft_strlen(*res) - 1;
	while (len && (*res)[len] && ft_isalnum((*res)[len]))
		(*res)[len--] = 0;
	len == 0 ? (*res)[0] = 0 : 0;
	*res = ft_strjoin_mod(*res, line);
	free(line);
	all->index = ft_strlen(*res);
	ft_printf("%s", *res);
}
