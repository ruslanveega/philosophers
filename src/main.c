/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:16:33 by fcassand          #+#    #+#             */
/*   Updated: 2022/06/08 03:05:42 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_all	*info;

	info = malloc(sizeof(t_all));
	if (!info)
		return (error_message("allocation error", NULL));
	if (init_info(info, argv, argc))
		return (1);
	return (0);
}
