#version 150

in vec3 vertPosition;
in vec3 vertNormal;
in vec2 vertTextureCoordinate;
uniform mat4 transform;
uniform mat4 viewFrustum;

void main(void){
	gl_Position = veiwFrustum * vertPosition;
}
