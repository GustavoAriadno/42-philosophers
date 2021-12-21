/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 23:04:35 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/22 00:02:52 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print_status(long int now, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->sett->print);
	if (!philo->sett->stop_sim)
		printf("%6ld %3d %s\n", now - philo->sett->sim_start,
			philo->id, status);
	pthread_mutex_unlock(&philo->sett->print);
}
