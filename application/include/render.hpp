#ifndef RENDER_HPP
#define RENDER_HPP

#include "glewInc.hpp"

#include "utils.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "skybox.hpp"
#include "framebuffer.hpp"

void setup();
void update();
void render();
void recursRender(Node& it, glm::fmat4 &mat = glm::fmat4(1.0f));

void renderQuad();

void drawFramebuffer();
void drawQuad();
void drawAsteroid();
void drawPlanet(Node& it);
void drawSun(Node& it);
void drawEarth(Node& it);
void drawOrbit(Node& it, glm::fmat4& mat);
void drawStars();
void drawSkybox();

void initializeOrbits();
void initializeStars(unsigned int amount);
void initializeAsteroids();

void uploadView();
void uploadProjection();

#endif