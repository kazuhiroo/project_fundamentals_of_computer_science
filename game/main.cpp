#include "Gra.h"

using namespace sf;
using namespace std;

int main()
{
    srand(time(NULL));

    std::fstream highscore_txt("stats.txt", std::ios::out | std::ios::in);

    int highscore=0;

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

            while(gra->get_working() && !gra->get_esc_g())
            {
                gra->update();

                gra->render();
            }
            

            highscore_txt >> highscore;

            if (highscore < gra->pts)
            {
                highscore_txt<< gra->pts;
                highscore_txt.close();
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
