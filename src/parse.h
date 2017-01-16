/** @file   write.h
 *  @brief  Header for the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

#ifndef SRC_PARSE_H_
#define SRC_PARSE_H_

/* -- Includes -- */

/* libc includes. */
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "json/json.h"
#include "boundary.h"

#define DIM 3

/* Parameters structure */
  struct Parameters {
    // Simulation parameters
    int nparticles;
    int nsteps;
    double dt;

    // Gravity parameters
    bool include_gravity;
    double G;

    // Drag parameters
    bool include_drag;
    double gamma;

    // Flocking parameters
    bool include_flocking;
    double beta;

    // Boundary
    Boundary boundary;
  };


/** @brief Read simulation parameters from params.json file
 *
 * Read simulation parameters such as # particles, # timesteps, boundary limits
 * and height, from 
 *
 * @params nsteps, nparticles, *boundary, filename
 * @return Void
 */
void ParseParams(Parameters *parameters);

/** @brief Read particle parameters to CSV file
 *
 * Read particle parameters: positions, velocities, masses and radii from CSV
 * file.
 *
 * @params filename *positions *velocities, *masses, radii
 * @return Void
 */
void ParseParticles(int nparticles,
                    const std::string filename,
                    double (*positions)[DIM],
                    double (*velocities)[DIM],
                    double *masses,
                    double *radii);

#endif  // SRC_PARSE_H_
