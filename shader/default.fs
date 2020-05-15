#version 130

in vec3 ex_Color;
in vec3 ex_Normal;
in vec3 ex_FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 fragColor;

void main(void) {
	vec3 result = vec3(0.0, 0.0, 0.0);

	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(ex_Normal);
	vec3 lightDir = normalize(lightPos - ex_FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	int reflectivity = 32;
	vec3 viewDir = normalize(cameraPos - ex_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflectivity);
	vec3 specular = specularStrength * spec * lightColor;

	result = (ambient + diffuse + specular) * ex_Color;
  	fragColor = vec4(result, 1.0); //Pass Color to Fragment
}
