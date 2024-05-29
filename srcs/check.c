/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:02:25 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/08 17:43:03 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_close(t_init *init)
{
	int	i;

	i = 0;
	while (i < init->nb_of_philo)
	{
		pthread_mutex_destroy(&init->forks[i]);
		pthread_mutex_destroy(&init->philo[i].mutex_time_last_eat);
		i++;
	}
	pthread_mutex_destroy(&init->print_mutex);
	pthread_mutex_destroy(&init->death_printed_mutex);
	pthread_mutex_destroy(&init->death_mutex);
	if (init->forks)
		free(init->forks);
	if (init->philo)
		free(init->philo);
	if (init)
		free(init);
}

int	check_flag_died(t_init *init)
{
	pthread_mutex_lock(&(init->death_mutex));
	if (init->flag_death != 0)
	{
		pthread_mutex_unlock(&(init->death_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(init->death_mutex));
	return (0);
}

int	check_all_deaths(t_init *init, t_philo *philo)
{
	long long int	time_last_eat;

	pthread_mutex_lock(&(philo->mutex_time_last_eat));
	time_last_eat = init->philo->time_last_eat;
	pthread_mutex_unlock(&(philo->mutex_time_last_eat));
	if ((ft_get_time() - time_last_eat) > init->time_to_die)
	{
		pthread_mutex_lock(&(init->death_mutex));
		init->flag_death = 1;
		pthread_mutex_unlock(&(init->death_mutex));
		print(init, philo->id_philo, " died");
		return (-1);
	}
	return (0);
}

int	help_verif_numbers(char *str)
{
	int	i;
	int	len;
	int	num;

	i = 0;
	while (str[i])
		i++;
	len = i;
	i = 0;
	num = ft_atoi_philo(str);
	while (i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (num <= 0)
		return (0);
	return (1);
}

int	check_numbers(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!help_verif_numbers(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
