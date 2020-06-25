#version 120

varying vec2 fragTexCoord;
varying vec3 fragNormal;

uniform sampler2D diffuse;

void main() {
		gl_FragColor = texture2D(diffuse, fragTexCoord) * clamp(dot(-vec3(1.0), fragNormal), 0.0, 1.0);
}
