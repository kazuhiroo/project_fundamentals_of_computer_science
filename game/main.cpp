#include "Gra.h"

using namespace sf;
using namespace std;

int main()
{
    srand(time(NULL));

    //data

    string nickname;

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

            switch (car_chosen)
            {
                case 1: h_txt.open("stats_ferrari.txt", ios::out); break;

                case 2: h_txt.open("stats_f1.txt", ios::out); break;

                case 3: h_txt.open("stats_miami.txt", ios::out); break;
            }

           h_txt >> highscore;

           h_txt.close();

            if (highscore < gra->get_points())
            {
                cout << endl << "CONGRATULATIONS! NEW HIGHSCORE!" << endl;
                cout << "Please, enter your nickname: ";

                switch (car_chosen)
                {
                    case 1: h1_txt.open("stats_ferrari.txt", ios::in); break;

                    case 2: h1_txt.open("stats_f1.txt", ios::in); break;

                    case 3: h1_txt.open("stats_miami.txt", ios::in); break;
                }

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
