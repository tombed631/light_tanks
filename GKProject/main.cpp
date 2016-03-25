#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>
#include <math.h>
using namespace sf;



class Tank:public sf::Drawable,public sf::Transformable
{
private:
	Sprite tankSprite;
	Texture tankTexture;
	Vector2f direction,velocity;
	float speed;
	Clock deltaClock;
public:
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(tankSprite);
	};
	Tank(String name, float positionX, float positionY)
	{
		speed = 150;
		if (!tankTexture.loadFromFile(name))
		{
			MessageBox(NULL, "Brak tekstury czolgu!", "ERROR", NULL);
			return;
		}
		tankSprite.setTexture(tankTexture);
		tankSprite.setPosition(positionX, positionY);
		tankSprite.setOrigin(80, 128);
		tankSprite.setScale(0.2, 0.2);
		tankSprite.setRotation(180);
	};

	Vector2f moveTank()
	{
		velocity.x = 0;
		velocity.y = 0;
		sf::Time dt = deltaClock.restart();
		double angle = tankSprite.getRotation()*3.14159265 / 180;
		//Vector2f direction = Vector2f((float)Math.cos(angle), (float)Math.Sin(angle))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			tankSprite.setRotation((tankSprite.getRotation() - 3));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			tankSprite.setRotation((tankSprite.getRotation() + 3));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			velocity.x = (speed * sin(angle)*dt.asSeconds());
			velocity.y = -speed * cos(angle)*dt.asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			velocity.x = -speed * sin(angle)*dt.asSeconds();
			velocity.y = speed * cos(angle)*dt.asSeconds();
		}
		
		tankSprite.move(velocity);
		return velocity;
		
	}


	Vector2f moveTank2()
	{
		velocity.x = 0;
		velocity.y = 0;
		sf::Time dt = deltaClock.restart();
		double angle = tankSprite.getRotation()*3.14159265 / 180;
		//Vector2f direction = Vector2f((float)Math.cos(angle), (float)Math.Sin(angle))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			tankSprite.setRotation((tankSprite.getRotation() - 3));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			tankSprite.setRotation((tankSprite.getRotation() + 3));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			velocity.x = (speed * sin(angle)*dt.asSeconds());
			velocity.y = -speed * cos(angle)*dt.asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			velocity.x = -speed * sin(angle)*dt.asSeconds();
			velocity.y = speed * cos(angle)*dt.asSeconds();
		}

		tankSprite.move(velocity);
		return velocity;

	}
	float getRotation()
	{
		float rot = atan2(direction.y, direction.x);
		rot = tankSprite.getRotation() * 180/ (float)3.14159265359;
		rot +=180;
		return rot;
	}
	void animation()
	{
		float rot = getRotation();
		tankSprite.setRotation(rot);
	}

};



int main()
{
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Tanks");
	sf::Event event;
	
	Tank *tank = new Tank("1.jpg",20,20);
	Tank *tank2 = new Tank("2.jpg", 50, 50);
	App.setFramerateLimit(100);
	bool running = true;
	while (running)
	{
		
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape))
				running = false;
			if (event.type == sf::Event::Resized)
				;
		}
		

		
		tank->moveTank();
		tank2->moveTank2();
		App.clear();
		App.draw(*tank);
		App.draw(*tank2);
		App.display();

	}

	return EXIT_SUCCESS;
}
