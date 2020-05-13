#include "../../TinyEngine/TinyEngine.h"
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
	Model mesh(_construct);
	mesh.translate(glm::vec3(-32.0, -15.0, -32.0));

	Shader defaultShader("shader/default.vs", "shader/default.fs", {"in_Position", "in_Normal"});

	// set up drawing pipeline
	Tiny::view.pipeline = [&]() {
		// prepare render target
		Tiny::view.target(color::black);
		// prepare shader
		defaultShader.use();
		defaultShader.uniform("model", mesh.model);
		defaultShader.uniform("projectionCamera", projection * camera);
		// render to target
		mesh.render(GL_LINES);
	};

	Tiny::loop([&](){
			// rotate camera
			camera = glm::rotate(camera, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
	});

	Tiny::quit();
	return 0;
}
