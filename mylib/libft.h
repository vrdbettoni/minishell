/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 15:54:13 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:21:57 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

typedef struct		s_struct
{
	int				flag1;
	int				flag2;
	int				flag3;
	int				width;
	int				flag4;
	int				precision;
	char			type;
}					t_struct;

typedef struct		s_list
{
	void			*content;
	int				subsh;
	int				assignable;
	int				prd;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
														void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list**alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
char				*ft_itoa_ll(long long int n);
char				*ft_itoa_base(long long int value, char *base);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr_ll(long long int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
long				ft_strlchr(const char *str, char c);
char				*ft_strdup(const char *s);
char				*ft_strdupc(char const *s1, char c);
char				*ft_strdupl(char const *s1, size_t l);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjmod(char const *s1, char const *s2);
char				*ft_strjsep(char const *s1, char const *s2, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strnstr(const char *haystack,
											const char *needle, size_t len);
void				ft_putnbr_base(unsigned long nb, char *base);
int					ft_strchr_mod(char *s);
char				*ft_strjoin_mod(char *s1, char const *s2);
void				*ft_realloc(void *ptr, size_t newsize, size_t count);
int					is_whitespaces(char c);
int					search(char *s, char c);
int					ft_lerpi(int first, int second, double p);
int					ft_printf(const char *format, ...)
 __attribute__((format(printf,1,2)));
int					get_next_line(int fd, char **line, int buffer_size);
int					print_c(char c, int nb);
int					conv_char(char c, t_struct *find);
int					conv_string(va_list ap, t_struct *find);
int					conv_pointer(va_list ap, t_struct *find);
int					conv_int(va_list ap, t_struct *find);
int					conv_ll(va_list ap, t_struct *find);
int					conv_x(va_list ap, t_struct *find);
int					putchar_mod(char *format);
t_struct			*init_struct(t_struct *find, int i);
void				*free_safe(void *p);
int					ft_strcmp(char *s1, char *s2);
int					ft_putchar(int c);
void				add_chr(char **str, char c);
char				*ft_last_word(char *s);

#endif
