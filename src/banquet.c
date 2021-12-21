/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:26:18 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/22 00:25:09 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonephilo(t_philo *phi)
{
	pthread_mutex_lock(&phi->sett->forks[phi->rfork]);
	print_status(get_now(), phi, TAKEN_FORK);
	print_status(get_now(), phi, THINKING);
	usleep(phi->sett->ttdie * 1000);
	print_status(get_now(), phi, DIED);
	phi->sett->stop_sim = 1;
	return (NULL);
}

void	eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->sett->forks[phi->rfork]);
	if (phi->sett->stop_sim)
	{
		pthread_mutex_unlock(&phi->sett->forks[phi->rfork]);
		return ;
	}
	print_status(get_now(), phi, TAKEN_FORK);
	pthread_mutex_lock(&phi->sett->forks[phi->lfork]);
	if (phi->sett->stop_sim)
	{
		pthread_mutex_unlock(&phi->sett->forks[phi->rfork]);
		pthread_mutex_unlock(&phi->sett->forks[phi->lfork]);
		return ;
	}
	print_status(get_now(), phi, TAKEN_FORK);
	phi->lastmeal = get_now();
	print_status(get_now(), phi, EATING);
	usleep(phi->sett->tteat * 1000);
	pthread_mutex_unlock(&phi->sett->forks[phi->rfork]);
	pthread_mutex_unlock(&phi->sett->forks[phi->lfork]);
	phi->have_eaten++;
}

void	*routine(void *param)
{
	t_philo	*phi;

	phi = param;
	if (phi->sett->nphilos == 1)
		return (lonephilo(phi));
	if (phi->id % 2 == 0)
		usleep(1600);
	while (!phi->sett->stop_sim)
	{
		eat(phi);
		if (phi->sett->stop_sim)
			break ;
		print_status(get_now(), phi, SLEEPING);
		usleep(phi->sett->ttsleep * 1000);
		if (phi->sett->stop_sim)
			break ;
		print_status(get_now(), phi, THINKING);
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
	if (pthread_create(&s->monitor, NULL, &monitor_routine, s))
		return (free_everything(s));
	i = -1;
	while (++i < s->nphilos)
		if (pthread_join(s->philos[i].thread, NULL))
			return (free_everything(s));
	if (pthread_join(s->monitor, NULL))
		return (free_everything(s));
	return (1);
}
