/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:24 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/08 16:22:40 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi_philo(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

long long	ft_get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print(t_init *init, int id, char *str)
{
	pthread_mutex_lock(&init->death_printed_mutex);
	if (check_flag_died(init) == 1)
	{
		if (init->death_printed == 0)
		{
			init->death_printed++;
			pthread_mutex_lock(&(init->print_mutex));
			printf("%lld %d", (ft_get_time() - init->philo->start_time), id);
			printf(" died\n");
			pthread_mutex_unlock(&init->print_mutex);
		}
		pthread_mutex_unlock(&init->death_printed_mutex);
		return ;
	}
	pthread_mutex_unlock(&init->death_printed_mutex);
	pthread_mutex_lock(&init->death_printed_mutex);
	if (check_flag_died(init) == 0)
	{
		pthread_mutex_lock(&(init->print_mutex));
		printf("%lld %d", (ft_get_time() - init->philo->start_time), id);
		printf("%s", str);
		pthread_mutex_unlock(&(init->print_mutex));
	}
	pthread_mutex_unlock(&init->death_printed_mutex);
}

void	cleanup_data(t_init *init, int last_index)
{
	while (last_index >= 0)
	{
		free(init->philo[last_index].data);
		last_index--;
	}
}
