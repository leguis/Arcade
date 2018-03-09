//
// IGame.hpp for arcade in /home/sebastien/Rendu/cpp_arcade
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Mon Apr  3 18:18:16 2017 Sebastien Le Guischer
// Last update Tue Apr  4 21:06:06 2017 meghenr
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <vector>
# include <map>
# include "Protocol.hpp"

extern "C"
{
  void Play(void);
}

namespace	arcade
{
  class		IGame
  {
  public:
    virtual ~IGame() {};
    virtual void Play() = 0;  //   Moulinette
    // this fuction simulate a round of your game
    virtual void playRound(arcade::CommandType) = 0;
    // this function allow you to load sprite of Character
    virtual std::map<int, std::string> loadSprite() = 0;
    //this function return the map
    virtual const std::vector<arcade::TileType> getMap() const = 0;
    //this function return width of the game
    virtual size_t getWidth() const = 0;
    //this function return height of the game
    virtual size_t getHeight() const = 0;
    //this function return all Characters sprite
    virtual const std::vector<std::string> getCharactSprite() const = 0;
    //this fuction return all postion x of Characters
    virtual const std::vector<float> getCharactX() const = 0;
    //this fuction return all postion xyof Characters
    virtual const std::vector<float> getCharactY() const = 0;
    //this fuction return score
    virtual size_t getScore() const = 0;
    //this fuction return heigh score of current game
    virtual std::map<size_t, std::string> getHighScore() const = 0;
    //this function return path of score file of the game
    virtual std::string getPathScore() const = 0;
    virtual bool getPlay() const = 0;
  };
}

#endif /* !IGAME_HPP_ */
