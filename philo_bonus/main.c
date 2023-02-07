/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:26:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/07 10:21:09 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (detecting_fallacies(argc, argv, &args))
		return (EXIT_FAILURE);
	simulation(&args);
	return (EXIT_SUCCESS);
}
