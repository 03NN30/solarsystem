#ifndef UTILS_HPP
#define UTILS_HPP

#include "application.hpp"
#include "node.hpp"
#include <string>

const float appVersion = 0.3f;

const bool fullScreen = false;
const int screenWidth = 1800;
const int screenHeight = 960;
// OH NO THIS ENTIRE PROJECT IS ABSOLUT TRASH!
const std::string resource_path = "/home/n30/Repos/solarsystem/resources/";

extern bool isMoving;
extern bool orbits;
extern bool stars;
extern bool realism;

extern float speedSlider;
extern float shininess;
extern float ambient;
extern float lightIntensity;
extern float reflectivity;
extern float lightConstant;
extern float lightLinear;
extern float lightQuadratic;
extern float exposure;
extern float gamma_;
extern float glow;
extern int bloom;
extern bool planetOutline;
extern bool blur;
extern bool grayscale;
extern bool verticalMirror;
extern bool horizontalMirror;
extern bool bloomFlag;
extern bool planetBloom;
extern bool planetRing;

extern Node *sg;

// menu
extern bool menu;
extern bool showMouse;
extern bool mouseEnabled;
extern float loadingProgress;
extern bool isFollowing;

#endif