#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "application.hpp"
#include "node.hpp"

const float appVersion = 0.3f;

const bool fullScreen = false;
const int screenWidth = 1800;
const int screenHeight = 960;
const std::string resource_path = "C:/Repositories/Solar-System/resources/";

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
extern float gamma;
extern float glow;
extern   int bloom;
extern  bool planetOutline;
extern  bool blur;
extern  bool grayscale;
extern  bool verticalMirror;
extern  bool horizontalMirror;
extern  bool bloomFlag;
extern  bool planetBloom;
extern  bool planetRing;

extern Node* sg;

// menu
extern bool menu;
extern bool showMouse;
extern bool mouseEnabled;
extern float loadingProgress;
extern bool isFollowing;

#endif