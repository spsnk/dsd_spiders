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
draw_thread ( void )
{
  while (1)
  {
    gfx_clear ();
    for(Spider &s : spiders)
    {
      s.draw();
    }
    gfx_flush ();
    usleep (16666);
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
  
  data msj, msj_client;
  char *ip_cliente;
  bool valid = true;
  
  SocketDatagrama server (port);
  PaqueteDatagrama pk_recv (sizeof (msj));
  for(int i = 0; i < 4; i++)
  {
    int sp_temp;
    cout << "Spider " << i << "'s speed: " << endl;
    cin << sp_temp;
    spiders [i] = Spider (0,0,sp_temp);
  }
    
  gfx_open (side_size, side_size, "Spiders");
  gfx_color (7, 242, 255);
  
  thread( draw_thread );
  
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
  return 0;
}

