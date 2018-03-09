//
// lapin.cpp for arcade in /home/sebastien/Rendu/arcade/cpp
//
// Made by Sebastien Le Guischer
// Login   <sebastien@epitech.net>
//
// Started on  Thu Mar 16 15:35:24 2017 Sebastien Le Guischer
// Last update Sun Apr  9 02:29:15 2017 meghenr
//

#include <iostream>
#include "Character.hpp"
#include "lapin.hpp"


t_bunny_response	loop(void *data)
{
	arcade::Lapin *lib = static_cast<arcade::Lapin *>(data);
	const	bool	*keyboard;
	std::map<t_bunny_keysym, arcade::CommandType> key = lib->getKey();
	auto it = key.begin();

	if ((keyboard = bunny_get_keyboard()) == NULL)
		throw std::string ("bunny_get_keyboard failed");
	while (it != key.end())
	{
		if (keyboard[it->first] == true)
		{
			lib->setCommand(it->second);
			return (EXIT_ON_SUCCESS);
		}
		it++;
	}
	lib->setCommand(arcade::CommandType::GO_FORWARD);
	return (EXIT_ON_SUCCESS);
}

t_bunny_response key_function(t_bunny_event_state state, t_bunny_keysym key, void *data)
{
	(void)(state);
	(void)(key);
	(void)(data);
	return (GO_ON);
}

unsigned int    getpixel(t_bunny_pixelarray *pix, t_bunny_position *pos)
{
  int           i;
  unsigned      *pixels;

  pixels = (unsigned *)pix->pixels;
  i = pix->clipable.clip_width * pos[0].y + pos[0].x;
  return (pixels[i]);
}

void            tekpixel(t_bunny_pixelarray *pix,
                         t_bunny_position *pos, t_color *col)
{
  t_color       *pixel;
  t_color       pixels;
  t_color       backpixel;
  float         ratio;

  ratio = (float)col->argb[3] / 255 * 100;
  backpixel.full = getpixel(pix, pos);
  pixels = col[0];
  pixels.argb[0] = (float)(100 - ratio) / 100 *
    backpixel.argb[0] + ratio / 100 * pixels.argb[0];
  pixels.argb[1] = (float)(100 - ratio) / 100 *
    backpixel.argb[1] + ratio / 100 * pixels.argb[1];
  pixels.argb[2] = (float)(100 - ratio) / 100 *
    backpixel.argb[2] + ratio / 100 * pixels.argb[2];
  pixel = (t_color *)pix->pixels;
  pixel[pix->clipable.clip_width * pos->y + pos->x] = pixels;
}

arcade::Lapin::Lapin(int width, int height)
: width(width), height(height), win(bunny_start(width, height, 0, "Plop")), pix(bunny_new_pixelarray(width, height - 50))
{
  this->pic = bunny_new_picture(width, height);
	if (win == NULL || pix == NULL || pic == NULL)
		throw std::string ("Something went wring in LibLapin");
  key.insert(std::make_pair(BKS_3, static_cast<arcade::CommandType>(10)));
  key.insert(std::make_pair(BKS_2, static_cast<arcade::CommandType>(11)));
  key.insert(std::make_pair(BKS_4, static_cast<arcade::CommandType>(12)));
  key.insert(std::make_pair(BKS_5, static_cast<arcade::CommandType>(13)));
  key.insert(std::make_pair(BKS_8, static_cast<arcade::CommandType>(14)));
  key.insert(std::make_pair(BKS_9, static_cast<arcade::CommandType>(15)));
  key.insert(std::make_pair(BKS_UP, arcade::CommandType::GO_UP));
  key.insert(std::make_pair(BKS_DOWN, arcade::CommandType::GO_DOWN));
	key.insert(std::make_pair(BKS_LEFT, arcade::CommandType::GO_LEFT));
	key.insert(std::make_pair(BKS_RIGHT, arcade::CommandType::GO_RIGHT));
	key.insert(std::make_pair(BKS_ESCAPE, arcade::CommandType::ILLEGAL));
	key.insert(std::make_pair(BKS_RETURN, arcade::CommandType::PLAY));
	key.insert(std::make_pair(BKS_SPACE, arcade::CommandType::SHOOT));
}

arcade::Lapin::~Lapin()
{
  auto it = this->charact.begin();
  auto i = this->sprite.begin();

  while (i != this->sprite.end())
  {
    bunny_delete_clipable(&(i->second)->clipable);
    i++;
  }
  while (it != this->charact.end())
  {
    bunny_delete_clipable(&(it->second)->clipable);
    it++;
  }
  bunny_delete_clipable(this->pic);
	bunny_delete_clipable(&this->pix->clipable);
	bunny_stop(win);
}

void	arcade::Lapin::display()
{
  bunny_clear(&this->win->buffer, BLACK);
  bunny_blit(&this->win->buffer, this->pic, NULL);
  bunny_blit(&win->buffer, &pix->clipable, NULL);
	bunny_display(this->win);
}

arcade::CommandType	arcade::Lapin::keyboard()
{
	bunny_set_key_response(key_function);
	bunny_set_loop_main_function(loop);
	bunny_loop(this->win, 60, this);
	return (com);
}

void	arcade::Lapin::setBlock(std::map<int, std::string> to_add)
{
	auto it = to_add.begin();

	while (it != to_add.end())
	{
		this->sprite.insert(std::make_pair(it->first, bunny_load_pixelarray(it->second.c_str())));
		it++;
	}
}

