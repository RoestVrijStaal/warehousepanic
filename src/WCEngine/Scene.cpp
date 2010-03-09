#include "Scene.h"

Scene::Scene( std::string name ) : name( name )
{
}

Scene::~Scene()
{
}

std::string Scene::GetName()
{
	return name;
}
