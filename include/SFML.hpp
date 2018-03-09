//
// SFML.hpp for arcade in /home/sebastien/Rendu/arcade/cpp
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Sun Mar 19 15:20:56 2017 Sebastien Le Guischer
// Last update Sun Mar 19 15:20:57 2017 Sebastien Le Guischer
//

#ifndef SFML_HPP_
# define SFML_HPP_

# define WIDTH this->width / this->width_game * 1.0
# define HEIGHT (this->height - 50) / this->height_game * 1.0

# include "IG_Lib.hpp"
#include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

namespace arcade {

    class SFML : public IG_Lib {
    public:
        SFML (int width, int height);
        virtual ~SFML ();

        virtual void updateMap(std::vector<arcade::TileType> map, size_t width, size_t height);
        virtual void updateCharacter(float x, float y, std::string sprite);
        virtual void display();
        virtual arcade::CommandType keyboard();
        virtual void setBlock(std::map<int, std::string>);
        virtual void displayMenu(const std::vector<size_t>& index, const std::vector<std::string>& lib,
                                const std::vector<std::string>& game, const std::string & nickname);
        virtual void displayPause();
        // display score 
        virtual void displayScore(std::map<size_t, std::string>, size_t);
        // allow you to print vector on window
        void  display_vec(std::vector<std::string> vec, int x_strat, int y_start, int size, size_t select);
        // allow you to print text on window
        void  draw_me_this_text(std::string const & str, int x, int y, int size,  sf::Color & col);
        // allow you to print name of current user
        void    displayname(std::string const & nickname, std::vector<size_t> index);



    private:
        std::map<int, sf::Texture> sprite;
        std::map<std::string, sf::Texture> charact;
        sf::RenderWindow window;
        sf::Clock clock;
        std::map <sf::Keyboard::Key, arcade::CommandType> key;
        arcade::CommandType com;
        int width;
        int height;
        int width_game;
        int height_game;
    };

    extern "C"
    {
    IG_Lib *createLib (int width, int height);
    }
}
#endif
