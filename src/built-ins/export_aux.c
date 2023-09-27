/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:17:20 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/27 10:34:13 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '_' || c == '?' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_alpha_num(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_'
		|| c == '?' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_alpha_num_exp(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_' || c == '?')
		return (1);
	return (0);
}

int	write_not_valid(char *var)
{
	write(2, "bash: export: `", 15);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}
