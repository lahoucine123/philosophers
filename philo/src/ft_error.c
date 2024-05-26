/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:50:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 16:17:06 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usage(void)
{
	write(2, "Error: Syntax error\n", 21);
	write(2, "Usage: ./philo [ARGUMENTS]...\n", 31);
	write(2, "\nARGUMENTS:\n", 13);
	write(2, "    ARG1:\tnumber_of_philosophers\n", 34);
	write(2, "    ARG2:\ttime_to_die\n", 23);
	write(2, "    ARG3:\ttime_to_eat\n", 23);
	write(2, "    ARG4:\ttime_to_sleep\n", 25);
	write(2, "    OPTIONAL:\tnumber_of_times_each_philosopher_must_eat\n", 57);
}

int	ft_error(int opt)
{
	if (opt == 1)
		ft_usage();
	if (opt == 2)
		write(2, "Error: Invalid argument\n", 25);
	if (opt == 3)
		write(2, "Error: you need at least one philosopher\n", 42);
	return (1);
}
