/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjmod.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 14:46:38 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:12:56 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjmod(char const *s1, char const *s2)
{
	size_t	len;
	char	*dest;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	len = len1 + len2 + 1;
	if (!(dest = (char*)malloc(len * sizeof(char))))
		return (NULL);
	*dest = 0;
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
	return (dest);
}
