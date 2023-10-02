/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:18:07 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/02 14:57:41 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	count_quotes(t_shell *shell, char *str)
{
	int		count;
	int		i;
	t_quote	*ptr;

	i = 0;
	count = 0;
	ptr = shell->quote;
	while (str[i])
	{
		if (i == ptr->start)
		{
			count += 2;
			i++;
			while (i != ptr->end)
				i++;
			return (count);
		}
		else
			i++;
	}
	return (count);
}

void	copy_new(t_shell *shell, char *new, char *str)
{
	int		i;
	int		j;
	t_quote	*ptr;

	i = 0;
	j = 0;
	ptr = shell->quote;
	while (str[i])
	{
		if (i == ptr->start - ptr->start)
		{
			i++;
			while (i != ptr->end - ptr->start)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
}

char	*remove_quotes(t_shell *shell, char *str)
{
	char	*tmp;
	int		len;

	len = count_quotes(shell, str);
	tmp = malloc(sizeof (char) * ft_strlen(str) - len + 1);
	copy_new(shell, tmp, str);
	free(str);
	return (tmp);
}
