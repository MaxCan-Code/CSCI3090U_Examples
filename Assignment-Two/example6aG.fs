#version 330 core
/*
 *  Simple fragment sharder for laboratory two
 Our first example is a straight forward translation of the Phong light model
 We will assume that we have a directional light, since that is easier to code
 Our vertex shader is quite simple, all it needs to do is transform the vertex position and normal

 Gouraud Shading
 - We can move the light model evaluation to the vertex shader, this will give us Gouraud shading
 - This will give us a colour at each vertex which will be interpolated across the polygon
 - Our fragment shader will now be trivial, just one line of code to copy the colour value
 */

// in vec3 normal;
in vec4 vert_colour;
out vec4 FragColor;

void main() {
/*
	vec3 N;
	vec3 L = vec3(1.0, 1.0, 0.0);
	vec4 colour = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 Lcolour = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 H = normalize(L + vec3(0.0, 0.0, 1.0));
	float diffuse;
	float specular;
	float n = 100.0;

	N = normalize(normal);
	L = normalize(L);
	diffuse = dot(N,L);
	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)),n);
	}

	FragColor = min(0.3*colour + diffuse*colour*Lcolour + Lcolour*specular, vec4(1.0));
	FragColor.a = colour.a;
 */
	FragColor = vert_colour;
}

/*
#version 330 core

 *  Simple vertex shader for example six


in vec4 vPosition;
in vec3 vNormal;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMat;
// out vec3 normal;
out vec4 vert_colour;

void main() {

	gl_Position = projection * modelView * vPosition;
	normal = normalMat* vNormal;

	vec3 N;
	vec3 L = vec3(1.0, 1.0, 0.0);
	vec4 colour = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 Lcolour = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 H = normalize(L + vec3(0.0, 0.0, 1.0));
	float diffuse;
	float specular;
	float n = 100.0;

	N = normalize(normal);
	L = normalize(L);
	diffuse = dot(N,L);
	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)),n);
	}

	vert_colour = min(0.3*colour + diffuse*colour*Lcolour + Lcolour*specular, vec4(1.0));
	vert_colour.a = colour.a;
} */
