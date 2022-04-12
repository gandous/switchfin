
#ifndef RECT_HPP_
#define RECT_HPP_

#include "type/Vector2.hpp"

namespace gana {

template<typename T>
class Rect {
    public:
        Rect();
        Rect(T x, T y, T w, T h);
        Rect(Vector2<T> position, Vector2<T> size);
        ~Rect();

        T x;
        T y;
        T w;
        T h;
    private:
};

#include "Rect.inl"

typedef Rect<float> Rectf;
typedef Rect<int> Recti;
typedef Rect<unsigned int> Rectui;

}

#endif /* RECT_HPP_ */