/*!
 * \brief Main entrypoint of the Raytracing system
 *  Choose between different scenes, further description
 *  found in their specific programs
 *
 * \note just add programs here
 */

#include "../include/sopro.h"

int main(int argc, char* argv[])
{
  size_t program = 2;
  int res = 0;


  switch(program)
  {
  case 1 : res = program1(argc,argv);break;
  case 2 : res = program2(argc,argv);break;
  default: break;
  }

  return res;
}


