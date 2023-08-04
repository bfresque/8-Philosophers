/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:02:25 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/04 14:08:26 by bfresque         ###   ########.fr       */
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
		i++;
	}
	if (init->philo)
		free(init->philo);
	if (init->forks)
		free(init->forks);
}

void	check_death(t_init *init, t_philo *philo)
{
	long long int	current_time;
	long long int	time_since_last_eat;

	current_time = ft_get_time();
	time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (long long int)init->time_to_die)
	{
		pthread_mutex_init(&(philo->death_mutex), NULL);
		pthread_mutex_lock(&(philo->death_mutex));
		init->flag_death = 1;
		pthread_mutex_unlock(&(philo->death_mutex));
	}
}

void	check_all_deaths(t_init *init)
{
	int	i;

	i = 0;
	while (i < init->nb_of_philo && (init->flag_death == 0))
	{
		check_death(init, &init->philo[i]);
		i++;
	}
}

// int	check_all_eat(t_init *init)
// {
// 	int	i;

// 	i = 0;
// 	init->all_philo_finished = 0;
// 	while (i < init->nb_of_philo)
// 	{
// 		pthread_mutex_lock(&(init->philo[i].eat_mutex));
// 		if (init->philo[i].nb_eat_time == init->number_must_eat)
// 			init->all_philo_finished++;
// 		pthread_mutex_unlock(&(init->philo[i].eat_mutex));
// 		i++;
// 	}
// 	if (init->all_philo_finished < init->nb_of_philo)
// 		return (0);
// 	else if (init->all_philo_finished == init->nb_of_philo)
// 	{
// 		init->flag_eat = 1;
// 		ft_close(init);
// 		return (1);
// 	}
// 	return (-1);
// }

int	help_verif_numbers(char *str)
{
	int	i;
	int	len;
	int	num;

	i = 0;
	len = strlen(str);/* attention fobiden fonctions */
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
