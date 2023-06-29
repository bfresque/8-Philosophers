jai un autre probleme les reponses donnee par le terminals sont aleatroires alors quelles devraient toujours etre les meme peux tu maider a resoudre ce probleme stp 

typedef struct s_philo
{
	int				id_philo;
	int				nb_eat_time;
	unsigned long	time_last_eat;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread_id;
	// struct s_init	*data;
	// pthread_mutex_t	left_fork_id;
	// pthread_mutex_t	*right_fork_id;
}	t_philo;

typedef struct s_init
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	unsigned long	start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_eat;
}	t_init;

typedef struct s_data
{
	t_init	*init;
	t_philo	*philo;
}	t_data;

t_init *init_data(t_init *data, char **av)
{
	data->nb_of_philo = ft_atoi_philo(av[1]);
	data->time_to_die = ft_atoi_philo(av[2]);
	data->time_to_eat = ft_atoi_philo(av[3]);
	data->time_to_sleep = ft_atoi_philo(av[4]);
	data->number_must_eat = ft_atoi_philo(av[5]);

	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (data->philo == NULL)
		return NULL;

	return data;
}


t_init *init_philo(t_init *data)
{
	int i;

	i = data->nb_of_philo;
	while (i > 0)
	{
		data->philo[i - 1].id_philo = i;  // Utilisez (i - 1) pour l'indice
		data->philo[i - 1].nb_eat_time = 0;
		data->philo[i - 1].time_last_eat = 0;
		i--;
	}
	return data;
}

t_init *init_forks(t_init *data)
{
	int i;

	i = data->nb_of_philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (data->forks == NULL)
		return NULL;
	while (i > 0)
	{
		pthread_mutex_init(&(data->forks[i - 1]), NULL);  // Utilisez (i - 1) pour l'indice
		data->philo[i - 1].left_fork_id = i - 1;  // Utilisez (i - 1) pour l'indice
		data->philo[i - 1].right_fork_id = i % data->nb_of_philo;  // Utilisez (i - 1) pour l'indice
		i--;
	}
	return data;
}

unsigned long int ft_get_time()
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return(-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_init *init, int id_phil, char *str)
{
	printf("%ld %d %s", (ft_get_time() - init->start_time), id_phil, str);
}

void	take_fork(t_init *init, t_philo *philo)
{
	pthread_mutex_lock(&(init->forks[philo->right_fork_id]));
	pthread_mutex_lock(&(init->forks[philo->left_fork_id]));
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
}

void	action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	philo[philo->id_philo].time_last_eat = ft_get_time();
	philo[philo->id_philo].nb_eat_time++;
	// usleep(init->time_to_eat * 1000);
	
	pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
}

void action_sleep(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is sleeping\n");
	// usleep(init->time_to_sleep * 1000);
	// printf("id philo = %d\n", philo->id_philo);
}

void	action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
}

static void *philo_life(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	take_fork(data->init, data->philo);
	action_eat(data->init, data->philo);
	action_sleep(data->init, data->philo);
	action_think(data->init, data->philo);
	return (NULL);
}

int start_threads(t_init *init)
{
	int					i;
	t_data				*data;
	unsigned long int	time_init;

	time_init = ft_get_time();

	i = init->nb_of_philo - 1;
	while(i >= 0)
	{
		data = malloc(sizeof(t_data));
		if(!data)
			return(0);
		data->init = init;
		data->philo = &init->philo[i];
		data->init->start_time = time_init;
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		i--;
	}
	return(0);
}

int main(int ac, char **av)
{
	t_init *data = malloc(sizeof(t_init));  // Allouer de la mémoire pour data
	if (data == NULL)
	{
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	free(data);  // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}

