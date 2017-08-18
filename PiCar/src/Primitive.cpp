#include "Primitive.h"

Primitive::Primitive()
{
    //ctor
}

Primitive::~Primitive()
{
    //dtor
}
Color::Color(int r,int g, int b)
{
    this->r=r;
    this->g=g;
    this->b=b;
}
Coord::Coord(int x,int y)
{
    this->x=x;
    this->y=y;
}
Coord::Coord(int x,int y, bool inPx)
{
    this->x=x;
    this->y=y;
    this->inPx=inPx;
}
