/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:30:45 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/08 13:49:04 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef struct s_philo
{
	int				id_philo;
	int				nb_eat_time;
	long long		time_last_eat;
	long long		start_time;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread_id;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	mutex_time_last_eat;
	struct s_data	*data;
}				t_philo;

typedef struct s_init
{
	int				flag_eat;
	int				flag_death;
	int				death_printed;
	int				time_to_think;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				all_philo_finished;
	t_philo			*philo;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_printed_mutex;
}				t_init;

typedef struct s_data
{
	t_init	*init;
	t_philo	*philo;
}				t_data;

int    check_flag_died(t_init *init);

/*********************	action.c ***********************/
void		action_think(t_init *init, t_philo *philo);
void		action_sleep(t_init *init, t_philo *philo);
void		take_fork(t_init *init, t_philo *philo);

/*********************	check.c ***********************/
int			check_all_deaths(t_init *init, t_philo *philo);
void		check_death(t_init *init, t_philo *philo);
int			check_all_eat(t_init *init);
int			check_numbers(int argc, char **argv);

/*********************	init.c ***********************/
t_init		*init_data(t_init *data, char **av);
t_init		*init_philo(t_init *init);
t_init		*init_forks(t_init *init);

/*********************	routine.c ***********************/
void		start_threads(t_init *data);

/*********************	utils.c ***********************/
int			ft_atoi_philo(char *str);
long long	ft_get_time(void);
void		print(t_init *init, int id, char *str);
void		philo_just_one(t_init *init, char **av);
void		ft_close(t_init *init);

#endif