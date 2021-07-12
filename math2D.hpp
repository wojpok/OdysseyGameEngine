#pragma once

class vector2 {
public:
	float x, y;
	
	vector2(float dx, float dy) : x(dx), y(dy) { }
	vector2() : x(0), y(0) { }
	
	friend std::ostream& operator<<(std::ostream& os, const vector2& vec) {
		return os<<"["<<vec.x<<" "<<vec.y<<"]";
	}
	
	vector2  operator+( vector2 vec2) {
		return vector2(x + vec2.x, y + vec2.y);
	}
	
	void  operator+=( vector2 vec2) {
		x += vec2.x;
		y += vec2.y;
	}
	
	vector2  operator-( vector2 vec2) {
		return vector2(x - vec2.x, y - vec2.y);
	}
	
	void  operator-=( vector2 vec2) {
		x -= vec2.x;
		y -= vec2.y;
	}
	
	vector2 operator*(float c) {
		return vector2(c*x, c*y);
	}
	
	void operator *=(float c) {
		x *= c; y *= c;
	}
	
	float operator*(vector2 vec2) {
		return x * vec2.x + y * vec2.y;
	}
};

class mat2 {
public:
	float values[2][2];
	
	mat2() {
		values[0][0] = values[1][1] = 1;
		values[1][0] = values[0][1] = 0;
	}
};

