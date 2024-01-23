#include "Gra.h"

using namespace sf;
using namespace std;

int main()
{
    srand(time(NULL));

    //data

    ifstream h_txt;
    ofstream h1_txt;

    int car_chosen = 1;
    int highscore=0;

    //Pointers

    Menu menu;
    
    Game* gra;

    Stats* statystyki;

    //Program loop

    while (menu.get_working_m() && !menu.get_esc())
    {
        
        menu.render_menu();

        menu.update_menu();

        if (menu.Play())
        {
            car_chosen = menu.get_car_type();

            gra = new Game(car_chosen);

            menu.play = false;

            while(gra->get_working() && !gra->get_esc_g())
            {
                gra->update();

                gra->render();
            }

           //getting data from txt file and checking 
           //the highscore after the game

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
