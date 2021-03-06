/** @file   write.h
 *  @brief  Header for the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

#ifndef SRC_WRITE_H_
#define SRC_WRITE_H_

/* -- Includes -- */

/* libc includes. */
#include "particles.h"
#include "boundary.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>


/**
 *  @brief Coordinate structure
 *
 *  Structure used for storing coordinates to be written to CSV file.
 **/
typedef struct {
    double x, y, z;
} Coordinates;



/* Functions */



/** @brief Write simulation parameters to CSV file
 *
 * Write simulation parameters such as # particles, # timesteps, boundary limits
 * and height, to CSV file
 *
 * @params nsteps, nparticles, *boundary, filename
 * @return Void
 */
void WriteParametersCSV(const int nsteps,
                        const int nparticles,
                        const Boundary *boundary,
                        const std::string filename);


/** @brief Write particles to CSV file
 *
 * Write particle parameters to CSV file
 *
 * @params *particles, nparticles, nt, filename
 * @return Void
 */
void WriteParticlesCSV(Particles *particles,
                        const int nparticles,
                        const int nt,
                        const std::string filename);

#endif  // SRC_WRITE_H_
