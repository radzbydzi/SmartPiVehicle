#ifndef GUI_H
#define GUI_H

#include<Primitive.h>
#include<GuiObject.h>
#include<vector>

using namespace std;
class Gui
{
    public:
        Gui();
        virtual ~Gui();
        vector<Primitive> getPrimitives();//have to had calculated position and size from panel; renderer only has to show it
    protected:
    private:
        vector<GuiObject> guiObj;//elements of GUI
};

#endif // GUI_H
