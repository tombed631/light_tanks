#include "ParticleSystem.h"



void ParticleSystem::setEmitter(sf::Vector2f position, int time)
{
	isAlive = true;
	m_emitter = position;
	for (std::size_t index = 0; index < m_particles.size(); ++index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 10.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 200) + time);

		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}
	visible = true;
};


void ParticleSystem::update(sf::Time elapsed)
{
	
		int koniec = 0;
		int red_yellow = 0;
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			// update the particle lifetime
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime >= sf::Time::Zero)
			{
				// update the position of the corresponding vertex
				m_vertices[i].position += p.velocity * elapsed.asSeconds();

				// update the alpha (transparency) of the particle according to its lifetime
				float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();

				if (!(m_vertices[i].color == Color::Red) || !(m_vertices[i].color == Color::Yellow))
				{
					switch (red_yellow)
					{
						case 0:
							m_vertices[i].color = Color::Red;
							red_yellow++;
							break;

						case 1:
							m_vertices[i].color = Color::Red;
							red_yellow++;
							break;
						case 2:
							m_vertices[i].color = Color::Yellow;
							red_yellow = 0;
							break;
					}
						
					
				}
					
				m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
			}
			else
			{
				m_vertices[i].color.a = 0;
				isAlive = false;
			}
				


			
		}
		
			
	
	
};

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
};
