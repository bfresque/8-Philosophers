ok je veux que tume modifie la boucle while (1) pour qu'elle s'arrette si le nombre de repas number_must_eat est atteint par tout les philosophe et quil ai tous bien mange le nombre de fois demandé

typedef struct s_philo
{
	int id_philo;
	int nb_eat_time;
	long long time_last_eat;
	long long start_time;
	int left_fork_id;
	int right_fork_id;
	pthread_t thread_id;

	// struct s_init	*data;
	// pthread_mutex_t	left_fork_id;
	// pthread_mutex_t	*right_fork_id;
} t_philo;

typedef struct s_init
{
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_must_eat;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_mutex_t is_eat;
} t_init;

typedef struct s_data
{
	t_init *init;
	t_philo *philo;
} t_data;


t_init *init_data(t_init *data, char **av)
{
	data->nb_of_philo = ft_atoi_philo(av[1]);
	data->time_to_die = ft_atoi_philo(av[2]);
	data->time_to_eat = ft_atoi_philo(av[3]);
	data->time_to_sleep = ft_atoi_philo(av[4]);
	data->number_must_eat = ft_atoi_philo(av[5]);
	pthread_mutex_init(&data->is_eat, NULL);
	return data;
}


t_init *init_philo(t_init *data)
{
	int i;

	i = data->nb_of_philo -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (data->philo == NULL)
		return NULL;
	while (i >= 0)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].nb_eat_time = 0;
		data->philo[i].left_fork_id = i;
		data->philo[i].right_fork_id = (i + 1) % data->nb_of_philo;
		data->philo[i].time_last_eat = 0;
		i--;
	}
	return data;
}

t_init *init_forks(t_init *data)
{
	int i;

	i = data->nb_of_philo - 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (data->forks == NULL)
		return NULL;
	while (i >= 0)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i--;
	}
	return data;
}


long long	ft_get_time()
{
	struct timeval    current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);

	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	// 1 sec = 1 000 milisecondes
}

void	print(t_init *init, int id_phil, char *str)
{
	printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id_phil, str);
}

void check_death(t_init *init, t_philo *philo)
{
	unsigned long int current_time = ft_get_time();
	unsigned long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (unsigned long int)init->time_to_die)
	{
		print(init, philo->id_philo, " has died\n");
		pthread_exit(NULL);
	}
}

void	action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	usleep(init->time_to_eat);
	
	if (philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);

	}
	else
	{
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	}
	philo[philo->id_philo].nb_eat_time++;
	philo[philo->id_philo].time_last_eat = ft_get_time();
}

void take_fork(t_init *init, t_philo *philo)
{
    pthread_mutex_lock(&init->is_eat);
    if (philo->left_fork_id < philo->right_fork_id)
    {
        pthread_mutex_lock(&init->forks[philo->left_fork_id]);
        pthread_mutex_lock(&init->forks[philo->right_fork_id]);
    }
    else 
    {
        pthread_mutex_lock(&init->forks[philo->right_fork_id]);
        pthread_mutex_lock(&init->forks[philo->left_fork_id]);
    }
    print(init, philo->id_philo, " has taken a fork\n");
    print(init, philo->id_philo, " has taken a fork\n");
    pthread_mutex_unlock(&init->is_eat);
    action_eat(init, philo);
    
    pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
    pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
}

// void	action_sleep(t_init *init, t_philo *philo)
// {
// 	print(init, philo->id_philo, " is sleeping\n");
// 	usleep(init->time_to_sleep);
// }

//VERSION DE LILI

void action_sleep(t_init *init, t_philo *philo)
{
    print(init, philo->id_philo, " is sleeping\n");
    long long int start_sleep_time = ft_get_time();
    usleep(init->time_to_sleep);
    long long int end_sleep_time = ft_get_time();
    long long int sleep_duration = end_sleep_time - start_sleep_time;
    if (sleep_duration < init->time_to_sleep)
        usleep(init->time_to_sleep - sleep_duration);
}


void	action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
}

static void *philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	while (1)
	{
		take_fork(data->init, data->philo);
		check_death(data->init, data->philo);
		action_sleep(data->init, data->philo);
		check_death(data->init, data->philo);
		action_think(data->init, data->philo);
	}

	return NULL;
}

void start_threads(t_init *init)
{
	int					i;
	long long int	time_init;
	t_data				*data;

	time_init = ft_get_time();
 
	i = init->nb_of_philo - 1;
	while(i >= 0)
	{
		data = malloc(sizeof(t_data));
		if(!data)
			return;
		data->init = init;
		data->philo = &init->philo[i];
		data->init->philo->start_time = time_init;
		data->philo->time_last_eat = ft_get_time();
		// if ((init->philo[i].id_philo % 2) == 0)
		// {
		// 	usleep(50);
		// }
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		i--;
	}
	 i = init->nb_of_philo - 1;
	// pthread_join attend que tous les threads se terminent avant de continuer
	while (i >= 0) 
	{
		pthread_join(init->philo[i].thread_id, NULL);
		i--;
		if (init->philo[i].nb_eat_time < init->number_must_eat)
			break;
	}

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
	// free(data);  // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}
