/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:46:29 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/26 22:51:18 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "projectile.h"

// SCENARIO:
// function tick(env, proj)
// position ← proj.position + proj.velocity
// velocity ← proj.velocity + env.gravity + env.wind
// return projectile(position, velocity)
// end function

//NORMALIZE velocity to control: * scalar :
//WITHOUT NORMALIZING :return (t_projectile){position, velocity};
t_projectile	projectile_create(t_tuple position, t_tuple velocity)
{
	t_tuple			norm_velocity;

	norm_velocity = normalize_vector(velocity);
	return ((t_projectile){position, norm_velocity});
}

t_projectile	tick(t_environment env, t_projectile proj)
{
	t_tuple			new_pos;
	t_tuple			acceleration;
	t_tuple			new_vel;

	new_pos = add(proj.position, proj.velocity);
	acceleration = add(env.gravity, env.wind);
	new_vel = add(proj.velocity, acceleration);
	return ((t_projectile){new_pos, new_vel});
}
