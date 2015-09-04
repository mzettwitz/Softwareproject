/*!
 * \brief Main entrypoint of the Raytracing system
 *  Choose between different scenes, further description
 *  found in their specific programs
 *
 * \note just add programs here
 */

#include "../include/sopro.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    int program = 3;
  std::cout << "Starting program " << program << std::endl;
  int res = 0;


  switch(program)
  {
  case 1 : res = program1(argc,argv);break;
  case 2 : res = program2(argc,argv);break;
  case 3 : res = program3(argc,argv);break;
  //case 4 : res = program4(argc,argv);break;
  default: res = 0 ;break;
  }

  return res;
}


