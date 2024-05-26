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

#include "philo.h"

int	ft_atoi(char *str, int *err)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[0] == 0)
		*err += ft_error(2);
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 44 - str[i++];
		if (str[i] == 0)
			*err += ft_error(2);
	}
	while (str[i] < 58 && str[i] > 47)
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	res = sign * res;
	if (str[i] != 0 || res > INT_MAX || res < INT_MIN || sign == -1)
		*err += ft_error(2);
	return ((int )res);
}

int	check_if_full(t_philo *tmp)
{
	int	i;
	int	num;

	num = tmp->ctl->num_of_philo;
	i = 0;
	while (tmp->eating_times >= tmp->ctl->num_eat && i <= num)
	{
		i++;
		tmp = tmp->next;
	}
	if (i >= tmp->ctl->num_of_philo)
		return (1);
	return (0);
}

void	ft_clean(t_philo *tmp, t_control *ctl, int num)
{
	int		i;
	t_philo	*tmp2;

	i = 0;
	while (i < num)
	{
		tmp2 = tmp->next;
		free(tmp);
		pthread_mutex_destroy(ctl->forks + i);
		tmp = tmp2;
		i++;
	}
	free(ctl->forks);
	free(ctl);
}
