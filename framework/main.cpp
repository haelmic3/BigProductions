/* Copyright (c) 2017 - Big Productions - Michael Moran
___       ___            __                    __ 
|\\       /|| _/\_       ||                    ||
| \\_____/ ||  \/  ____  ||___   ___     ____  ||
|  \\ ||/  ||  || / ||\/ ||  \\ '___|\  /___|/ ||
|   \\|/   ||  || \_||__ ||  || \__/\|_\\____  ||_
|/    ||  ||    ||  ||   __  '___|\  |)/  \\
||    |/  ||    |/  ||   || /|   ||  ||    ||
 \___//    \____/  _||_ _||_\\__/\| _||_  _||_
| \\     / ||  ___   _ ___   ___   _ ____
|  \\   /  || //  \\ |/  \/ '___|\ |)/  \/
|   \\_/   || \\__// ||     \__/\| ||   ||
*/
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<string>
#include<stdexcept>

sf::Font font;
const int unit = 80; // 16*unit * 9*unit = 1280 * 720
namespace util
{
	std::string s(unsigned rate)
	{
		std::string d;
		do d.insert(0, 1, rate % 10 + '0');
		while (rate /= 10);
		return d;
	}
}
namespace game
{
	void pause(sf::RenderWindow&window){
		window.close();
	}
	namespace asset
	{
		class player
		{
		 public:
			player(int x,int y,int z)
			{
			}
		};
	}
}
int main(int argc, char*argv[])
{
	sf::RenderWindow
		window(sf::VideoMode(16*unit, 9*unit), "Project Sunshine")
	;
	sf::Text
		text
	,	drag
	;
	sf::Clock
		clock
	;
	unsigned
		frame = 16000
	,	fmax = 16000
	,	fmin = 0
	,	fsum = 0
	,	fcount = 0
	;
	std::string
		a = "R"
	;
	//window.setVerticalSyncEnabled(true);
	if (!font.loadFromFile("arial.ttf"))
	{
		return 1;
	}
	text.setFont(font);
	text.setCharacterSize(unit/4);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(0,0);
	while (	window.isOpen() )
	{	sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				game::pause(window);
		}
		text.setString(
			" max: "+ util::s(1000000.0 / fmax)+
			" min: "+ util::s(1000000.0 / fmin)+
			" avr: "+ util::s(1000000.0 / fsum * fcount)+
			" cur: "+ util::s(1000000.0 / frame)
		);
		if(fcount>1000){
			frame = fsum*fcount;
			fmax = fsum*fcount;
			fmin = 0;
			fsum = 0;
			fcount = 0;
		}
		drag.setString(a);
		window.clear();
		window.draw(text);
		window.draw(drag);
		window.display();
		fcount++;
		frame = clock.restart().asMicroseconds();
		fsum+=frame;
		if(fmax>frame)fmax=frame;
		if(fmin<frame)fmin=frame;
	}
	return 0;
}
