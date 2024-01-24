#include "Gra.h"

using namespace sf;
using namespace std;

string nickname;
bool good_nick = false;

void enter_nick()
{
    cin >> nickname;
    if (nickname.size() > 6)
    {
        cout << "Your nickname must not have more than 6 characters. Please try again." << endl;
    }
    else
    {
        good_nick = true;
    }
}


int main()
{
    srand(time(NULL));

    //data

  

    ifstream h_txt;
    ofstream h1_txt, n_stats;

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
                
               do
                {
                    cout << "Please, enter your nickname: ";
                    enter_nick();
                }
                while (good_nick == false);


                switch (car_chosen)
                {
                    case 1: h1_txt.open("stats_ferrari.txt", ios::in); break;

                    case 2: h1_txt.open("stats_f1.txt", ios::in); break;

                    case 3: h1_txt.open("stats_miami.txt", ios::in); break;
                }

                h1_txt << gra->get_points() << std::endl << nickname;

                h1_txt.close();
            }

            std::cout << endl;

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
