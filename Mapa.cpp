#include "Mapa.h"
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace sf;

Mapa::Mapa(int _filas, int _columnas)
{
	//le otorga el valor de _filas al atributo nFilas
	nFilas = _filas;
	nColumnas = _columnas;
	
	//al ser un vector de la libreria <Vector> podemos modificar el tamaño del mismo, en este caso es una matriz.
	tilMap.resize(nFilas);
	for(int i = 0; i < nFilas; ++i)
	{
		tilMap[i].resize(nColumnas);
	}
	for (int i = 0; i < 20; i++)
	{
		switch (i)
		{
		case 0:
			break;
		case 1:
			_texture[i].loadFromFile("Textura/Mapa/grass.png");
			break;
		case 2:
			_texture[i].loadFromFile("Textura/Mapa/grass_derecha.png");
			break;
		case 3:
			_texture[i].loadFromFile("Textura/Mapa/grass_izquierda.png");
			break;
		case 4:
			_texture[i].loadFromFile("Textura/Mapa/grass1.png");
			break;
		case 5:
			_texture[i].loadFromFile("Textura/Mapa/fondo.png");
			break;
		case 6:
			_texture[i].loadFromFile("Textura/Mapa/pared_izq.png");
			break;
		case 7:
			_texture[i].loadFromFile("Textura/Mapa/fondo.png");
			break;
		case 8:
			_texture[i].loadFromFile("Textura/Mapa/piedra_3.png");
			break;
		case 9:
			_texture[i].loadFromFile("Textura/Mapa/piedra_2.png");
			break;
		case 10:
			_texture[i].loadFromFile("Textura/Mapa/techo.png");
			break;
		case 11:
			_texture[i].loadFromFile("Textura/Mapa/techo_der.png");
			break;
		case 12:
			_texture[i].loadFromFile("Textura/Mapa/techo_izq.png");
			break;
		case 13:
			_texture[i].loadFromFile("Textura/Mapa/piedras.png");
			break;
		}
	}
}
Mapa::Mapa()
{
	
}
Mapa::~Mapa() 
{
	//es el destructor del mapa
}

void Mapa::MapCreator(std::ifstream& file)
{


	int spriteType;
	
	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			file >> spriteType;
			switch (spriteType) {
			case 0:
				break;
			case 1:
				tilMap[i][j].setTexture(_texture[1]);
				break;
			case 2:
				tilMap[i][j].setTexture(_texture[2]);
				break;
			case 3:
				tilMap[i][j].setTexture(_texture[3]);
				break;
			case 4:
				tilMap[i][j].setTexture(_texture[4]);
				break;
			case 5:
				tilMap[i][j].setTexture(_texture[5]);
				break;
			case 6:
				tilMap[i][j].setTexture(_texture[6]);
				break;
			case 7:
				tilMap[i][j].setTexture(_texture[7]);
				break;
			case 8:
				tilMap[i][j].setTexture(_texture[8]);
				break;
			case 9:
				tilMap[i][j].setTexture(_texture[9]);
				break;
			case 10:
				tilMap[i][j].setTexture(_texture[10]);
				break;
			case 11:
				tilMap[i][j].setTexture(_texture[11]);
				break;
			case 12:
				tilMap[i][j].setTexture(_texture[12]);
				break;
			case 13:
				tilMap[i][j].setTexture(_texture[13]);
				break;
			}
			tilMap[i][j].setPosition(j * 32, i * 32); 
		}
	}
	file.close();
};

sf::Sprite Mapa::getSprite(int i, int j)
{
	return tilMap[i][j];
}
