#include <iostream>
#include <GL/glew.h>
//#include <noise/noise.h>
//#include <math.h>
//#include <time.h>
#include "include/engine/engine.h"
#include "include/noiseMapGeneration.h"
//#include "include/hydraulicErosion.h"

#define WIDTH 1200
#define HEIGHT 800

//int SEED = time(NULL);

//void generateVertexArray(int mapSize, float scale, float lacunarity, float persistence, int octaves, Vertex* vertices) {
	//noise::module::Perlin perlin;
	//perlin.SetOctaveCount(octaves);
	//perlin.SetFrequency(1.0);
	//perlin.SetPersistence(persistence);
	//perlin.SetLacunarity(lacunarity);

	//for (int y = 0; y < mapSize; y++) {
		//for (int x = 0; x < mapSize; x++) {
			//float aPerlin = -fabs(perlin.GetValue((float)(y / mapSize), (float)(x / mapSize), SEED));
			//float bPerlin = -fabs(perlin.GetValue((float)((y + 1) / mapSize), (float)(x / mapSize), SEED));
			//float cPerlin = -fabs(perlin.GetValue((float)(y / mapSize), (float)((x + 1) / mapSize), SEED));
			//float dPerlin = -fabs(perlin.GetValue((float)((y + 1) / mapSize), (float)((x + 1) / mapSize), SEED));
			//float ePerlin = -fabs(perlin.GetValue((float)((y + 1) / mapSize), (float)((x - 1) / mapSize), SEED));
			//float fPerlin = -fabs(perlin.GetValue((float)((y - 1) / mapSize), (float)((x + 1) / mapSize), SEED));
			//float gPerlin = -fabs(perlin.GetValue((float)((y - 1) / mapSize), (float)((x - 1) / mapSize), SEED));
			//float hPerlin = -fabs(perlin.GetValue((float)((y - 1) / mapSize), (float)(x / mapSize), SEED));
			//float iPerlin = -fabs(perlin.GetValue((float)(y / mapSize), (float)((x - 1) / mapSize), SEED));

			//std::cout << bPerlin << std::endl;

			//glm::vec3 pos = glm::vec3(y, (scale * aPerlin), x);
			//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;

			//glm::vec2 texCoord = glm::vec2(0.0);

			//glm::vec3 normal = glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - bPerlin), 1.0, 0.0));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (hPerlin - aPerlin), 1.0, 0.0));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - cPerlin), 1.0, 0.0));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (iPerlin - aPerlin), 1.0, 0.0));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - dPerlin)/sqrt(2), sqrt(2), scale * (aPerlin - dPerlin)/sqrt(2)));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - ePerlin)/sqrt(2), sqrt(2), scale * (aPerlin - ePerlin)/sqrt(2)));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - fPerlin)/sqrt(2), sqrt(2), scale * (aPerlin - fPerlin)/sqrt(2)));
			//normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (aPerlin - gPerlin)/sqrt(2), sqrt(2), scale * (aPerlin - gPerlin)/sqrt(2)));

			//Vertex vertex(pos, texCoord, normal);
			//vertices[(x * mapSize) + y] = vertex;
		//}
	//}
//}

void generateVertexArray(int mapSize, float scale, const std::vector<std::vector<float>>& heightmap, Vertex* vertices) {
	for (int y = 1; y < mapSize - 1; y++) {
		for (int x = 1; x < mapSize - 1; x++) {
			glm::vec3 pos = glm::vec3(y, (scale * heightmap[y][x]), x);

			glm::vec2 texCoord = glm::vec2(0.0);

			glm::vec3 normal = glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y+1][x]), 1.0, 0.0));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y-1][x] - heightmap[y][x]), 1.0, 0.0));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y][x+1]), 1.0, 0.0));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x-1] - heightmap[y][x]), 1.0, 0.0));

			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y+1][x+1])/sqrt(2), sqrt(2), scale * (heightmap[y][x] - heightmap[y+1][x+1])/sqrt(2)));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y+1][x-1])/sqrt(2), sqrt(2), scale * (heightmap[y][x] - heightmap[y+1][x-1])/sqrt(2)));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y-1][x+1])/sqrt(2), sqrt(2), scale * (heightmap[y][x] - heightmap[y-1][x+1])/sqrt(2)));
			normal += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[y][x] - heightmap[y-1][x-1])/sqrt(2), sqrt(2), scale * (heightmap[y][x] - heightmap[y-1][x-1])/sqrt(2)));

			Vertex vertex(pos, texCoord, normal);
			vertices[(y * mapSize) + x] = vertex;
		}
	}
}

void generateIndexArray(int mapSize, unsigned int* indices) {
	int i = 0;
	for (int y = 0; y < mapSize - 1; ++y) {
		for (int x = 0; x < mapSize - 1; ++x) {
			unsigned int tl = (x * mapSize) + y;
			unsigned int tr = ((x + 1) * mapSize) + y;
			unsigned int bl = (x * mapSize) + (y + 1);
			unsigned int br = ((x + 1) * mapSize) + (y + 1);

			indices[i++] = tl;
			indices[i++] = tr;
			indices[i++] = bl;

			indices[i++] = tr;
			indices[i++] = br;
			indices[i++] = bl;
		}
	}
}

int main() {
	int mapSize = 256;
	float scale = 10.0;
	float lacunarity = 1.7f;
	float persistence = 0.6f;
	int numOctaves = 15;
	bool normalise = true;

	std::vector<std::vector<float>> heightmap(mapSize, std::vector<float>(mapSize, 0));
	Vertex vertices[mapSize*mapSize];
	unsigned int indices[6*mapSize*mapSize];

	//generateVertexArray(mapSize, scale, lacunarity, persistence, numOctaves, vertices);
	generateNoiseMap(mapSize, heightmap, lacunarity, persistence, numOctaves, normalise);
	generateVertexArray(mapSize, scale, heightmap, vertices);
	generateIndexArray(mapSize, indices);

	Display display(WIDTH, HEIGHT, "Window");
	View camera(glm::vec3(128.0, 33.0, 330.0), 70.0f, (float)(WIDTH / HEIGHT), 0.1f, 10000.0f);

	Model terrainMesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Model cubeMesh("assets/cube.obj");

	Shader terrainShader("shader/default");

	Texture terrainTexture("assets/rock_texture.png");

	Transform transform;
	float count = 0.0f;
	while (!display.IsClosed()) {
		display.Clear(0.3f, 0.5f, 0.8f, 1.0f);

		transform.SetRotation(glm::vec3(count, 0.0, 0.0));
		//camera = View(glm::vec3(0.0, (count / 10), count), 70.0f, (float)(WIDTH / HEIGHT), 0.1f, 10000.0f);
		//std::cout << count << std::endl;

		terrainShader.Bind();
		terrainShader.Update(transform, camera);

		terrainTexture.Bind(0);

		terrainMesh.Render(GL_TRIANGLES);
		//terrainMesh.Render(GL_TRIANGLE_STRIP);
		cubeMesh.Render(GL_TRIANGLES);

		display.Update();
		count += 0.0001f;
	}
}
