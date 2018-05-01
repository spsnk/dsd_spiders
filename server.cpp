#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "data.h"
#include "spider.h"

using namespace std;

Spider spiders [4];

int
draw_thread ( int side_size )
{  
  gfx_open (side_size, side_size, "Spiders");
  gfx_color (7, 242, 255);
  int frame = 1;
  while (1)
  {
    cout << "Frame: " << frame++ << '\r' << flush;
    gfx_clear ();
    for(auto &s : spiders)
    {
      s.draw();
    }
    gfx_flush ();
    usleep (16666);
  }
}

int
network_thread ( int port )
{
  data msj, msj_client;
  char *ip_cliente;
  SocketDatagrama server (port);
  PaqueteDatagrama pk_recv (sizeof (msj));
  while (1) {
    cout << "Waiting for packet" << endl;
    int n = server.recibe (pk_recv);
    ip_cliente = pk_recv.obtieneDireccion ();
    int pto_cliente = pk_recv.obtienePuerto ();
    cout << "Packet received from " << ip_cliente << ":" << pto_cliente << endl;
    msj_client = *pk_recv.obtieneDatos ();
    cout << "Received:"<< endl;
    msj_client.print();
    
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_cliente, 3939);
    cout << "Enviando mensaje..." << endl;
    SocketDatagrama client (3939);
    int m = client.envia (pk_send);
    cout << "Mensaje enviado." << endl; 
  }
}

int
main (int argc, char* argv[])
{
  if(argc < 2)
  {
    cout << "Argument missing. Usage: server side_size" << endl;
    return 1;
  }
  
  int port = 3939;
  int side_size =  atoi(argv[1]);
  
  int i = 1;
  for(auto &s : spiders)
  {
    float sp_temp;
    cout << "Spider " << i++ << " speed: " << endl;
    cin >> sp_temp;
    s = Spider (side_size/2,side_size/2,sp_temp);
  }
  
  spiders[0].set_position(10,10);
  spiders[1].set_position(side_size - 10,10);
  spiders[2].set_position(side_size - 10,side_size - 10);
  spiders[3].set_position(10,side_size - 10);
  
  thread drawing ( draw_thread, side_size );
  thread receiving ( network_thread, port );
  
  drawing.join();
  receiving.join();
  
  return 0;
}

