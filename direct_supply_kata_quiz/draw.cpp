#pragma once
#include "draw.hpp"
//#include "Server/entityManager.hpp"
//#include "Server/Components/component.hpp"
//#include "Server/Components/geometricComponent.hpp"
//#include "Server/Components/renderedComponent.hpp"
//
//void drawEntity(EntityManager* entMan, Entity* entity)
//{
//	GeometricComponent* geoComp = (GeometricComponent*)entMan->getComponent(entity, Component::GEOMETRIC);
//	RenderedComponent* rendComp = (RenderedComponent*)entMan->getComponent(entity, Component::RENDERED);
//
//	SDL_Rect rect = { geoComp->position.first, geoComp->position.second, geoComp->size.first, geoComp->size.second };
//	SDL_SetRenderDrawColor(app->renderer, rendComp->color.r, rendComp->color.g, rendComp->color.b, rendComp->color.a);
//	SDL_RenderFillRect(app->renderer, &rect);
//}

void prepareScene(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(app->renderer, r, g, b, a);

	SDL_RenderClear(app->renderer);

}

void presentScene(void)
{
	SDL_RenderPresent(app->renderer);
}