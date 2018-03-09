/*
** ICharacter.hpp for cpp_arcade in /home/meghen_r/delivery/cpp_arcade/ICharacter.hpp
**
** Made by Riadh Meghenem
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  mer. avr. 05 14:07:14 2017 Riadh Meghenem
** Last update mer. avr. 05 14:07:14 2017 Riadh Meghenem
*/

#ifndef CPP_ARCADE_CHARACTER_HPP
#define CPP_ARCADE_CHARACTER_HPP

#include <vector>
#include <string>

namespace arcade {

    class Character {
    private:
        float x;
        float y;
        float x_speed;
        float y_speed;
        int   state;
        std::vector <std::string> img;

    public:
        Character (float x, float y);

        virtual ~Character ();

        virtual float getX () const;

        virtual void setX (float x);

        virtual float getY () const;

        virtual void setY (float speed);

        virtual float getXSpeed () const;

        virtual void setXSpeed (float speed);

        virtual float getYSpeed () const;

        virtual void  setState(int i);
        virtual int   getState() const ;

        virtual void setYSpeed (float speed);

        virtual const std::vector <std::string> getImg () const;

        virtual void setImg (std::string const  to_add);
    };
}
#endif //CPP_ARCADE_CHARACTER_HPP
