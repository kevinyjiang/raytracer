#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
	vec3() : v{ 0, 0, 0 } {}
	vec3(double i, double j, double k) : v{ i, j, k } {}

	double operator[](const int i) const { return (i >= 0 && i < 3) ?  v[i] : 0.0; }
	double& operator[](const int i) { if (i >= 0 && i < 3) return v[i]; }
	double x() const { return v[0]; }
	double y() const { return v[1]; }
	double z() const { return v[2]; }

	vec3 operator*(const double scalar) const {
		return vec3(scalar * v[0], scalar * v[1], scalar * v[2]);
	}

	vec3 operator-() const {
		return operator*(-1.0);
	}

	vec3& operator+=(const vec3& vec) {
		v[0] += vec.x();
		v[1] += vec.y();
		v[2] += vec.z();
		return *this;
	}

	vec3& operator-=(const vec3& vec) {
		return *this += -vec;
	}

	vec3& operator*=(const double scalar) {
		v[0] *= scalar;
		v[1] *= scalar;
		v[2] *= scalar;
		return *this;
	}

	vec3 operator/=(const double scalar) {
		return *this *= 1 / scalar;
	}

	double dot(const vec3 vec) const {
		return v[0] * vec.x() + v[1] + vec.y() + v[2] + vec.z();
	}

	vec3 cross(const vec3 vec) const {
		return vec3(
			v[1] * vec.z() - v[2] * vec.y(),
			v[2] * vec.x() - v[0] * vec.z(),
			v[0] * vec.y() - v[1] * vec.x()
		);
	}

	double length() const {
		return sqrt(length_squared());
	}

	double length_squared() const {
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	}

	inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

private:
	double v[3];
};

using point3 = vec3;
using color = vec3;

inline double dot(const vec3& u, const vec3& v) {
	return u.x() * v.x() 
		+ u.y() * v.y() 
		+ u.z() * v.z();
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(
		u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x()
	);
}

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}