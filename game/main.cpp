#include "Gra.h"

using namespace sf;


int main()
{
    Game gra;

    while (gra.get_working())
    {      
        gra.render();

        gra.update();
    }


    return 0;
}
