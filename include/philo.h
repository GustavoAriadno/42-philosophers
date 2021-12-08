/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 23:27:06 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/08 04:48:37 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKEN_FORK	"has taken a fork\n"
# define EATING		"is eating\n"
# define SLEEPING	"is sleeping\n"
# define THINKING	"is thinking\n"
# define DIED		"died\n"

typedef pthread_mutex_t pthrd_mtx_t;

typedef struct s_philo t_philo;
typedef struct s_settings t_settings;

struct	s_philo
{
	int			id;
	int			ate;
	int			lfork;
	int			rfork;
	long int	time;
	pthread_t	thread;
	t_settings	*sett;
};

struct	s_settings
{
	long int	sim_start;
	int			nphilos;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			tmust_eat;
	t_philo		*philos;
	pthrd_mtx_t	*forks;
	pthrd_mtx_t	print;
};

int	setup(int argc, char **argv, t_settings *sett);

int	start_banquet(t_settings *sett);

int	basic_free(t_settings *sett);
int	free_n_philos(t_settings *sett, int n);
int	free_everything(t_settings *sett);

#endif