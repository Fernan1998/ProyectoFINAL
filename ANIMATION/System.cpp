#include "System.h"
#include "Mapa.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

System::System(Player& player, Camera& camara, Mapa& mapa, Mapa& fondo, Mapa& obstacle, Mapa& dead, int anchoMapa, int altoMapa, std::ifstream& fileMap)
{
	_mainCamera = camara;
	_player = player;
	_mapa = mapa;
	_fondo = fondo;
	_obstacle = obstacle;
	_dead = dead;
	_anchoMapa = anchoMapa;
	_altoMapa = altoMapa;
	_mapa.MapCreator(fileMap);
}
System::~System()
{
	
}
void System::update(float deltaTime)
{	
	_player.update(deltaTime);
	_mainCamera.FollowAndUpdate(_player.getPosition(), &_mainCamera);

}
void System::cmd()
{
	_player.cmd();
}
void System::CheckCollision()
{
	sf::FloatRect hitBoxPlayer(_player.getBody().getGlobalBounds().left, _player.getBody().getGlobalBounds().top + _player.getBody().getGlobalBounds().height -16,_player.getBody().getGlobalBounds().width , 16);
	auto playerGlobalBounds = _player.getBody().getGlobalBounds();

	sf::FloatRect hitBoxMap;
	sf::FloatRect hitBoxMapIzq;
	sf::FloatRect hitBoxMapDer;
	sf::FloatRect hitBoxMapPlatform;
	sf::FloatRect hitBoxPlayerHead;
	sf::FloatRect hitBoxMapHead;
	
	for(int i=0; i<_anchoMapa; i++)
	{
		for(int j=0; j<_altoMapa; j++)
		{	
			hitBoxMap = sf::FloatRect(_mapa.getSprite(i, j).getGlobalBounds().left, _mapa.getSprite(i, j).getGlobalBounds().top - 16, _mapa.getSprite(i, j).getGlobalBounds().width, 16);
			hitBoxMapIzq = sf::FloatRect(_mapa.getSprite(i, j).getGlobalBounds().left - 4, _mapa.getSprite(i, j).getGlobalBounds().top, _mapa.getSprite(i, j).getGlobalBounds().width + 4, _mapa.getSprite(i, j).getGlobalBounds().height);
			hitBoxMapDer = sf::FloatRect(_mapa.getSprite(i, j).getGlobalBounds().left + 32, _mapa.getSprite(i, j).getGlobalBounds().top, 4, _mapa.getSprite(i, j).getGlobalBounds().height);
			hitBoxPlayerHead = sf::FloatRect(playerGlobalBounds.left, playerGlobalBounds.top, playerGlobalBounds.width, 16);
			hitBoxMapHead = sf::FloatRect(_mapa.getSprite(i, j).getGlobalBounds().left, _mapa.getSprite(i, j).getGlobalBounds().top + 32, _mapa.getSprite(i, j).getGlobalBounds().width , 2);
			hitBoxMapPlatform = sf::FloatRect(_obstacle.getSprite(i, j).getGlobalBounds().left, _obstacle.getSprite(i, j).getGlobalBounds().top - 16, _obstacle.getSprite(i, j).getGlobalBounds().width, 16);
			hitBoxMapHead = sf::FloatRect(_mapa.getSprite(i, j).getGlobalBounds().left, _mapa.getSprite(i, j).getGlobalBounds().top + 32, _mapa.getSprite(i, j).getGlobalBounds().width , 2);
			
			if(playerGlobalBounds.top - playerGlobalBounds.height < _mapa.getSprite(i,j).getGlobalBounds().top
			&& hitBoxPlayer.intersects(hitBoxMap)
			&& _player.getVelocidadSalto() < 0)
			{
				_player.quieto(_player.getPosition().x, _mapa.getSprite(i,j).getGlobalBounds().top - _player.getBody().getGlobalBounds().height/2);
			}
			if(playerGlobalBounds.left + playerGlobalBounds.width <= _mapa.getSprite(i,j).getGlobalBounds().left
			   && playerGlobalBounds.intersects(hitBoxMapIzq))
			{
				_player.setMoveX();
			}
			if(playerGlobalBounds.left > _mapa.getSprite(i,j).getGlobalBounds().left + _mapa.getSprite(i,j).getGlobalBounds().width
			   && playerGlobalBounds.intersects(hitBoxMapDer))
			{
				_player.setMoveXY();
			}
			if(playerGlobalBounds.intersects(_dead.getSprite(i,j).getGlobalBounds()))
			{
				_player.setPosition(sf::Vector2f(0,0));
			}
			if(playerGlobalBounds.top - playerGlobalBounds.height < _obstacle.getSprite(i,j).getGlobalBounds().top
			   && hitBoxPlayer.intersects(hitBoxMapPlatform)
			   && _player.getVelocidadSalto() < 0)
			{
				_player.quieto(_player.getPosition().x, _obstacle.getSprite(i,j).getGlobalBounds().top - _player.getBody().getGlobalBounds().height/2);
			}
			if(hitBoxPlayerHead.intersects(hitBoxMapHead))
			{
				_player.quieto2();
			}
		}
	}
}
sf::Vector2f System::getPositionPlayer()
{
	return _player.getPosition();
}	

void System::draw(sf::RenderWindow& window)
{
	
	
	for(int i=0; i<_anchoMapa; i++)
	{
		for(int j=0; j<_altoMapa; j++)
		{	
			
			window.draw(_fondo.getSprite(i,j));
			window.draw(_mapa.getSprite(i,j));
			window.draw(_obstacle.getSprite(i,j));
			window.draw(_dead.getSprite(i,j));
			
		}
	}	
	window.draw(_player);
}
