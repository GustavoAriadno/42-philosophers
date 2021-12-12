/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:26:18 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/12 03:37:33 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonephilo(t_philo *phi)
{
	pthread_mutex_lock(&phi->sett->forks[phi->rfork]);
	print_status(phi, TAKEN_FORK);
	usleep(phi->sett->ttdie * 1000);
	print_status(phi, THINKING);
	print_status(phi, DIED);
	return (NULL);
}

void	*routine(void *param)
{
	t_philo	*phi;

	phi = param;
	if (phi->sett->nphilos == 1)
		return (lonephilo(phi));
	if (phi->id % 2 == 0)
		usleep(500);
	while (!phi->sett->someone_died)
	{
		print_status(phi, THINKING);
		if (!eat(phi))
			break ;
		print_status(phi, SLEEPING);
		if (death_during(phi, phi->sett->ttsleep))
			break ;
	}
	return (NULL);
}

int	start_banquet(t_settings *s)
{
	int	i;

	i = -1;
	s->sim_start = get_now();
	while (++i < s->nphilos)
		if (pthread_create(&s->philos[i].thread, NULL, &routine, &s->philos[i]))
			return (free_everything(s));
	i = -1;
	while (++i < s->nphilos)
		if (pthread_join(s->philos[i].thread, NULL))
			return (free_everything(s));
	return (1);
}
