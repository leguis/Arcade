//
// Pacman.cpp for arcade in /home/sebastien/Rendu/cpp_arcade
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Tue Apr  4 16:26:36 2017 Sebastien Le Guischer
// Last update Tue Apr  4 21:02:25 2017 meghenr
//

#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include "Pacman.hpp"

extern "C"
{
arcade::IGame *createLib(int width, int height) {
    return (new arcade::Pacman (width, height));
}
}

void    arcade::Pacman::loadScore(){
    std::ifstream file(this->path);
    std::ofstream cfile;
    std::string     str;

    if (!file.is_open()){
        cfile.open(this->path);
    }else{
        while (std::getline(file, str)) {
             this->scores.insert(std::make_pair(std::stoi(str.erase(0, str.find(" ") + 1)), str.substr(0, str.find(" "))));
        }
}
}

arcade::Pacman::Pacman (int width, int height)
        : width (width), height (height), score(0) {
    Character *tmp;

    this->ParseMap ();
    this->path = "pacman.score";
    this->loadScore();
    this->scores.insert(std::make_pair(0, "AAA"));
    this->action.insert (std::make_pair (arcade::CommandType::GO_UP, &arcade::Pacman::MoveUp));
    this->action.insert (std::make_pair (arcade::CommandType::GO_DOWN, &arcade::Pacman::MoveDown));
    this->action.insert (std::make_pair (arcade::CommandType::GO_LEFT, &arcade::Pacman::MoveLeft));
    this->action.insert (std::make_pair (arcade::CommandType::GO_RIGHT, &arcade::Pacman::MoveRight));
    this->action.insert (std::make_pair (arcade::CommandType::ILLEGAL, &arcade::Pacman::Option));
    this->nb_terate = 0;
    this->Player = new arcade::Character (10, 15);
    this->Player->setImg ("./ressources/C_4_pacman_1.png");
    this->Player->setImg ("./ressources/C_4_pacman_2.png");
    this->characters.push_back (this->Player);


    tmp = new arcade::Character (10, 9);
    tmp->setImg ("./ressources/A_7_pacman_evil_dude.png");
    tmp->setImg ("./ressources/A_5_pacman_evil_dude_fear.png");
    tmp->setImg ("./ressources/m_8_pacman_evil_dude_eye.png");
    this->characters.push_back (tmp);

    tmp = new arcade::Character (10, 8);
    tmp->setImg ("./ressources/A_7_pacman_evil_dude2.png");
    tmp->setImg ("./ressources/A_5_pacman_evil_dude_fear.png");
    tmp->setImg ("./ressources/m_8_pacman_evil_dude_eye.png");
    this->characters.push_back (tmp);


    tmp = new arcade::Character (11, 9);
    tmp->setImg ("./ressources/A_7_pacman_evil_dude3.png");
    tmp->setImg ("./ressources/A_5_pacman_evil_dude_fear.png");
    tmp->setImg ("./ressources/m_8_pacman_evil_dude_eye.png");
    this->characters.push_back (tmp);

    tmp = new arcade::Character (9, 9);
    tmp->setImg ("./ressources/A_7_pacman_evil_dude4.png");
    tmp->setImg ("./ressources/A_5_pacman_evil_dude_fear.png");
    tmp->setImg ("./ressources/m_8_pacman_evil_dude_eye.png");
    this->characters.push_back (tmp);

    this->com = arcade::CommandType::GO_FORWARD;
}

arcade::Pacman::~Pacman () {
}

void arcade::Pacman::Play () {
}

void arcade::Pacman::playRound (arcade::CommandType com) {
    auto it = this->action.find (com);

    if (it == this->action.end ()) {
        it = this->action.find (this->com);
        if (it != this->action.end ())
            (this->*it->second) ();
    } else if (it != this->action.end ()) {
        if (((this->*it->second) ()) == 1)
            it = this->action.find (this->com);
        if (it != this->action.end ())
            (this->*it->second) ();
    }
    if (this->canMove (this->Player->getX (), this->Player->getY (), this->Player->getX () + this->Player->getXSpeed (),
                       this->Player->getY () + this->Player->getYSpeed ())) {
        this->Player->setY (this->Player->getY () + this->Player->getYSpeed ());
        this->Player->setX (this->Player->getX () + this->Player->getXSpeed ());
    }
    this->updateCharacter ();
    this->eatOther ();
    this->eatGhost();
    this->moveGhost();
    this->timer();
}

