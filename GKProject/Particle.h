#ifndef Particle_hpp
#define Particle_hpp


#include "Includes.h"

// stan  cz¹steczki
class ParticleState
{
public:
	Color color;
	float angle;
	float size;
};

// cz¹steczka
class Particle
{
public:
	// pozycja
	Vector2f position;

	// prêdkoœæ
	Vector2f velocity;

	// aktualne parametry cz¹steczki
	ParticleState current;

	// docelowe parametry cz¹steczki 
	ParticleState change;

	// czas w jakim cz¹steczka ma przejœæ w stan docelowy
	float changeDuration;

	// zamiana docelowych parametrów na to o ile maj¹ siê zmieniaæ
	void CalculateChangePerSecond();

private:
	friend class ParticleSystem;

	Particle* nextParticle;
	Particle* prevParticle;
};

#endif