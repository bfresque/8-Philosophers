/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:24 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 15:22:36 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

int	ft_atoi_philo(char *str)
{
	int result = 0;
	int sign = 1;

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

long long ft_get_time()
{
	struct timeval current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);

	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void print(t_init *init, int id_phil, char *str)
{
	pthread_mutex_lock(&(init->print_mutex));
	printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id_phil, str);
	if(str[1] == 'd')
	{
		ft_close(init);
		exit(-1);
	}
	pthread_mutex_unlock(&(init->print_mutex));
}

void	philo_just_one(t_init *init, char **av)
{
	free(init);
	usleep(ft_atoi_philo(av[2]) * 1000);
	printf("%d 1 died\n", ft_atoi_philo(av[2]) + 1);
	exit(1);
}