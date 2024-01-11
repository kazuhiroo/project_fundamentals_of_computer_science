#include "Gra.h"

using namespace sf;

int main()
{
    srand(time(NULL));

    Menu menu;
    
    Game* gra;

    Stats* statystyki;

    while (menu.get_working_m() && !menu.get_esc())
    {
        
        menu.render_menu();

        menu.update_menu();

        if (menu.Play())
        {
            gra = new Game;
            
            menu.play = false;

            while(gra->get_working() && !gra->get_exit())
            {
                gra->update();

                gra->render();
            }

            delete gra;
        }

        if (menu.Statistics())
        {
            statystyki = new Stats;

            menu.stats = false;

            while (statystyki->get_working_s() && !statystyki->get_esc_s())
            {
                statystyki->update_stats();

                statystyki->render_stats();
            }

            delete statystyki;
        }
    }
      
    return 0;
}
