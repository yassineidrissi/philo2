/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:00:05 by yassine           #+#    #+#             */
/*   Updated: 2023/06/18 00:06:18 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handl_errors(int i)
{
	printf("\033[1;31m");
	printf("Error\n");
	if (i == 1)
		printf("Failed >> parametres unvalied \n");
	else if (i == 3)
		printf("Failed >> border unvalid\n");
	else if (i == 4)
		printf("Failed >> Upper / Lower boarder is not valid\n");
	else if (i == 5)
		printf("Failed >> side boarder not valid\n");
	else if (i == 6)
		printf("Failed >> reading error\n");
	else if (i == 7)
		printf("Failed >> Moved outside map boarder\n");
	else if (i == 8)
		printf("Failed >> No Valid Path \n");
	else if (i == 9)
		printf("Failed >> 1 or More of Required Element Missing  \n");
	else if (i == 10)
		printf("Failed >> No Valid Arguements! \n");
	printf("\033[0m");
	exit(0);
}