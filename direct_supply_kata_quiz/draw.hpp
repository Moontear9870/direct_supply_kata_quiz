#pragma once
#include <SDL.h>
#include "windowStructs.hpp"
//#include "Server/entity.hpp"
//#include "Server/entityManager.hpp"
//#include "Server/Components/component.hpp"

extern App* app;

void prepareScene(int r, int g, int b, int a);

void presentScene(void);

//void drawEntity(EntityManager* entMan, Entity* entity);
