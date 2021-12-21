/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:17:01 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/21 23:09:13 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	invalid_args(int argc, char **argv)
{
	int	i;

	while (argc--)
	{
		i = -1;
		while (argv[argc][++i])
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (1);
	}
	return (0);
}

int	miniatoi(char *str)
{
	int	res;

	res = 0;
	while (*str)
		res = res * 10 + *str++ - '0';
	return (res);
}

int	create_philos(t_settings *sett)
{
	int	i;

	i = 0;
	while (i < sett->nphilos)
	{
		sett->philos[i].id = i + 1;
		sett->philos[i].have_eaten = 0;
		sett->philos[i].rfork = i;
		sett->philos[i].lfork = i + 1;
		sett->philos[i].lastmeal = get_now();
		sett->philos[i].sett = sett;
		if (pthread_mutex_init(&sett->forks[i], NULL))
			return (free_n_philos(sett, i));
		i++;
	}
	sett->philos[i - 1].lfork = 0;
	return (1);
}

int	setup(int argc, char **argv, t_settings *sett)
{
	if ((argc != 4 && argc != 5) || invalid_args(argc, argv))
		return (0);
	sett->stop_sim = 0;
	sett->nphilos = miniatoi(argv[0]);
	sett->ttdie = miniatoi(argv[1]);
	sett->tteat = miniatoi(argv[2]);
	sett->ttsleep = miniatoi(argv[3]);
	if (sett->nphilos == 0 || sett->ttdie == 0
		|| sett->tteat == 0 || sett->ttsleep == 0)
		return (0);
	if (argv[4])
		sett->tmust_eat = miniatoi(argv[4]);
	if (argv[4] && sett->tmust_eat == 0)
		return (0);
	sett->philos = NULL;
	sett->forks = NULL;
	sett->philos = malloc(sett->nphilos * sizeof(t_philo));
	sett->forks = malloc(sett->nphilos * sizeof(pthread_mutex_t));
	if (!sett->philos || !sett->forks
		|| pthread_mutex_init(&sett->print, NULL))
		return (basic_free(sett));
	return (create_philos(sett));
}
