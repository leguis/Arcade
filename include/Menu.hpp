#ifndef MENU_H_
#define  MENU_H_

#include <string>
#include <map>
#include <vector>
#include "Protocol.hpp"

namespace arcade{

class Menu{

private:
  std::vector<std::string> libs;
  std::vector<std::string> games;
  std::string              nickname;
  std::vector<size_t>         index;
  size_t                  current;
  std::map<arcade::CommandType, void (arcade::Menu::*)()> action;

public:

  Menu();
  ~Menu();
  std::vector<std::string>  getLibs();
  std::vector<std::string>  getGames();
  std::vector<size_t>          getIndex();
  std::string  getPseudo();
  void    getKeyword(arcade::CommandType com);
  void    incIndex();
  void    decIndex();
  void    changeCurrent();
  void    changeLeft();
  void    changeRight();
  void    setIndexGame(size_t);
  void    setIndexLib(size_t);
  };
}
#endif /* MENU_H_ */
