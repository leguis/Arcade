//
// lapin.hpp for arcade in /home/sebastien/Rendu/arcade/cpp
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Thu Mar 16 15:35:32 2017 Sebastien Le Guischer
// Last update Tue Apr  4 20:34:14 2017 meghenr
//

#ifndef LAPIN_HPP_
# define LAPIN_HPP_

# include <map>
# include "IG_Lib.hpp"
# include "lapin.h"

# define WIDTH this->width / this->width_game * 1.0
# define HEIGHT (this->height - 50) / this->height_game * 1.0

namespace arcade
{
  class Lapin : public IG_Lib
  {
  public:
    Lapin (int width, int height);
    virtual ~Lapin ();

    virtual void display();
    virtual arcade::CommandType keyboard ();
    virtual void setBlock (std::map<int, std::string> to_add);
    virtual void updateCharacter(float x, float y, std::string sprite);
    virtual void displayMenu(const std::vector<size_t>&, const std::vector<std::string>&,
                            const std::vector<std::string>&, const std::string &);
    virtual void displayPause ();
    virtual void updateMap (std::vector <arcade::TileType> map, size_t width, size_t height);
    virtual void displayScore(std::map<size_t, std::string>, size_t);

    // display the name of current user
    void displayName(std::string name, size_t index, t_bunny_picture *pic);
    // allow you to print vector on window
    void displayVector(std::vector<std::string> list, t_bunny_position start, size_t index, t_bunny_picture *pic);
    // allow you to print text
    void printText(std::string text, t_bunny_picture *pic, unsigned int color, t_bunny_position pos, t_bunny_position size);
    // allow you to print text
    void printSprite (int x, int y, t_bunny_pixelarray *sprite);
    // return event keyboard
    const std::map <t_bunny_keysym, arcade::CommandType> getKey () const;
    void setCommand (arcade::CommandType com);

  private:
    int width;
    int height;
    int width_game;
    int height_game;
    t_bunny_window *win;
    t_bunny_pixelarray *pix;
    t_bunny_picture *pic;
    arcade::CommandType com;
    std::map<int, t_bunny_pixelarray *> sprite;
    std::map<std::string, t_bunny_pixelarray *> charact;
    std::map <t_bunny_keysym, arcade::CommandType> key;
  };

  extern "C"
  {
    IG_Lib *createLib (int width, int height);
  }
}

#endif
