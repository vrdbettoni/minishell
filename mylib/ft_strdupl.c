/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdupl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 14:50:18 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:12:03 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupl(char const *s1, size_t l)
{
	char	*copy;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[len] && len < l)
		len++;
	if (!(copy = (char*)malloc(len + 1)))
		return (NULL);
	while (s1[i] && i < l)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
