    /*
 *  Simple fragment sharder for Lab 2
 */

#version 330 core

in vec3 normal;
in vec3 position;
uniform samplerCube tex;
uniform vec3 Eye;
out vec4 FragColor;

void main() {
	vec3 tc;
	vec3 V = -normalize(Eye-position);
	
	tc = reflect(V,normal);
	FragColor = texture(tex,normalize(position));

}