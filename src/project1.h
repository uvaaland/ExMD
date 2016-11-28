/** @file       project1.h
 *  @brief Function prototypes for project1.
 *
 *  This contains the prototypes for the project1.cpp implementation file, all
 *  the information you will need for this dummy project.
 *
 *  @author Jon Doe (doe@gmail.com)
 *  @date   11/28/2016
 *  @bug    No known bugs.
 */

#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <iostream> // IO access

class Project1 {

    public:
        /** @brief Update variable i
         *
         *  @param i Some integer.
         *  @return Void.
         */
	    void foo(int &i);

};

/** @brief Update variable i
 *
 *  @param i Some integer.
 *  @return Void.
 */
void independentMethod(int &i);

#endif /* PROJECT1_H_ */
