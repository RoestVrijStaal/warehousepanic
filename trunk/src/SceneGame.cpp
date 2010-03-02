#include "SceneGame.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"

using namespace std;
using namespace sf;

// This is the important part. You need to give this scene a name. I call this one game
SceneGame::SceneGame() : Scene( "game" )
{
	App.AddScene( this );
}

SceneGame::~SceneGame()
{
}

void SceneGame::Initialize()
{
	//Resouse Loading
    img_crate_red.LoadFromFile("media/crate-red.png");
    img_crate_red.SetSmooth(false);

    img_crate_orange.LoadFromFile("media/crate-orange.png");
    img_crate_orange.SetSmooth(false);

    img_crate_yellow.LoadFromFile("media/crate-yellow.png");
    img_crate_yellow.SetSmooth(false);

    img_crate_green.LoadFromFile("media/crate-green.png");
    img_crate_green.SetSmooth(false);

    img_crate_blue.LoadFromFile("media/crate-blue.png");
    img_crate_blue.SetSmooth(false);

    img_crate_purple.LoadFromFile("media/crate-purple.png");
    img_crate_purple.SetSmooth(false);
    //-----------
    img_conveyor_vert.LoadFromFile("media/conveyor-vert.png");
    img_conveyor_vert.SetSmooth(false);

    img_conveyor_hor.LoadFromFile("media/conveyor-hor.png");
    img_conveyor_hor.SetSmooth(false);
    //-----------
    img_incinerator.LoadFromFile("media/incinerator.png");
    img_incinerator.SetSmooth(false);
    //-----------
    img_arrow_vert_left.LoadFromFile("media/arrow-vert-left.png");
    img_arrow_vert_left.SetSmooth(false);

    img_arrow_vert_right.LoadFromFile("media/arrow-vert-right.png");
    img_arrow_vert_right.SetSmooth(false);

    img_arrow_vertr_left.LoadFromFile("media/arrow-vertr-left.png");
    img_arrow_vertr_left.SetSmooth(false);

    img_arrow_vertr_right.LoadFromFile("media/arrow-vertr-right.png");
    img_arrow_vertr_right.SetSmooth(false);

    img_arrow_hor_left.LoadFromFile("media/arrow-hor-left.png");
    img_arrow_hor_left.SetSmooth(false);

    img_arrow_hor_right.LoadFromFile("media/arrow-hor-right.png");
    img_arrow_hor_right.SetSmooth(false);
    //-----------
    img_gate_red_right.LoadFromFile("media/gate-red-right.png");
    img_gate_red_right.SetSmooth(false);

    img_gate_orange_right.LoadFromFile("media/gate-orange-right.png");
    img_gate_orange_right.SetSmooth(false);

    img_gate_yellow_right.LoadFromFile("media/gate-yellow-right.png");
    img_gate_yellow_right.SetSmooth(false);

    img_gate_green_right.LoadFromFile("media/gate-green-right.png");
    img_gate_green_right.SetSmooth(false);

    img_gate_blue_right.LoadFromFile("media/gate-blue-right.png");
    img_gate_blue_right.SetSmooth(false);

    img_gate_purple_right.LoadFromFile("media/gate-purple-right.png");
    img_gate_purple_right.SetSmooth(false);
    //-----------
    img_truck_right.LoadFromFile("media/truck-right.png");
    img_truck_right.SetSmooth(false);
    //----------------------------------------------
    fnt_arial_lrg.LoadFromFile("media/arial.ttf",40);

    fnt_arial_sml.LoadFromFile("media/arial.ttf",12);

    //Set everything up
    str_paused_msg1 = sf::String("Game Paused",fnt_arial_lrg,40);
    str_paused_msg1.SetPosition(32.5f,25);
    str_paused_msg1.SetColor(sf::Color(0,0,0));

    str_paused_msg2 = sf::String("Continue",fnt_arial_lrg,35);
    str_paused_msg2.SetPosition(90,102.5f);
    str_paused_msg2.SetColor(sf::Color(0,0,0));

    str_paused_msg3 = sf::String("Quit",fnt_arial_lrg,35);
    str_paused_msg3.SetPosition(125,172.5f);
    str_paused_msg3.SetColor(sf::Color(0,0,0));

    str_score = sf::String("Score: 0",fnt_arial_sml,12);
    str_score.SetPosition(4,224);
    str_score.SetColor(sf::Color(0,0,0));

    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 10, 10 * 12);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 9, 10 * 13);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 7, 10 * 13);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 11, 10 * 13);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 8, 10 * 14);
    conveyors.back().dir_amo = 2;
    conveyors.back().dir = 2;
    conveyors.back().speed = 1;
    conveyors.back().change = true;
    conveyors.back().arrow_0.SetImage(img_arrow_vertr_left);
    conveyors.back().arrow_1.SetImage(img_arrow_vertr_right);
    conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 12, 10 * 14);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 9, 10 * 15);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 8, 10 * 16);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 7, 10 * 17);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 11, 10 * 15);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 10, 10 * 16);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 9, 10 * 17);
    conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = true;
    conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_vert);
    conveyors.back().sprite.SetPosition(20 * 8, 10 * 18);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 1;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_hor_right);
    //conveyors.back().arrow_1.SetImage(img_arrow_hor_left);
    //conveyors.back().arrow_0.SetPosition(conveyors.back().sprite.GetPosition());
    //conveyors.back().arrow_1.SetPosition(conveyors.back().sprite.GetPosition());
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 10, 10 * 18);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_vert_left);
    //conveyors.back().arrow_1.SetImage(img_arrow_vert_right);
    //conveyors.back().arrow_0.SetPosition(20 * 5, 10 * 5);
    //conveyors.back().arrow_1.SetPosition(20 * 5, 10 * 5);
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 11, 10 * 19);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_vert_left);
    //conveyors.back().arrow_1.SetImage(img_arrow_vert_right);
    //conveyors.back().arrow_0.SetPosition(20 * 5, 10 * 5);
    //conveyors.back().arrow_1.SetPosition(20 * 5, 10 * 5);
    conveyors.push_back(conveyor());
    conveyors.back().sprite.SetImage(img_conveyor_hor);
    conveyors.back().sprite.SetPosition(20 * 12, 10 * 20);
    //conveyors.back().dir_amo = 2;
    conveyors.back().dir = 0;
    conveyors.back().speed = 1;
    conveyors.back().change = false;
    //conveyors.back().arrow_0.SetImage(img_arrow_vert_left);
    //conveyors.back().arrow_1.SetImage(img_arrow_vert_right);
    //conveyors.back().arrow_0.SetPosition(20 * 5, 10 * 5);
    //conveyors.back().arrow_1.SetPosition(20 * 5, 10 * 5);
    //-----------
    /*
    incinerators.push_back(sf::Sprite());
    incinerators.back().SetImage(img_incinerator);
    incinerators.back().SetPosition(20 * 9, 10 * 9);
    */
    //-----------
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_red_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 0 + 4);
    gates.back().color = "red";
    gates.back().value = 10;
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_orange_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 3 + 4);
    gates.back().color = "orange";
    gates.back().value = 10;
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_yellow_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 6 + 4);
    gates.back().color = "yellow";
    gates.back().value = 10;
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_green_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 9 + 4);
    gates.back().color = "green";
    gates.back().value = 10;
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_blue_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 12 + 4);
    gates.back().color = "blue";
    gates.back().value = 10;
    gates.push_back(gate());
    gates.back().sprite.SetImage(img_gate_purple_right);
    gates.back().sprite.SetPosition(20 * 0, 10 * 15 + 4);
    gates.back().color = "purple";
    gates.back().value = 10;
    //-----------
    trucks.push_back(truck());
    trucks.back().sprite.SetImage(img_truck_right);
    trucks.back().sprite.SetPosition(20 * 13, 10 * 19 + 4);
    trucks.back().intervalmax = trucks.back().interval = 60;
    trucks.back().colors.push_back("red");
    trucks.back().colors.push_back("orange");
    trucks.back().colors.push_back("yellow");
    trucks.back().colors.push_back("green");
    trucks.back().colors.push_back("blue");
    trucks.back().colors.push_back("purple");
    trucks.back().delay = 0;
    trucks.back().active = true;
    //--------------------------
    pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
    pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));

    //Other stuff
    isMouseDown = false;
    paused = false;
    points = 0;
    csel = 0;
}

