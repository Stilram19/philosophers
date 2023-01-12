/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:41:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/12 18:12:15 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

int	main(int argc, char **argv)
{
	t_global	g;

	detecting_fallacies(argc, argv, &(g.args));
	simulation_init(&g);
	create_philosophers(&g);
	monitoring(&g);
	simulation_destr(&g);
	return (0);
}
