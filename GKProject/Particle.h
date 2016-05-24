#ifndef Particle_hpp
#define Particle_hpp


#include "Includes.h"

// stan  cz�steczki
class ParticleState
{
public:
	Color color;
	float angle;
	float size;
};

// cz�steczka
class Particle
{
public:
	// pozycja
	Vector2f position;

	// pr�dko��
	Vector2f velocity;

	// aktualne parametry cz�steczki
	ParticleState current;

	// docelowe parametry cz�steczki 
	ParticleState change;

	// czas w jakim cz�steczka ma przej�� w stan docelowy
	float changeDuration;

	// zamiana docelowych parametr�w na to o ile maj� si� zmienia�
	void CalculateChangePerSecond();

private:
	friend class ParticleSystem;

	Particle* nextParticle;
	Particle* prevParticle;
};

#endif