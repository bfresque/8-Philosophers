peux tu maider a resoudre les leaks stp 

voici les leaks :
➜  philo git:(main) ✗ valgrind --leak-check=full --show-leak-kinds=all ./philo 2 310 200 1
==505547== Memcheck, a memory error detector
==505547== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==505547== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==505547== Command: ./philo 2 310 200 1
==505547== 
41 1  has taken a fork
49 1  has taken a fork
49 1  is eating
255 1  is sleeping
257 2  has taken a fork
257 2  has taken a fork
258 2  is eating
259 1  is thinking
461 1  died
==505547== 
==505547== HEAP SUMMARY:
==505547==     in use at exit: 656 bytes in 5 blocks
==505547==   total heap usage: 8 allocs, 3 frees, 2,008 bytes allocated
==505547== 
==505547== 32 bytes in 2 blocks are still reachable in loss record 1 of 3
==505547==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==505547==    by 0x10A005: start_threads (routine.c:75)
==505547==    by 0x109E0C: main (philo.c:35)
==505547== 
==505547== 80 bytes in 1 blocks are definitely lost in loss record 2 of 3
==505547==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==505547==    by 0x109CEF: init_forks (init.c:67)
==505547==    by 0x109DFC: main (philo.c:34)
==505547== 
==505547== 544 bytes in 2 blocks are possibly lost in loss record 3 of 3
==505547==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==505547==    by 0x40147D9: calloc (rtld-malloc.h:44)
==505547==    by 0x40147D9: allocate_dtv (dl-tls.c:375)
==505547==    by 0x40147D9: _dl_allocate_tls (dl-tls.c:634)
==505547==    by 0x4909834: allocate_stack (allocatestack.c:430)
==505547==    by 0x4909834: pthread_create@@GLIBC_2.34 (pthread_create.c:647)
==505547==    by 0x10A0AB: start_threads (routine.c:82)
==505547==    by 0x109E0C: main (philo.c:35)
==505547== 
==505547== LEAK SUMMARY:
==505547==    definitely lost: 80 bytes in 1 blocks
==505547==    indirectly lost: 0 bytes in 0 blocks
==505547==      possibly lost: 544 bytes in 2 blocks
==505547==    still reachable: 32 bytes in 2 blocks
==505547==         suppressed: 0 bytes in 0 blocks
==505547== 
==505547== For lists of detected and suppressed errors, rerun with: -s
==505547== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

'
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
	pthread_mutex_t death_mutex;
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
	// pthread_mutex_t print;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
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

	if(ft_atoi_philo(av[1]) == 1)
		philo_just_one(init, av);
	init->nb_of_philo = ft_atoi_philo(av[1]);
	init->time_to_die = ft_atoi_philo(av[2]);
	init->time_to_eat = ft_atoi_philo(av[3]);
	init->time_to_sleep = ft_atoi_philo(av[4]);
	t_to_th = (init->time_to_die - (init->time_to_eat + init->time_to_sleep)) / 2;
	if (t_to_th < 0)
		t_to_th = 0;
	init->time_to_think = t_to_th;
	if(av[5])
		init->number_must_eat = ft_atoi_philo(av[5]);
	else
		init->number_must_eat = -1;
	init->all_philo_finished = 0;
	pthread_mutex_init(&(init->print_mutex), NULL);
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
	pthread_mutex_lock(&(init->print_mutex));
	printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id_phil, str);
	if(str[1] == 'd')
	{
		ft_close(init);
		exit(-1);
	}
	pthread_mutex_unlock(&(init->print_mutex));
}


void check_death(t_init *init, t_philo *philo)
{
	long long int current_time = ft_get_time();
	long long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (long long int)init->time_to_die)
	{
		pthread_mutex_init(&(philo->death_mutex), NULL);
		pthread_mutex_lock(&(philo->death_mutex));
		print(init, philo->id_philo, " died\n");
		// exit(1);
		pthread_mutex_unlock(&(philo->death_mutex));
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void	ft_close(t_init *init)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&init->print_mutex);
	pthread_mutex_destroy(&init->philo->eat_mutex);
	pthread_mutex_destroy(&init->philo->death_mutex);

	while(i < init->nb_of_philo)
	{
		if(init->philo != NULL)
			pthread_mutex_destroy(&init->forks[i]);
		i++;
	}
	
	free(init->philo);
	free(init);
	// // while (++i < data->nb_of_philo)
	// {
	// 	if (NULL != data->ware)
	// 		pthread_mutex_destroy(&data->ware[i]);
	// 	if (NULL != data->philos)
	// 		pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
	// }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		ft_close(init);
		exit(1);
		return 1;
	}
	return -1;
}

int help_verif_numbers(const char *str)
{
	int len = strlen(str);
	int i = 0;

	while (i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}

	int num = atoi(str);
	if (num <= 0)
		return 0;
	return 1;
}

int check_numbers(int argc, char **argv)
{
	int i = 1;

	while (i < argc)
	{
		if (!help_verif_numbers(argv[i]))
			return 0;
		i++;
	}
	return 1;
}

void	philo_just_one(t_init *init, char **av)
{
	free(init);
	usleep(ft_atoi_philo(av[2]) * 1000);
	printf("%d 1 died\n", ft_atoi_philo(av[2]) + 1);
	exit(1);
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
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	usleep(init->time_to_eat * 1000);
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
	// usleep(100);
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
	// usleep(100);
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
	t_data	*data; //jamais free

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
		pthread_join(init->philo[i].thread_id, NULL);
	free(data);
}

int main(int ac, char **av)
{
	t_init *data ;

	if (ac != 5 && ac != 6)
	{
		printf("Error: number of arguments\n");
		return(0);
	}
	if (!check_numbers(ac, av))
	{
		printf("Error: All arguments must be positive integers.\n");
		return(0);
	}
	data = malloc(sizeof(t_init));
	if (data == NULL)
		return 1;
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	free(data);
	return(0);
}
