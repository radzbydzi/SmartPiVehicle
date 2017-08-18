#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include<vector>
#include"Texture.h"

using namespace std;
struct Coord
{
    int x,y;
    bool inPx=true;//other option is using percents: 0%-50% => -1.0 - 0.0 | 50%-100% => 0.0 - 1.0
    Coord(int x,int y);
    Coord(int x,int y, bool inPx);
};
struct Color
{
    int r,g,b;
    Color(int r,int g, int b);
    Color();
};
class Primitive
{
    public:
        Primitive();
        virtual ~Primitive();
    protected:
    private:
        vector<Coord> vertices;
        vector<Coord> texCoords;
        Texture* tex;
        Color color = Color(0,0,0);
};

#endif // PRIMITIVE_H
