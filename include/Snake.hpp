//
// Snake.hpp for arcade in /home/sebastien/Rendu/cpp_arcade/games/snake
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Thu Apr  6 22:47:26 2017 Sebastien Le Guischer
// Last update Thu Apr  6 22:47:27 2017 Sebastien Le Guischer
//

#ifndef SNAKE_HPP_
# define SNAKE_HPP_

# include "Character.hpp"
# include "IGame.hpp"

extern "C"
{
  void Play(void);
}

namespace arcade
{
	class Snake : public IGame
	{
	public:
		Snake(int width, int height);
		virtual ~Snake();

		virtual void Play() {};
		virtual void playRound(arcade::CommandType com);
		virtual std::map<int, std::string> loadSprite();
    virtual const std::vector<arcade::TileType> getMap() const;
    virtual const std::vector<std::string> getCharactSprite() const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;
    virtual const std::vector<float> getCharactX() const;
    virtual const std::vector<float> getCharactY() const;
    virtual std::map<size_t, std::string> getHighScore() const;
    virtual std::string getPathScore() const;
    virtual bool getPlay() const;
    virtual size_t getScore() const;

    int Option();
    int MoveUp();
    int MoveDown();
    int MoveLeft();
    int MoveRight();
  	void	createMap();
  	void	spawnFood();
		void	updateSnake();
    void eat();
    void hurt();
    void spawn();
    void reSpawn();
		void loadScore();
  private:
  	int width;
  	int height;
    int display;
    size_t score;
  	arcade::CommandType com;
  	std::vector<arcade::TileType> map;
  	Character *head;
  	std::vector<Character *> snake;
		std::string				path;
    std::map<arcade::CommandType, int (arcade::Snake::*)()> action;
		std::map<size_t, std::string> scores;
		};
}

#endif
