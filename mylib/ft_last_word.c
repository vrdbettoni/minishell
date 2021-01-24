/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_last_word.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 21:09:59 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:11:04 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_last_word(char *s)
{
	int		i;
	int		j;

	i = ft_strlen(s);
	i > 0 ? i-- : 0;
	while (s[i] && is_whitespaces(s[i]))
		i--;
	j = i + 1;
	while (i > 0 && ft_isalnum(s[i]))
		i--;
	is_whitespaces(s[i]) ? i++ : 0;
	return (ft_strdupl(&(s[i]), j - i));
}
