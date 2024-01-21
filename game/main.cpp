#include "Gra.h"

using namespace sf;
using namespace std;

int main()
{
    srand(time(NULL));

    ifstream h_txt;
    ofstream h1_txt;

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
            //renderwindow
            //return obiekt pojazd
            //window close

            gra = new Game;
            
            menu.play = false;

            while(gra->get_working() && !gra->get_esc_g())
            {
                gra->update();

                gra->render();
            }
           
           h_txt.open("stats.txt", ios::in);

           h_txt >> highscore;

           h_txt.close();

            if (highscore < gra->get_points())
            {
                h1_txt.open("stats.txt", ios::in);

                h1_txt << gra->get_points();

                h1_txt.close();
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
