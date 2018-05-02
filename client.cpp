#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "data.h"

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc < 3)
  {
    cout << "Missing argument. Usage: client ip port";
    return 1;
  }
  char *ip;
  memcpy( ip, argv[1], strlen(argv[1]) );
  int port = atoi(argv [2]);
  data msj;
  msj.id = -1;
  SocketDatagrama client (0);
  PaqueteDatagrama pk_send (&msj, sizeof (msj), ip, port);
  
  while (1)
  {
    cout << "->" << ip << ":" << port << endl;
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip, port);
    client.envia(pk_send);
    
    cout << "Waiting response..." << endl;
    
    client.recibe(pk_recv);
    msj = *pk_recv.obtieneDatos();
    msj.print();
    
    float nx = msj.x;
    float ny = msj.y;
    float dx = msj.x_dest;
    float dy = msj.y_dest;
    float sp = msj.speed;
    
    if (valid)
    {
      cout << "El numero es primo" << endl;
    }
    else
    {
      cout << "El numero NO es primo" << endl;
    }
    usleep(16666)
  }
}
