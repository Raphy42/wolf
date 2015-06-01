/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 11:41:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/11 16:05:45 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef NULL
#  define NULL		((void *)0)
# endif

typedef unsigned long long t_ull;

# define INT_MAX	2147483647
# define LONG_MAX	9223372036854775807
# define BASE		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define BUFF_SIZE	512

/*
** 	Vanilla functions
*/
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t len);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_strtrim(const char *s);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strequ(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
**		Bonus functions
*/
char			**ft_arraydeli(char **array, int i);
char			**ft_arrayappend(char **array, char *str);
char			*ft_itobase(long nb, int base);
double			ft_atod(const char *str);
int				ft_arraylen(char **array);
int				ft_strcasecmp(const char *s1, const char *s2);
int				ft_strncasecmp(const char *s1, const char *s2, size_t n);
long			ft_basetol(const char *str, int base);
void			ft_arraydel(char **array);
char			**ft_arraydup(char **array);
void			ft_strlower(char *str);
void			ft_strrev(char *str);
void			ft_strupper(char *str);
char			*ft_strndup(const char *s, size_t n);

/*
**		https://github.com/Zoellingam
**			-used with permission
*/
int				ft_fprintf(int fd, char const *format, ...);

/*
**		haha mdr tumblr.com facorreg
**			-tres la douceur et tout
*/
int				get_next_line(int const fd, char **line);

#endif
