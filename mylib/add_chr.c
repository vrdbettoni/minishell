/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_chr.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 14:56:25 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:09:12 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		add_chr_next(char **str, char c)
{
	int		i;
	char	*tmp;

	tmp = (char*)malloc((ft_strlen(*str) + 2) * sizeof(char));
	if (!tmp)
		return ;
	i = 0;
	while ((*str)[i])
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	*str = free_safe(*str);
	*str = tmp;
	tmp = 0;
}

void			add_chr(char **str, char c)
{
	char	*tmp;

	if (!(*str))
	{
		tmp = (char*)malloc(2 * sizeof(char));
		if (!tmp)
			return ;
		tmp[0] = c;
		tmp[1] = '\0';
		*str = tmp;
		return ;
	}
	else
		add_chr_next(str, c);
}
