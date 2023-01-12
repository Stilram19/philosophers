/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:41:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/12 21:21:15 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

int	main(int argc, char **argv)
{
	t_args		a;

	detecting_fallacies(argc, argv, &a);
	simulation_init(&a);
	create_philosophers();
	superviser(&p);
	simulation_destr(&p);
	return (0);
}
