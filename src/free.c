/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:40:42 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/08 01:49:38 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	basic_free(t_settings *sett)
{
	free(sett->forks);
	free(sett->philos);
	pthread_mutex_destroy(&sett->print);
	return (0);
}

int	free_n_philos(t_settings *sett, int n)
{
	while (n != -1)
		pthread_mutex_destroy(&sett->forks[n--]);
	return (basic_free(sett));
}

int	free_everything(t_settings *sett)
{
	return (free_n_philos(sett, sett->nphilos - 1));
}
