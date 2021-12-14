/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 23:04:35 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/14 03:47:17 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->sett->print);
	if (!philo->sett->someone_died)
		printf("%6ld %3d %s\n", get_now() - philo->sett->sim_start,
			philo->id, status);
	pthread_mutex_unlock(&philo->sett->print);
}

void	last_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->sett->print);
	philo->sett->someone_died++;
	if (philo->sett->someone_died == 1)
		printf("%6ld %3d died\n", get_now() - philo->sett->sim_start, philo->id);
	pthread_mutex_unlock(&philo->sett->print);
}

int	stop_sim(t_settings *sett)
{
	int			i;
	int			have_eaten_enough;
	long int	now;

	i = -1;
	have_eaten_enough = 0;
	while (++i < sett->nphilos)
	{
		now = get_now();
		if (!(now < sett->philos[i].lastmeal)
			&& now - sett->philos[i].lastmeal > sett->ttdie)
		{
			last_print(&sett->philos[i]);
			return (1);
		}
		if (sett->philos[i].have_eaten >= sett->tmust_eat)
			have_eaten_enough++;
	}
	if (sett->tmust_eat && have_eaten_enough == sett->nphilos)
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
