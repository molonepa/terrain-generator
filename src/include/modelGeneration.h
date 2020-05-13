#include "noiseMapGeneration.h"

int mapSize = 512;
float scale = 30.0;
float lacunarity = 2.0f;
float gain = 0.5f;
int numOctaves = 7;
bool normalise = true;

float heightmap[512][512] = {0.0};

const int WIDTH = 1200;
const int HEIGHT = 800;
glm::vec3 viewPos = glm::vec3(50, 1, 50);
float zoom = 0.05;
float zoomInc = 0.001;
float rotation = 0.0f;
glm::vec3 cameraPos = glm::vec3(50, 50, 50);
glm::vec3 lookPos = glm::vec3(0, 0, 0);
glm::mat4 camera = glm::lookAt(cameraPos, lookPos, glm::vec3(0, 1, 0));
glm::mat4 projection;

void setup(){
	projection = glm::ortho(-(float)Tiny::view.WIDTH*zoom, (float)Tiny::view.WIDTH*zoom, -(float)Tiny::view.HEIGHT*zoom, (float)Tiny::view.HEIGHT*zoom, -800.0f, 500.0f);

	generateNoiseMap(mapSize, heightmap, scale, lacunarity, gain, numOctaves, normalise);
};

std::function<void()> eventHandler = [&](){
	if (!Tiny::event.scroll.empty()) {
		if (Tiny::event.scroll.back().wheel.y > 0.99 && zoom <= 0.3) {
			zoom += zoomInc;
			projection = glm::ortho(-(float)WIDTH*zoom, (float)WIDTH*zoom, -(float)HEIGHT*zoom, (float)HEIGHT*zoom, -800.0f, 500.0f);
		}
		else if (Tiny::event.scroll.back().wheel.y < -0.99 && zoom > 0.005) {
			zoom += zoomInc;
			projection = glm::ortho(-(float)WIDTH*zoom, (float)WIDTH*zoom, -(float)HEIGHT*zoom, (float)HEIGHT*zoom, -800.0f, 500.0f);
		}
		else if (Tiny::event.scroll.back().wheel.x < -0.8) {
			rotation += 1.5f;
			camera = glm::rotate(camera, glm::radians(1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (Tiny::event.scroll.back().wheel.x > 0.8) {
			rotation -= 1.5f;
			camera = glm::rotate(camera, glm::radians(-1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (rotation < 0.0) rotation = 360.0 + rotation;
		else if(rotation > 360.0) rotation = rotation - 360.0;
		camera = glm::rotate(glm::lookAt(cameraPos, lookPos, glm::vec3(0, 1, 0)), glm::radians(rotation), glm::vec3(0, 1, 0));
		Tiny::event.scroll.pop_back();
	}
};

// Model Constructing Function
std::function<void(Model* m)> _construct = [&](Model* h){
	//Loop over all positions and add the triangles!
	for(int i = 0; i < mapSize-1; i++){
		for(int j = 0; j < mapSize-1; j++){

			//Add to Position Vector
			glm::vec3 a = glm::vec3(i, scale*heightmap[i][j], j);
			glm::vec3 b = glm::vec3(i+1, scale*heightmap[i+1][j], j);
			glm::vec3 c = glm::vec3(i, scale*heightmap[i][j+1], j+1);
			glm::vec3 d = glm::vec3(i+1, scale*heightmap[i+1][j+1], j+1);

			//UPPER TRIANGLE

			//Add Indices
			h->indices.push_back(h->positions.size()/3+0);
			h->indices.push_back(h->positions.size()/3+1);
			h->indices.push_back(h->positions.size()/3+2);

			h->positions.push_back(a.x);
			h->positions.push_back(a.y);
			h->positions.push_back(a.z);
			h->positions.push_back(b.x);
			h->positions.push_back(b.y);
			h->positions.push_back(b.z);
			h->positions.push_back(c.x);
			h->positions.push_back(c.y);
			h->positions.push_back(c.z);

			glm::vec3 n1 = glm::cross(a-b, c-b);

			for(int i = 0; i < 3; i++){
				h->normals.push_back(n1.x);
				h->normals.push_back(n1.y);
				h->normals.push_back(n1.z);
			}

			//Lower Triangle
			h->indices.push_back(h->positions.size()/3+0);
			h->indices.push_back(h->positions.size()/3+1);
			h->indices.push_back(h->positions.size()/3+2);

			h->positions.push_back(d.x);
			h->positions.push_back(d.y);
			h->positions.push_back(d.z);
			h->positions.push_back(c.x);
			h->positions.push_back(c.y);
			h->positions.push_back(c.z);
			h->positions.push_back(b.x);
			h->positions.push_back(b.y);
			h->positions.push_back(b.z);

			glm::vec3 n2 = glm::cross(d-c, b-c);

			for(int i = 0; i < 3; i++){
				h->normals.push_back(n2.x);
				h->normals.push_back(n2.y);
				h->normals.push_back(n2.z);
			}
		}
	}
};
