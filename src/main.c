/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:16:33 by fcassand          #+#    #+#             */
/*   Updated: 2022/05/18 03:30:45 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_massage(char *str, t_all *info)
{
	printf("ERROR: %s\n", str);
	free(info);
	return (1);
}

int	init_info(t_all *info, char **av, int argc)
{
	if (argc != 5 || argc != 6)
 		return(error_message("wrong number of arguments", info));
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 ||
		ft_atoi(av[4]) <= 0)
		return (error_message("wrong arguments format", info));
	info->amount = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	*info;

	info = malloc(sizeof(t_all));
	if (init_info(info, argv, argc))
		return (1);
}
