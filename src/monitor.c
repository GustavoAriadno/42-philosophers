/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:18:55 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/17 01:19:03 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_sim(t_settings *sett)
{
	int	i;
	int	have_eaten_enough;

	i = -1;
	have_eaten_enough = 0;
	while (++i < sett->nphilos)
	{
		if (get_now() - sett->philos[i].lastmeal > sett->ttdie)
		{
			print_status(&sett->philos[i], DIED);
			return (1);
		}
		if (sett->philos[i].have_eaten >= sett->tmust_eat)
			have_eaten_enough++;
	}
	if (sett->tmust_eat && have_eaten_enough == sett->nphilos)
		return (1);
	return (0);
}

void	*monitor_routine(void *param)
{
	t_settings	*sett;

	sett = param;
	while (!sett->stop_sim)
	{
		sett->stop_sim = stop_sim(sett);
		usleep(1000);
	}
	return (NULL);
}
