/*
** sfml.cpp for cpp_arcade in /home/meghen_r/delivery/cpp_arcade/sfml.cpp
**
** Made by Riadh Meghenem
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  sam. avr. 08 01:45:02 2017 Riadh Meghenem
** Last update sam. avr. 08 01:45:02 2017 Riadh Meghenem
*/

#include "unistd.h"
#include "SFML.hpp"

arcade::SFML::SFML(int width, int height)
:width(width), height(height)
{
    this->window.create(sf::VideoMode(width, height), "arcade");

    key.insert(std::make_pair(sf::Keyboard::Num3, static_cast<arcade::CommandType>(10)));
    key.insert(std::make_pair(sf::Keyboard::Num2, static_cast<arcade::CommandType>(11)));
    key.insert(std::make_pair(sf::Keyboard::Num4, static_cast<arcade::CommandType>(12)));
    key.insert(std::make_pair(sf::Keyboard::Num5, static_cast<arcade::CommandType>(13)));
    key.insert(std::make_pair(sf::Keyboard::Num8, static_cast<arcade::CommandType>(14)));    
    key.insert(std::make_pair(sf::Keyboard::Num9, static_cast<arcade::CommandType>(15)));    
    key.insert(std::make_pair(sf::Keyboard::Up, arcade::CommandType::GO_UP));
    key.insert(std::make_pair(sf::Keyboard::Down, arcade::CommandType::GO_DOWN));
    key.insert(std::make_pair(sf::Keyboard::Left, arcade::CommandType::GO_LEFT));
    key.insert(std::make_pair(sf::Keyboard::Right, arcade::CommandType::GO_RIGHT));
    key.insert(std::make_pair(sf::Keyboard::Escape, arcade::CommandType::ILLEGAL));
    key.insert(std::make_pair(sf::Keyboard::Return, arcade::CommandType::PLAY));
    key.insert(std::make_pair(sf::Keyboard::Space, arcade::CommandType::SHOOT));
}


arcade::SFML::~SFML(){
  this->window.close();
};

void arcade::SFML::updateMap(std::vector<arcade::TileType> map, size_t width, size_t height){

    int     i = 0;
    auto    it = this->sprite.begin();
    float ratx;
    float raty;
    sf::Sprite sprite;

    this->width_game = width;
    this->height_game = height;
    while (i < this->width_game * this->height_game){
        it = this->sprite.find(static_cast<int>(map[i]));
        if (it != this->sprite.end()) {
            sprite.setTexture(it->second);
            ratx = (float)WIDTH / (float)(it->second).getSize().x;
            raty = (float)HEIGHT / (float)(it->second).getSize().y;
            sprite.setScale (sf::Vector2f (ratx, raty));
            sprite.setPosition (sf::Vector2f ((i % this->width_game) * WIDTH, (i / this->width_game) * HEIGHT));
            this->window.draw(sprite);
        }
        i++;
    }
}

void arcade::SFML::updateCharacter(float x, float y, std::string sprite){
    sf::Texture     pix;
    sf::Sprite      spritee;
    float ratx;
    float raty;

    auto it = this->charact.find(sprite);

    if (it == this->charact.end())
    {
        pix.loadFromFile(sprite.c_str());
        this->charact.insert(std::make_pair(sprite, pix));
    }
    else
        pix = it->second;
    spritee.setTexture(pix);

    ratx = (float)WIDTH / (float)(it->second).getSize().x;
    raty = (float)HEIGHT / (float)(it->second).getSize().y;
    spritee.setScale(ratx, raty);
    spritee.setPosition (sf::Vector2f (x * WIDTH, y * HEIGHT));
    this->window.draw(spritee);

}

void arcade::SFML::display(){
  this->window.display();
  while (this->clock.getElapsedTime().asSeconds() < 0.05){}
  this->clock.restart();
  this->window.clear();
}

