/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:38 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/03 10:25:27 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define MAX_EAT_TIMES 2

typedef struct s_philo
{
	int id_philo;
	int nb_eat_time;
	long long time_last_eat;
	long long start_time;
	int left_fork_id;
	int right_fork_id;
	pthread_t thread_id;
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
    int all_philo_finished;
} t_init;

typedef struct s_data
{
	t_init *init;
	t_philo *philo;
} t_data;

/*********************	libft_philo.c ***********************/
int	ft_atoi_philo(char *str);

/*********************	init.c ***********************/
t_init	*init_data(t_init *data, char **av);
t_init	*init_philo(t_init *data);
t_init	*init_forks(t_init *data);

void start_threads(t_init *data);


void *routine(void *arg);
#endif