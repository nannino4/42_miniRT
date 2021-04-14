/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_square_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:20:27 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/14 15:21:16 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	move_square(void *param, t_v axis)
{
	t_square	*square;

	square = (t_square *)param;
	square->c = v_sum(square->c, v_scalar_mul(axis, MOVE_EPSILON));
}
