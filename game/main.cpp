#include "Gra.h"

using namespace sf;


int main()
{
    srand(time(NULL));

    Game gra;

    while (gra.get_working() && !gra.get_exit())
    {      
        
        gra.render();
        srand(time(NULL));
        gra.update();
    }


    return 0;
}
