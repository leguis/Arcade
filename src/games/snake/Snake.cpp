//
// Snake.cpp for arcade in /home/sebastien/Rendu/cpp_arcade/games/snake
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Thu Apr  6 22:47:17 2017 Sebastien Le Guischer
// Last update Sun Apr  9 04:07:14 2017 meghenr
//

#include <unistd.h>
#include "Snake.hpp"
#include <fstream>
#include <iostream>

void Play()
{
    arcade::Snake *snake = new arcade::Snake(21, 21);
    std::vector<float> snakeX = snake->getCharactX();
    std::vector<float> snakeY = snake->getCharactY();
    std::vector<arcade::TileType> map;
    arcade::CommandType com;
    arcade::WhereAmI *w;
    arcade::GetMap *m;
    size_t i;
    arcade::Position pos;

    while (read(0, &com, sizeof(arcade::CommandType)) > 0)
    {
        if (com == arcade::CommandType::GO_UP)
            snake->MoveUp();
        if (com == arcade::CommandType::GO_LEFT)
            snake->MoveLeft();
        if (com == arcade::CommandType::GO_RIGHT)
            snake->MoveRight();
        if (com == arcade::CommandType::GO_DOWN)
            snake->MoveDown();
        if (com == arcade::CommandType::PLAY)
            snake->playRound(com);
        if (com == arcade::CommandType::GET_MAP)
        {
            i = 0;

            map = snake->getMap();
            m = (arcade::GetMap*) ::operator new (sizeof(arcade::GetMap) + sizeof(arcade::TileType) * map.size());
            m->type = arcade::CommandType::GET_MAP;
            m->width = snake->getWidth();
            m->height = snake->getHeight();
            while (i < map.size())
            {
                m->tile[i] = map[i];
                i++;
            }
            write(1, m, sizeof(arcade::GetMap) + sizeof(arcade::TileType) * map.size());
            delete m;
        }
        if (com == arcade::CommandType::WHERE_AM_I)
        {
            snakeX = snake->getCharactX();
            snakeY = snake->getCharactY();
            w = (arcade::WhereAmI*) ::operator new (sizeof(arcade::WhereAmI) + (sizeof(arcade::Position) * snakeX.size()));
            w->lenght = snakeX.size();
            w->type = com;
            i = 0;
            while (i < snakeX.size())
            {
                pos.x = (int)snakeX[i];
                pos.y = (int)snakeY[i];
                w->position[i] = pos;
                i++;
            }
            write(1, w, sizeof(arcade::WhereAmI) + (sizeof(arcade::Position) * snakeX.size()));
            delete w;
        }
    }
}

extern "C"
{
arcade::IGame *createLib(int width, int height)
{
	return (new arcade::Snake(width, height));
}
}

void 	arcade::Snake::loadScore(){
	std::ifstream file(this->path);
	std::ofstream cfile;
	std::string		str;

	if (!file.is_open()){
		cfile.open(this->path);
	}else{
		while (std::getline(file, str)) {
			 this->scores.insert(std::make_pair(std::stoi(str.erase(0, str.find(" ") + 1)), str.substr(0, str.find(" "))));
		}
}
}

arcade::Snake::Snake(int width, int height)
: width(width), height(height), display(0), score(0)
{
	this->createMap();
	srand(time(NULL) * getpid());
	this->spawnFood();
	this->path = "./snake.score";
	this->loadScore();
  this->scores.insert(std::make_pair(0, "AAA"));
	this->action.insert (std::make_pair (arcade::CommandType::GO_UP, &arcade::Snake::MoveUp));
    this->action.insert (std::make_pair (arcade::CommandType::GO_DOWN, &arcade::Snake::MoveDown));
    this->action.insert (std::make_pair (arcade::CommandType::GO_LEFT, &arcade::Snake::MoveLeft));
    this->action.insert (std::make_pair (arcade::CommandType::GO_RIGHT, &arcade::Snake::MoveRight));
    this->action.insert (std::make_pair (arcade::CommandType::ILLEGAL, &arcade::Snake::Option));
    this->spawn();
}

arcade::Snake::~Snake()
{
}

void arcade::Snake::playRound(arcade::CommandType com)
{
    auto it = this->action.find (com);

    this->display = (this->display + 1) % 1;
  	if (it != this->action.end()) {
  		this->com = com;
   	}
    if (this->display == 0)
    {
    	it = this->action.find (this->com);
			(this->*it->second) ();
    	this->eat();
 	    this->updateSnake();
    	this->head->setX(this->head->getX() + this->head->getXSpeed());
    	this->head->setY(this->head->getY() + this->head->getYSpeed());
        this->hurt();
   	}
}

std::map<int, std::string> arcade::Snake::loadSprite()
{
    std::map<int, std::string> sprite;

    sprite.insert (std::make_pair (0, "./ressources/E_6_pacman_empty.png"));
    sprite.insert (std::make_pair (6, "./ressources/O_8_pacman_powerup.png"));
    return  (sprite);
}

const std::vector<arcade::TileType> arcade::Snake::getMap() const
{
    return (this->map);
}

