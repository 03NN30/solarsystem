#ifndef RENDER_HPP
#define RENDER_HPP

#include "glewInc.hpp"

#include "framebuffer.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "skybox.hpp"
#include "texture.hpp"
#include "utils.hpp"

void setup();
void update();
void render();
void recursRender(Node &it, glm::fmat4 &mat);

void renderQuad();
void drawQuad();
void drawFramebuffer();

void drawRing(Node &it, glm::fmat4 &mat);
void drawPlanet(Node &it);
void drawSun(Node &it);
void drawEarth(Node &it);
void drawOrbit(Node &it, glm::fmat4 &mat);
void drawStars();
void drawAsteroid();
void drawSkybox();

void initializeFramebuffer();
void initializeOrbits();
void initializeStars(unsigned int amount);
void initializeAsteroids();

void uploadView();
void uploadProjection();

#endif