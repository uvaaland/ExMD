/** @file   write.cpp
 *  @brief  Implementation of the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "write.h"


void WriteParametersCSV(const int nsteps,
                        const int nparticles,
                        const Boundary *boundary,
                        const std::string filename) {
    std::string filepath = "../output/csv/" + filename + "_params.csv";

    double box_ox = (boundary->limits[0][0] + boundary->limits[0][1])/2.0;
    double box_oy = (boundary->limits[1][0] + boundary->limits[1][1])/2.0;
    double box_oz = (boundary->limits[2][0] + boundary->limits[2][1])/2.0;
    double box_lx = boundary->limits[0][1] - boundary->limits[0][0];
    double box_ly = boundary->limits[1][1] - boundary->limits[1][0];
    double box_lz = boundary->limits[2][1] - boundary->limits[2][0];

    std::ofstream outfile;
    outfile.open(filepath);
    outfile << "nsteps,nparticles,box_ox,box_oy,box_oz,box_lx,box_ly,box_lz\n";
    outfile << nsteps << "," << nparticles << ",";
    outfile << box_ox << "," << box_oy << "," << box_oz << ",";
    outfile << box_lx << "," << box_ly << "," << box_lz;
    outfile.close();
}


void WriteParticlesCSV(Particles *particles,
                        const int nparticles,
                        const int nt,
                        const std::string filename) {
    std::string filepath = "../output/csv/" + filename
                         + ".csv." + std::to_string(nt);

    Coordinates *coord_list;
    coord_list = new Coordinates[nparticles];
    for (int i = 0; i < nparticles; ++i) {
        coord_list[i].x = particles->p[i][0];
        coord_list[i].y = particles->p[i][1];
        coord_list[i].z = particles->p[i][2];
    }

    std::ofstream outfile;
    outfile.open(filepath);
    outfile << "x,y,z,v,radius\n";
    for (int i = 0; i < nparticles; i++) {
        outfile << particles->p[i][0] << ",";
        outfile << particles->p[i][1] << ",";
        outfile << particles->p[i][2] << ",";
        outfile << std::sqrt(particles->v[i][0]*particles->v[i][0] +
                             particles->v[i][1]*particles->v[i][1] +
                             particles->v[i][2]*particles->v[i][2]) << ",";
        outfile << particles->radius[i] << "\n";
    }
    outfile.close();
    delete[] coord_list;
}
