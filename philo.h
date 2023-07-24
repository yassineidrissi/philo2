/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:42:31 by yassine           #+#    #+#             */
/*   Updated: 2023/07/19 15:40:01 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define PHILO_EAT "\033[1;93mis eating\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork\033[0;39m"
# define PHILO_DIE "\033[1;91mdied\033[0;39m"
# define ERR_USAGE "Usage: ./philo <nb philosophers> <time to die> <time to eat>\
 <time to sleep> [optional :times each philosopher must eat]\n"
# define UNLOCK 1
# define LOCK 0

typedef struct s_philo
{
    int id;
    int nb_meals;
    useconds_t last_meal;
    struct s_data *data;
}t_philo;

typedef struct s_data
{
    useconds_t init_time;
    int nb_philo;
    int max_meals;
    int tm_sleep;
    useconds_t tm_eat;
    bool died;
    useconds_t tm_die;
    unsigned long last_meal;
    pthread_t threads[250];    
    pthread_mutex_t fork[250];
    pthread_mutex_t	meal;
	pthread_mutex_t	writing;
    pthread_mutex_t	death;
    pthread_mutex_t lock;
    pthread_mutex_t time;
    t_philo philo[250];
}t_data;

//********philo_srcs************///
void ft_parser(int ac, char ** av, t_data *data);
void handl_errors(int i);
void ft_fill_params_master(int ac, char **av, t_data *data);
void ft_fill_params_slive(int ac, t_data *data, char **av, int i);
void* start_thread(void* arg);
void init_threads(t_data * data);
// useconds_t get_time(void);
int ft_usleep(useconds_t time);
void philo_timestamp(t_philo *philo, char *action);
useconds_t	philo_get_time(void);
//********lib_srcs************///
int ft_isdigit(char c);
int ft_strisdigit(char *str);
int ft_atoi(char *str);


#endif
