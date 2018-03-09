//
// NCurses.cpp for arcade in /home/sebastien/Rendu/cpp_arcade/lib/ncurses
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Sat Apr  8 05:21:47 2017 Sebastien Le Guischer
// Last update Sat Apr  8 05:21:48 2017 Sebastien Le Guischer
//

#include <unistd.h>
#include "NCurses.hpp"

arcade::NCurses::NCurses(int width, int height)
: width(width), height(height), win(NULL)
{
	initscr();
	curs_set(0);
	start_color();
	noecho();
	keypad(stdscr, true);
	cbreak();
	if (((ioctl(0, TCGETS, this->old_term)) == - 1) || ioctl(0, TCGETS, this->new_term))
		throw std::string ("ioctl failed");
	this->new_term.c_lflag &= ~ECHO;
  this->new_term.c_lflag &= ~ICANON;
  this->new_term.c_cc[VTIME] = 1;
  this->new_term.c_cc[VMIN] = 0;
  if ((ioctl(0, TCSETS, &(this->new_term))) == -1)
		throw std::string ("ioctl failed");
	key.insert(std::make_pair(tigetstr("kcuu1"), arcade::CommandType::GO_UP));
	key.insert(std::make_pair(tigetstr("kcud1"), arcade::CommandType::GO_DOWN));
	key.insert(std::make_pair(tigetstr("kcub1"), arcade::CommandType::GO_LEFT));
	key.insert(std::make_pair(tigetstr("kcuf1"), arcade::CommandType::GO_RIGHT));
	key.insert(std::make_pair("a", arcade::CommandType::ILLEGAL));
	key.insert(std::make_pair("e", arcade::CommandType::PLAY));
	key.insert(std::make_pair(" ", arcade::CommandType::SHOOT));
	key.insert(std::make_pair("3", static_cast<arcade::CommandType>(10)));
	key.insert(std::make_pair("2", static_cast<arcade::CommandType>(11)));
	key.insert(std::make_pair("4", static_cast<arcade::CommandType>(12)));
	key.insert(std::make_pair("5", static_cast<arcade::CommandType>(13)));
	key.insert(std::make_pair("8", static_cast<arcade::CommandType>(14)));
	key.insert(std::make_pair("9", static_cast<arcade::CommandType>(15)));
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
}

arcade::NCurses::~NCurses()
{
  ioctl(0, TCSETS, &(this->old_term));
	endwin();
}

void arcade::NCurses::updateMap(std::vector<arcade::TileType> map, size_t width, size_t height)
{
	size_t i;
	std::map<int, std::string>::iterator it;
	std::string			cha;
	int							paire;

	if ((size_t)this->width != width || (size_t)this->height != height)
	{
		if (this->win != NULL)
			delwin(this->win);
		win = newwin(width + 2, height + 2, 5, 5);
	}
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	this->width = width;
	this->height = height;
	i = 0;
	while (i < width * height)
	{
		it = this->sprite.find(static_cast<int>(map[i]));
		cha = (it->second.substr(it->second.find_last_of("/") + 1));
		try{
			paire = std::stoi((cha.substr(cha.find("_") + 1, cha.find("_"))));
		}catch(std::invalid_argument& e){
			throw std::string ("stoi faild");
		}
		wattron(this->win, COLOR_PAIR(paire));
		mvwprintw(this->win, i / width + 1, i % width + 1, "%c", cha.substr(0, cha.find("_"))[0]);
		wattroff(this->win, COLOR_PAIR(paire));
		i++;
	}
}

void arcade::NCurses::updateCharacter(float x, float y, std::string sprite)
{
		std::string			cha;
		int							paire;

		cha = (sprite.substr(sprite.find_last_of("/") + 1));
		try{
			paire = std::stoi((cha.substr(cha.find("_") + 1, cha.find("_"))));
		}catch(std::invalid_argument& e){
			throw std::string ("stoi faild");
		}
		wattron(this->win, COLOR_PAIR(paire));
		mvwprintw(this->win, y + 1, x + 1, cha.substr(0, cha.find("_")).c_str());
		wattroff(this->win, COLOR_PAIR(paire));
}

