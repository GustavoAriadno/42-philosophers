/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 23:04:35 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/12 03:36:29 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print(char *str, long int x, long int y, t_settings *s)
{
	pthread_mutex_lock(&s->print);
	printf(str, x, y);
	pthread_mutex_unlock(&s->print);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->sett->print);
	if (!philo->sett->someone_died)
		printf("%6ld %3d %s\n", get_now()
			- philo->sett->sim_start, philo->id, status);
	pthread_mutex_unlock(&philo->sett->print);
}
