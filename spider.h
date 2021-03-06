#ifndef __SPIDER_H__
#define __SPIDER_H__

#include "gfx.h"
#include <cstddef>
#include <cmath>
#include <vector>

class Spider;

class Point
{
  friend class Spider;
private:
  float x;
  float y;
public:
  Point (void);
  Point (const float&, const float&);
  float getX (void);
  float getY (void);
};

class Spider
{
private:
  float speed;
  Point vertex[30];
  std::vector <Point> path;
  Point position;
  Point direction;
  Point getVertex (const size_t&);
public:
  Spider ( void ) { }
  Spider (const int&, const int&, const size_t&);
  void set_position (const int&, const int&);
  void set_direction ( const int&, const int&);
  float getX ( void );
  float getY ( void );
  float getSpeed ( void );
  void draw ();
};

const float pi = acos(-1);

#endif
