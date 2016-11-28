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

using namespace std;

/** @brief Main routine for dummy project
 *
 *  Does some stuff
 *
 *  @return 0
 */
int main() {
	cout << "do stuff" << endl;
	int x = 4;
	cout << x << endl;
	independentMethod(x);
	cout << x << endl;
	Project1 p;
	p.foo(x);
	cout << x << endl;
    return 0;
}
