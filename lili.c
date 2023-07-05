pourquoi mon code ne marche pas pour un philo quand en argument je mets 1 philo ca beug

typedef struct s_philo
{
	int	id_philo;
	int	nb_eat_time;
	long	long time_last_eat;
	long	long start_time;
	int	left_fork_id;
	int	right_fork_id;
	pthread_t thread_id;
	pthread_mutex_t eat_mutex;
} t_philo;

typedef struct s_init
{
	int	time_to_think;
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_must_eat;
	t_philo *philo;
	pthread_mutex_t print;
	pthread_mutex_t *forks;
	int all_philo_finished;
} t_init;

typedef struct s_data
{
	t_init *init;
	t_philo *philo;
} t_data;

t_init *init_data(t_init *init, char **av)
{
	int t_to_th;

//verifier qu'en entree les arguments soit bien des nombres positifs
	init->nb_of_philo = ft_atoi_philo(av[1]);
	init->time_to_die = ft_atoi_philo(av[2]);
	init->time_to_eat = ft_atoi_philo(av[3]);
	init->time_to_sleep = ft_atoi_philo(av[4]);
	t_to_th = (init->time_to_die - (init->time_to_eat + init->time_to_sleep)) / 2;
	if (t_to_th < 0)
		t_to_th = 0;
	if (1 == init->nb_of_philo)
		t_to_th = -1;
	init->time_to_think = t_to_th;
	if(av[5])
		init->number_must_eat = ft_atoi_philo(av[5]);
	else
		init->number_must_eat = -1;
	init->all_philo_finished = 0;
	return init;
}

t_init *init_philo(t_init *init)
{
	int i;

	i = init->nb_of_philo -1;
	init->philo = malloc(sizeof(t_philo) * init->nb_of_philo);
	if (init->philo == NULL)
		return NULL;
	while (i >= 0)
	{
		init->philo[i].id_philo = i + 1;
		init->philo[i].nb_eat_time = 0;
		init->philo[i].left_fork_id = i;
		init->philo[i].right_fork_id = (i + 1) % init->nb_of_philo;
		init->philo[i].time_last_eat = 0;
		pthread_mutex_init(&(init->philo[i].eat_mutex), NULL);
		i--;
	}
	return init;
}

t_init *init_forks(t_init *init)
{
	int i;

	i = 0;
	init->forks = malloc(sizeof(pthread_mutex_t) * init->nb_of_philo);
	if (init->forks == NULL)
		return NULL;
	while (i < init->nb_of_philo)
	{
		pthread_mutex_init(&(init->forks[i]), NULL);
		i++;
	}
	return init;
}

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
	printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id_phil, str);
}

void check_death(t_init *init, t_philo *philo)
{
	long long int current_time = ft_get_time();
	long long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (long long int)init->time_to_die)
	{
		print(init, philo->id_philo, " has died\n");
		exit(1);
	}
}

void check_all_deaths(t_init *init)
{
	int i = 0;
	while (i < init->nb_of_philo)
	{
		check_death(init, &init->philo[i]);
		i++;
	}
}

int check_all_eat(t_init *init)
{
	int i = 0;
	init->all_philo_finished = 0;
	while (i < init->nb_of_philo)
	{
		pthread_mutex_lock(&(init->philo[i].eat_mutex));
		if (init->philo[i].nb_eat_time == init->number_must_eat)
			init->all_philo_finished++;
		pthread_mutex_unlock(&(init->philo[i].eat_mutex));
		i++;
	}
	if (init->all_philo_finished < init->nb_of_philo)
		return 0;
	else if (init->all_philo_finished == init->nb_of_philo)
	{
		exit(1);
		return 1;
	}
	return -1;
}

void action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
	usleep(init->time_to_think * 1000);
}

void action_sleep(t_init *init, t_philo *philo)
{
	long long int start_sleep_time;
	long long int end_sleep_time;
	long long int sleep_duration;

	print(init, philo->id_philo, " is sleeping\n");
	start_sleep_time = ft_get_time();
	usleep(init->time_to_sleep * 1000);
	end_sleep_time = ft_get_time();
	sleep_duration = end_sleep_time - start_sleep_time;
	if (sleep_duration < init->time_to_sleep)
		usleep(init->time_to_sleep - sleep_duration);
}

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	philo->time_last_eat = ft_get_time();
	pthread_mutex_lock(&(philo->eat_mutex));//ne pas toucher
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex)); //ne pas toucher

	usleep(init->time_to_eat * 1000); //mit a la fin ca marche super mais cest interdit 
	if(philo->id_philo % 2 == 0)
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

void take_fork(t_init *init, t_philo *philo)
{
	// if (philo->id_philo % 2 == 0)
	// {
	// 	usleep(50);
	// }
	if(philo->id_philo % 2 == 0)
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
	action_eat(init, philo);
}

void	routine_one(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= init->number_must_eat)
	{
		take_fork(init, philo);
		if(i == init->number_must_eat)
			break;
		check_all_deaths(init);
		check_all_eat(init);
		action_sleep(init, philo);
		check_all_deaths(init);
		action_think(init, philo);
		check_all_deaths(init);
		i++;
	}
}

void	routine_two(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i)
	{
		take_fork(init, philo);
		check_all_deaths(init);
		action_sleep(init, philo);
		check_all_deaths(init);
		action_think(init, philo);
		check_all_deaths(init);
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	if(data->init->number_must_eat > 0)
		routine_one(data->init, data->philo);
	else if(data->init->number_must_eat < 0)
		routine_two(data->init, data->philo);
	else
		exit(-1);
	return(NULL);
}

void	start_threads(t_init *init)
{
	int	i;
	long long int	time_init;
	t_data	*data;

	time_init = ft_get_time();
	i = 0;
	while (i < init->nb_of_philo)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return;
		data->init = init;
		data->philo = &init->philo[i];
		data->init->philo->start_time = time_init;
		data->philo->time_last_eat = ft_get_time();
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		i++;
	}
	i = -1;
	while (i++ < init->nb_of_philo)
	{
		pthread_join(init->philo[i].thread_id, NULL);
	}
}

int main(int ac, char **av)
{
	t_init *data = malloc(sizeof(t_init));
	if (data == NULL)
	{
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}

	if (ac != 5 && ac != 6)
	{
		printf("Error: number of arguments\n");
		free(data);
		return(0);
	}
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	free(data); // Libérer la mémoire une fois que vous avez terminé avec data
	return 0;
}