void arcade::Pacman::ParseMap () {
    std::string name_game = "./ressources/pacman.map";
    std::ifstream file;

    char c;
    file.open (name_game);
    if (file.is_open ()) {
        while (file.get (c)) {
            if (c != '\n')
                this->map.push_back (static_cast<arcade::TileType>((c - 48)));
        }
    }
    file.close ();
}

std::map<int, std::string> arcade::Pacman::loadSprite () {
    std::map<int, std::string> sprite;

    sprite.insert (std::make_pair (0, "./ressources/E_6_pacman_empty.png"));
    sprite.insert (std::make_pair (1, "./ressources/B_5_pacman_block.png"));
    sprite.insert (std::make_pair (3, "./ressources/A_7_pacman_evil_dude.png"));
    sprite.insert (std::make_pair (6, "./ressources/O_8_pacman_powerup.png"));
    sprite.insert (std::make_pair (7, "./ressources/o_8_pacman_other.png"));
    return (sprite);
}

std::map<size_t, std::string> arcade::Pacman::getHighScore() const
{
    return (this->scores);
}

std::string arcade::Pacman::getPathScore() const
{
    return (this->path);
}

size_t arcade::Pacman::getScore() const
{
    return (this->score);
}

bool arcade::Pacman::getPlay() const
{
    return (true);
}

bool arcade::Pacman::canMove (float x, float y, float new_x, float new_y) {
    int i = (int) (x * 10) % 10;
    int j = (int) (y * 10) % 10;

    if (x - new_x > 0 && j == 0)
        if (this->map[(int) (y) * this->width + (int) (new_x)] != arcade::TileType::BLOCK)
            return (true);
    if (y - new_y > 0 && i == 0)
        if (this->map[(int) (new_y) * this->width + (int) (x)] != arcade::TileType::BLOCK)
            return (true);
    if (x - new_x < 0 && j == 0)
        if (this->map[(int) (y) * this->width + (int) (x) + 1] != arcade::TileType::BLOCK)
            return (true);
    if (y - new_y < 0 && i == 0)
        if (this->map[(int) (y) * this->width + (int) (x) + this->width] != arcade::TileType::BLOCK)
            return (true);
    return (false);
}

int arcade::Pacman::MoveUp () {
    this->com = arcade::CommandType::GO_UP;
    if (this->canMove (this->Player->getX (), this->Player->getY (), this->Player->getX (),
                       this->Player->getY () - 0.5)) {
        this->Player->setXSpeed (0);
        this->Player->setYSpeed (-0.1);
    } else
        return (1);
    return (0);
}

int arcade::Pacman::MoveDown () {
    this->com = arcade::CommandType::GO_DOWN;
    if (this->canMove (this->Player->getX (), this->Player->getY (), this->Player->getX (),
                       this->Player->getY () + 0.5)) {
        this->Player->setXSpeed (0);
        this->Player->setYSpeed (0.1);
    } else
        return (1);
    return (0);
}

int arcade::Pacman::MoveLeft () {
    this->com = arcade::CommandType::GO_LEFT;
    if (this->canMove (this->Player->getX (), this->Player->getY (), this->Player->getX () - 0.1,
                       this->Player->getY ())) {
        this->Player->setXSpeed (-0.1);
        this->Player->setYSpeed (0);
    } else
        return (1);
    return (0);
}

int arcade::Pacman::MoveRight () {
    this->com = arcade::CommandType::GO_RIGHT;
    if (this->canMove (this->Player->getX (), this->Player->getY (), this->Player->getX () + 0.1,
                       this->Player->getY ())) {
        this->Player->setXSpeed (0.1);
        this->Player->setYSpeed (0);
    } else
        return (1);
    return (0);
}

int arcade::Pacman::Option () {
    return (0);
}

void arcade::Pacman::updateCharacter () {
    this->Player->setState (0 + !(this->Player->getState () == 1));
}

const std::vector <arcade::TileType> arcade::Pacman::getMap () const {
    return (this->map);
}

