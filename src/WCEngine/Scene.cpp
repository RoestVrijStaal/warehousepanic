#include "Scene.h"

Scene::Scene( std::string name ) : name( name )
{
}

Scene::~Scene()
{
}

void Scene::SetRenderWindow( sf::RenderWindow& target )
{
		window = &target;
}

std::string Scene::GetName()
{
	return name;
}
