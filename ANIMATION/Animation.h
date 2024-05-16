#pragma once
#include <SFML/Graphics.hpp>

class Animation {

public:
	Animation(sf::Texture* textura, sf::Vector2u imageCount, float switchTime);

	void Update(int columna, float deltaTime);
	
	sf::IntRect uvRect;
	
private:
	sf::Vector2u imageCount;
	sf::Vector2u imagenActual;
	
	float totalTime;
	float switchTime;
};