const std::vector <std::string> arcade::Pacman::getCharactSprite () const {
    std::vector <std::string> sprite;
    size_t i;

    i = 0;
    while (i < this->characters.size ()) {
        sprite.push_back (((this->characters[i])->getImg ())[(this->characters[i])->getState ()]);
        i++;
    }
    return (sprite);
}

const std::vector<float> arcade::Pacman::getCharactX () const {
    std::vector<float> x;
    size_t i;

    i = 0;
    while (i < this->characters.size ()) {
        x.push_back ((this->characters[i])->getX ());
        i++;
    }
    return (x);
}

const std::vector<float> arcade::Pacman::getCharactY () const {
    std::vector<float> y;
    size_t i;

    i = 0;
    while (i < this->characters.size ()) {
        y.push_back ((this->characters[i])->getY ());
        i++;
    }
    return (y);
}

void    arcade::Pacman::moveGhost() {
    auto it = this->characters.begin();

    float     speed = 0.1;
    it++;

    if ((*it)->getX() <= this->Player->getX()
        && this->canMove((*it)->getX(), (*it)->getY(), (*it)->getX() + speed / 2, (*it)->getY())) {
        (*it)->setX((*it)->getX () + speed / 2);
    }
    if ((*it)->getX() >= this->Player->getX()
        && this->canMove((*it)->getX(), (*it)->getY(), (*it)->getX() - speed / 2, (*it)->getY()))
        (*it)->setX((*it)->getX () - speed / 2);

    if ((*it)->getY() <= this->Player->getY()
        && this->canMove((*it)->getX(), (*it)->getY(), (*it)->getX(), (*it)->getY() + speed / 2) ) {
        (*it)->setY((*it)->getY () + speed / 2);
    }
    if ((*it)->getY() >= this->Player->getY()
        && this->canMove((*it)->getX(), (*it)->getY(), (*it)->getX(), (*it)->getY() - speed / 2)) {
        (*it)->setY((*it)->getY () - speed / 2);
    }
}

void arcade::Pacman::timer() {
    int         max = 200;
    bool  fear = false;
    auto it = this->characters.begin();

    it++;
    while (it != this->characters.end())
    {
	    if ((*it)->getState() == 1 && fear == false) {
	    	fear = true;
 	      this->nb_terate += 1;
 	    }
    	it++;
    }
    it = this->characters.begin();
    it++;
    if (this->nb_terate >= max){
        this->nb_terate = 0;
        while (it != this->characters.end()){
        	if ((*it)->getState() == 1)
            (*it)->setState(0);
            it++;
        }
    }
}

void    arcade::Pacman::reset()
{
    this->Player->setX(10);
    this->Player->setY(15);
    this->Player->setYSpeed(0);
    this->Player->setXSpeed(0);

}

void arcade::Pacman::eatGhost() {
    auto it = this->characters.begin();

    it++;
    while (it != this->characters.end()){
        if (((int)this->Player->getX() == (int)(*it)->getX()
          && (int)this->Player->getY() == (int)(*it)->getY()))
          {
           	if ((*it)->getState() == 0)
          	  this->reset();
          	else if ((*it)->getState() == 1)
            {
                this->score += 200;
          		(*it)->setState(2);
            }
	   }
        it++;
    }
}

void arcade::Pacman::eatOther () {
    if (this->map[(int) this->Player->getY () * this->width + (int) this->Player->getX ()] == arcade::TileType::OTHER) {
        this->score += 10;
         this->map[(int) this->Player->getY () * this->width + (int) this->Player->getX ()] = arcade::TileType::EMPTY;
    }
    if (this->map[(int) this->Player->getY () * this->width + (int) this->Player->getX ()] == arcade::TileType::POWERUP){
        auto it = this->characters.begin();
        it++;
        while (it != this->characters.end()){
        	if ((*it)->getState() == 0)
            (*it)->setState(1);
          it++;
        }
        this->nb_terate = 0;
        this->score += 50;
        this->map[(int) this->Player->getY () * this->width + (int) this->Player->getX ()] = arcade::TileType::EMPTY;
    }
}

size_t arcade::Pacman::getWidth() const
{
	return (this->width);
}

size_t arcade::Pacman::getHeight() const
{
	return (this->height);
}
