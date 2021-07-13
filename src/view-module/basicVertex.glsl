#version 330 core
// Output data ; will be interpolated for each fragment.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec4 offset;
//uniform float time;
//uniform mat4 offset2;

void main(){
	
	float ang = offset[3];
	vec4 off = vec4(offset[0], offset[1], offset[2], 0);
	
	mat4 rotation = mat4(vec4(1, 0, 0, 0),
						 vec4(0, cos(ang), sin(ang), 0),
						 vec4(0, -sin(ang), cos(ang), 0),
						 vec4(0, 0, 0, 1));
	
	gl_Position =  MVP * ( (rotation * vec4(vertexPosition_modelspace, 1)) + off);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

