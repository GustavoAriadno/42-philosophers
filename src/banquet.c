/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:26:18 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/08 05:28:00 by gariadno         ###   ########.fr       */
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
	printf("%8ld %d %s", get_now() - philo->sett->sim_start, philo->id, status);
	pthread_mutex_unlock(&philo->sett->print);
}

void	*routine(void *param)
{
	t_philo	*phi;

	phi = param;
	print_status(phi, THINKING);
	return (NULL);
}

int	start_banquet(t_settings *sett)
{
	// pthread_detach RETURN PRA DA ERRO
	int	i;

	i = -1;
	sett->sim_start = get_now();
	while (++i < sett->nphilos)
		if (pthread_create(&sett->philos[i].thread, NULL, &routine, &sett->philos[i]))
			return (0);
	i = -1;
	while (++i < sett->nphilos)
		if (pthread_join(sett->philos[i].thread, NULL))
			return (0);
	return (1);
}
