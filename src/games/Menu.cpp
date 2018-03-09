#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include "Menu.hpp"


std::vector<std::string> opendir_so(std::string const & path){
  DIR *dir;
  std::string   tmp;
  std::vector<std::string> file;
  struct dirent *ent;

  if ((dir = opendir (path.c_str())) != NULL)
  {
    while ((ent = readdir (dir)) != NULL){
      tmp = ent->d_name;
      if (tmp.find(".so") != std::string::npos)
        file.push_back(tmp);
    }
    closedir (dir);
    return file;
  }
  else
    throw std::string ("opend dir failed");
}

arcade::Menu::Menu(){
  this->libs = opendir_so("./lib");
  this->games = opendir_so("./games");
  this->index.push_back(0);
  this->index.push_back(0);
  this->index.push_back(0);
  this->index.push_back(0);
  this->nickname = "ABC";
  this->current = 0;
  this->action.insert(std::make_pair(arcade::CommandType::GO_DOWN, &arcade::Menu::incIndex));
  this->action.insert(std::make_pair(arcade::CommandType::GO_UP, &arcade::Menu::decIndex));
  this->action.insert(std::make_pair(arcade::CommandType::SHOOT, &arcade::Menu::changeCurrent));
  this->action.insert(std::make_pair(arcade::CommandType::GO_LEFT, &arcade::Menu::changeLeft));
  this->action.insert(std::make_pair(arcade::CommandType::GO_RIGHT, &arcade::Menu::changeRight));
}


arcade::Menu::Menu::~Menu(){

}

std::vector<std::string> arcade::Menu::getLibs(){
  return this->libs;
}

std::vector<std::string> arcade::Menu::getGames(){
  return this->games;
}

std::vector<size_t> arcade::Menu::getIndex(){
  return this->index;
}

std::string arcade::Menu::getPseudo(){
  return this->nickname;
}

void  arcade::Menu::incIndex(){

  if (this->current == 0){
    this->index[this->current] = (this->index[this->current] + 1) % this->libs.size();
  }
  else if (this->current == 1){
    this->index[this->current] = (this->index[this->current] + 1) % this->games.size();
  }
  if (this->current == 2){
    this->nickname[this->index[3]] = this->nickname[this->index[3]] + 1;
    if (this->nickname[this->index[3]] > 'Z')
      this->nickname[this->index[3]] = 'A';
  }
}

void  arcade::Menu::setIndexGame(size_t nb){
  this->index[1] = nb;
}


void  arcade::Menu::setIndexLib(size_t nb){
  this->index[0] = nb;
}

void  arcade::Menu::decIndex(){

  if (this->current == 0){
    this->index[this->current] = (this->index[this->current] - 1)  % this->libs.size();
  }
  if (this->current == 1){
    this->index[this->current] = (this->index[this->current] - 1) % this->games.size();
  }
  if (this->current == 2){
    this->nickname[this->index[3]] = this->nickname[this->index[3]] - 1;
    if (this->nickname[this->index[3]] < 'A')
      this->nickname[this->index[3]] = 'Z';
  }
}

void  arcade::Menu::changeCurrent(){
  this->current = (this->current + 1) % 3;
}

void arcade::Menu::changeLeft(){
  if (this->current == 2){
    this->index[3] = this->index[3] - 1;
  }
}

void arcade::Menu::changeRight(){
  if (this->current == 2){
    this->index[3] = (this->index[3] + 1) % 3;
  }
}

void arcade::Menu::getKeyword(arcade::CommandType com){
    auto it = this->action.find(com);

  if (it != this->action.end()){
    (this->*it->second)();
  }
}
