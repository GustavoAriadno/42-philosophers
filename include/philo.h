/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 23:27:06 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/12 01:08:39 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TESTE		"TESTANDO"
# define TAKEN_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

typedef pthread_mutex_t		t_pthrd_mtx;

typedef struct s_philo		t_philo;
typedef struct s_settings	t_settings;

struct	s_philo
{
	int			id;
	int			have_eaten;
	int			lfork;
	int			rfork;
	long int	lastmeal;
	pthread_t	thread;
	t_settings	*sett;
};

struct	s_settings
{
	long int	sim_start;
	int			someone_died;
	int			nphilos;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			tmust_eat;
	t_philo		*philos;
	t_pthrd_mtx	*forks;
	t_pthrd_mtx	print;
};

int			setup(int argc, char **argv, t_settings *sett);

int			start_banquet(t_settings *sett);

int			eat(t_philo *phi);
int			death_during(t_philo *phi, int action_time);


long int	get_now(void);
void		print(char *str, long int x, long int y, t_settings *s);
void		print_status(t_philo *philo, char *status);

int			basic_free(t_settings *sett);
int			free_n_philos(t_settings *sett, int n);
int			free_everything(t_settings *sett);

#endif