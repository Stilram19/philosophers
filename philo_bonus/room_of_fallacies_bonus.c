/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_of_fallacies_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:40:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 16:36:23 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

t_sophia	safe_atoi(char *str)
{
	t_sophia	ret;

	ret = NIHIL;
	if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		ret *= 10;
		ret += (*str - 48);
		str++;
	}
	return (ret);
}

t_sophia	digit_test(char *arg)
{
	t_sophia	digit_existence;

	digit_existence = NIHIL;
	if (*arg == '+')
		arg++;
	while (*arg)
	{
		if (*arg < 48 || *arg > 57)
			return (INVALID);
		digit_existence = EXIST;
		arg++;
	}
	return (digit_existence);
}

t_sophia	extrem_test(char *arg)
{
	if (*arg == '+')
		arg++;
	if (ft_strlen(arg) < 10
		|| (ft_strlen(arg) == 10 && ft_strncmp(arg, EXTREM, 10) < 0))
		return (VALID);
	return (INVALID);
}

t_sophia	detecting_fallacies(int argc, char **argv, t_args *args)
{
	t_sophia	i;
	t_sophia	boolean;
	t_sophia	*ptr_to_field;

	i = 0;
	boolean = VALID;
	ptr_to_field = (t_sophia *)args;
	if (argc != 5 && argc != 6)
		return (ERROR);
	while (boolean && ++i < argc)
	{
		if (boolean)
			boolean = digit_test(*(argv + i));
		if (boolean)
			boolean = extrem_test(*(argv + i));
		if (boolean)
			*ptr_to_field = safe_atoi(*(argv + i));
		ptr_to_field++;
	}
	if (argc != 6)
		args->meals_num = -1;
	return (!boolean);
}
