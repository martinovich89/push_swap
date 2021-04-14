/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 02:12:51 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/14 02:12:54 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_element
{
	char				*data;
	int					fd;
	int					ret;
	struct s_element	*next;
}				t_element;

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_read(t_element *curr);
t_element			*ft_getcontent(int fd, t_element **stat);
int				ft_cpytoline(t_element *curr, char **line);
void			ft_free_elem(t_element *curr, t_element **stat);

#endif