arcade::CommandType arcade::SFML::keyboard(){

    sf::Event event;

    this->window.pollEvent(event);
    if (event.type == sf::Event::KeyPressed){
        auto it = this->key.find(event.key.code);
        if (it != this->key.end()){
            return (it->second);
        }
    }
    return (arcade::CommandType::GO_FORWARD);
}

void arcade::SFML::displayScore(std::map<size_t, std::string> hs, size_t score)
{
  sf::Text        text;
  sf::Font        font;
  //sf::Color       col = sf::Color::Red;
  auto it = hs.end();

  it--;
  font.loadFromFile("ressources/ka1.ttf");
  text.setFont(font);
  text.setString("Score:" + std::to_string(score) + " - " + it->second + ":" + std::to_string(it->first));
  text.setCharacterSize(15);
  text.setFillColor(sf::Color::Red);
  text.setPosition(0, this->height - 50);
  this->window.draw(text);
}

void arcade::SFML::setBlock(std::map<int, std::string> to_add){
    auto it = to_add.begin();

    while (it != to_add.end()){
        sf::Texture texture;

        texture.loadFromFile(it->second.c_str());
        this->sprite.insert(std::make_pair(it->first, texture));
        it++;
    }
}

extern "C"
{
arcade::IG_Lib *createLib(int width, int height)
{
    return (new arcade::SFML(height, width));
}
}

void  arcade::SFML::draw_me_this_text(std::string const & str,
                                      int x, int y, int size,  sf::Color & col){
  sf::Text        text;
  sf::Font font;

  font.loadFromFile("ressources/ka1.ttf");
  text.setFont(font);
  text.setString(str);
  text.setCharacterSize(size);
  text.setFillColor(col);
  text.setPosition(x, y);
  this->window.draw(text);
}

void arcade::SFML::display_vec(std::vector<std::string> vec, int x_strat, int y_start, int size, size_t select){
  sf::Color       col = sf::Color::Red;

  for (size_t i = 0; i < vec.size(); i++) {
    if (i == select){
      col = sf::Color::Green;
      this->draw_me_this_text(vec[i].c_str(), x_strat, y_start, size, col);
      col = sf::Color::Red;
    }
    else
      this->draw_me_this_text(vec[i].c_str(), x_strat, y_start, size, col);
    y_start += 50;
  }
}

void arcade::SFML::displayname(std::string const & nickname, std::vector<size_t> index){
  sf::Color       col = sf::Color::Red;

  if (index[3] == 0)
    col = sf::Color::Blue;
  this->draw_me_this_text(nickname.substr(0, 1), 465, 575, 35, col);
  col = sf::Color::Red;
  if (index[3] == 1)
    col = sf::Color::Blue;
  this->draw_me_this_text(nickname.substr(1, 1), 635, 575, 35, col);
  col = sf::Color::Red;
  if (index[3] == 2)
    col = sf::Color::Blue;
  this->draw_me_this_text(nickname.substr(2, 2), 785, 575, 35, col);
  col = sf::Color::Red;
}

void arcade::SFML::displayMenu(const std::vector<size_t>& index, const std::vector<std::string>& lib,
                        const std::vector<std::string>& game, const std::string & nickname){
                          sf::Font        font;
  sf::Texture     pix;
  sf::Sprite      sprite;
  sf::Color       col = sf::Color::Red;
  pix.loadFromFile("ressources/menu_lapin.png");
  sprite.setTexture(pix);
  this->window.draw(sprite);
  this->draw_me_this_text("Menu", this->width / 2 - 105, 0, 60, col);
  this->draw_me_this_text("Chose your lib", this->width / 3 - 270, 155, 35, col);
  this->display_vec(lib, this->width / 3 - 300, 245, 20, index[0]);
  this->draw_me_this_text("Chose your game", this->width / 3 + 350, 155, 35, col);
  this->display_vec(game, this->width / 3 + 340, 245, 20, index[1]);
  this->displayname(nickname, index);
  this->display();
  this->window.clear(sf::Color::Black);
}

void arcade::SFML::displayPause(){

}