void arcade::NCurses::display()
{
	wrefresh(this->win);
	refresh();
}

arcade::CommandType arcade::NCurses::keyboard()
{
	char tmp[10];
	int 	size;
	std::map<std::string, arcade::CommandType>::iterator it;


	size = read(0, tmp, 10);
	tmp[size] = '\0';
	it = this->key.find(tmp);
	if (it != this->key.end())
		return (it->second);
	return (arcade::CommandType::GO_FORWARD);
}

void arcade::NCurses::setBlock(std::map<int, std::string> to_add)
{
	auto it = to_add.begin();

	while (it != to_add.end())
	{
		this->sprite.insert(std::make_pair(it->first, it->second));
		it++;
	}
}

void write_it(){
	attron(COLOR_PAIR(1));
	mvprintw(1, 75," /$$      /$$");
	mvprintw(2, 75,"| $$$    /$$$");
	mvprintw(3, 75,"| $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$");
	mvprintw(4, 75,"| $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$");
	mvprintw(5, 75,"| $$  $$$| $$| $$$$$$$$| $$  \\ $$| $$  | $$");
	mvprintw(6, 75,"| $$\\  $ | $$| $$_____/| $$  | $$| $$  | $$");
	mvprintw(7, 75,"| $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$/");
	mvprintw(8, 75,"|__/     |__/ \\_______/|__/  |__/ \\______/ ");
	attroff(COLOR_PAIR(1));
}

void 	arcade::NCurses::disp_vec(std::vector<std::string> const &vec, size_t target, int y, int x){

	for (size_t i = 0; i < vec.size(); i++) {
		if (i == target){
			attron(COLOR_PAIR(2));
			mvprintw(y, x, vec[i].c_str());
			attroff(COLOR_PAIR(2));
		}
		else
			mvprintw(y, x, vec[i].c_str());
		y += 1;
	}
}

void print_style(char c, int y, int x){
	attron(COLOR_PAIR(3));
	mvprintw(y, x, "%c", c);
	attroff(COLOR_PAIR(3));
}

void 	print_name(const std::string & name, size_t select){

	attron(COLOR_PAIR(1));
	mvprintw(22, 93, "Chose you name : ");
	attroff(COLOR_PAIR(1));

	if (select == 0)
		print_style(name[0], 25, 90);
	else
		mvprintw(25, 90, "%c",  name[0]);
	if (select == 1)
		print_style(name[1], 25, 100);
	else
		mvprintw(25, 100, "%c", name[1]);
	if (select == 2)
		print_style(name[2], 25, 110);
	else
		mvprintw(25, 110, "%c", name[2]);
}

void arcade::NCurses::displayMenu(const std::vector<size_t>& index, const std::vector<std::string>& lib,
                        const std::vector<std::string>& game, const std::string & nickname)
{
	write_it();
	attron(COLOR_PAIR(1));
	mvprintw(12, 48, "Chose your lib :");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(1));
	mvprintw(12, 122, "Chose your Game :");
	attroff(COLOR_PAIR(1));
	this->disp_vec(lib, index[0], 15, 45);
	this->disp_vec(game, index[1], 15, 125);
	print_name(nickname, index[3]);
	this->display();
}

void arcade::NCurses::displayScore(std::map<size_t, std::string> hs, size_t score)
{
	auto it = hs.end();

	it--;
	mvprintw(100, 20, "toto");
	mvwprintw(this->win, 0, 0, "Score: %u", score);
	mvwprintw(this->win, 22, 0, "%s %u", (it->second).c_str(), it->first);
}


void arcade::NCurses::displayPause()
{

}

extern "C"
{
arcade::IG_Lib *createLib(int width, int height)
{
	(void)width;
	(void)height;
	return (new arcade::NCurses(0, 0));
}
}
