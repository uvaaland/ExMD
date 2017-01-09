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
 * Write simulation parameters such as #particles, #timesteps, space width
 * and height, to CSV file
 *
 * @params nsteps, nparticles
 * @return Void
 */
void WriteParametersCSV(const int nsteps, const int nparticles);


/** @brief Write particles to HDF5 file
 *
 * Write particles to HDF5 file with user specified period
 *
 * @params *particles, nparticles, nt
 * @return Void
 */
void WriteParticlesCSV(Particles *particles,
                        const int nparticles,
                        const int nt);

#endif  // SRC_WRITE_H_
