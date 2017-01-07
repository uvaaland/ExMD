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
#include <string>        /* for filename in WriteOutput */
#include <H5Cpp.h>       /* for writing to HDF5 file */

/* HDF5 Parameters */
// Parameters
const char ParameterDatasetName[] = "Parameters";
const char member_nparticles[] = "NPARTICLES";
const char member_nsteps[] = "NSTEPS";
const char member_height[] = "HEIGHT";
const char member_width[] = "WIDTH";

// Particles
const char ParticleDatasetName[] = "Coordinates";
const char member_x[] = "X";
const char member_y[] = "Y";
const char member_z[] = "Z";

/**
 *  @brief Parameter structure
 *
 *  Structure used for storing parameters to be written to HDF5 file.
 **/
typedef struct {
    int nparticles, nsteps, height, width;
} Parameters;


/**
 *  @brief Coordinate structure
 *
 *  Structure used for storing coordinates to be written to HDF5 file.
 **/
typedef struct {
    double x, y, z;
} Coordinates;



/* Functions */



/** @brief Write simulation parameters to HDF5 file
 *
 * Write simulation parameters such as #particles, #timesteps, space width
 * and height, to HDF5 file
 *
 * @params filename
 * @return Void
 */
void WriteParametersHDF5(const int nsteps, const int nparticles);


/** @brief Write particles to HDF5 file
 *
 * Write particles to HDF5 file with user specified period
 *
 * @params filename
 * @return Void
 */
void WriteParticlesHDF5(Particles *particles,
                        const int nparticles,
                        const int nt);


#endif  // SRC_WRITE_H_
