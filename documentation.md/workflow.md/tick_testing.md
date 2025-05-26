
///I
//1. Velocity normalization
//When: Only during projectile initialization or direction change.
//Where: In the projectile_create() factory function or before passing to it

// projectile.h
t_projectile projectile_create(t_tuple position, t_tuple velocity);

// projectile.c
t_projectile projectile_create(t_tuple position, t_tuple velocity) {
    // Velocity normalization (if required)
    t_tuple norm_velocity = normalize_vector(velocity);
    return (t_projectile){position, norm_velocity};
}

//2. Velocity scaling
//When: If speed needs to be greater/less than 1 unit/tick.
//Where: Before creating the projectile.

// main.c (or tests)
t_tuple direction = vector(1, 3, 0);
t_tuple initial_velocity = multiply(normalize_vector(direction), 5); // Speed = 5
t_projectile proj = projectile_create(point(0, 1, 0), initial_velocity);

//3. tick() function
//Does not normalize velocity - works with current vector.
//Updates position and velocity by adding acceleration.

// projectile.c
t_projectile tick(t_environment env, t_projectile proj) {
    t_tuple new_pos = add(proj.position, proj.velocity);
    t_tuple acceleration = add(env.gravity, env.wind);
    t_tuple new_vel = add(proj.velocity, acceleration);
    return (t_projectile){new_pos, new_vel};
}

//4. Testing
//Normalization tests:

// test_projectile.c
void test_normalize_velocity() {
    t_tuple v = vector(1, 3, 0);
    t_tuple norm = normalize_vector(v);
    TEST_ASSERT(floats_equal(magnitude(norm), 1.0));
}

//Projectile movement tests:

void test_tick_updates_position_and_velocity() {
    t_projectile p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
    t_environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
    
    p = tick(env, p);
    TEST_ASSERT(tuples_equal(p.position, point(1, 2, 0))); // Position check
}