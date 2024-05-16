#include <SFML/Graphics.hpp>
#include "Animation.h"
#pragma once
#include <iostream>

class Player : public sf::Drawable{
public:
	
	Player(float speed);
	Player();
	~Player();
	void cmd();
	void update(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	sf::RectangleShape getBody()
	{
		return _body;
	}	
	float getVelocidadSalto()
	{
		return _jumpVelocity;
	}
	void setPosition(sf::Vector2f position)
	{
		_body.setPosition(position);
	}
	void quieto(float x, float y)
	{
		_estado = ESTADOS::QUIETO;
		_jumpVelocity = 0;
		_body.setPosition(x,y);
		_jump = true;
	}	
	void quieto2()
	{
		if(_jumpVelocity>0)
		{
			_jumpVelocity = 0;
		}
		_estado = ESTADOS::CAYENDO;
		std::cout << "COLISION CABEZA\n";
		
	}	
	void setMoveX()
	{
		_colisionIzq = true;
		std::cout << "COLISION LATERAL IZQ\n";
	}
	void setMoveXY()
	{
		_colisionDer = true;
		std::cout << "COLISION LATERAL DER\n";
	}	


private:
	enum ESTADOS{
		QUIETO,
		CAMINANDO_ADELANTE,
		SALTANDO_ADELANTE,
		CAMINANDO_ATRAS,
		SALTANDO_ATRAS,
		SALTANDO,
		ATACANDO,
		CAYENDO
	};
	ESTADOS _estado;
	sf::Texture _texture;
	sf::RectangleShape _body;
	sf::RectangleShape _attackBody;
	sf::Vector2f _velocity;
	float _speed;
	float _jumpVelocity;
	bool _jump;
	bool _colisionIzq;
	bool _colisionDer;
	
	Animation animacion;
};