void SceneGame::Terminate()
{
	// Free any resources reserved in initialize()
}

void SceneGame::Step()
{
	//Events
	sf::Vector2f mousepos(window->GetInput().GetMouseX(),window->GetInput().GetMouseY());

	if (mousepos.x > pbutton1.GetPointPosition(0).x and mousepos.y > pbutton1.GetPointPosition(0).y and
        mousepos.x < pbutton1.GetPointPosition(2).x and mousepos.y < pbutton1.GetPointPosition(2).y and
        paused == true)
    {
        csel = 1;
    }
    else if (mousepos.x > pbutton2.GetPointPosition(0).x and mousepos.y > pbutton2.GetPointPosition(0).y and
        mousepos.x < pbutton2.GetPointPosition(2).x and mousepos.y < pbutton2.GetPointPosition(2).y and
        paused == true)
    {
        csel = 2;
    }
    else
    {
        csel = 0;
    }
    if (window->GetInput().IsMouseButtonDown( sf::Mouse::Left) and isMouseDown == false)
    {
        if (paused == false)
        {
            sf::Vector2f mousepos(window->GetInput().GetMouseX(),window->GetInput().GetMouseY());
            for (unsigned int i = 0; i < conveyors.size(); i++)
            {
                conveyor &c = conveyors[i];
                if (c.sprite.GetPosition().x + 8 < mousepos.x and c.sprite.GetPosition().y + 3 < mousepos.y and
                    c.sprite.GetPosition().y + c.sprite.GetSubRect().GetHeight() - 3 > mousepos.y and
                    c.sprite.GetPosition().x + c.sprite.GetSubRect().GetWidth() - 8 > mousepos.y and
                    c.change == true)
                {
                    if (c.dir == 0)
                    {
                        c.dir = 1;
                    }
                    else
                    {
                        c.dir = 0;
                    }
                }
            }
        }
        else
        {
            if (csel == 1)
            {
                paused = false;
            }
            else if (csel == 2)
            {
                EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
            }
        }
    }
    if (window->GetInput().IsKeyDown(sf::Key::Space) and paused == false)
    {
        if (paused == false)
        {
            paused = true;
            csel = 0;
        }
    }
    //Compute
    if (paused == false)
    {
        for (unsigned int i = 0; i < crates.size(); i++)
        {
            if (crates[i].tomove.x != 0 or crates[i].tomove.y != 0)
            {
                if (crates[i].tomove.x < 0)
                {
                    crates[i].sprite.Move(-2,0);
                    crates[i].tomove.x += 2;
                }
                else if (crates[i].tomove.x > 0)
                {
                    crates[i].sprite.Move(2,0);
                    crates[i].tomove.x -= 2;
                }
                if (crates[i].tomove.y < 0)
                {
                    crates[i].sprite.Move(0,-1);
                    crates[i].tomove.y += 1;
                }
                else if (crates[i].tomove.y > 0)
                {
                    crates[i].sprite.Move(0,1);
                    crates[i].tomove.y -= 1;
                }
                continue;
            }
            sf::Vector2f ipos = crates[i].sprite.GetPosition();
            for (unsigned int ii = 0; ii < conveyors.size(); ii++)
            {
                sf::Vector2f iipos = conveyors[ii].sprite.GetPosition();
                if (ipos.x >= iipos.x - 20 and ipos.x <= iipos.x + 20 and
                    ipos.y >= iipos.y - 17 and ipos.y <= iipos.y + 9 and
                    crates[i].incint == false and crates[i].coll == false)
                {
                    const sf::Image* iis = conveyors[ii].sprite.GetImage();
                    if (iis == &img_conveyor_hor)
                    {
                        if (conveyors[ii].dir == 0)
                        {
                            crates[i].tomove.x = -(conveyors[ii].speed * 2);
                            crates[i].tomove.y = -(conveyors[ii].speed * 1);
                        }
                        else
                        {
                            crates[i].tomove.x = conveyors[ii].speed * 2;
                            crates[i].tomove.y = conveyors[ii].speed * 1;
                        }
                    }
                    else
                    {
                        if (conveyors[ii].dir == 0)
                        {
                            crates[i].tomove.x = conveyors[ii].speed * 2;
                            crates[i].tomove.y = -(conveyors[ii].speed * 1);
                        }
                        else
                        {
                            crates[i].tomove.x = -(conveyors[ii].speed * 2);
                            crates[i].tomove.y = conveyors[ii].speed * 1;
                        }
                    }
                }
            }
            for (unsigned int ii = 0; ii < incinerators.size(); ii++)
            {
                sf::Vector2f iipos = incinerators[ii].GetPosition();
                if (ipos.x >= iipos.x - 20 and ipos.x <= iipos.x + 20 and
                    ipos.y >= iipos.y - 17 and ipos.y <= iipos.y + 10 and
                    crates[i].tomove.x == 0 and crates[i].tomove.y == 0)
                {
                    crates[i].incint = true;
                    sf::IntRect cratesub = crates[i].sprite.GetSubRect();
                    if (cratesub.Bottom >= 1.25)
                    {
                        cratesub.Bottom -= 1.25;
                        crates[i].sprite.SetSubRect(cratesub);
                        crates[i].sprite.Move(0,1.25);
                    }
                    else
                    {
                        crates.erase(crates.begin() + i);
                    }
                }
            }
            for (unsigned int ii = 0; ii < gates.size(); ii++)
            {
                sf::Vector2f iipos = gates[ii].sprite.GetPosition();
                if (ipos.x >= iipos.x + 20 and ipos.x <= iipos.x + 65 and
                    ipos.y >= iipos.y + 20 and ipos.y <= iipos.y + 50)
                {
                    crates[i].coll = true;
                    sf::IntRect cratesub = crates[i].sprite.GetSubRect();
                    const sf::Image* iis = gates[ii].sprite.GetImage();
                    if (iis == &img_gate_red_right or iis == &img_gate_orange_right or
                        iis == &img_gate_yellow_right or iis == &img_gate_green_right or
                        iis == &img_gate_blue_right or iis == &img_gate_purple_right)
                    {
                        if (cratesub.Left <= 38)
                        {
                            cratesub.Left += 1;
                            cratesub.Top += 0.5;
                            crates[i].sprite.Move(-0.4,-0.4);
                            crates[i].sprite.SetSubRect(cratesub);
                        }
                        else
                        {
                            if (crates[i].color == gates[ii].color)
                            {
                                points += gates[ii].value;
                            }
                            else if (points > gates[ii].value / 2)
                            {
                                points -= gates[ii].value / 2;
                            }
                            else
                            {
                                points = 0;
                            }
                            crates.erase(crates.begin() + i);
                        }
                    }
                }
            }
        }
        for (unsigned int i = 0; i < trucks.size(); i++)
        {
            if (trucks[i].interval <= 0 and trucks[i].active == true)
            {
                trucks[i].interval = trucks[i].intervalmax;
                sf::Vector2f tpos = trucks[i].sprite.GetPosition();
                crates.push_back(crate());
                crates.back().sprite.SetPosition(tpos.x - 8, tpos.y + (10 * 2) - 16);
                crates.back().incint = false;
                crates.back().coll = false;
                int random = rand() % trucks[i].colors.size();
                if (trucks[i].colors[random] == "red")
                {
                    crates.back().color = "red";
                    crates.back().sprite.SetImage(img_crate_red);
                }
                else if (trucks[i].colors[random] == "orange")
                {
                    crates.back().color = "orange";
                    crates.back().sprite.SetImage(img_crate_orange);
                }
                else if (trucks[i].colors[random] == "yellow")
                {
                    crates.back().color = "yellow";
                    crates.back().sprite.SetImage(img_crate_yellow);
                }
                else if (trucks[i].colors[random] == "green")
                {
                    crates.back().color = "green";
                    crates.back().sprite.SetImage(img_crate_green);
                }
                else if (trucks[i].colors[random] == "blue")
                {
                    crates.back().color = "blue";
                    crates.back().sprite.SetImage(img_crate_blue);
                }
                else if (trucks[i].colors[random] == "purple")
                {
                    crates.back().color = "purple";
                    crates.back().sprite.SetImage(img_crate_purple);
                }
            }
            else if (trucks[i].delay <= 0 and trucks[i].active == true)
            {
                trucks[i].interval -= 1;
            }
            else if (trucks[i].active == true)
            {
                trucks[i].delay -= 1;
            }
        }
        stringstream score;
        score << "Score: " << points;
        str_score.SetText(score.str());
    }
}

