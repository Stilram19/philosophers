/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:41:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 16:58:41 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

int	main(int argc, char **argv)
{
	t_args	args;

	detecting_fallacies(argc, argv, &args);
	
	return (0);
}
