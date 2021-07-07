#version 330 core
// Output data ; will be interpolated for each fragment.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 offset;
//uniform float time;
//uniform mat4 offset2;

void main(){

	gl_Position =  MVP * offset * vec4(vertexPosition_modelspace, 1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

