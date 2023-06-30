/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:30:16 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	parsing_atoi(int *n, char *str)
{
	int	nb;

	nb = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			if (parsing_safeadd(&nb, *str - '0'))
				return (1);
		}
		else
			return (2);
		str++;
	}
	*n = nb;
	return (0);
}

int	parsing_safeadd(int *a, int b)
{
	if (*a > (INT_MAX - b) / 10)
		return (1);
	*a = *a * 10 + b;
	return (0);
}
