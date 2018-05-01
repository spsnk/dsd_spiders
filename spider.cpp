#include "spider.h"

Point::Point (void):
  x(0), y(0)
{

}

Point::Point (const float &x, const float &y):
  x(x), y(y)
{

}

float
Point::getX (void)
{
  return x;
}

float
Point::getY (void)
{
  return y;
}

Spider::Spider (const int &x, const int &y, const size_t &speed):
  position (Point (x, y)), speed (speed)
{
  // upper body
  vertex[ 0] = Point (-2, 6 );
  vertex[ 1] = Point (-1, 7 );
  vertex[ 2] = Point ( 1, 7 );
  vertex[ 3] = Point ( 2, 6 );
  vertex[ 4] = Point ( 2, 4 );
  vertex[ 5] = Point ( 1, 3 ); //right root
  vertex[ 6] = Point (-1, 3 ); //left root
  vertex[ 7] = Point (-2, 4 );
  //lower body
  vertex[ 8] = Point ( 2, 2 ); //from right root
  vertex[ 9] = Point ( 2,-2 );
  vertex[10] = Point ( 1,-3 );
  vertex[11] = Point (-1,-3 );
  vertex[12] = Point (-2,-2 );
  vertex[13] = Point (-2, 2 ); //to left root
  //upper left legs
  vertex[14] = Point (-4, 4 ); //from root
  vertex[15] = Point (-4,10 );
  vertex[16] = Point (-6, 4 ); //from root
  vertex[17] = Point (-6, 8 );
  //lower left
  vertex[18] = Point (-4, 2 ); //from root
  vertex[19] = Point (-4,-4 );
  vertex[20] = Point (-6, 2 ); //from root
  vertex[21] = Point (-6,-6 );
  //upper right  
  vertex[22] = Point ( 4, 4 );
  vertex[23] = Point ( 4,10 );
  vertex[24] = Point ( 6, 4 );
  vertex[25] = Point ( 6, 8 );
  //lower right
  vertex[26] = Point ( 4, 2 );
  vertex[27] = Point ( 4,-4 );
  vertex[28] = Point ( 6, 2 );
  vertex[29] = Point ( 6,-6 );
  
  direction = Point ( 0, 0 );
}

Point
Spider::getVertex (const size_t &index)
{
  if (index < 0 || index > 10)
  {
    return Point ();
  }
  int in;
  if( index > 29 )
  {
    in = 0;
  }
  else
  {
    in = index;
  }
  float
  xv = position.x + vertex[in].x ;
  float
  yv = position.y + vertex[in].y ;
  return Point (xv, yv);
}

float
Spider::getX (void)
{
  return position.getX ();
}

float
Spider::getY (void)
{
  return position.getY ();
}

void
Spider::set_direction ( const int& x, const int& y)
{
  direction = Point(x,y);
}

void
Spider::draw (void)
{
  //position.x += speed*direction.getX();
  //position.y += speed*direction.getY();
  for (int i = 0; i < 8; i++)
  {
    gfx_line (getVertex (i).x, getVertex (i).y, getVertex (i+1).x, getVertex (i+1).y);
  }
  for (int i = 8; i < 13; i++)
  {
    gfx_line (getVertex (i).x, getVertex (i).y, getVertex (i+1).x, getVertex (i+1).y);
  }
  gfx_line (getVertex (5).x, getVertex (5).y, getVertex (8).x, getVertex (8).y);
  gfx_line (getVertex (6).x, getVertex (6).y, getVertex (13).x, getVertex (13).y);
}