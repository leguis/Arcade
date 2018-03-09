//
// IG_Lib.hpp for arcade in /home/sebastien/Rendu/arcade/cpp
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Fri Mar 17 18:13:07 2017 Sebastien Le Guischer
// Last update Tue Apr  4 20:35:48 2017 meghenr
//

#ifndef IG_LIB_HPP_
# define IG_LIB_HPP_

# include <string>
# include <map>
# include <vector>
# include "Character.hpp"
# include "Protocol.hpp"

namespace	arcade
{
  class		IG_Lib
  {
  public:
    virtual ~IG_Lib() {};
    //This function update Map
    virtual void updateMap(std::vector<arcade::TileType> map, size_t width, size_t height) = 0;
    //this function update position of Character in map
    virtual void updateCharacter(float x, float y, std::string sprite) = 0;
    //this fuction allow you to update all changes made on the map
    virtual void display() = 0;
    //this function return event on keyboard
    virtual arcade::CommandType keyboard() = 0;
    //this function allow you to load texture of your game
    virtual void setBlock(std::map<int, std::string>) = 0;
    //this fuction display menu of your game
    virtual void displayMenu(const std::vector<size_t>&, const std::vector<std::string>&,
                            const std::vector<std::string>&, const std::string &) = 0;
    virtual void displayPause() = 0;
    //this function display the current score
    virtual void displayScore(std::map<size_t, std::string>, size_t) = 0;
  };
}

#endif /* !IG_LIB_HPP_ */
