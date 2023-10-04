/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:01:06 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:11:00 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static int	count_numbers(char *argument)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (argument[i] == '-')
		i++;
	while (argument[i] == '0')
		i++;
	while (argument[i])
	{
		i++;
		c++;
	}
	return (c);
}

static void	set_numbers(int *number, char *argument)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argument[i] == '-')
		i++;
	while (argument[i])
	{
		number[j] = argument[i] - '0';
		i++;
		j++;
	}
}

static int	compare(int *number, int *long_compare, int n)
{
	int	i;

	i = 0;
	while (n)
	{
		if (number[i] > long_compare[i])
			return (1);
		else if (number[i] < long_compare[i])
			return (0);
		else
			i++;
		n--;
	}
	return (0);
}

static int	compare_aux(char *argument, char *long_compare)
{
	if (count_numbers(argument) > count_numbers(long_compare))
	{
		free(long_compare);
		return (1);
	}
	if (count_numbers(argument) < count_numbers(long_compare))
	{
		free(long_compare);
		return (0);
	}
	return (-1);
}

int	compare_exit(char *argument)
{
	int		*number;
	int		*long_array;
	char	*long_compare;
	int		ret;

	if (argument[0] == '-')
		long_compare = ft_strdup("9223372036854775808");
	else
		long_compare = ft_strdup("9223372036854775807");
	ret = compare_aux(argument, long_compare);
	if (ret == 0 || ret == 1)
		return (ret);
	number = malloc(sizeof (int) * count_numbers(argument));
	check_malloc_error(number);
	long_array = malloc(sizeof (int) * count_numbers(long_compare));
	check_malloc_error(long_array);
	set_numbers(number, argument);
	set_numbers(long_array, long_compare);
	ret = compare(number, long_array, count_numbers(long_compare));
	free(long_compare);
	free(long_array);
	free(number);
	return (ret);
}
