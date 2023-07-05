jai un probleme pourquoi est ce que mon philo meurt alors que le programme devrait tourner indefiniment avec ces arguments:

sortie terminal :
➜  philo git:(main) ✗ ./philo 5 410 200 200                                       
0 1  has taken a fork
0 1  has taken a fork
0 1  is eating
0 3  has taken a fork
0 3  has taken a fork
0 3  is eating
200 3  is sleeping
200 1  is sleeping
200 2  has taken a fork
200 2  has taken a fork
200 2  is eating
200 5  has taken a fork
200 5  has taken a fork
200 5  is eating
400 3  is thinking
400 1  is thinking
400 5  is sleeping
400 4  has taken a fork
400 4  has taken a fork
400 1  has taken a fork
400 1  has taken a fork
400 1  is eating
400 4  is eating
400 2  is sleeping
600 3  has died

mon code :
typedef struct s_philo
{
	int id_philo;
	int nb_eat_time;
	long long time_last_eat;
	long long start_time;
	int left_fork_id;
	int right_fork_id;
	pthread_t thread_id;
	pthread_mutex_t eat_mutex;
} t_philo;

typedef struct s_init
{
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_must_eat;
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
	init->nb_of_philo = ft_atoi_philo(av[1]);
	init->time_to_die = ft_atoi_philo(av[2]);
	init->time_to_eat = ft_atoi_philo(av[3]);
	init->time_to_sleep = ft_atoi_philo(av[4]);
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
}

void action_sleep(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is sleeping\n");
	long long int start_sleep_time = ft_get_time();
	usleep(init->time_to_sleep * 1000);
	long long int end_sleep_time = ft_get_time();
	long long int sleep_duration = end_sleep_time - start_sleep_time;
	if (sleep_duration < init->time_to_sleep)
		usleep(init->time_to_sleep - sleep_duration);
}

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	philo->time_last_eat = ft_get_time();
	usleep(init->time_to_eat * 1000);
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
}

void take_fork(t_init *init, t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
	}
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
	action_eat(init, philo);
	pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
}

void *philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	int i = 1;
	if(data->init->number_must_eat > 0)
	{
		while (i <= data->init->number_must_eat)
		{
			take_fork(data->init, data->philo);
			if(i == data->init->number_must_eat)
				break;
			check_all_deaths(data->init);
			check_all_eat(data->init);
			action_sleep(data->init, data->philo);
			check_all_deaths(data->init);
			action_think(data->init, data->philo);
			check_all_deaths(data->init);
			i++;
		}
	}
	else if(data->init->number_must_eat < 0)
	{
		while (i)
		{
			take_fork(data->init, data->philo);
			check_all_deaths(data->init);
			action_sleep(data->init, data->philo);
			check_all_deaths(data->init);
			action_think(data->init, data->philo);
			check_all_deaths(data->init);
			i++;
		}
	}
	else
		exit(-1);
	return(NULL);
}

void start_threads(t_init *init)
{
	int i;
	long long int time_init;
	t_data *data;

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
	i = 0;
	while (i < init->nb_of_philo)
	{
		pthread_join(init->philo[i].thread_id, NULL);
		i++;
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
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	// free(data); // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}
