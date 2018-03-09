//
// main.cpp for arcade in /home/sebastien/Rendu/arcade/cpp
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Thu Mar 16 15:29:24 2017 Sebastien Le Guischer
// Last update Sat Apr  8 22:28:09 2017 meghenr
//

#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include "IG_Lib.hpp"
#include "Protocol.hpp"
#include "Menu.hpp"
#include "IGame.hpp"

template<typename T>
T *createLib(int width, int height);

void loopgame (arcade::IG_Lib *lib, arcade::IGame *game) {
    std::vector<float> x;
    std::vector<float> y;
    std::vector <std::string> sprite;
    size_t i;

    sprite = game->getCharactSprite ();
    x = game->getCharactX ();
    y = game->getCharactY ();
    lib->updateMap (game->getMap (), game->getWidth (), game->getHeight ());
    i = 0;
    while(i < sprite.size ()) {
        lib->updateCharacter (x[i], y[i], sprite[i]);
        i++;
    }
    lib->displayScore(game->getHighScore(), game->getScore());
}

arcade::IG_Lib  *catchGame(arcade::CommandType & com, arcade::IG_Lib *glib, arcade::IGame *game, arcade::Menu & menu)
{
  void *hundler;
  arcade::IG_Lib * (*func) (int, int);

  if (com == static_cast<arcade::CommandType>(10))
  {
    delete glib;
    menu.setIndexLib(((menu.getIndex())[0] + 1) % (menu.getLibs().size()));
    if ((hundler = dlopen(("./lib/" + (menu.getLibs())[(menu.getIndex())[0]]).c_str(), RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    glib = func (785, 735);
    glib->setBlock (game->loadSprite ());
  }
  if (com == static_cast<arcade::CommandType>(11))
  {
    delete glib;
    if ((menu.getIndex())[0] == 0)
      menu.setIndexLib(menu.getLibs().size() - 1);
    else
      menu.setIndexLib(((menu.getIndex())[0] - 1));
    if ((hundler = dlopen(("./lib/" + (menu.getLibs())[(menu.getIndex())[0]]).c_str(), RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    glib = func (785, 735);
    glib->setBlock (game->loadSprite ());
  }
  return (glib);
}

arcade::IGame  *catchCGame(arcade::CommandType & com, arcade::IGame *game, arcade::Menu & menu)
{
  void *hundler;
  arcade::IGame * (*func) (int, int);

  if (com == static_cast<arcade::CommandType>(12))
  {
    delete game;
    menu.setIndexGame(((menu.getIndex())[1] + 1) % menu.getGames().size());
    if ((hundler = dlopen(("./games/" + (menu.getGames())[(menu.getIndex())[1]]).c_str(), RTLD_LAZY)) == NULL)
      throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IGame *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    game = func (21, 21);
  }
  if (com == static_cast<arcade::CommandType>(13))
  {
    delete game;
    if ((menu.getIndex())[1] == 0)
      menu.setIndexGame((menu.getGames()).size() - 1);
    else
      menu.setIndexGame((menu.getIndex())[1] - 1);
    if ((hundler = dlopen(("./games/" + (menu.getGames())[(menu.getIndex())[1]]).c_str(), RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IGame *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    game = func (21, 21);
  }
  if (com == static_cast<arcade::CommandType>(14))
  {
    delete game;
    if ((hundler = dlopen(("./games/" + (menu.getGames())[(menu.getIndex())[1]]).c_str(), RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IGame *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    game = func (21, 21);
  }
  return (game);
}

arcade::IG_Lib  *catchMenu(arcade::CommandType & com, arcade::IG_Lib *glib, arcade::Menu menu){
  void *hundler;
  arcade::IG_Lib * (*func) (int, int);

  if (com == static_cast<arcade::CommandType>(10))
  {
    delete glib;
    menu.setIndexLib(((menu.getIndex())[0] + 1) % menu.getLibs().size());
    if ((hundler = dlopen(("./lib/" + (menu.getLibs())[(menu.getIndex())[0]]).c_str(), RTLD_LAZY)) == NULL)
      throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    glib = func (720, 1240);
  }
  if (com == static_cast<arcade::CommandType>(11))
  {
    delete glib;
    if ((menu.getIndex())[0] == 0)
      menu.setIndexLib((menu.getLibs()).size() - 1);
    else
      menu.setIndexLib((menu.getIndex())[0] - 1);
    if ((hundler = dlopen(("./lib/" + (menu.getLibs())[(menu.getIndex())[0]]).c_str(), RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
    if ((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
      throw std::string ("reinterpret_cast failed");
    glib = func (720, 1240);
  }
  return (glib);
}

int  loopMenu(arcade::Menu & menu, arcade::IG_Lib *glib){

  arcade::CommandType com = arcade::CommandType::GO_FORWARD;

  while (com != arcade::CommandType::PLAY) {
    com = glib->keyboard();
    glib = catchMenu(com, glib, menu);
    menu.getKeyword(com);
    glib->displayMenu(menu.getIndex(), menu.getLibs(), menu.getGames(), menu.getPseudo());
    if (com == arcade::CommandType::ILLEGAL)
    {
      delete glib;
      return (1);
    }
  }
  delete glib;
  return (0);
}

void    init_game(arcade::IG_Lib * (*func) (int, int), arcade::IGame * (*funcg) (int, int), arcade::Menu menu){
  arcade::IGame *game = funcg (21, 21);
  arcade::IG_Lib *glib = func (785, 735);
  arcade::CommandType com = arcade::CommandType::GO_FORWARD;
  std::ofstream   file;

  glib->setBlock (game->loadSprite ());
  while(com != arcade::CommandType::ILLEGAL)
  {
    com = glib->keyboard();
    game = catchCGame(com, game, menu);
    glib = catchGame(com, glib, game, menu);
    game->playRound (com);
    loopgame (glib, game);
    glib->display ();
  }

  auto  it = (game->getHighScore()).end();
  file.open(game->getPathScore());

  if ((game->getHighScore()).size() > 0){
    it--;
    if (it->first < game->getScore())
      file << menu.getPseudo() << " " << game->getScore() << std::endl;
  }
  delete glib;
  delete game;
}

void  updateCurrentLib_Game(std::string const & lib, std::string const & game, arcade::Menu menu){
  int to = 0;

  for (size_t i = 0; (menu.getLibs())[i] != lib; i++){
    to += 1;
  }
  menu.setIndexLib(to);
  to = 0;
  for (size_t i = 0; (menu.getGames())[i] != game; i++){
    to += 1;
  }
  menu.setIndexGame(to);
}

int main (int ac, char **av) {
    void *hundler;
    void *hundler2;
    arcade::IG_Lib * (*func) (int, int);
    arcade::IGame * (*funcg) (int, int);

    try{

      if (ac != 2)
        throw std::string ("USAGE: ./core [LIB]");
      arcade::Menu  menu;
      if ((hundler = dlopen (av[1], RTLD_LAZY)) == NULL)
        throw std::string (dlerror());
      if ((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
        throw std::string ("reinterpret_cast failed");
      arcade::IG_Lib *glib = func (720, 1240);
      if (loopMenu(menu, glib) == 1)
        return 0;
      dlclose(hundler);
      if (((hundler = dlopen(("./lib/" + (menu.getLibs())[(menu.getIndex())[0]]).c_str(), RTLD_LAZY)) == NULL)
       || ((hundler2 = dlopen (("./games/" + (menu.getGames())[(menu.getIndex())[1]]).c_str(), RTLD_LAZY)) == NULL))
        throw std::string (dlerror());
      updateCurrentLib_Game((menu.getLibs())[(menu.getIndex())[0]], (menu.getGames())[(menu.getIndex())[1]], menu);
      if (((func = reinterpret_cast<arcade::IG_Lib *(*) (int, int)>(dlsym (hundler, "createLib"))) == NULL)
        || (((funcg = reinterpret_cast<arcade::IGame *(*) (int, int)>(dlsym (hundler2, "createLib"))) == NULL)))
         throw std::string ("reinterpret_cast failed");
     init_game(func, funcg, menu);
    }catch (std::string msg){

      std::cout <<  msg<< std::endl;
      exit (84);
    }
    return (0);
}
