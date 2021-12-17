/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 23:26:53 by gariadno          #+#    #+#             */
/*   Updated: 2021/12/16 03:41:20 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_settings	sett;

	memset(&sett, '\0', sizeof(sett));
	if (!setup(--argc, ++argv, &sett))
		return (1);
	if (!start_banquet(&sett))
		return (1);
	return (free_everything(&sett));
}
