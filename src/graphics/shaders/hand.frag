#version 150

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTextureCoordnate;

const vec3 light = vec3(0.58, 0.58, 0.58);

void main(void){
	float shade = clamp(dot(light, normalize(fragNormal)), 0, 1);
}
