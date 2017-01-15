/** @file   particles.h
 *  @brief  Header for the particles class.
 *
 * Particles are represented as spheres of varying radii and mass, each with
 * positions and velocities in 3-D space.
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_PARTICLES_H_
#define SRC_PARTICLES_H_

class Particles {
 public:
    /** @brief Constructor function
    *  @return void
    */
    Particles(int nparticles, double (*positions)[3], \
    double (*velocities)[3], double *masses, double *radii);
    /** @brief Destructor function
    *  @return void
    */
    ~Particles();
    /** @brief Number of particles
    */
    const int nparticles;
    /** @brief 2-D array of particle coordinates in 3 dimensions
    */
    double (*p)[3];
    /** @brief 2-D array of particle velocities in 3 dimensions
    */
    double (*v)[3];
    /** @brief Particle masses
    */
    double *mass;
    /** @brief Particle radii
    */
    double *radius;
};

#endif  // SRC_PARTICLES_H_
