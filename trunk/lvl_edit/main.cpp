#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "random_class.h"

using namespace std;







#include <sstream>
template <class T>
bool FromString( const std::string& s, T& t, std::ios_base& (*f)(std::ios_base&) = std::dec )
{
	std::istringstream iss( s );
	return !(iss >> f >> t).fail();
}
#define StringToInt( str, num ) FromString<int>( str, num )
#define StringToLong( str, num ) FromString<long>( str, num )
#define StringToFloat( str, num ) FromString<float>( str, num )







sf::Image load_image(string name)
{
	sf::Image timage;
	timage.LoadFromFile("lvl_edit/" + name);
	timage.SetSmooth(false);
	return timage;
}

int main ()
{
	sf::Shape levelborder = sf::Shape::Rectangle(10,10,466,466,sf::Color(255,255,255),1.f,sf::Color(0,0,0));
	sf::Image img_truck_hor		  = load_image("truck-hor.PNG"	  );
	sf::Image img_truck_vert		 = load_image("truck-vert.PNG"	 );
	//-----
	sf::Image img_gate_red_hor	   = load_image("gate-red-hor.PNG"	);
	sf::Image img_gate_orange_hor	= load_image("gate-orange-hor.PNG" );
	sf::Image img_gate_yellow_hor	= load_image("gate-yellow-hor.PNG" );
	sf::Image img_gate_green_hor	 = load_image("gate-green-hor.PNG"  );
	sf::Image img_gate_blue_hor	  = load_image("gate-blue-hor.PNG"   );
	sf::Image img_gate_purple_hor	= load_image("gate-purple-hor.PNG" );
	sf::Image img_gate_red_vert	  = load_image("gate-red-vert.PNG"   );
	sf::Image img_gate_orange_vert   = load_image("gate-orange-vert.PNG");
	sf::Image img_gate_yellow_vert   = load_image("gate-yellow-vert.PNG");
	sf::Image img_gate_green_vert	= load_image("gate-green-vert.PNG" );
	sf::Image img_gate_blue_vert	 = load_image("gate-blue-vert.PNG"  );
	sf::Image img_gate_purple_vert   = load_image("gate-purple-vert.PNG" );
	//-----
	sf::Image img_conveyor_hor	   = load_image("conveyor-hor.PNG"	  );
	sf::Image img_conveyor_vert	  = load_image("conveyor-vert.PNG"	 );
	sf::Image img_arrow_vert_up	  = load_image("arrow-vert-up.png"	 );
	sf::Image img_arrow_vert_down	= load_image("arrow-vert-down.png"   );
	sf::Image img_arrow_hor_left	 = load_image("arrow-hor-left.png"	);
	sf::Image img_arrow_hor_right	= load_image("arrow-hor-right.png"   );
	sf::Image img_arrow_vert		 = load_image("arrow-vert.png"		);
	sf::Image img_arrow_vertr		= load_image("arrow-vertr.png"	   );
	sf::Image img_arrow_hor		  = load_image("arrow-hor.png"		 );
	sf::Image img_arrow_horr		 = load_image("arrow-horr.png"		);
	//-----
	sf::Image img_level_templ		= load_image("warehouse-template.png");
	sf::Image img_save			   = load_image("button-save.PNG"	   );
	sf::Font arial;
	arial.LoadFromFile( "lvl_edit/arial.ttf", 15 );

	vector<random_class> level( 18 * 18 );
	cout << "Type the level NAME excluding path and extension to load, or press enter to create new: ";
	string filename = "";
	int width = 18;
	int height = 18;
	float crateSpeed = 0.01f;
	float crateInterval = 350;
	float crateSpeedIncrement = 0.0000001f;
	int cratesPerTruck = 10;
	int truckDelay = 100 * 5; // Five seconds in game.
	long levelTime = 100 * 180; // Three minutes in game.
	getline(cin,filename);
	if (filename != "")
	{
		cout << "Loading file..." << endl;
		string line;
		ifstream myfile(("levels/" + filename + ".lvl").c_str());
		if (myfile.is_open())
		{
			while (! myfile.eof() )
			{
				string line;
				getline(myfile, line);

				string key = line.substr(0, line.find("="));
				string value = line.substr(line.find("=") + 1);

				if ( key == "width" )
				{
					StringToInt(value, width);
				}
				else if ( key == "height" )
				{
					StringToInt(value, height);
				}
				else if ( key == "leveltime" )
				{
					StringToLong(value, levelTime);
				}
				else if ( key == "cratespeed" )
				{
					StringToFloat(value, crateSpeed);
				}
				else if ( key == "crateinterval" )
				{
					StringToFloat(value, crateInterval);
				}
				else if ( key == "cratespeedincrement" )
				{
					StringToFloat(value, crateSpeedIncrement);
				}
				else if ( key == "cratespertruck" )
				{
					StringToInt(value, cratesPerTruck);
				}
				else if ( key == "truckdelay" )
				{
					StringToInt(value, truckDelay);
				}
				else if ( key == "tiles" )
				{
					// Process each tile
					size_t idx = 0;
					while (idx < value.size())
					{
						switch(value[idx])
						{
							case 'A':
								break;
							case 'B':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = false;
								level[idx].dir = 1;
								break;
							case 'C':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = false;
								level[idx].dir = 0;
								break;
							case 'D':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = false;
								level[idx].dir = 0;
								break;
							case 'E':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = false;
								level[idx].dir = 1;
								break;
							case 'F':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = true;
								level[idx].dir = 1;
								break;
							case 'G':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = true;
								level[idx].dir = 0;
								break;
							case 'H':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = true;
								level[idx].dir = 0;
								break;
							case 'I':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_conveyor_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								level[idx].change = true;
								level[idx].dir = 1;
								break;
							case 'J':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_blue_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'K':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_blue_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'L':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_green_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'M':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_green_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'N':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_orange_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'O':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_orange_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'P':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_purple_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'Q':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_purple_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'R':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_red_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'S':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_red_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'T':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_yellow_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'U':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_gate_yellow_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'V':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_truck_hor);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
							case 'W':
								level[idx] = random_class();
								level[idx].sprite.SetImage(img_truck_vert);
								level[idx].sprite.SetPosition((idx%18) * 24 + 10, (int)(idx/18) * 24 + 10);
								break;
						}

						++idx;
					} // End process each tile
				}
			} // if not end of file
			myfile.close();
		} // End load level
		else
		{
			filename = ""; // Failed to load
		}
	}

	sf::RenderWindow Editor(sf::VideoMode(476,676,32),"Warehouse Panic Level Editor", sf::Style::Close);
	//----------
	vector<sf::Sprite> buttons;
	buttons.push_back( sf::Sprite(img_truck_hor	   ,sf::Vector2f(10 ,260 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_red_hor	,sf::Vector2f(68 ,260 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_orange_hor ,sf::Vector2f(126,260 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_yellow_hor ,sf::Vector2f(184,260 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_green_hor  ,sf::Vector2f(242,260 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_blue_hor   ,sf::Vector2f(10 ,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_purple_hor ,sf::Vector2f(68 ,294 + 220)) );
	//-----
	buttons.push_back( sf::Sprite(img_truck_vert	   ,sf::Vector2f(126,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_red_vert	,sf::Vector2f(150,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_orange_vert ,sf::Vector2f(184,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_yellow_vert ,sf::Vector2f(208,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_green_vert  ,sf::Vector2f(242,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_blue_vert   ,sf::Vector2f(266,294 + 220)) );
	buttons.push_back( sf::Sprite(img_gate_purple_vert ,sf::Vector2f(330,294 + 220)) );
	//-----
	buttons.push_back( sf::Sprite(img_conveyor_hor	,sf::Vector2f(296,294 + 220)) );
	buttons.push_back( sf::Sprite(img_conveyor_vert   ,sf::Vector2f(296,328 + 220)) );
	buttons.push_back( sf::Sprite(img_save			,sf::Vector2f(371,621 + 0  )) );
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
								if ( filename == "" )
								{
									cout << "Enter file name: ";
									getline(cin,filename);
								}
								if ( filename == "" )
									filename = "default";

								ofstream file;
								file.open(("levels/" + filename + ".lvl").c_str());
								file << "width=" << width << endl;
								file << "height=" << height << endl;
								file << "leveltime=" << levelTime << endl;
								file << "cratespeed=" << crateSpeed << endl;
								file << "crateinterval=" << crateInterval << endl;
								file << "cratespeedincrement=" << crateSpeedIncrement << endl;
								file << "cratespertruck=" << cratesPerTruck << endl;
								file << "truckdelay=" << truckDelay << endl;
								file << "tiles=";
								int pos = 0;
								for ( vector<random_class>::iterator it = level.begin(); it != level.end(); ++it, ++pos )
								{
									if ((*it).sprite.GetImage() == &img_conveyor_hor or (*it).sprite.GetImage() == &img_conveyor_vert)
									{
										if ((*it).change == false)
										{
											if ((*it).dir == 0 and (*it).sprite.GetImage() == &img_conveyor_hor)
												file << "D";
											else if ((*it).dir == 1 and (*it).sprite.GetImage() == &img_conveyor_hor)
												file << "B";
											else if ((*it).dir == 0 and (*it).sprite.GetImage() == &img_conveyor_vert)
												file << "C";
											else if ((*it).dir == 1 and (*it).sprite.GetImage() == &img_conveyor_vert)
												file << "E";
										}

										// Switches
										else
										{
											// TODO: Handle direction of switch
											if ((*it).sprite.GetImage() == &img_conveyor_hor or (*it).sprite.GetImage() == &img_conveyor_vert)
											{
												int x = pos % width;
												int y = pos / width;
												if ( level[x + (y+1) * width].sprite.GetImage() == &img_conveyor_vert && level[x + (y+1) * width].dir == 0 )
													file << "G";
												else if ( level[x + (y-1) * width].sprite.GetImage() == &img_conveyor_vert && level[x + (y-1) * width].dir == 1 )
													file << "I";
												else if ( level[(x+1) + y * width].sprite.GetImage() == &img_conveyor_hor && level[(x+1) + y * width].dir == 0 )
													file << "H";
												else if ( level[(x-1) + y * width].sprite.GetImage() == &img_conveyor_hor && level[(x-1) + y * width].dir == 1 )
													file << "F";
												else
													file << "A";
											}
										}
									}
									else if ((*it).sprite.GetImage() == &img_gate_blue_hor)
									{
										file << "J";
									}
									else if ((*it).sprite.GetImage() == &img_gate_blue_vert)
									{
										file << "K";
									}
									else if ((*it).sprite.GetImage() == &img_gate_green_hor)
									{
										file << "L";
									}
									else if ((*it).sprite.GetImage() == &img_gate_green_vert)
									{
										file << "M";
									}
									else if ((*it).sprite.GetImage() == &img_gate_orange_hor)
									{
										file << "N";
									}
									else if ((*it).sprite.GetImage() == &img_gate_orange_vert)
									{
										file << "O";
									}
									else if ((*it).sprite.GetImage() == &img_gate_purple_hor)
									{
										file << "P";
									}
									else if ((*it).sprite.GetImage() == &img_gate_purple_vert)
									{
										file << "Q";
									}
									else if ((*it).sprite.GetImage() == &img_gate_red_hor)
									{
										file << "R";
									}
									else if ((*it).sprite.GetImage() == &img_gate_red_vert)
									{
										file << "S";
									}
									else if ((*it).sprite.GetImage() == &img_gate_yellow_hor)
									{
										file << "T";
									}
									else if ((*it).sprite.GetImage() == &img_gate_yellow_vert)
									{
										file << "U";
									}
									else if ((*it).sprite.GetImage() == &img_truck_hor)
									{
										file << "V";
									}
									else if ((*it).sprite.GetImage() == &img_truck_vert)
									{
										file << "W";
									}
									else
									{
										file << "A";
									}
								}
								file.close();
								exit(0);
							}
							mdraw.SetSubRect(sf::IntRect(0,0,mdraw.GetImage()->GetWidth(),mdraw.GetImage()->GetHeight()));
							mdraw.SetCenter(mdraw.GetSubRect().GetWidth() / 2,mdraw.GetSubRect().GetHeight() / 2);
						}
					}

					for (vector<random_class>::iterator it = level.begin(); it != level.end(); ++it )
					{
						sf::Sprite &c = (*it).sprite;
						if (c.GetPosition().x < Editor.GetInput().GetMouseX() and
							c.GetPosition().y < Editor.GetInput().GetMouseY() and
							c.GetPosition().x + c.GetSubRect().GetWidth() > Editor.GetInput().GetMouseX() and
							c.GetPosition().y + c.GetSubRect().GetHeight() > Editor.GetInput().GetMouseY())
						{
							if ((*it).sprite.GetImage() == &img_conveyor_hor or (*it).sprite.GetImage() == &img_conveyor_vert)
							{
								if ((*it).dir == 0)
									(*it).dir = 1;
								else if ((*it).dir == 1)
									(*it).dir = 0;
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
						level[rid.x + rid.y * width] = random_class();
					}
					else if (Editor.GetInput().GetMouseY() > rdraw.GetPosition().y  + 20 and
						Editor.GetInput().GetMouseY() < rdraw.GetPosition().y + 40 and
						Editor.GetInput().GetMouseX() > rdraw.GetPosition().x and
						Editor.GetInput().GetMouseX() < rdraw.GetPosition().x + 150)
					{
						if (level[rid.x + rid.y * width].sprite.GetImage() == &img_conveyor_hor or level[rid.x + rid.y * width].sprite.GetImage() == &img_conveyor_vert)
						{
							if (level[rid.x + rid.y * width].change == false)
							{
								level[rid.x + rid.y * width].change = true;
							}
							else if (level[rid.x + rid.y * width].change == true)
							{
								level[rid.x + rid.y * width].change = false;
							}
						}
					}
					else if (Editor.GetInput().GetMouseY() > rdraw.GetPosition().y  + 40 and
						Editor.GetInput().GetMouseY() < rdraw.GetPosition().y + 60 and
						Editor.GetInput().GetMouseX() > rdraw.GetPosition().x and
						Editor.GetInput().GetMouseX() < rdraw.GetPosition().x + 150)
					{
						if (level[rid.x + rid.y * width].sprite.GetImage() == &img_conveyor_hor or level[rid.x + rid.y * width].sprite.GetImage() == &img_conveyor_vert)
						{
							if (level[rid.x + rid.y * width].dir == 0)
							{
								level[rid.x + rid.y * width].dir = 1;
							}
							else if (level[rid.x + rid.y * width].dir == 1)
							{
								level[rid.x + rid.y * width].dir = 0;
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
					int pos = 0;
					for (vector<random_class>::iterator it = level.begin(); it != level.end(); ++it, ++pos )
					{
							sf::Sprite &c = (*it).sprite;
							if (c.GetPosition().x < Editor.GetInput().GetMouseX() and
							c.GetPosition().y < Editor.GetInput().GetMouseY() and
							c.GetPosition().y + c.GetSubRect().GetHeight() > Editor.GetInput().GetMouseY() and
							c.GetPosition().x + c.GetSubRect().GetWidth() > Editor.GetInput().GetMouseX())
							{
								if (c.GetImage() == &img_conveyor_vert)
								{
									if ((*it).change == false)
									{
										rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
										rdraw.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2),
														  (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2));
										rclick = true;
										rid = sf::Vector2<int>(pos%width, pos/width);
										ras = 3;
										str1 = sf::String("Delete",arial,15);
										str2 = sf::String("Changable",arial,15);
										if ((*it).dir == 0)
										{
											str3 = sf::String("Face Down",arial,15);
										}
										else
										{
											str3 = sf::String("Face Up",arial,15);
										}
										str1.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
										str2.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
										str3.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
										str1.SetColor(sf::Color(0,0,0));
										str2.SetColor(sf::Color(0,0,0));
										str3.SetColor(sf::Color(0,0,0));
									}
									else
									{
										rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
										rdraw.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2),
														  (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2));
										rclick = true;
										rid = sf::Vector2<int>(pos%width, pos/width);
										ras = 3;
										str1 = sf::String("Delete",arial,15);
										str2 = sf::String("Unchangable",arial,15);
										if ((*it).dir == 0)
										{
											str3 = sf::String("Start Down",arial,15);
										}
										else
										{
											str3 = sf::String("Start Up",arial,15);
										}
										str1.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
										str2.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
										str3.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
										str1.SetColor(sf::Color(0,0,0));
										str2.SetColor(sf::Color(0,0,0));
										str3.SetColor(sf::Color(0,0,0));
									}
								}
								else if (c.GetImage() == &img_conveyor_hor)
								{
									if ((*it).change == false)
									{
										rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
										rdraw.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2),
														  (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2));
										rclick = true;
										rid = sf::Vector2<int>(pos%width, pos/width);
										ras = 3;
										str1 = sf::String("Delete",arial,15);
										str2 = sf::String("Changable",arial,15);
										if ((*it).dir == 0)
										{
											str3 = sf::String("Face Right",arial,15);
										}
										else
										{
											str3 = sf::String("Face Left",arial,15);
										}
										str1.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
										str2.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
										str3.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
										str1.SetColor(sf::Color(0,0,0));
										str2.SetColor(sf::Color(0,0,0));
										str3.SetColor(sf::Color(0,0,0));
									}
									else
									{
										rdraw = sf::Shape::Rectangle(0,0,150,60,sf::Color(255,255,255),1,sf::Color(0,0,0));
										rdraw.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2),
														  (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2));
										rclick = true;
										rid = sf::Vector2<int>(pos%width, pos/width);
										ras = 3;
										str1 = sf::String("Delete",arial,15);
										str2 = sf::String("Unchangable",arial,15);
										if ((*it).dir == 0)
										{
											str3 = sf::String("Start Right",arial,15);
										}
										else
										{
											str3 = sf::String("Start Left",arial,15);
										}
										str1.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
										str2.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
										str3.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
														 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
										str1.SetColor(sf::Color(0,0,0));
										str2.SetColor(sf::Color(0,0,0));
										str3.SetColor(sf::Color(0,0,0));
									}
								}
								else
								{
									rdraw = sf::Shape::Rectangle(0,0,150,20,sf::Color(255,255,255),1,sf::Color(0,0,0));
									rdraw.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2),
													  (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2));
									rclick = true;
									rid = sf::Vector2<int>(pos%width, pos/width);
									ras = 1;
									str1 = sf::String("Delete",arial,15);
									str2 = sf::String("Changable",arial,15);
									if ((*it).dir == 0)
									{
										str3 = sf::String("Face Down",arial,15);
									}
									else
									{
										str3 = sf::String("Face Up",arial,15);
									}
									str1.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
													 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 0);
									str2.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
													 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 20);
									str3.SetPosition((*it).sprite.GetPosition().x + ((*it).sprite.GetSubRect().GetWidth() / 2 + 5),
													 (*it).sprite.GetPosition().y + ((*it).sprite.GetSubRect().GetHeight() / 2) + 3 + 40);
									str1.SetColor(sf::Color(0,0,0));
									str2.SetColor(sf::Color(0,0,0));
									str3.SetColor(sf::Color(0,0,0));
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
							level[mipx + mipy * width] = random_class();
							level[mipx + mipy * width].sprite.SetImage( (*mi) );
							level[mipx + mipy * width].sprite.SetPosition(mipx * 24 + 10, mipy * 24 + 10);
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
			} // End of event loop

			Editor.Clear(sf::Color(0,185,235));
			for (unsigned int i = 0; i < buttons.size(); i++)
			{
				Editor.Draw(buttons[i]);
			}
			Editor.Draw(levelborder);
			Editor.Draw(level_template);
			for (vector<random_class>::iterator it = level.begin(); it != level.end(); ++it)
			{
				Editor.Draw((*it).sprite);
				if ((*it).sprite.GetImage() == &img_conveyor_hor)
				{
					if ((*it).change == false)
					{
						if ((*it).dir == 0)
						{
							sf::Sprite tmp(img_arrow_hor,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
						else
						{
							sf::Sprite tmp(img_arrow_horr,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
					}
					else
					{
						if ((*it).dir == 0)
						{
							sf::Sprite tmp(img_arrow_hor_left,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
						else
						{
							sf::Sprite tmp(img_arrow_hor_right,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
					}
				}
				else if ((*it).sprite.GetImage() == &img_conveyor_vert)
				{
					if ((*it).change == false)
					{
						if ((*it).dir == 0)
						{
							sf::Sprite tmp(img_arrow_vert,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
						else
						{
							sf::Sprite tmp(img_arrow_vertr,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
					}
					else
					{
						if ((*it).dir == 0)
						{
							sf::Sprite tmp(img_arrow_vert_up,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
						}
						else
						{
							sf::Sprite tmp(img_arrow_vert_down,(*it).sprite.GetPosition());
							Editor.Draw(tmp);
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
