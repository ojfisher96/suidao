#ifndef COORDINATE_HPP
#define COORDINATE_HPP
namespace Suidao {

template <class T>
struct Vector2 {
    T x, y;
    Vector2();
    Vector2(T x, T y);
};

template <class T>
struct Coord2 {
    T x, y;
    Coord2();
    Coord2(T x, T y);
};

template <class T>
Vector2<T> operator*(const Vector2<T>& v, const T& s);
template <class T>
Vector2<T> operator*(const T& s, const Vector2<T>& v);
template <class T>
Vector2<T> operator/(const Vector2<T>& v, const T& s);
template <class T>
Vector2<T> operator/(const T& s, const Vector2<T>& v);
template <class T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);
template <class T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);

template <class T>
Coord2<T> operator+(const Coord2<T>& c, const Vector2<T>& v);
template <class T>
Coord2<T> operator+(const Vector2<T>& v, const Coord2<T>& c);

template <class T>
Coord2<T> operator-(const Coord2<T>& c, const Vector2<T>& v);
template <class T>
Coord2<T> operator-(const Vector2<T>& v, const Coord2<T>& c);

template <class T>
Vector2<T> operator-(const Coord2<T>& c1, const Coord2<T>& c2);


template <class T>
struct Vector3 {
    T x, y, z;
    Vector3();
    Vector3(T x, T y, T z);
};

template <class T>
struct Coord3 {
    T x, y, z;
    Coord3();
    Coord3(T x, T y, T z);
};

template <class T>
Vector3<T> operator*(const Vector3<T>& v, const T& s);
template <class T>
Vector3<T> operator*(const T& s, const Vector3<T>& v);
template <class T>
Vector3<T> operator/(const Vector3<T>& v, const T& s);
template <class T>
Vector3<T> operator/(const T& s, const Vector3<T>& v);
template <class T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);
template <class T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);

template <class T>
Coord3<T> operator+(const Coord3<T>& c, const Vector3<T>& v);
template <class T>
Coord3<T> operator+(const Vector3<T>& v, const Coord3<T>& c);

template <class T>
Coord3<T> operator-(const Coord3<T>& c, const Vector3<T>& v);
template <class T>
Coord3<T> operator-(const Vector3<T>& v, const Coord3<T>& c);

template <class T>
Vector3<T> operator-(const Coord3<T>& c1, const Coord3<T>& c2);

// Implementation

// 2D

template <class T>
Vector2<T>::Vector2() {}
template <class T>
Vector2<T>::Vector2(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T>
Coord2<T>::Coord2() {}
template <class T>
Coord2<T>::Coord2(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T>
Vector2<T> operator*(Vector2<T> v, T s) {
    return Vector2<T>(v.x * s, v.y * s);
}
template <class T>
Vector2<T> operator*(const T& s, const Vector2<T>& v) {
    return v * s;
}

template <class T>
Vector2<T> operator/(const Vector2<T>& v, const T& s) {
    return Vector2<T>(v.x / s, v.y / s);
}
template <class T>
Vector2<T> operator/(const T& s, const Vector2<T>& v) {
    return v / s;
}


template <class T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <class T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
}

template <class T>
Coord2<T> operator+(const Coord2<T>& c, const Vector2<T>& v) {
    return Coord2<T>(c.x + v.x, c.y + v.y);
}
template <class T>
Coord2<T> operator+(const Vector2<T>& v, const Coord2<T>& c) {
    return c + v;
}

template <class T>
Coord2<T> operator-(const Coord2<T>& c, const Vector2<T>& v) {
    return Coord2<T>(c.x - v.x, c.y - v.y);
}
template <class T>
Coord2<T> operator-(const Vector2<T>& v, const Coord2<T>& c) {
    return c - v;
}

template <class T>
Vector2<T> operator-(const Coord2<T>& c1, const Coord2<T>& c2) {
    return Vector2<T>(c1.x - c2.x, c1.y - c2.y);
}


// 3D


template <class T>
Vector3<T>::Vector3() {}
template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Coord3<T>::Coord3() {}
template <class T>
Coord3<T>::Coord3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector3<T> operator*(Vector3<T> v, T s) {
    return Vector3<T>(v.x * s, v.y * s, v.z * s);
}
template <class T>
Vector3<T> operator*(const T& s, const Vector3<T>& v) {
    return v * s;
}

template <class T>
Vector3<T> operator/(const Vector3<T>& v, const T& s) {
    return Vector3<T>(v.x / s, v.y / s, v.z / s);
}
template <class T>
Vector3<T> operator/(const T& s, const Vector3<T>& v) {
    return v / s;
}


template <class T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <class T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <class T>
Coord3<T> operator+(const Coord3<T>& c, const Vector3<T>& v) {
    return Coord3<T>(c.x + v.x, c.y + v.y, c.z + v.z);
}
template <class T>
Coord3<T> operator+(const Vector3<T>& v, const Coord3<T>& c) {
    return c + v;
}

template <class T>
Coord3<T> operator-(const Coord3<T>& c, const Vector3<T>& v) {
    return Coord3<T>(c.x - v.x, c.y - v.y, c.z - v.z);
}
template <class T>
Coord3<T> operator-(const Vector3<T>& v, const Coord3<T>& c) {
    return c - v;
}

template <class T>
Vector3<T> operator-(const Coord3<T>& c1, const Coord3<T>& c2) {
    return Vector3<T>(c1.x - c2.x, c1.y - c2.y, c1.z - c2.z);
}

}
#endif // COORDINATE_HPP
