#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <cmath>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "data.h"

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc < 3)
  {
    cout << "Missing argument. Usage: client ip port" << endl;
    return 1;
  }
  char ip[16];
  memcpy( ip, argv[1], strlen(argv[1])+1 );
  int port = atoi(argv [2]);
  data msj;
  msj.id = -1;
  msj.valid = true;
  SocketDatagrama  client (0);
  PaqueteDatagrama pk_send (&msj, sizeof (msj), ip, port);
  float x_0 = -1;
  float y_0 = -1;
  cout << "Sending initialization packet to " << ip << ":" << port << endl;
  while ( msj.valid )
  {
    cout << "->" << endl;
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip, port);
    client.envia(pk_send);
    
    cout << "Waiting response..." << endl;
    PaqueteDatagrama pk_recv (sizeof (msj));
    client.recibe(pk_recv);
    msj = *pk_recv.obtieneDatos();
    cout << "<-" << endl;
    msj.print();
    
    if( x_0 < 0 || y_0 < 0 )
    {
      x_0 = msj.x;
      y_0 = msj.y;
    }
    
    float nx = msj.x;
    float ny = msj.y;
    float dx = msj.x_dest - nx;
    float dy = msj.y_dest - ny;
    float sp = msj.speed;
    float mag = sqrt( dx*dx + dy*dy );
    
    dx /= mag;
    dy /= mag;
    dx *= sp;
    dy *= sp;
    nx += dx;
    ny += dy;
    
    msj.x = nx;
    msj.y = ny;
    
    if ( 
        ( (msj.x <= ( (int) msj.x_dest + 5) ) &&
          (msj.x >= ( (int) msj.x_dest - 5) ) ) &&
        ( (msj.y <= ( (int) msj.y_dest + 5) ) &&
          (msj.y >= ( (int) msj.y_dest - 5) ) )
       )
    {
      msj.valid = false;
    }  
    usleep(16666);
  }
  
  cout << "Route completed\nDistance traveled: " << (msj.x - x_0)/(msj.y - y_0) << " pixels" << endl;
  
  return 0;
}
