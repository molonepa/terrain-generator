#include <stdio.h>
#include "include/hydraulicErosion.h"

glm::vec3 surfaceNormal(float scale, float heightmap[][512], int i, int j) {
	glm::vec3 n = glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[i][j] - heightmap[i+1][j]), 1.0, 0.0));
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[i-1][j] - heightmap[i][j]), 1.0, 0.0));
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[i][j] - heightmap[i][j+1]), 1.0, 0.0));
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(scale * (heightmap[i][j-1] - heightmap[i][j]), 1.0, 0.0));

	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(heightmap[i][j]-heightmap[i+1][j+1])/sqrt(2), sqrt(2), scale*(heightmap[i][j]-heightmap[i+1][j+1])/sqrt(2)));
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(heightmap[i][j]-heightmap[i+1][j-1])/sqrt(2), sqrt(2), scale*(heightmap[i][j]-heightmap[i+1][j-1])/sqrt(2)));
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(heightmap[i][j]-heightmap[i-1][j+1])/sqrt(2), sqrt(2), scale*(heightmap[i][j]-heightmap[i-1][j+1])/sqrt(2)));
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(heightmap[i][j]-heightmap[i-1][j-1])/sqrt(2), sqrt(2), scale*(heightmap[i][j]-heightmap[i-1][j-1])/sqrt(2)));

	return n;
}

void erode(int mapSize, float heightmap[][512], int iterations, ErosionParameters params, float scale) {
	for (int i = 0; i < iterations; i++) {
		printf("%d/%d\r", i, iterations);
		// spawn new particle at random position on heightmap
		glm::vec2 newPos = glm::vec2(rand()%mapSize, rand()%mapSize);
		Drop drop;
		drop.pos = newPos;

		while (drop.volume > params.minVolume) {
			glm::ivec2 ipos = drop.pos;
			glm::vec3 normal = surfaceNormal(scale, heightmap, ipos.x, ipos.y);

			drop.speed += params.dt * glm::vec2(normal.x, normal.z) / (drop.volume * params.density); // accelerate particle according to surface normal
			drop.pos += params.dt * drop.speed; // update particle's position
			drop.speed *= (1.0 - params.dt * params.friction); // apply friction

			// if particle's updated position is out of bounds
			if (!glm::all(glm::greaterThanEqual(drop.pos, glm::vec2(0))) || !glm::all(glm::lessThanEqual(drop.pos, glm::vec2(mapSize)))) {
				break;
			}

			float maxSediment = drop.volume * glm::length(drop.speed) * (heightmap[ipos.x][ipos.y] - heightmap[(int)drop.pos.x][(int)drop.pos.y]);
			if (maxSediment < 0.0) maxSediment = 0.0;
			float sedimentDiff = maxSediment - drop.sediment;

			// erode heightmap
			drop.sediment += params.dt * params.depositionRate * sedimentDiff;
			heightmap[ipos.x][ipos.y] -= params.dt * drop.volume * params.depositionRate * sedimentDiff;

			drop.volume *= (1.0 - params.dt * params.evaporationRate);
		}
	}
}