const std::vector<std::string> arcade::Snake::getCharactSprite() const
{
    std::vector <std::string> sprite;
    size_t i;

    i = 0;
    while (i < this->snake.size ()) {
        sprite.push_back (((this->snake[i])->getImg ())[(this->snake[i])->getState ()]);
        i++;
    }
    return (sprite);
}

std::map<size_t, std::string> arcade::Snake::getHighScore() const
{
  return (this->scores);
}

std::string arcade::Snake::getPathScore() const
{
    return (this->path);
}

size_t arcade::Snake::getScore() const
{
    return (this->score);
}

bool arcade::Snake::getPlay() const
{
    return (true);
}

const std::vector<float> arcade::Snake::getCharactX() const
{
    std::vector<float> x;
    size_t i;

    i = 0;
    while (i < this->snake.size ()) {
        x.push_back ((this->snake[i])->getX ());
        i++;
    }
    return (x);
}

const std::vector<float> arcade::Snake::getCharactY() const
{
    std::vector<float> y;
    size_t i;

    i = 0;
    while (i < this->snake.size ()) {
        y.push_back ((this->snake[i])->getY ());
        i++;
    }
    return (y);
}

void arcade::Snake::createMap()
{
	int i;

	i = 0;
	while (i < this->width * this->height)
	{
		map.push_back(arcade::TileType::EMPTY);
		i++;
	}
}

void	arcade::Snake::spawnFood()
{
	int i;

	i = rand() % (this->width * this->height);
	this->map[i] = arcade::TileType::POWERUP;
}

int arcade::Snake::MoveUp () {
	if (this->head->getYSpeed() == 0)
	{
        this->com = arcade::CommandType::GO_UP;
		this->head->setYSpeed(-1);
		this->head->setXSpeed(0);
	}
  return (0);
}

int arcade::Snake::MoveDown () {
	if (this->head->getYSpeed() == 0)
	{
        this->com = arcade::CommandType::GO_DOWN;
		this->head->setYSpeed(1);
		this->head->setXSpeed(0);
	}
  return (0);
}

int arcade::Snake::MoveLeft () {
	if (this->head->getXSpeed() == 0)
	{
        this->com = arcade::CommandType::GO_LEFT;
		this->head->setYSpeed(0);
		this->head->setXSpeed(-1);
	}
  return (0);
}

int arcade::Snake::MoveRight () {
	if (this->head->getXSpeed() == 0)
	{
        this->com = arcade::CommandType::GO_RIGHT;
		this->head->setYSpeed(0);
		this->head->setXSpeed(1);
	}
  return (0);
}

int arcade::Snake::Option () {
    return (0);
}

void    arcade::Snake::updateSnake() {
    for (size_t i = this->snake.size() - 1; i > 0; i--){
        this->snake[i]->setX(this->snake[i - 1]->getX());
        this->snake[i]->setY(this->snake[i - 1]->getY());
        this->snake[i]->setState(this->snake[i - 1]->getState());
    }
}

void arcade::Snake::eat()
{
	Character *tail;
	auto it = this->snake.end();

	it--;
	if (map[this->head->getY() * this->width + this->head->getX()] == arcade::TileType::POWERUP)
	{
		map[this->head->getY() * this->width + this->head->getX()] = arcade::TileType::EMPTY;
		tail = new Character((*it)->getX(), (*it)->getY());
		tail->setImg("./ressources/D_2_snake2.png");
		tail->setState((*it)->getState());
		this->snake.push_back(tail);
        this->score += 100;
		this->spawnFood();
	}
}

void    arcade::Snake::reSpawn()
{
    arcade::Character   *tmp;

    delete (this->head);
    this->snake.erase(this->snake.begin(), this->snake.end());

    this->head = new arcade::Character(11, 11);
    this->head->setState(0);
    this->head->setXSpeed(1);
    this->head->setImg("./ressources/S_2_snake.png");
    this->snake.push_back(this->head);

    tmp = new arcade::Character (10, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);
    this->com = arcade::CommandType::GO_RIGHT;

    tmp = new arcade::Character (9, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);

    tmp = new arcade::Character (8, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);
		this->score = 0;
}

void    arcade::Snake::spawn()
{
    arcade::Character   *tmp;

    this->head = new arcade::Character(11, 11);
    this->head->setState(0);
    this->head->setXSpeed(1);
    this->head->setImg("./ressources/S_2_snake.png");
    this->snake.push_back(this->head);

    tmp = new arcade::Character (10, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);

    tmp = new arcade::Character (9, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);

    tmp = new arcade::Character (8, 11);
    tmp->setImg ("./ressources/D_2_snake2.png");
    this->snake.push_back (tmp);

    this->com = arcade::CommandType::GO_RIGHT;
}

void arcade::Snake::hurt()
{
	auto it = this->snake.begin();

	if (this->head->getX() < 0 || this->head->getX() > this->width
	 || this->head->getY() < 0 || this->head->getY() > this->height)
		this->reSpawn();
	it++;
    while (it != this->snake.end ()) {
            if (this->head->getX () == (*it)->getX () && this->head->getY () == (*it)->getY ()) {
                this->reSpawn ();
                return;
            }
            it++;
    }
}

size_t arcade::Snake::getWidth() const
{
	return (this->width);
}

size_t arcade::Snake::getHeight() const
{
	return (this->height);
}
