/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_unset_export.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:34:39 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:11 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_err(void)
{
	ft_printf("%s\n", strerror(errno));
	exit(-1);
}

int		get_env(t_all *all, char **environ)
{
	int		i;
	int		i_eq;
	t_env	*new;
	char	*var;

	i = -1;
	var = NULL;
	all->env_list = NULL;
	while (++i < env_len(environ))
	{
		var = ft_strdup(environ[i]);
		i_eq = ft_strlchr(var, '=');
		var[i_eq] = 0;
		env_lstaddb(&(all->env_list), var, var + i_eq + 1, 1);
		var = free_safe(var);
	}
	return (0);
}

int		unset_env(t_env **env_list, char *arg)
{
	t_env	*lst;
	t_env	*prev;

	lst = *env_list;
	while (lst)
	{
		if (!ft_strcmp(lst->var, arg))
		{
			lst->value = free_safe(lst->value);
			lst->var = free_safe(lst->var);
			prev->next = lst->next;
			lst = free_safe(lst);
			break ;
		}
		prev = lst;
		lst = lst->next;
	}
	return (0);
}

int		export_env(t_env **env_list, char *arg)
{
	t_env	*lst;

	if (ft_strlchr(arg, '=') >= 0)
		add_env(env_list, arg, 1, 0);
	else
	{
		lst = *env_list;
		while (lst)
		{
			if (!ft_strcmp(lst->var, arg))
			{
				lst->exp = 1;
				return (0);
			}
			lst = lst->next;
		}
	}
	return (0);
}

int		export_no_arg(t_all *all)
{
	int		i;
	char	*value;
	int		eq;
	int		len;

	i = 0;
	sort_env_array(all);
	len = env_len(all->env_array);
	while (i < len)
	{
		eq = ft_strlchr(all->env_array[i], '=');
		all->env_array[i][eq] = 0;
		ft_printf("declare -x %s=", all->env_array[i]);
		ft_printf("\"%s\"\n", all->env_array[i] + eq + 1);
		i++;
	}
	i = 0;
	while (all->env_array[i])
		free_safe(all->env_array[i++]);
	all->env_array = free_safe(all->env_array);
	return (1);
}
