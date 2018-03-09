/*
** Character.cpp for cpp_arcade in /home/meghen_r/delivery/cpp_arcade/Character.cpp
**
** Made by Riadh Meghenem
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  mer. avr. 05 14:35:47 2017 Riadh Meghenem
** Last update mer. avr. 05 14:35:47 2017 Riadh Meghenem
*/

#include <vector>
#include <string>
#include "Character.hpp"

arcade::Character::Character(float x, float y)
:   x(x), y(y), x_speed(0), y_speed(0)
{
    this->state = 0;
}

arcade::Character::~Character()
{
}

float arcade::Character::getX() const{
    return this->x;
}

void arcade::Character::setX(float x) {
    this->x = x;
}

float arcade::Character::getY() const {
    return this->y;
}

void arcade::Character::setY(float y){
    this->y = y;
}

float arcade::Character::getXSpeed() const {
    return  this->x_speed;
}

void arcade::Character::setXSpeed(float speed){
    this->x_speed = speed;
}

float arcade::Character::getYSpeed() const{
    return this->y_speed;
}

void arcade::Character::setYSpeed(float speed){
    this->y_speed = speed;
}

int arcade::Character::getState() const{
    return this->state;
}

void arcade::Character::setState(int i){
    this->state = i;
}


const std::vector<std::string> arcade::Character::getImg() const {
    return this->img;
}

void arcade::Character::setImg(std::string const to_add)
{
    this->img.push_back(to_add);
}