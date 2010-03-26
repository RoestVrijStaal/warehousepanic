#include "Scene.h"
#include "Application.h"

#include "Application.h"

namespace gdn
{
	Scene::Scene( std::string name ) : name( name )
	{
		App.AddScene( this );
	}

	Scene::~Scene()
	{
	}

	std::string Scene::GetName()
	{
		return name;
	}
}