void    arcade::Lapin::printSprite(int x, int y, t_bunny_pixelarray *sprite)
{
	float ratiox;
	float ratioy;
	float _x;
	float _y;
  t_bunny_position pos;
  t_bunny_position pos2;
  t_color         col;

  if (sprite == NULL)
  	throw std::string ("Failed to load sprite");
  ratiox = sprite->clipable.clip_width / (WIDTH * 1.0);
  ratioy = sprite->clipable.clip_height / (HEIGHT * 1.0);
  _y = 0;
  pos.y = 0;
  pos2.y = y;
  while (pos2.y < y + HEIGHT)
  {
    _x = 0;
    pos.x = 0;
    pos2.x = x;
    while (pos2.x < x + WIDTH)
    {
      col.full = getpixel(sprite, &pos);
      tekpixel(this->pix, &pos2, &col);
      pos2.x = pos2.x + 1;
      _x += ratiox;
      pos.x = _x;
    }
    pos2.y = pos2.y + 1;
    _y += ratioy;
	  pos.y = _y;
  }
}

void arcade::Lapin::displayScore(std::map<size_t, std::string> hs, size_t score)
{
  t_bunny_position size = {30, 40};
  t_bunny_position pos;
  auto it = hs.end();

  it--;
  bunny_clear(&this->pic->buffer, BLACK);
  pos.y = this->height - 51;
  pos.x = 10;
  printText("Score:" + std::to_string(score) + " - " + it->second + ":" + std::to_string(it->first), this->pic, WHITE, pos, size);
}

void	arcade::Lapin::updateMap(const std::vector<arcade::TileType> map, size_t width, size_t height)
{
	auto i = 0;
	std::map<int, t_bunny_pixelarray *>::iterator sprite_it;

  bunny_clear(&this->pix->clipable.buffer, BLACK);
	this->width_game = width;
	this->height_game = height;
	while (i < this->width_game * this->height_game)
	{
		sprite_it = this->sprite.find(static_cast<int>(map[i]));
		if (sprite_it != this->sprite.end())
			printSprite((i % this->width_game) * WIDTH, (i / this->width_game) * HEIGHT, sprite_it->second);
		i++;
	}
}

void arcade::Lapin::printText(std::string text, t_bunny_picture *pic, unsigned int color, t_bunny_position pos, t_bunny_position size)
{
  t_color col;
  t_bunny_font *fnt = bunny_load_font(85 * text.size(), 100, "ressources/ka1.ttf", &size);

	if (fnt == NULL)
		throw std::string ("failed to load font");
  fnt->color = color;
  col.full = BLACK;
  col.argb[3] = 0;
  fnt->string = text.c_str();
  bunny_clear(&fnt->clipable.buffer, col.full);
  bunny_draw(&fnt->clipable);
  bunny_blit(&pic->buffer, &fnt->clipable, &pos);
  bunny_delete_clipable(&fnt->clipable);
}

void arcade::Lapin::displayVector(std::vector<std::string> list, t_bunny_position start, size_t index, t_bunny_picture *pic)
{
  size_t i = 0;
  t_bunny_position pos;
  t_bunny_position size = {12, 17};

  pos.x = start.x;
  pos.y = start.y;
  while (i < list.size())
  {
    if (i == index)
      this->printText(list[i], pic, rand() | BLACK, pos, size);
    else
      this->printText(list[i], pic, WHITE, pos, size);
    pos.y = pos.y + 45;
    i++;
  }
}

void arcade::Lapin::displayName(std::string name, size_t index, t_bunny_picture *pic)
{
  t_bunny_position size = {42, 50};
  t_bunny_position pos;
  size_t i = 0;

  pos.x = 460;
  pos.y = 565;
  while (i < 3)
  {
    if (i == 0)
    {
      if (i == index)
       printText(name.substr(i, i + 1), pic, rand() | BLACK, pos, size);
     else
       printText(name.substr(i, i + 1), pic, WHITE, pos, size);
    }
    else
    {
      if (i == index)
       printText(name.substr(i, i), pic, rand() | BLACK, pos, size);
      else
       printText(name.substr(i, i), pic, WHITE, pos, size);
    }
    pos.x = pos.x + 160;
    i++;
  }
}

void arcade::Lapin::displayMenu(const std::vector<size_t>& index, const std::vector<std::string>& lib,
                        const std::vector<std::string>& game, const std::string & nickname)
{
  t_bunny_picture *pic;
  t_bunny_position pos;
  t_bunny_position size = {42, 50};

  if ((pic = bunny_load_picture("ressources/menu_lapin.png")) == NULL)
		throw std::string ("failed to load picture");
  pos.x = (this->win->buffer.width / 2) - 85;
  pos.y = 50;

  this->printText("Menu", pic, rand() | BLACK, pos, size);
  pos.x = 100;
  pos.y = 220;
  this->displayVector(lib, pos, index[0], pic);
  pos.x = 740;
  this->displayVector(game, pos, index[1], pic);
  this->displayName(nickname, index[3], pic);
  bunny_blit(&this->win->buffer, pic, NULL);
  bunny_display(this->win);
  bunny_delete_clipable(pic);
}

void arcade::Lapin::displayPause()
{
}

const std::map<t_bunny_keysym, arcade::CommandType> arcade::Lapin::getKey() const
{
	return (this->key);
}

void arcade::Lapin::setCommand(arcade::CommandType  com)
{
	this->com = com;
}

void    arcade::Lapin::updateCharacter(float x, float y, std::string sprite)
{
  t_bunny_pixelarray  *pix;
  auto it = this->charact.find(sprite);

  if (it == this->charact.end())
  {
	  if ((pix = bunny_load_pixelarray(sprite.c_str())) == NULL)
			throw std::string ("faile to load pixelarray");
	  this->charact.insert(std::make_pair(sprite, pix));
  }
  else
  	pix = it->second;
  this->printSprite(x * WIDTH, y * HEIGHT, pix);
}

extern "C"
{
arcade::IG_Lib *createLib(int width, int height)
{
	return (new arcade::Lapin(height, width));
}
}
