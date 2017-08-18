#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"Primitive.h"

class Rectangle : public Primitive
{
    public:
        Rectangle(int x, int y, int w, int h, int Color);
        ~Rectangle();
    protected:
    private:
};

#endif // RECTANGLE_H
