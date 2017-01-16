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

#define DIM 3

/** @brief Read simulation parameters from params.json file
 *
 * Read simulation parameters such as # particles, # timesteps, boundary limits
 * and height, from 
 *
 * @params nsteps, nparticles, *boundary, filename
 * @return Void
 */
void ParseParams(int *nparticles,
                 int *nsteps,
                 double *dt,
                 bool *include_gravity,
                 double *G);

/** @brief Read particle parameters to CSV file
 *
 * Read particle parameters: positions, velocities, masses and radii from CSV
 * file.
 *
 * @params filename *positions *velocities, *masses, radii
 * @return Void
 */
void ParseParticles(const std::string filename,
                    double (*positions)[DIM],
                    double (*velocities)[DIM],
                    double *masses,
                    double *radii);

#endif  // SRC_PARSE_H_
