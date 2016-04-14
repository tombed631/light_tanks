#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp
#endif

#include "Includes.h"

// koordynaty fragmentu tekstury
struct UVRegion
{
	// lewy górny róg
	float u0, v0;

	// prawy dolny róg
	float u1, v1;

	UVRegion();

	UVRegion(float u0, float v0, float u1, float v1)
		: u0(u0), v0(v0), u1(u1), v1(v1){};
};

extern const UVRegion DefaultRegion;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	
	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(1))

	{};

	bool isAlive = false;
	bool colors;

	void setEmitter(sf::Vector2f position, int time, int _angle, int _speed, bool colors);

	void update(sf::Time elapsed);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	vector<Particle> m_particles;
	VertexArray m_vertices;
	Time m_lifetime;
	Vector2f m_emitter;
	map<string, UVRegion*> regions;
	
	bool visible = false;


	
};