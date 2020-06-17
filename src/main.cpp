#include "include/TinyEngine/TinyEngine.h"
#include "include/modelGeneration.h"

int main(int argc, char* args[]) {
	// launch window
	Tiny::init("Heightmap Render", WIDTH, HEIGHT);

	// event handler for camera movement
	Tiny::event.handler = eventHandler;

	// set up interface
	Tiny::view.interface = [&](){
		/* ... */
	};

	setup();

	// set up mesh and shader
	Model mesh;
	mesh.construct(mapSize, heightmap, scale);
	mesh.translate(glm::vec3(0.0, 0.0, 0.0));

	Shader defaultShader("shader/default.vs", "shader/default.fs", {"in_Position", "in_Normal"});

	// set up drawing pipeline
	Tiny::view.pipeline = [&]() {
		// prepare render target
		Tiny::view.target(glm::vec3(0.3, 0.5, 0.8));

		// prepare shader
		defaultShader.use();
		defaultShader.uniform("lightPos", lightPos);
		defaultShader.uniform("lightColor", lightColor);
		defaultShader.uniform("model", mesh.model);
		defaultShader.uniform("projectionCamera", projection * camera);
		defaultShader.uniform("cameraPos", cameraPos);
		defaultShader.uniform("flatColor", flatColor);
		defaultShader.uniform("steepColor", steepColor);
		defaultShader.uniform("slope", slope);

		// render to target
		//mesh.render(GL_LINES);
		mesh.render(GL_TRIANGLES);
	};

	Tiny::loop([&](){
		if (doErosion) {
			erode(mapSize, heightmap, iterations, parameters, scale);
			mesh.construct(mapSize, heightmap, scale);
			mesh.update();
			doErosion = false;
		}
	});

	Tiny::quit();
	return 0;
}
