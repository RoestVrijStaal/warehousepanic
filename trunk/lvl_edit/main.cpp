#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "random_class.h"

using namespace std;
using namespace sf;

sf::Image load_image(string name)
{
    sf::Image timage;
    timage.LoadFromFile(name);
    timage.SetSmooth(false);
    return timage;
}

int main ()
{
    sf::Shape levelborder = sf::Shape::Rectangle(10,10,466,466,sf::Color(255,255,255),1.f,sf::Color(0,0,0));
    sf::Font fnt_arial_sml;
    fnt_arial_sml.LoadFromFile("arial.ttf",15);
    sf::Image img_truck_hor          = load_image("truck-hor.png"      );
    sf::Image img_truck_vert         = load_image("truck-vert.png"     );
    //-----
    sf::Image img_gate_red_hor       = load_image("gate-red-hor.png"    );
    sf::Image img_gate_orange_hor    = load_image("gate-orange-hor.png" );
    sf::Image img_gate_yellow_hor    = load_image("gate-yellow-hor.png" );
    sf::Image img_gate_green_hor     = load_image("gate-green-hor.png"  );
    sf::Image img_gate_blue_hor      = load_image("gate-blue-hor.png"   );
    sf::Image img_gate_purple_hor    = load_image("gate-purple-hor.png" );
    sf::Image img_gate_red_vert      = load_image("gate-red-vert.png"   );
    sf::Image img_gate_orange_vert   = load_image("gate-orange-vert.png");
    sf::Image img_gate_yellow_vert   = load_image("gate-yellow-vert.png");
    sf::Image img_gate_green_vert    = load_image("gate-green-vert.png" );
    sf::Image img_gate_blue_vert     = load_image("gate-blue-vert.png"  );
    sf::Image img_gate_purple_vert   = load_image("gate-purple-vert.png" );
    //-----
    sf::Image img_conveyor_hor       = load_image("conveyor-hor.png"      );
    sf::Image img_conveyor_vert      = load_image("conveyor-vert.png"     );
    sf::Image img_arrow_vert_up      = load_image("arrow-vert-up.png"     );
    sf::Image img_arrow_vert_down    = load_image("arrow-vert-down.png"   );
    sf::Image img_arrow_hor_left     = load_image("arrow-hor-left.png"    );
    sf::Image img_arrow_hor_right    = load_image("arrow-hor-right.png"   );
    sf::Image img_arrow_vert         = load_image("arrow-vert.png"        );
    sf::Image img_arrow_vertr        = load_image("arrow-vertr.png"       );
    sf::Image img_arrow_hor          = load_image("arrow-hor.png"         );
    sf::Image img_arrow_horr         = load_image("arrow-horr.png"        );
    //-----
    sf::Image img_level_templ        = load_image("warehouse-template.png");
    sf::Image img_save               = load_image("button-save.png"       );
    random_class level[18][18];
    cout << "Create or load? ";
    string choice;
    getline(cin,choice);
    if (choice == "load")
    {
        cout << "Load what file? ";
        getline(cin,choice);
        cout << "Loading file..." << endl;
        string line;
        ifstream myfile (choice.c_str());
        if (myfile.is_open())
        {
            int lines = 0;
            bool start_examine = false;
            while (! myfile.eof() )
            {
                if (lines == 3)
                {
                    start_examine = true;
                }
                string line;
                getline (myfile,line);
                if (start_examine == true)
                {
                    line.erase(0,5);
                    int sofar = 0;
                    while (line.length() >= 1)
                    {
                        if (line.at(0) == 'A')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                        }
                        else if (line.at(0) == 'B')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = false;
                            level[sofar % 18][(int)(sofar / 18)].dir = 1;
                        }
                        else if (line.at(0) == 'C')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = false;
                            level[sofar % 18][(int)(sofar / 18)].dir = 0;
                        }
                        else if (line.at(0) == 'D')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = false;
                            level[sofar % 18][(int)(sofar / 18)].dir = 0;
                        }
                        else if (line.at(0) == 'E')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = false;
                            level[sofar % 18][(int)(sofar / 18)].dir = 1;
                        }
                        else if (line.at(0) == 'F')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = true;
                            level[sofar % 18][(int)(sofar / 18)].dir = 1;
                        }
                        else if (line.at(0) == 'G')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = true;
                            level[sofar % 18][(int)(sofar / 18)].dir = 0;
                        }
                        else if (line.at(0) == 'H')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = true;
                            level[sofar % 18][(int)(sofar / 18)].dir = 0;
                        }
                        else if (line.at(0) == 'I')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_conveyor_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                            level[sofar % 18][(int)(sofar / 18)].change = true;
                            level[sofar % 18][(int)(sofar / 18)].dir = 1;
                        }
                        else if (line.at(0) == 'J')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_blue_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'K')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_blue_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'L')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_green_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'M')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_green_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'N')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_orange_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'O')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_orange_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'P')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_purple_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'Q')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_purple_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'R')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_red_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'S')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_red_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'T')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_yellow_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'U')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_gate_yellow_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'V')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_truck_hor);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        else if (line.at(0) == 'W')
                        {
                            level[sofar % 18][(int)(sofar / 18)] = random_class();
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetImage(img_truck_vert);
                            level[sofar % 18][(int)(sofar / 18)].sprite.SetPosition((sofar / 18) * 24 + 10, (int)(sofar % 18) * 24 + 10);
                        }
                        line.erase(0,1);
                        sofar += 1;
                    }
                }
                lines += 1;
            }
            myfile.close();
        }
    }
    sf::RenderWindow Editor(sf::VideoMode(476,676,32),"Warehouse Panic Level Editor");
    //----------
    vector<sf::Sprite> buttons;
    buttons.push_back( sf::Sprite(img_truck_hor       ,sf::Vector2f(10 ,260 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_red_hor    ,sf::Vector2f(68 ,260 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_orange_hor ,sf::Vector2f(126,260 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_yellow_hor ,sf::Vector2f(184,260 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_green_hor  ,sf::Vector2f(242,260 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_blue_hor   ,sf::Vector2f(10 ,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_purple_hor ,sf::Vector2f(68 ,294 + 220)) );
    //-----
    buttons.push_back( sf::Sprite(img_truck_vert       ,sf::Vector2f(126,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_red_vert    ,sf::Vector2f(150,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_orange_vert ,sf::Vector2f(184,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_yellow_vert ,sf::Vector2f(208,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_green_vert  ,sf::Vector2f(242,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_blue_vert   ,sf::Vector2f(266,294 + 220)) );
    buttons.push_back( sf::Sprite(img_gate_purple_vert ,sf::Vector2f(330,294 + 220)) );
    //-----
    buttons.push_back( sf::Sprite(img_conveyor_hor    ,sf::Vector2f(296,294 + 220)) );
    buttons.push_back( sf::Sprite(img_conveyor_vert   ,sf::Vector2f(296,328 + 220)) );
    buttons.push_back( sf::Sprite(img_save            ,sf::Vector2f(371,621 + 0  )) );
    //----------
    sf::Sprite level_template(img_level_templ, sf::Vector2f(10,10));
    //----------
    bool inEditor = true, mfull = false, rclick = false;
    float mousex = 0, mousey = 0;
    string mwhat = "";
    sf::Sprite mdraw;
    sf::Vector2<int> rid(0,0);
    sf::Shape rdraw = sf::Shape::Rectangle(0,0,0,0,sf::Color(255,255,255),1,sf::Color(0,0,0));
    sf::String str1, str2, str3;
    int ras = 0;
    while (inEditor == true)
    {
        sf::Event Event;
        while (Editor.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
            {
                inEditor = false;
            }
            else if (Event.Type == sf::Event::MouseButtonPressed and
                     Event.MouseButton.Button == sf::Mouse::Left)
            {
                if (mfull == false and rclick == false)
                {
                    for (unsigned int i = 0; i < buttons.size(); i++)
                    {
                        sf::Sprite &c = buttons[i];
                        if (c.GetPosition().x < Editor.GetInput().GetMouseX() and
                            c.GetPosition().y < Editor.GetInput().GetMouseY() and
                            c.GetPosition().y + c.GetSubRect().GetHeight() > Editor.GetInput().GetMouseY() and
                            c.GetPosition().x + c.GetSubRect().GetWidth() > Editor.GetInput().GetMouseX())
                        {
                            mfull = true;
                            const sf::Image* cbi = buttons[i].GetImage();
                            if (cbi == &img_truck_hor)
                            {
                                mwhat = "img_truck_hor";
                                mdraw.SetImage(img_truck_hor);
                            }
                            else if (cbi == &img_truck_vert)
                            {
                                mwhat = "img_truck_vert";
                                mdraw.SetImage(img_truck_vert);
                            }
                            else if (cbi == &img_gate_red_hor)
                            {
                                mwhat = "img_gate_red_hor";
                                mdraw.SetImage(img_gate_red_hor);
                            }
                            else if (cbi == &img_gate_orange_hor)
                            {
                                mwhat = "img_gate_orange_hor";
                                mdraw.SetImage(img_gate_orange_hor);
                            }
                            else if (cbi == &img_gate_yellow_hor)
                            {
                                mwhat = "img_gate_yellow_hor";
                                mdraw.SetImage(img_gate_yellow_hor);
                            }
                            else if (cbi == &img_gate_green_hor)
                            {
                                mwhat = "img_gate_green_hor";
                                mdraw.SetImage(img_gate_green_hor);
                            }
                            else if (cbi == &img_gate_blue_hor)
                            {
                                mwhat = "img_gate_blue_hor";
                                mdraw.SetImage(img_gate_blue_hor);
                            }
                            else if (cbi == &img_gate_purple_hor)
                            {
                                mwhat = "img_gate_purple_hor";
                                mdraw.SetImage(img_gate_purple_hor);
                            }
                            //-----
                            else if (cbi == &img_gate_red_vert)
                            {
                                mwhat = "img_gate_red_vert";
                                mdraw.SetImage(img_gate_red_vert);
                            }
                            else if (cbi == &img_gate_orange_vert)
                            {
                                mwhat = "img_gate_orange_vert";
                                mdraw.SetImage(img_gate_orange_vert);
                            }
                            else if (cbi == &img_gate_yellow_vert)
                            {
                                mwhat = "img_gate_yellow_vert";
                                mdraw.SetImage(img_gate_yellow_vert);
                            }
                            else if (cbi == &img_gate_green_vert)
                            {
                                mwhat = "img_gate_green_vert";
                                mdraw.SetImage(img_gate_green_vert);
                            }
                            else if (cbi == &img_gate_blue_vert)
                            {
                                mwhat = "img_gate_blue_vert";
                                mdraw.SetImage(img_gate_blue_vert);
                            }
                            else if (cbi == &img_gate_purple_vert)
                            {
                                mwhat = "img_gate_purple_vert";
                                mdraw.SetImage(img_gate_purple_vert);
                            }
                            //-----
                            else if (cbi == &img_conveyor_hor)
                            {
                                mwhat = "img_conveyor_hor";
                                mdraw.SetImage(img_conveyor_hor);
                            }
                            else if (cbi == &img_conveyor_vert)
                            {
                                mwhat = "img_conveyor_vert";
                                mdraw.SetImage(img_conveyor_vert);
                            }
                            else if (cbi == &img_save)
                            {
                                Editor.Close();
                                cout << "Enter file name: " << endl << "SAVE WITH A DIFFERENT NAME THAN BEFORE";
                                string fname;
                                getline(cin,fname);
                                ofstream file;
                                file.open(fname.c_str());
                                file << "width=18\n";
                                file << "height=18\n";
                                file << "time=60\n";
                                file << "tile=";
                                for (int i = 0; i < 18; i++)
                                {
                                    for (int ii = 0; ii < 18; ii++)
                                    {
                                        if (level[i][ii].sprite.GetImage() == &img_conveyor_hor)
                                        {
                                            if (level[i][ii].change == false)
                                            {
                                                if (level[i][ii].dir == 0)
                                                {
                                                    file << "D";
                                                }
                                                else
                                                {
                                                    file << "B";
                                                }
                                            }
                                            else
                                            {
                                                if (level[i][ii].dir == 0)
                                                {
                                                    file << "H";
                                                }
                                                else
                                                {
                                                    file << "F";
                                                }
                                            }
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_conveyor_vert)
                                        {
                                            if (level[i][ii].change == false)
                                            {
                                                if (level[i][ii].dir == 0)
                                                {
                                                    file << "C";
                                                }
                                                else
                                                {
                                                    file << "E";
                                                }
                                            }
                                            else
                                            {
                                                if (level[i][ii].dir == 0)
                                                {
                                                    file << "G";
                                                }
                                                else
                                                {
                                                    file << "I";
                                                }
                                            }
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_blue_hor)
                                        {
                                            file << "J";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_blue_vert)
                                        {
                                            file << "K";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_green_hor)
                                        {
                                            file << "L";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_green_vert)
                                        {
                                            file << "M";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_orange_hor)
                                        {
                                            file << "N";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_orange_vert)
                                        {
                                            file << "O";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_purple_hor)
                                        {
                                            file << "P";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_purple_vert)
                                        {
                                            file << "Q";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_red_hor)
                                        {
                                            file << "R";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_red_vert)
                                        {
                                            file << "S";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_yellow_hor)
                                        {
                                            file << "T";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_gate_yellow_vert)
                                        {
                                            file << "U";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_truck_hor)
                                        {
                                            file << "V";
                                        }
                                        else if (level[i][ii].sprite.GetImage() == &img_truck_vert)
                                        {
                                            file << "W";
                                        }
                                        else
                                        {
                                            file << "A";
                                        }
                                    }
                                }
                                file.close();
                                exit(0);
                            }
                            mdraw.SetSubRect(sf::IntRect(0,0,mdraw.GetImage()->GetWidth(),mdraw.GetImage()->GetHeight()));
                            mdraw.SetCenter(mdraw.GetSubRect().GetWidth() / 2,mdraw.GetSubRect().GetHeight() / 2);
                        }
                    }
                    for (int i = 0; i < 18; i++)
                    {
                        for (int ii = 0; ii < 18; ii++)
                        {
                            sf::Sprite &c = level[i][ii].sprite;
                            if (c.GetPosition().x < Editor.GetInput().GetMouseX() and
                                c.GetPosition().y < Editor.GetInput().GetMouseY() and
                                c.GetPosition().x + c.GetSubRect().GetWidth() > Editor.GetInput().GetMouseX() and
                                c.GetPosition().y + c.GetSubRect().GetHeight() > Editor.GetInput().GetMouseY())
                            {
                                if (level[i][ii].sprite.GetImage() == &img_conveyor_hor or level[i][ii].sprite.GetImage() == &img_conveyor_vert)
                                {
                                    if (level[i][ii].dir == 0)
                                    {
                                        level[i][ii].dir = 1;
                                    }
                                    else if (level[i][ii].dir == 1)
                                    {
                                        level[i][ii].dir = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                else if (Editor.GetInput().GetMouseY() - (mdraw.GetSubRect().GetHeight() / 2) > 250 and rclick == false)
                {
                    mfull = false;
                }
                else if (rclick == true)
                {
                    if (Editor.GetInput().GetMouseY() > rdraw.GetPosition().y and
                        Editor.GetInput().GetMouseY() < rdraw.GetPosition().y + 20 and
                        Editor.GetInput().GetMouseX() > rdraw.GetPosition().x and
                        Editor.GetInput().GetMouseX() < rdraw.GetPosition().x + 150)
                    {
                        level[rid.x][rid.y] = random_class();
                    }
                    else if (Editor.GetInput().GetMouseY() > rdraw.GetPosition().y  + 20 and
                        Editor.GetInput().GetMouseY() < rdraw.GetPosition().y + 40 and
                        Editor.GetInput().GetMouseX() > rdraw.GetPosition().x and
                        Editor.GetInput().GetMouseX() < rdraw.GetPosition().x + 150)
                    {
                        if (level[rid.x][rid.y].sprite.GetImage() == &img_conveyor_hor or level[rid.x][rid.y].sprite.GetImage() == &img_conveyor_vert)
                        {
                            if (level[rid.x][rid.y].change == false)
                            {
                                level[rid.x][rid.y].change = true;
                            }
                            else if (level[rid.x][rid.y].change == true)
                            {
                                level[rid.x][rid.y].change = false;
                            }
                        }
                    }
                    else if (Editor.GetInput().GetMouseY() > rdraw.GetPosition().y  + 40 and
                        Editor.GetInput().GetMouseY() < rdraw.GetPosition().y + 60 and
                        Editor.GetInput().GetMouseX() > rdraw.GetPosition().x and
                        Editor.GetInput().GetMouseX() < rdraw.GetPosition().x + 150)
                    {
                        if (level[rid.x][rid.y].sprite.GetImage() == &img_conveyor_hor or level[rid.x][rid.y].sprite.GetImage() == &img_conveyor_vert)
                        {
                            if (level[rid.x][rid.y].dir == 0)
                            {
                                level[rid.x][rid.y].dir = 1;
                            }
                            else if (level[rid.x][rid.y].dir == 1)
                            {
                                level[rid.x][rid.y].dir = 0;
                            }
                        }
                    }
                }
                else
                {
                    mfull = false;
                }
            }
            else if (Event.Type == sf::Event::MouseButtonPressed and
                     Event.MouseButton.Button == sf::Mouse::Right)
            {
                if (mfull == false)
                {
                    for (int i = 0; i < 18; i++)
                    {
                        for (int ii = 0; ii < 18; ii++)
                        {
                            sf::Sprite &c = level[i][ii].sprite;
                            if (c.GetPosition().x < Editor.GetInput().GetMouseX() and
                            c.GetPosition().y < Editor.GetInput().GetMouseY() and
                            c.GetPosition().y + c.GetSubRect().GetHeight() > Editor.GetInput().GetMouseY() and
                            c.GetPosition().x + c.GetSubRect().GetWidth() > Editor.GetInput().GetMouseX())
                            {
                                if (c.GetImage() == &img_conveyor_vert)
                                {
                                    if (level[i][ii].change == false)
                                    {
                                        rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
                                        rdraw.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2),
                                                          level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2));
                                        rclick = true;
                                        rid = sf::Vector2<int>(i,ii);
                                        ras = 3;
                                        str1 = sf::String("Delete",fnt_arial_sml,15);
                                        str2 = sf::String("Changable",fnt_arial_sml,15);
                                        if (level[i][ii].dir == 0)
                                        {
                                            str3 = sf::String("Face Down",fnt_arial_sml,15);
                                        }
                                        else
                                        {
                                            str3 = sf::String("Face Up",fnt_arial_sml,15);
                                        }
                                        str1.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
                                        str2.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
                                        str3.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
                                        str1.SetColor(sf::Color(0,0,0));
                                        str2.SetColor(sf::Color(0,0,0));
                                        str3.SetColor(sf::Color(0,0,0));
                                    }
                                    else
                                    {
                                        rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
                                        rdraw.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2),
                                                          level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2));
                                        rclick = true;
                                        rid = sf::Vector2<int>(i,ii);
                                        ras = 3;
                                        str1 = sf::String("Delete",fnt_arial_sml,15);
                                        str2 = sf::String("Unchangable",fnt_arial_sml,15);
                                        if (level[i][ii].dir == 0)
                                        {
                                            str3 = sf::String("Start Down",fnt_arial_sml,15);
                                        }
                                        else
                                        {
                                            str3 = sf::String("Start Up",fnt_arial_sml,15);
                                        }
                                        str1.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
                                        str2.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
                                        str3.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
                                        str1.SetColor(sf::Color(0,0,0));
                                        str2.SetColor(sf::Color(0,0,0));
                                        str3.SetColor(sf::Color(0,0,0));
                                    }
                                }
                                else if (c.GetImage() == &img_conveyor_hor)
                                {
                                    if (level[i][ii].change == false)
                                    {
                                        rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
                                        rdraw.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2),
                                                          level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2));
                                        rclick = true;
                                        rid = sf::Vector2<int>(i,ii);
                                        ras = 3;
                                        str1 = sf::String("Delete",fnt_arial_sml,15);
                                        str2 = sf::String("Changable",fnt_arial_sml,15);
                                        if (level[i][ii].dir == 0)
                                        {
                                            str3 = sf::String("Face Right",fnt_arial_sml,15);
                                        }
                                        else
                                        {
                                            str3 = sf::String("Face Left",fnt_arial_sml,15);
                                        }
                                        str1.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
                                        str2.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
                                        str3.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
                                        str1.SetColor(sf::Color(0,0,0));
                                        str2.SetColor(sf::Color(0,0,0));
                                        str3.SetColor(sf::Color(0,0,0));
                                    }
                                    else
                                    {
                                        rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
                                        rdraw.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2),
                                                          level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2));
                                        rclick = true;
                                        rid = sf::Vector2<int>(i,ii);
                                        ras = 3;
                                        str1 = sf::String("Delete",fnt_arial_sml,15);
                                        str2 = sf::String("Unchangable",fnt_arial_sml,15);
                                        if (level[i][ii].dir == 0)
                                        {
                                            str3 = sf::String("Start Right",fnt_arial_sml,15);
                                        }
                                        else
                                        {
                                            str3 = sf::String("Start Left",fnt_arial_sml,15);
                                        }
                                        str1.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
                                        str2.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
                                        str3.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                         level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
                                        str1.SetColor(sf::Color(0,0,0));
                                        str2.SetColor(sf::Color(0,0,0));
                                        str3.SetColor(sf::Color(0,0,0));
                                    }
                                }
                                else
                                {
                                    rdraw = sf::Shape::Rectangle(0,0,150,20,sf::Color(255,255,255),1,sf::Color(0,0,0));
                                    rdraw.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2),
                                                      level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2));
                                    rclick = true;
                                    rid = sf::Vector2<int>(i,ii);
                                    ras = 1;
                                    str1 = sf::String("Delete",fnt_arial_sml,15);
                                    str2 = sf::String("Changable",fnt_arial_sml,15);
                                    if (level[i][ii].dir == 0)
                                    {
                                        str3 = sf::String("Face Down",fnt_arial_sml,15);
                                    }
                                    else
                                    {
                                        str3 = sf::String("Face Up",fnt_arial_sml,15);
                                    }
                                    str1.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                     level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
                                    str2.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                     level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
                                    str3.SetPosition(level[i][ii].sprite.GetPosition().x + (level[i][ii].sprite.GetSubRect().GetWidth() / 2 + 5),
                                                     level[i][ii].sprite.GetPosition().y + (level[i][ii].sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
                                    str1.SetColor(sf::Color(0,0,0));
                                    str2.SetColor(sf::Color(0,0,0));
                                    str3.SetColor(sf::Color(0,0,0));
                                }
                            }
                        }
                    }
                }
            }
            else if (Event.Type == sf::Event::MouseButtonReleased and
                     Event.MouseButton.Button == sf::Mouse::Left)
            {
                if (mfull == true and rclick == false)
                {
                    if (mousex > 0 and mousey > 0 and mousex < 476 and mousey < 476)
                    {
                        mfull = false;
                        const sf::Image *mi = mdraw.GetImage();
                        sf::Vector2f mip = mdraw.GetPosition();
                        mip.x -= (mi->GetWidth () / 2);
                        mip.y -= (mi->GetHeight() / 2);
                        int mipx = (mip.x / 24);
                        int mipy = (mip.y / 24);
                        level[mipx][mipy] = random_class();
                        level[mipx][mipy].sprite.SetImage( (*mi) );
                        level[mipx][mipy].sprite.SetPosition(mipx * 24 + 10, mipy * 24 + 10);
                    }
                    else
                    {
                        mfull = false;
                    }
                }
                else if (rclick == true)
                {
                    rclick = false;
                }
            }
            else if (sf::Event::MouseMoved)
            {
                mousex = Event.MouseMove.X;
                mousey = Event.MouseMove.Y;
                mdraw.SetPosition(mousex,mousey);
            }
        }
        Editor.Clear(sf::Color(0,185,235));
        for (unsigned int i = 0; i < buttons.size(); i++)
        {
            Editor.Draw(buttons[i]);
        }
        Editor.Draw(levelborder);
        Editor.Draw(level_template);
        for (int i = 0; i < 18; i++)
        {
            for (int ii = 0; ii < 18; ii++)
            {
                Editor.Draw(level[i][ii].sprite);
                if (level[i][ii].sprite.GetImage() == &img_conveyor_hor)
                {
                    if (level[i][ii].change == false)
                    {
                        if (level[i][ii].dir == 0)
                        {
                            sf::Sprite tmp(img_arrow_hor,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                        else
                        {
                            sf::Sprite tmp(img_arrow_horr,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                    }
                    else
                    {
                        if (level[i][ii].dir == 0)
                        {
                            sf::Sprite tmp(img_arrow_hor_left,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                        else
                        {
                            sf::Sprite tmp(img_arrow_hor_right,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                    }
                }
                else if (level[i][ii].sprite.GetImage() == &img_conveyor_vert)
                {
                    if (level[i][ii].change == false)
                    {
                        if (level[i][ii].dir == 0)
                        {
                            sf::Sprite tmp(img_arrow_vert,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                        else
                        {
                            sf::Sprite tmp(img_arrow_vertr,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                    }
                    else
                    {
                        if (level[i][ii].dir == 0)
                        {
                            sf::Sprite tmp(img_arrow_vert_up,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                        else
                        {
                            sf::Sprite tmp(img_arrow_vert_down,level[i][ii].sprite.GetPosition());
                            Editor.Draw(tmp);
                        }
                    }
                }
            }
        }
        if (rclick == true)
        {
            Editor.Draw(rdraw);
            if (ras == 1)
            {
                Editor.Draw(str1);
            }
            else if (ras == 2)
            {
                Editor.Draw(str1);
                Editor.Draw(str2);
            }
            else if (ras == 3)
            {
                Editor.Draw(str1);
                Editor.Draw(str2);
                Editor.Draw(str3);
            }
        }
        if (mfull == true)
        {
            Editor.Draw(mdraw);
        }
        Editor.Display();
    }
    Editor.Close();
    return 0;
}

