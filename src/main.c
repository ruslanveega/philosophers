/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:16:33 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/15 03:45:07 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_all	*info;

	if (argc < 5 || argc > 6)
		return (error_massage("wrong number of arguments", NULL));
	info = malloc(sizeof(t_all));
	if (!info)
		return (error_massage("allocation error", info));
	if (init_info(info, argv, argc))
		return (1);
	start(info);
	mutex_destroy(info);
	free_info(info);
	return (0);
}
