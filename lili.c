comment je peux rappeler la structure init dans ma fonction routine sans perdre les donnees qui sont 


typedef struct s_philo
{
	int				id_philo;
	int				nb_eat_time;
	pthread_mutex_t	left_fork_id;
	pthread_mutex_t	right_fork_id;
	unsigned long	time_last_eat;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_init
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	unsigned long	start_time;
	pthread_mutex_t	is_eat;
	t_philo			*philo;
}	t_init;

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

t_init *init_data(t_init *data, char **av)
{
	data = malloc(sizeof(t_init));
	if(!data)
		return(0);
	data->nb_of_philo = ft_atoi_philo(av[1]);
	data->time_to_die = ft_atoi_philo(av[2]);
	data->time_to_eat = ft_atoi_philo(av[3]);
	data->time_to_sleep = ft_atoi_philo(av[4]);
	data->number_must_eat = ft_atoi_philo(av[5]);

	printf("%s INIT DATA \n", MAGENTA);
	printf("nb_of_philo = %d\n", data->nb_of_philo);
	printf("time_to_die = %d\n", data->time_to_die);
	printf("time_to_eat = %d\n", data->time_to_eat);
	printf("time_to_sleep = %d\n", data->time_to_sleep);
	printf("nb_must_eat = %d\n", data->number_must_eat);
	printf("** END INIT DATA **\n\n%s", RESET);
	return(data);
}

t_init *init_philo(t_init *data)
{
	int i;

	i = data->nb_of_philo;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if(data->philo == NULL)
		return(0);
	while(i > 0)
	{
		data->philo[i].id_philo = i;
		data->philo[i].nb_eat_time = 0;
		// data->philo[i].left_fork_id= i;
		// data->philo[i].right_fork_id = (i + 1) % data->nb_of_philo;
		data->philo[i].time_last_eat = 0;

		printf("%s***** INIT PHILO nb : '%d' *****\n", BLUE, i);
		printf("philo_id = %d\n", data->philo[i].id_philo);
		printf("nb_time_eat = %d\n", data->philo[i].nb_eat_time);
		// printf("right_fork_id = %d\n", data->philo[i].left_fork_id);
		// printf("left_fork_id = %d\n", data->philo[i].right_fork_id );
		printf("time_last_eat = %ld\n", data->philo[i].time_last_eat);
		printf("i = %d\n", i);
		printf("** END INIT PHILO **\n\n%s", RESET);
		i--;
	}
	return(data);
}

unsigned long int ft_get_time()
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return(-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;int main(int ac, char **av)
{
	t_init *data;
	data = malloc(sizeof(t_init));  // Allouer de la mémoire pour data
	if (data == NULL) {
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}
	data = init_data(data, av);
	data = init_philo(data);
	start_threads(data);
	free(data);  // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}


	time = ft_get_time();
	while (ft_get_time() - time < (unsigned long int)ms)
		usleep(ms / 10);
}

void	print(t_philo *philo, t_init *data, char *str)
{
	printf("%ld %d %s", (ft_get_time() - data->start_time), philo->id_philo, str);
}

void routine(t_philo *philo, t_init *data)
{
	print(philo, data, " is sleeping\n");
	ft_usleep(data->time_to_sleep);
	// print(philo, " is thinking\n");
}

static void *philo_life(void *arg)
{
	t_philo	*philo;
	t_init *data;

	philo = (t_philo *)arg;
	data = (t_init *)arg;
	routine(philo, data);
	return (NULL);
}

int start_threads(t_init *data)
{
	int i;

	i = 1;
	data->start_time = ft_get_time();
	printf("%s INIT DATA \n", GREEN);
	printf("nb_of_philo = %d\n", data->nb_of_philo);
	printf("time_to_die = %d\n", data->time_to_die);
	printf("time_to_eat = %d\n", data->time_to_eat);
	printf("time_to_sleep = %d\n", data->time_to_sleep);
	printf("nb_must_eat = %d\n", data->number_must_eat);
	printf("time of start = %ld\n", data->start_time);
	printf("** END INIT DATA **\n\n%s", RESET);
	while(i < data->nb_of_philo)
	{
		data->philo[i].time_last_eat = ft_get_time();
		if(pthread_create(&data->philo[i].thread_id, NULL, philo_life, &data->philo[i]))
		i++;
	}
	return(0);
}

int main(int ac, char **av)
{
	t_init *data;
	data = malloc(sizeof(t_init));  // Allouer de la mémoire pour data
	if (data == NULL) {
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}
	data = init_data(data, av);
	data = init_philo(data);
	start_threads(data);
	free(data);  // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}
void    run_routine_philo(t_init *init)
{
    int    i;
    long long time_init;
    t_data *data;

    // j init mon time ici
    time_init = get_time_philo();

    // creation des threads par philosophers
    i = init->nb_of_philo - 1;
    while(i >= 0)
    {
        data = malloc(sizeof(t_data));
        if (data == NULL)
        {
            // faire des free ou autre pour mettre fin
            return;
        }
        data->init = init;
        data->philo = &init->philo[i];
        data->philo->time_init = time_init;
        // data->philo[i].init_data = init; // utile ? 
        pthread_create(&init->philo[i].thread_philo, NULL, thread_routine, data);
        i--;
    }
    
    i = init->nb_of_philo - 1;
    // pthread_join attend que tous les threads se terminent avant de continuer
    while (i >= 0) 
    {
        pthread_join(init->philo[i].thread_philo, NULL);
        i--;
    }
}