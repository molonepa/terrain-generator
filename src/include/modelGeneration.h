#include "noiseMapGeneration.h"
#include "hydraulicErosion.h"

// heightmap initialisation and generation parameters
int mapSize = 1024;
float scale = 100.0;
float lacunarity = 1.7f;
float persistence = 0.60f;
int numOctaves = 15;
bool normalise = true;
//bool normalise = false;
float heightmap[1024][1024] = {0.0};

// erosion parameters
int iterations = (mapSize * mapSize) / 2;
ErosionParameters parameters;

// view parameters
const int WIDTH = 1200;
const int HEIGHT = 800;
glm::vec3 cameraPos = glm::vec3(mapSize + (mapSize / 4), 2 * (mapSize / 3), mapSize + (mapSize / 4));
glm::vec3 lookPos = glm::vec3((mapSize / 2), 0, (mapSize / 2));
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
glm::mat4 camera = glm::lookAt(cameraPos, lookPos, cameraUp);
glm::mat4 projection;
float fov = 50.0f;
float cameraMoveInc = 10.0f;

// shading parameters
glm::vec3 lightPos = glm::vec3(mapSize, (mapSize / 2), mapSize);
glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);
float slope = 0.9975;
glm::vec3 flatColor = glm::vec3(0.6);
glm::vec3 steepColor = glm::vec3(0.4);

bool doErosion = false;

void setup() {
	projection = glm::perspective(glm::radians(fov), (float)WIDTH/(float)HEIGHT, 0.1f, (float)(3 * mapSize));

	generateNoiseMap(mapSize, heightmap, lacunarity, persistence, numOctaves, normalise);
};

std::function<void()> eventHandler = [&](){
	if (!Tiny::event.keys.empty()) {
		glm::vec3 cameraFront = glm::normalize(glm::vec3(cameraPos.x - lookPos.x, cameraPos.y - lookPos.y, cameraPos.z - lookPos.z));
		if (Tiny::event.keys.back().key.keysym.sym == SDLK_w) {
			cameraPos -= cameraFront * cameraMoveInc;
			camera = glm::lookAt(cameraPos, lookPos, cameraUp);
		}
		else if (Tiny::event.keys.back().key.keysym.sym == SDLK_s) {
			cameraPos += cameraFront * cameraMoveInc;
			camera = glm::lookAt(cameraPos, lookPos, cameraUp);
		}
		else if (Tiny::event.keys.back().key.keysym.sym == SDLK_a) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMoveInc;
			camera = glm::lookAt(cameraPos, lookPos, cameraUp);
		}
		else if (Tiny::event.keys.back().key.keysym.sym == SDLK_d) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMoveInc;
			camera = glm::lookAt(cameraPos, lookPos, cameraUp);
		}
		else if (Tiny::event.keys.back().key.keysym.sym == SDLK_e) {
			doErosion = true;
		}
	}
};

