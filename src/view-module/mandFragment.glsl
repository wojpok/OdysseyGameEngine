#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float offX;
uniform float offY;

vec2 squareImaginary(vec2 number){
	return vec2(
		pow(number.x,2)-pow(number.y,2),
		2*number.x*number.y
	);
}

float iterateMandelbrot(vec2 coord){
	
	vec2 offset = vec2( offX, offY );
	
	vec2 z = coord;
	for(int i=0;i<200;i++){
		z = squareImaginary(z) + offset;
		if(length(z)>2) return i/200.0;
	}
	return 1.0;
}

void main(){
	//color = texture( myTextureSampler, UV ).rgba;
	//color = vec4(1, 1, 1, 1);
	float res = iterateMandelbrot(4*(UV - vec2(0.5, 0.5)));
	
	color = vec4(res, res, res, 1);
	
	vec4 color0 = vec4(0.2, 0, 0.3, 1);
	vec4 color1 = vec4(0.3, 0.1, 1, 1);
	vec4 color2 = vec4(1, 0.2, 0.2, 1);
	
	if(res < 0.5 ) {
		float lerp =  res/0.5;
		color = color1 * lerp + color0 * (1 - lerp);
	}
	else {
		float lerp = (res-0.5)/0.5;
		color = color2 * lerp + color1 * (1 - lerp);
	}
}
