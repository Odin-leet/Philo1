/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:16:46 by aali-mou          #+#    #+#             */
/*   Updated: 2019/10/23 20:49:21 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(char *str, int *number)
{
	long	result;

	result = 0;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str - '0');
		else
			return (0);
		str++;
	}
	if (result > INT_MAX)
		return (0);
	*number = result;
	return (1);
}
