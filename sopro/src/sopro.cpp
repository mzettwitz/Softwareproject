/*!
 * \brief Mainentrypoint of the Raytracing system
 *  Choose between different Scenes, further description
 *  found in their specific programs
 *
 * \note just add programs here
 */

#include "sopro/include/sopro.h"

int main(int argc, char* argv[])
{
  size_t program = 1;
  int res = 0;


  switch(program)
  {
  case 1 : res = program1(argc,argv);break;
  case 2 : res = program2(argc,argv);break;
  default: break;
  }

  return res;
}