void SceneGame::Draw()
{
	//Drawing
    window->Clear(sf::Color(255,255,255));
    //-------------
    if (paused == true)
    {
        window->Draw(str_paused_msg1);
        if (csel == 1)
        {
            pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),3.f,sf::Color(255,210,0));
            pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
        }
        else if (csel == 2)
        {
            pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
            pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),3.f,sf::Color(255,210,0));
        }
        else
        {
            pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
            pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
        }
        window->Draw(pbutton1);
        window->Draw(pbutton2);
        window->Draw(str_paused_msg2);
        window->Draw(str_paused_msg3);
    }
    else if (paused == false)
    {
        for (unsigned int i = 0; i < gates.size(); i++)
        {
            sf::Sprite &c = gates[i].sprite;
            window->Draw(c);
        }
        for (unsigned int i = 0; i < conveyors.size(); i++)
        {
            conveyor &c = conveyors[i];
            window->Draw(c.sprite);
            if (c.change == true)
            {
                if (c.dir == 0)
                {
                    window->Draw(c.arrow_0);
                }
                else
                {
                    window->Draw(c.arrow_1);
                }
            }
        }
        for (unsigned int i = 0; i < incinerators.size(); i++)
        {
            sf::Sprite &c = incinerators[i];
            window->Draw(c);
        }
        for (unsigned int i = 0; i < crates.size(); i++)
        {
            sf::Sprite &c = crates[i].sprite;
            window->Draw(c);
        }
        for (unsigned int i = 0; i < trucks.size(); i++)
        {
            sf::Sprite &c = trucks[i].sprite;
            window->Draw(c);
        }
        window->Draw(str_score);
    }
    //-------------
    window->Display();

    //Update stuff
    isMouseDown = window->GetInput().IsMouseButtonDown( sf::Mouse::Left );
    isEnterDown = window->GetInput().IsKeyDown( sf::Key::Return );
    isUpDown = window->GetInput().IsKeyDown( sf::Key::Down );
    isDownDown = window->GetInput().IsKeyDown( sf::Key::Down );
}



// This makes sure the scene is added to the engine!
SceneGame* game = new SceneGame();
