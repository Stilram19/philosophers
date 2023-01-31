/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:26:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/31 16:21:25 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (detecting_fallacies(argc, argv, (t_sophia *)&args))
		return (EXIT_FAILURE);
	if (!(args.philo_num))
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
