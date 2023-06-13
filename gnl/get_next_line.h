/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:09:13 by jgravalo          #+#    #+#             */
/*   Updated: 2023/03/14 17:20:08 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 1

size_t			ft_strlen(const char *str);

char			*ft_strchr(char *text, int c);

char			*ft_strjoin(char *s1, char *s2);

int				ft_atoi(char *str);

char			*maketext(char *text, int fd);

char			*makeline(char *text);

char			*modifytext(char *text);

char			*get_next_line(int fd);

#endif
