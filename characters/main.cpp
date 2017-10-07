#include <string>
#include <SFML/Graphics.hpp>

namespace game
{
	class Engine
	{
		sf::VideoMode mode;
		std::string title;
		sf::RenderWindow*window;
	 public:
		Engine(sf::VideoMode mode, const std::string &title)
		:mode(mode),title(title)
		{
			window = new sf::RenderWindow(mode,title);
		}
		~Engine()
		{
			delete window;
		}
		void display()
		{
			window->display();
		}
		void clear(const sf::Color&color=sf::Color(0,0,0,255))
		{
			window->clear(color);
		}
		void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default)
		{
			window->draw(drawable,states);
		}
		void restart()
		{
			window->create(mode,title);
		}
		void stop()
		{
			window->close();
		}
		bool running(){
			return window->isOpen();
		}
		bool pollEvent(sf::Event&event)
		{
			return window->pollEvent(event);
		}
	};
	void quit(game::Engine& engine)
	{
		engine.stop();
	}
}
int main(){
	game::Engine engine(sf::VideoMode(640,360),"Sad raw");
	while(engine.running())
	{
		sf::Event event;
		while(engine.pollEvent(event)){
			if(event.type == sf::Event::Closed)game::quit(engine);
		}
		engine.clear();
		engine.display();
	}
}
