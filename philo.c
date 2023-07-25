/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:38:50 by yassine           #+#    #+#             */
/*   Updated: 2023/07/19 17:49:37 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_sleep(t_philo *philo)
// {
//     philo_timestamp(philo, PHILO_SLEEP);
//     ft_usleep(philo->data->tm_sleep);
// }

// void ft_think(t_philo *philo)
// {
//    philo_timestamp(philo, PHILO_THINK);
// }

// void ft_eat(t_philo *philo)
// {
//     philo_timestamp(philo, PHILO_EAT);
//     ft_usleep(philo->data->tm_eat);
// }

void*   start_thread(void* arg)
{
    t_philo *philo = (t_philo*)arg;

    pthread_mutex_lock(&philo->data->time);
    philo->last_meal = philo_get_time();
    pthread_mutex_unlock(&philo->data->time);
    if (philo->id % 2 == 0)
        usleep(300);
    while(1)
    {
        pthread_mutex_lock(&philo->data->fork[philo->id]);
        pthread_mutex_lock(&philo->data->fork[(philo->id + 1) % philo->data->nb_philo]);
        philo_timestamp(philo, PHILO_TAKE_FORK);
        philo_timestamp(philo, PHILO_EAT);//!need to craate my own speep function
        // philo->last_meal = philo_get_time();
        pthread_mutex_unlock(&philo->data->fork[philo->id]);
        pthread_mutex_unlock(&philo->data->fork[(philo->id + 1) % philo->data->nb_philo]);
        philo_timestamp(philo, PHILO_SLEEP);
        ft_usleep(philo->data->tm_sleep);
        philo_timestamp(philo, PHILO_THINK);
    }
    return NULL;
}

void ft_monitoring(t_data *data)
{
    int i;
    useconds_t eat_c;
    int meals;
    // useconds_t last_meal;
    i = -1;
    
    while(++i < data->nb_philo)
    {
        pthread_mutex_lock(&data->time);
        eat_c = philo_get_time() - data->philo[i].last_meal;
        pthread_mutex_unlock(&data->time);
        pthread_mutex_lock(&data->meal);
        meals = data->philo[i].nb_meals;
        pthread_mutex_unlock(&data->meal);
        // printf("im here the eat_c is %d and last_meal is %d, and philo id is %d\n", eat_c, data->philo[i].last_meal, data->philo[i].id);
        if (eat_c >=  data->tm_die || ( data->max_meals != -1 && meals >= data->max_meals))
        {
            printf("--%d , %d-- and i %d\n", eat_c, data->philo[i].last_meal, i);
            // pthread_mutex_lock(&data->writing);
            // meals = data->philo[i % data->nb_philo].nb_meals;
            pthread_mutex_lock(&data->lock);
            data->died = true;
            pthread_mutex_unlock(&data->lock);
            // pthread_mutex_lock(&data->writing);
            // printf("make im here\n");
            philo_timestamp(&data->philo[i], PHILO_DIE);
            pthread_mutex_unlock(&data->writing);
            return ;
            // pthread_mutex_unlock(&data->writing);
        }
        if (i == data->nb_philo - 1)
            i = -1;
        ft_usleep(100);
        // pthread_mutex_lock(&data->eat_count);
		// eat_c = philo->data->eat_count;
		// pthread_mutex_unlock(&philo->data->eat_count_lock);
		// pthread_mutex_lock(&philo->last_meal_lock);
		// last_meal = philo->last_meal;
		// pthread_mutex_unlock(&philo->last_meal_lock);
		// if (philo_get_time() - philo->data->init_time - last_meal >= \
		// 	philo->data->die_time || eat_c == \
		// 	philo->data->philo_count * philo->data->repeat_count)
		// {
		// 	pthread_mutex_lock(&philo->data->died_lock);
		// 	philo->data->died = 1;
		// 	pthread_mutex_unlock(&philo->data->died_lock);
		// 	if (eat_c != philo->data->philo_count * philo->data->repeat_count)
		// 		philo_timestamp(start, PHILO_DIE);
		// 	return (NULL);
		// }
    }
}

void init_threads(t_data * data)
{
    int i;

    i = -1;
    while (++i < data->nb_philo)
    {
        data->philo[i].last_meal = data->init_time;
        pthread_create(data->threads + i, NULL, start_thread, data->philo + i);
        // usleep(100);
        // pthread_detach(*(data->threads + i));
    }
    //! if there is a probleme sleep also here 
    // Pass the t_philo struct as the argument to the philosopher function
    // Wait for the threads to finish
    ft_monitoring(data);
}


int main(int ac, char **av)
{
    t_data data;

    if (ac != 6 && ac != 5)
        handl_errors(1);
    ft_parser(ac ,av, &data);
    // printf("initing threads the value of tm to eat is %d and for tm to sleep is %d\n", data.tm_die , data.tm_sleep);
    init_threads(&data);
    // ft_monitoring(&data);
    // printf("im working ");
}
