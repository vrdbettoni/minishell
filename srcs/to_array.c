/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   to_array.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:30:28 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_len(char **env)
{
	int		len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int		print_env_array(char **env)
{
	int i;

	i = 0;
	while (env[i])
		ft_printf("[%s]\n", env[i++]);
	return (0);
}

int		env_list2array(t_all *all)
{
	int		i;
	int		lstlen;
	t_env	*lst;

	lstlen = env_lstlen(all->env_list);
	all->env_array = (char**)malloc((lstlen + 1) * sizeof(char*));
	if (!all->env_array)
		exit_err();
	i = -1;
	lst = all->env_list;
	while (++i < lstlen)
	{
		all->env_array[i] = ft_strjsep(lst->var, lst->value, '=');
		lst = lst->next;
	}
	all->env_array[i] = NULL;
	return (0);
}

int		sort_env_array(t_all *all)
{
	int		size;
	char	*tmp;
	int		i;

	size = env_lstlen(all->env_list);
	env_list2array(all);
	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(all->env_array[i], all->env_array[i + 1]) > 0)
		{
			tmp = all->env_array[i];
			all->env_array[i] = all->env_array[i + 1];
			all->env_array[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (1);
}
