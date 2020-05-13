#define STB_PERLIN_IMPLEMENTATION
#include "include/stb_perlin.h"        // Required for: stb_perlin_fbm_noise3
#include "include/noiseMapGeneration.h"

void generateNoiseMap(int mapSize, float map[][512], float scale, float lacunarity, float gain, int octaves, bool normalise){
	float min, max = 0.0;
	for (int y = 0; y < mapSize; y++) {
		for (int x = 0; x < mapSize; x++) {
			float nx = (float)x * scale / (float)mapSize;
			float ny = (float)y * scale / (float)mapSize;
			map[x][y] = stb_perlin_fbm_noise3(nx, ny, scale, lacunarity, gain, octaves);

			if (map[x][y] > max) { max = map[x][y]; }
			if (map[x][y] < min) { min = map[x][y]; }
		}
	}

	if (normalise) {
		for (int y = 0; y < mapSize; y++) {
			for (int x = 0; x < mapSize; x++) {
				map[x][y] = (map[x][y] - min) / (max - min);
			}
		}
	}
}
