# Info
* Requires `SFML 2.5.1`
* Particles are handled by using `sf::VertexArray`
* Using the Particle class constructor, you can pass how many particles you would like to spawn.
* Change the starting positions of particles in the `Particle::SetPosition()` function within `Particle.cpp`
* Each body acts as a gravity source. Place it in position and tweak its strength using the default constructor.

# Behavior 
* Particles do not apply gravitational force upon each other. The bodies also do not attract each other.
* This does not fully apply Newtons law of universal gravitation. Bodies act as a static particle attractor.
* The strength of gravitational pull is inversely proportional to the square of the distance between particle and body.
* Each particle obtains a vector that reflects the gravitational acceleration to the nearer (or stronger) body.
* Look at `Particle.cpp` to see the implementation.

#### Demo with 100,000 particles.
https://user-images.githubusercontent.com/6244191/229238686-2dcd7183-188c-4296-843b-ea87bcf17c09.mp4

# Contributing
* This project could use better optimization, however this was more of a learning project for me. So if you would like to contribute, I will accept pull requests.
