#pragma once
#include "Mapa.h"
#include "Player.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>


class System 
{
public:
	
	System(Player& player, Camera &camara, Mapa& mapa, Mapa& fondo, Mapa& obstacle, Mapa& dead, int anchoMapa, int altoMapa, std::ifstream& fileMap);
	~System();
	void update(float deltaTime);
	void cmd();
	void draw(sf::RenderWindow& window);
	void CheckCollision();
	sf::Vector2f getPositionPlayer();
	
private:
	Camera _mainCamera;
	Player _player;
	Mapa _mapa;
	Mapa _fondo;
	Mapa _obstacle;
	Mapa _dead;
	int _anchoMapa;
	int _altoMapa;
};
