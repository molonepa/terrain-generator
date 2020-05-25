#include <time.h>
#include <noise/noise.h>
#include "include/noiseMapGeneration.h"

int SEED = time(NULL);

void generateNoiseMap(int mapSize, float map[][512], float lacunarity, float persistence, int octaves, bool normalise){
	noise::module::Perlin perlin;
	perlin.SetOctaveCount(octaves);
	perlin.SetFrequency(1.0);
	perlin.SetPersistence(persistence);
	perlin.SetLacunarity(lacunarity);

	float min, max = 0.0;

	for (int y = 0; y < mapSize; y++) {
		for (int x = 0; x < mapSize; x++) {
			float nx = (float)x / (float)mapSize;
			float ny = (float)y / (float)mapSize;
			map[x][y] = perlin.GetValue(ny, nx, SEED);

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
