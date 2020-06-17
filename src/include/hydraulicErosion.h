#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#endif

struct Drop {
	//Drop(glm::vec2 _pos){pos = _pos;}

	glm::vec2 pos = glm::vec2(0.0);
	glm::vec2 speed = glm::vec2(0.0);

	float volume = 1.0; // total volume of particle
	float sediment = 0.0; // fraction of volume that is sediment
};

struct ErosionParameters {
	float dt = 1.2;
	float density = 1.0;
	float evaporationRate = 0.01;
	float depositionRate = 0.1;
	float minVolume = 0.01;
	float friction = 0.05;
};

glm::vec3 surfaceNormal(float scale, float heightmap[][1024], int i, int j);

void erode(int mapSize, float heightmap[][1024], int iterations, ErosionParameters params, float scale);

