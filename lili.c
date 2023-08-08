



void	ft_philo_sleep(unsigned long duration, t_init *init)
{
	unsigned long	start;

	start = ft_get_time();
	while (check_all_deaths(init, init->philo) == 0)
	{
		if (ft_get_time() - start >= duration)
			break ;
		usleep(init->nb_of_philo * 2);
	}
}

void	action_think(t_init *init, t_philo *philo)
{
	check_all_deaths(init, philo);
	// if (init->flag_death != 0)
	// 	return ;
	print(init, philo->id_philo, " is thinking\n");
	// if (init->flag_death != 0)
	// 	return ;
	ft_philo_sleep((init->time_to_think), init);
}

void	action_sleep(t_init *init, t_philo *philo)
{
	check_all_deaths(init, philo);
	// if (init->flag_death != 0)
	// 	return ;
	print(init, philo->id_philo, " is sleeping\n");
	// if (init->flag_death != 0)
	// 	return ;
	ft_philo_sleep((init->time_to_sleep), init);
}

void	action_eat(t_init *init, t_philo *philo)
{
	check_all_deaths(init, philo);
	// if (init->flag_death != 0)
	// 	return ;
	print(init, philo->id_philo, " is eating\n");
	// if (init->flag_death != 0)
	// 	return ;
	philo->time_last_eat = ft_get_time();
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	usleep(init->time_to_eat * 1000);
	// ft_philo_sleep((init->time_to_eat), init);
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	}
}

void	take_fork(t_init *init, t_philo *philo)
{
	check_all_deaths(init, philo);
	// if (init->flag_death != 0)
	// 	return ;
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		print(init, philo->id_philo, " has taken a fork\n");
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		print(init, philo->id_philo, " has taken a fork\n");;
		action_eat(init, philo);
	}
	else if (philo->id_philo % 2 != 0)
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		print(init, philo->id_philo, " has taken a fork\n");
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		print(init, philo->id_philo, " has taken a fork\n");
		action_eat(init, philo);
	}	
}







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

int	check_all_deaths(t_init *init, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(init->time_last_eat));
	long long int time_last_eat = init->philo[i].time_last_eat;
	pthread_mutex_unlock(&(init->time_last_eat));

	while (i < init->nb_of_philo && (init->flag_death == 0))
	{
		if ((ft_get_time() - time_last_eat) > init->time_to_die)
		{
			pthread_mutex_init(&(init->death_mutex), NULL);
			pthread_mutex_lock(&(init->death_mutex));
			init->flag_death = 1;
			print(init, philo->id_philo, " died");
			pthread_mutex_unlock(&(init->death_mutex));
			return (-1);
		}
		i++;
	}
	return (0);
}

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
