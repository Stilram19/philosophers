/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:26:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/05 17:29:06 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

/*void	ft_display(t_args *args)
{
	printf("%d\n", args->philo_num);
	printf("%d\n", args->time_to_die);
	printf("%d\n", args->time_to_eat);
	printf("%d\n", args->time_to_sleep);
	printf("%d\n", args->meals_num);
}*/

int	main(int argc, char **argv)
{
	t_args	args;

	if (detecting_fallacies(argc, argv, &args))
		return (EXIT_FAILURE);
	simulation(&args);
	//system("leaks philo_bonus");
	return (EXIT_SUCCESS);
}
