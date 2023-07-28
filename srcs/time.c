/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:59:20 by yaidriss          #+#    #+#             */
/*   Updated: 2023/07/08 19:01:28 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

useconds_t	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(useconds_t time)
{
	useconds_t	start;

	start = philo_get_time();
	while (philo_get_time() - start < time)
		usleep(100);
	return (0);
}
