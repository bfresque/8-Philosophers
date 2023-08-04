/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:24 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/04 14:00:07 by bfresque         ###   ########.fr       */
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
	check_all_deaths(init);
	if (init->flag_death != 0)
	{
		if (init->death_printed != 1)
		{
			init->death_printed++;
			pthread_mutex_lock(&(init->print_mutex));
			printf("%lld %d ", (ft_get_time() - init->philo->start_time), id);
			printf("%s died\n%s", RED, RESET);
		}
		else
			pthread_mutex_unlock(&init->death_printed_mutex);
		return ;
	}
	pthread_mutex_unlock(&init->death_printed_mutex);
	pthread_mutex_lock(&init->death_printed_mutex);
	if (init->flag_death == 0)
	{
		pthread_mutex_lock(&(init->print_mutex));
		printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id, str);
		pthread_mutex_unlock(&(init->print_mutex));
	}
	pthread_mutex_unlock(&init->death_printed_mutex);
}

void	philo_just_one(t_init *init, char **av)
{
	free(init);
	usleep(ft_atoi_philo(av[2]) * 1000);
	printf("%d 1 died\n", ft_atoi_philo(av[2]) + 1);
}
