#version 130

in vec3 in_Position;
in vec3 in_Normal;

uniform mat4 model;
uniform mat4 projectionCamera;

out vec4 ex_Color;
out vec3 ex_Normal;
out vec3 ex_FragPos;

void main(void) {
	//Fragment Position in Model Space
	ex_FragPos = (model * vec4(in_Position, 1.0f)).xyz;
	ex_Normal = in_Normal;	//Pass Normal

	//Fragment in Screen Space
	gl_Position = projectionCamera * vec4(ex_FragPos, 1.0f);

	//Color from Normal Vector
	vec3 color = normalize(in_Normal);
	//ex_Color = vec4(0.0, color.g, 0.0, 1.0);
	ex_Color = vec4(color, 1.0);
	//ex_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
