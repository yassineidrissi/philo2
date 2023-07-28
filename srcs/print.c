/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:05:18 by yaidriss          #+#    #+#             */
/*   Updated: 2023/07/26 16:33:09 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_timestamp(t_philo *philo, char *action)
{
	useconds_t	time;

	pthread_mutex_lock(&philo->data->lock);
	time = philo_get_time() - philo->data->init_time;
	pthread_mutex_unlock(&philo->data->lock);
	if (action[10] == 'd')
	{
		pthread_mutex_lock(&philo->data->writing);
		printf("\033[1;39m%06u\033[0;39m  \033[1;96m%03d  \033[0;39m%s\n", time, \
			philo->id + 1, action);
		return ;
	}
	else
	{
		pthread_mutex_lock(&philo->data->writing);
		if (philo->data->died)
			return ;
		printf("\033[1;39m%06u\033[0;39m  \033[1;96m%03d  \033[0;39m%s\n", time, \
			philo->id + 1, action);
		pthread_mutex_unlock(&philo->data->writing);
		if (action[10] == 'e')
		{
			pthread_mutex_lock(&philo->data->meal);
			philo->nb_meals++;
			pthread_mutex_unlock(&philo->data->meal);
			pthread_mutex_lock(&philo->data->time);
			philo->last_meal = philo_get_time();
			pthread_mutex_unlock(&philo->data->time);
			ft_usleep(philo->data->tm_eat);
		}
	}
}
