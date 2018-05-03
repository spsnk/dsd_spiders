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
  gfx_open (side_size, side_size, "Baby Spiders' Tag");
  gfx_color (7, 242, 255);
  gfx_clear_color( 33, 33, 33 );
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
  int client_spider = 0;
  while (1) {
    cout << "Waiting for packet" << endl;
    int n = server.recibe (pk_recv);
    ip_cliente = pk_recv.obtieneDireccion ();
    int pto_cliente = pk_recv.obtienePuerto ();
    cout << "<-" << ip_cliente << ":" << pto_cliente << endl;
    msj_client = *pk_recv.obtieneDatos ();
    cout << "Received data:"<< endl;
    msj_client.print();
    if(msj_client.id == -1 && client_spider < 4)
    {
      msj.id = client_spider;
      msj.x = spiders[client_spider].getX();
      msj.y = spiders[client_spider].getY();
      
      msj.x_dest = spiders[client_spider<4?client_spider+1:0].getX();
      msj.y_dest = spiders[client_spider<4?client_spider+1:0].getY();
      
      msj.speed = spiders[client_spider].getSpeed();
      msj.valid = true;
      client_spider++;
    }
    else if ( msj_client.valid = true )
    {
      int temp_id = msj_client.id;
      
      spiders[temp_id].set_position(msj_client.x, msj_client.y);
      spiders[temp_id].set_direction(msj_client.x_dest, msj_client.y_dest);
      
      msj = msj_client;
      msj.x_dest = spiders[temp_id<3?temp_id+1:0].getX();
      msj.y_dest = spiders[temp_id<3?temp_id+1:0].getY();
    }
    cout << "Crafted data:" << endl;
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_cliente, pto_cliente);
    cout << "->" << ip_cliente << ":" << pto_cliente << endl;
    int m = server.envia (pk_send);
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
    sp_temp = sp_temp<1?1:(sp_temp>10?10:sp_temp);
    s = Spider (side_size/2,side_size/2,sp_temp);
  }
  
  spiders[0].set_position(15,15);
  spiders[1].set_position(side_size - 15,15);
  spiders[2].set_position(side_size - 15,side_size - 15);
  spiders[3].set_position(15,side_size - 15);
  
  thread drawing ( draw_thread, side_size );
  thread receiving ( network_thread, port );
  
  drawing.join();
  receiving.join();
  
  return 0;
}

