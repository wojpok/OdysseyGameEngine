#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
	color = texture( myTextureSampler, UV ).rgba;
	//color = vec4(1, 1, 1, 1);
}


