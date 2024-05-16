#include <SFML/Graphics.hpp>
#include <vector>
#include "Mapa.h"
#include "Player.h"
#include "System.h"
#include "Animation.h"
#include <fstream>

using namespace sf;

int main(int argc, char *argv[]){

	int x = 1024;
	int y = 768;
	
	RenderWindow w(VideoMode(1024,768),"MapCreator");
	w.setFramerateLimit(60);
	float cameraOffsetX = 400;
	float cameraOffsetY = 300;
	Camera mainCamera(&w, x, y, 1344, 992); 
	
	
	Player player(0.5);
	int nFila = 31;
	int nColumna = 42;
	
	std::ifstream file_map;
	file_map.open("Mapas/mapa_cueva.txt");
	Mapa map(nFila, nColumna);
	map.MapCreator(file_map);

	std::ifstream file_fondo;
	file_fondo.open("Mapas/fondo_cueva.txt");
	Mapa fondo(nFila, nColumna);
	fondo.MapCreator(file_fondo);
	
	std::ifstream file_obstacle;
	file_obstacle.open("Mapas/plataformas_cueva.txt");
	Mapa obstacle(nFila, nColumna);
	obstacle.MapCreator(file_obstacle);
	
	std::ifstream file_dead;
	file_dead.open("Mapas/muerte.txt");
	Mapa dead(nFila, nColumna);
	dead.MapCreator(file_dead);
	
	System sistema(player, mainCamera, map, fondo, obstacle, dead, nFila, nColumna, file_map);
	

	sf::Clock clock;
	
	while(w.isOpen()) {
		
		float deltaTime = clock.restart().asSeconds();
		
		Event e;
		while(w.pollEvent(e)) {
			if(e.type == Event::Closed)
				w.close();	
		}
		
//		float cameraX = sistema.getPositionPlayer().x - cameraOffsetX;
//		
//		float cameraY = sistema.getPositionPlayer().y - cameraOffsetY;
//		
//		w.setView(sf::View(sf::FloatRect(cameraX, cameraY, x, y)));
		
		w.clear();
		sistema.CheckCollision();
		sistema.cmd();
		sistema.update(deltaTime);
		sistema.draw(w);


		w.display();

	}
	return 0;
}

	
