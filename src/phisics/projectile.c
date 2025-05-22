/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:46:29 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 22:22:33 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "projectile.h"

// t_projectile	tick(t_tuple env, t_tuple proj)

// function tick(env, proj)
// position ← proj.position + proj.velocity
// velocity ← proj.velocity + env.gravity + env.wind
// return projectile(position, velocity)
// end function


/*May be will see*/
// t_projectile	tick(t_environment env, t_projectile proj)
// {
// 	t_tuple new_position = add_two_tuples(proj.position, proj.velocity);
// 	t_tuple new_velocity = add_two_tuples(proj.velocity, add_two_tuples(env.gravity, env.wind));
// 	return (t_projectile){new_position, new_velocity};
// }

// t_projectile projectile_create(t_tuple pos, t_tuple vel) {
//     return (t_projectile){pos, vel};
// }

t_projectile tick(t_environment env, t_projectile proj) 
{
	t_tuple new_pos = add_two_tuples(proj.position, proj.velocity);
	t_tuple acceleration = add_two_tuples(env.gravity, env.wind);
	t_tuple new_vel = add_two_tuples(proj.velocity, acceleration);
	return (t_projectile){new_pos, new_vel};
}
