//
// Pacman.hpp for arcade in /home/sebastien/Rendu/cpp_arcade
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Tue Apr  4 16:26:43 2017 Sebastien Le Guischer
// Last update Tue Apr  4 21:01:08 2017 meghenr
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include <vector>
# include <map>
# include "IGame.hpp"
# include "Character.hpp"

namespace arcade
{
  class Pacman : public IGame
  {
  public:
    Pacman(int width, int height);
    virtual ~Pacman();

    virtual void Play();
    virtual void playRound(arcade::CommandType);
    virtual std::map<int, std::string>	loadSprite();
    virtual const std::vector<std::string>  getCharactSprite() const;
    virtual const std::vector<float>  getCharactX() const;
    virtual const std::vector<float>  getCharactY() const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;
    virtual const std::vector<arcade::TileType> getMap() const;
    virtual std::map<size_t, std::string> getHighScore() const;
    virtual std::string getPathScore() const;
    virtual bool getPlay() const;
    virtual size_t getScore() const;

    void loadScore();
    int MoveUp();
    int MoveDown();
    int MoveLeft();
    int MoveRight();
    int Option();
    void ParseMap();
    bool canMove(float x, float y, float new_x, float new_y);
    void updateCharacter();
    void eatOther();
    void  eatGhost();
    void  reset();
      void moveGhost();
    void timer();

  private:
    int	width;
    int	height;
    size_t score;
    int   nb_terate;
    std::string path;
    std::map<size_t, std::string> scores;
    arcade::CommandType com;
    std::vector<arcade::TileType> map;
    std::map<arcade::CommandType, int (arcade::Pacman::*)()> action;
    Character     *Player;
    std::vector<arcade::Character *> characters;
  };

  extern "C"
  {
    void Play(void) {};
  }
}

#endif
