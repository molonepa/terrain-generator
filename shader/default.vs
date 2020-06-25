#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

uniform mat4 transform;

varying out vec2 fragTexCoord;
varying out vec3 fragNormal;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	fragTexCoord = texCoord;
	fragNormal = (transform * vec4(normal, 0.0)).xyz;
}
