/** @file main.cpp
 *  @brief Main routine for dummy project.
 *
 *  This file contains the main() function for the dummy project.
 *
 *  @author Jon Doe (doe@gmail.com)
 *  @date   11/28/2016
 *  @bug    No known bugs.
 */

#include <iostream>
#include "project1.h"

/** @brief Main routine for dummy project
 *
 *  Does some stuff
 *
 *  @return 0
 */
int main() {
  std::cout << "do stuff" << std::endl;
  int x = 4;
  std::cout << x << std::endl;
  independentMethod(&x);
  std::cout << x << std::endl;
  Project1 p;
  p.foo(&x);
  std::cout << x << std::endl;
  return 0;
}
