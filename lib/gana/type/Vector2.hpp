
#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <cmath>
#include <functional>
#include "Logger.hpp"

namespace gana {

template<typename T>
class Vector2 {
    public:
        Vector2();
        Vector2(T x, T y);
        Vector2(const Vector2<T> &vect);
        ~Vector2();

        Vector2 normalize();
        float length();
        Vector2<T> &operator*(T nb);
        Vector2<T> operator*(const Vector2<T> &vec) const;
        Vector2<T> operator-(const Vector2<T> &vec) const;
        Vector2<T> operator+(const Vector2<T> &vec) const;
        Vector2<T> &operator=(const Vector2<T> &vec);
        T x;
        T y;
    protected:
    private:
};

template<typename T>
class HashVector {
    public:
        std::size_t operator()(const Vector2<T> &vect) const
        {
            return (std::hash<T>()(vect.x) & std::hash<T>()(vect.y));
        }

};

#include "Vector2.inl"

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;

template<typename T>
std::string to_string(Vector2<T> vector)
{
    return ("Vector2(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")");
}
}

#endif /* !VECTOR2_HPP_ */
