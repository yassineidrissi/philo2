/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:38:50 by yassine           #+#    #+#             */
/*   Updated: 2023/07/26 16:32:15 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = philo_get_time();
	if (philo->id % 2 == 0)
	{
		philo_timestamp(philo, PHILO_THINK);
		usleep(200);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		philo_timestamp(philo, PHILO_TAKE_FORK);
		philo_timestamp(philo, PHILO_EAT);
		pthread_mutex_unlock(&philo->data->fork[philo->id]);
		pthread_mutex_unlock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		philo_timestamp(philo, PHILO_SLEEP);
		ft_usleep(philo->data->tm_sleep);
		philo_timestamp(philo, PHILO_THINK);
	}
	return (NULL);
}

void	ft_monitoring(t_data *data)
{
	int			i;
	useconds_t	eat_c;
	int			meals;

	i = -1;
	while (++i < data->nb_philo)
	{
		eat_c = philo_get_time() - data->philo[i].last_meal;
		meals = data->philo[i].nb_meals;
		if (eat_c >= data->tm_die)
		{
			pthread_mutex_lock(&data->lock);
			data->died = true;
			pthread_mutex_unlock(&data->lock);
			philo_timestamp(&data->philo[i], PHILO_DIE);
			return ;
		}
		if (data->max_meals != -1 && meals > data->max_meals)
			return ;
		if (i == data->nb_philo - 1)
			i = -1;
		ft_usleep(100);
	}
}

void	init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].last_meal = data->init_time;
		pthread_create(data->threads + i, NULL, start_thread, data->philo + i);
	}
	ft_monitoring(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 6 && ac != 5)
		handl_errors(1);
	ft_parser(ac, av, &data);
	init_threads(&data);
}
