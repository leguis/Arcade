//
// NCurses.hpp for arcade in /home/sebastien/Rendu/cpp_arcade/include
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Sat Apr  8 05:22:14 2017 Sebastien Le Guischer
// Last update Sat Apr  8 05:22:15 2017 Sebastien Le Guischer
//

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <ncurses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <string>
# include "IG_Lib.hpp"

namespace arcade
{
	class NCurses : public IG_Lib
	{
	public:
		NCurses(int width, int height);
		virtual ~NCurses();
    virtual void updateMap(std::vector<arcade::TileType> map, size_t width, size_t height);
    virtual void updateCharacter(float x, float y, std::string sprite);
    virtual void display();
    virtual arcade::CommandType keyboard();
    virtual void setBlock(std::map<int, std::string>);
    virtual void displayMenu(const std::vector<size_t>& index, const std::vector<std::string>& lib,
		                        const std::vector<std::string>& game, const std::string & nickname);
    virtual void displayPause();
    virtual void displayScore(std::map<size_t, std::string>, size_t);
		void    disp_vec(std::vector<std::string> const &vec, size_t target, int x, int y);

  private:
  	int width;
  	int height;
  	WINDOW *win;
  	struct termios new_term;
  	struct termios old_term;
  	std::map<int, std::string> sprite;
    std::map <std::string, arcade::CommandType> key;
	};

	extern "C"
	{
		IG_Lib *createLib(int width, int height);
	}
}
#endif
