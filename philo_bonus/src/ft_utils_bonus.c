/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:03:21 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/10 18:12:09 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_control *ctl)
{
	free(ctl);
	ft_error(2);
}

int	ft_atoi(char *str, t_control *ctl)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[0] == 0)
		clean_exit(ctl);
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 44 - str[i++];
		if (str[i] == 0)
			clean_exit(ctl);
	}
	while (str[i] < 58 && str[i] > 47)
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	res = sign * res;
	if (str[i] != 0 || res > INT_MAX || res < INT_MIN || sign == -1)
		clean_exit(ctl);
	return ((int )res);
}
