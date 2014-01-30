#ifndef COORDINATE_HPP
#define COORDINATE_HPP
namespace suidao {

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


}
#endif // COORDINATE_HPP
