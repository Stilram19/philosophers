/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_of_fallacies.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:28:13 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/31 11:25:26 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

t_sophia	safe_atoi(char *arg)
{
	t_sophia	ret;

	ret = NIHIL;
	if (*arg == '+') {
		arg++;
	}
	while (*arg >= 48 && *arg <= 57)
	{
		ret *= 10;
		ret += (*arg - 48);
		arg++;
	}
	return (ret);
}

t_sophia	extrem_test(char *arg)
{
	if (*arg == '+') {
		arg++;
	}
	if (ft_strlen(arg) > 10 || (ft_strlen(arg) == 10
			&& ft_strncmp(EXTREM, arg, 10) < 0))
		return (INVALID);
	return (VALID);
}

t_sophia	digits_test(char *arg)
{
	t_sophia	digit_existence;

	digit_existence = NIHIL;
	if (*arg == '+') {
		arg++;
	}
	while (*arg)
	{
		if (*arg < 48 || *arg > 57)
			return (INVALID);
		digit_existence = EXIST;
		arg++;
	}
	return (digit_existence);
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
		boolean = digits_test(*(argv + i));
		if (boolean) {
			boolean = extrem_test(*(argv + i));
			*ptr_to_field = safe_atoi(*(argv + i));
		}
		ptr_to_field++;
	}
	if (argc != 6) {
		args->number_of_meals = -1;
	}
	return (!boolean);
}
