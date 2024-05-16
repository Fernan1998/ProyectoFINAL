#include "Player.h"
#include "Animation.h"
#include <iostream>

Player::Player(float _speed)
	: animacion(&_texture, sf::Vector2u(4,1), 0.3f)
{
	_texture.loadFromFile("Textura/Player/BENJAMIN.png");
	_body.setTexture(&_texture);
	_body.setSize(sf::Vector2f(42.0f, 87.0f));
	_body.setPosition(0, 0);
	_speed = _speed;
	_velocity = sf::Vector2f(0,0);
	_estado = ESTADOS::CAYENDO;
	_jumpVelocity = 0;
	_body.setOrigin(_body.getGlobalBounds().width/2.0f, _body.getGlobalBounds().height/2.0f);
	_jump = false;	
	_colisionIzq = false;
	_colisionDer = false;

}
Player::Player()
	: animacion(&_texture, sf::Vector2u(63, 128), 0.3f)
{
}
Player::~Player()
{
	
}
sf::Vector2f Player::getPosition()
{
	return _body.getPosition();
}
void Player::cmd()
{

	
	if(_estado == ESTADOS::QUIETO && !_colisionDer || _estado == ESTADOS::CAYENDO && !_colisionDer || _estado == ESTADOS::CAMINANDO_ADELANTE && !_colisionDer)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			_estado = ESTADOS::CAMINANDO_ATRAS;
			_velocity.x=-4;
		};
	}
	if(_estado == ESTADOS::QUIETO && !_colisionIzq || _estado == ESTADOS::CAYENDO && !_colisionIzq || _estado == ESTADOS::CAMINANDO_ADELANTE && !_colisionIzq)
	{	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_estado = ESTADOS::CAMINANDO_ADELANTE;
			_velocity.x=4;
		};
	}
	
	if(_jump)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			_estado = ESTADOS::SALTANDO_ADELANTE;
			_jumpVelocity = 10;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			_estado = ESTADOS::SALTANDO_ATRAS;
			_jumpVelocity = 10;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			_estado = ESTADOS::SALTANDO;
			_jumpVelocity = 10;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_jumpVelocity = -16;
		}
	}
	_jump = false;	
	_colisionIzq = false;
	_colisionDer = false;
	
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
//		{
//			_estado = ESTADOS::ATACANDO;
//		}
		
}

void Player::update(float deltaTime)
{	

		switch(_estado)
		{
			case QUIETO:
				_jumpVelocity=0;
				std::cout << "QUIETO\n";
				break;
			case CAMINANDO_ADELANTE:
				_body.setScale(1,1);
				_body.move(_velocity.x, -_jumpVelocity);
				_estado= ESTADOS::CAYENDO;
				std::cout << "CAMINANDO ADELANTE\n";
				animacion.Update(0, deltaTime);
				_body.setTextureRect(animacion.uvRect);	break;
				break;
			case CAMINANDO_ATRAS:
				_body.setScale(-1,1);
				_body.move(_velocity.x, -_jumpVelocity);
				_estado= ESTADOS::CAYENDO;
				std::cout << "CAMINANDO ATRAS\n";
				animacion.Update(0, deltaTime);
				_body.setTextureRect(animacion.uvRect);	break;
				break;
			case SALTANDO:
				_body.move(0, -_jumpVelocity);
				_estado= ESTADOS::CAYENDO;
				std::cout << "SALTANDO\n";
				break;
			case SALTANDO_ADELANTE:
				_body.setScale(1,1);
				_body.move(10, -_jumpVelocity);
				_estado= ESTADOS::CAYENDO;
				break;
			case SALTANDO_ATRAS:
				_body.setScale(-1,1);
				_body.move(-10, -_jumpVelocity);
				_estado= ESTADOS::CAYENDO;
				break; 
			case CAYENDO:
				_body.move(0, -_jumpVelocity);
				//std::cout << "CAYENDO\n";
				break;
				
//			case ATACANDO:
//			_body.move(0, -_jumpVelocity);
//			_estado = ESTADOS::CAYENDO;
//		
				
		}
	std::cout << _jumpVelocity << std::endl;
	_jumpVelocity-=0.5;
	_velocity=sf::Vector2f(0,0);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(_body, states);
}


