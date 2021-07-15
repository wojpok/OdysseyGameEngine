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
	
	vector2 operator/(vector2 vec2) {
		return vector2(x / vec2.x, y / vec2.y);
	}
	
	void operator/=(vector2 vec2) {
		x /= vec2.x;
		y /= vec2.y;
	}
};

class mat2 {
public:
	float values[2][2];
	
	mat2() {
		values[0][0] = values[1][1] = 1;
		values[1][0] = values[0][1] = 0;
	}
	
	mat2(float ang) {
		values[0][0] = values[1][1] = cos(ang);
		values[1][0] = -(values[0][1] = sin(ang));
	}
	
	mat2(float a, float b, float c, float d) {
		values[0][0] = a;
		values[0][1] = b;
		values[1][0] = c;
		values[1][1] = d;
	}
	
	friend std::ostream& operator <<(std::ostream& os, const mat2 mat) {
		return os<<"|"<<mat.values[0][0]<<" "<<mat.values[0][1]<<"|\n|"<<mat.values[1][0]<<" "<<mat.values[1][1]<<"|";
	}
	
	vector2 operator*(vector2 vec) {
		return vector2( vector2(values[0][0], values[0][1]) * vec,
						vector2(values[1][0], values[1][1]) * vec);
	}
};


class line {
	vector2 pos, dir;
};

vector2 lineVsLineCollision(line line1, line line2) {
	
	return vector2(0, 0);
}

bool aabbCollisionDetection(vector2 origin1, vector2 size1, vector2 origin2, vector2 size2) {
	return ((origin1.x <= origin2.x + size2.x) &&
			(origin1.x + size1.x >= origin2.x) &&
			(origin1.y <= origin2.y + size2.y) &&
			(origin1.y + size1.y >= origin2.y));
}







