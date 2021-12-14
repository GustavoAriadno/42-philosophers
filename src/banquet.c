/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:26:18 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/14 03:47:37 by gariadno         ###   ########.fr       */
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

int	eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->sett->forks[phi->rfork]);
	print_status(phi, TAKEN_FORK);
	pthread_mutex_lock(&phi->sett->forks[phi->lfork]);
	print_status(phi, TAKEN_FORK);
	phi->lastmeal = get_now() + phi->sett->tteat;
	print_status(phi, EATING);
	if (death_during(phi, phi->sett->tteat))
	{
		pthread_mutex_unlock(&phi->sett->forks[phi->rfork]);
		pthread_mutex_unlock(&phi->sett->forks[phi->lfork]);
		return (0);
	}
	pthread_mutex_unlock(&phi->sett->forks[phi->rfork]);
	pthread_mutex_unlock(&phi->sett->forks[phi->lfork]);
	phi->have_eaten++;
	return (1);
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
