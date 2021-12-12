/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:27:06 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/12 03:35:37 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_sim(t_settings *sett)
{
	int			i;
	int			every_one_have_eaten_enough;
	long int	now;

	i = -1;
	every_one_have_eaten_enough = 0;
	while (++i < sett->nphilos)
	{
		now = get_now();
		if (!(now < sett->philos[i].lastmeal)
			&& now - sett->philos[i].lastmeal > sett->ttdie)
		{
			print_status(&sett->philos[i], DIED);
			sett->someone_died = 1;
			return (1);
		}
		if (sett->philos[i].have_eaten >= sett->tmust_eat)
			every_one_have_eaten_enough++;
	}
	if (sett->tmust_eat && every_one_have_eaten_enough == sett->nphilos)
		return (1);
	return (0);
}

int	death_during(t_philo *phi, int action_time)
{
	long int	duration;

	if (phi->sett->someone_died)
		return (1);
	duration = get_now() + action_time;
	while (get_now() < duration)
	{
		if (stop_sim(phi->sett))
			return (1);
		usleep(1000);
	}
	return (0);
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
