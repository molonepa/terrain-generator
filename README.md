# terragen
Perlin-based terrain generation with simulated hydraulic erosion

### Heightmap Generation
The initial terrain is generated from Perlin noise using [libnoise]. To produce the mountain range-like ridges in the image below, the absolute value of the noise is taken, then it is inverted.

![alt text](https://github.com/molonepa/terragen/raw/master/assets/noisemap.png "Ridged Perlin Noise")

### Hydraulic Erosion
The erosion simulation spawns particles at a random position on the heightmap, which then roll downhill, collecting sediment as they move and depositing it when they stop.

A drop's velocity is calculated using its mass and the slope of the terrain and its position is updated, then friction is applied. The drop's maximum sediment carrying capacity is proportional to its speed and direction of movement (drop moving downhill can carry more sediment). The drop then loses some mass to evaporation, and the process is repeated until the drop's volume falls below the minimum, or falls out of the bounds of the map, or stops moving.

The erosion code is parallelised with OpenMP, resulting in a speedup of xxxx.

### Results
The results are pretty satisfying and greatly improve the look of the noise generated terrain.

Before:
![alt text](https://github.com/molonepa/terragen/raw/master/assets/before1.png "Before")

After:
![alt text](https://github.com/molonepa/terragen/raw/master/assets/after1.png "After ~1 million simulated particles")

Before:
![alt text](https://github.com/molonepa/terragen/raw/master/assets/before2.png "Before")

After:
![alt text](https://github.com/molonepa/terragen/raw/master/assets/after2.png "After ~1 million simulated particles")


### Future Additions

[linoise]: http://libnoise.sourceforge.net/index.html
