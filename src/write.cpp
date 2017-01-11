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
                        const std::string filename) {
    std::string filepath = "../output/csv/" + filename + "_params.csv";

    double width = 10.0;
    double length = 10.0;
    double height = 10.0;

    std::ofstream outfile;
    outfile.open(filepath);
    outfile << "nsteps,nparticles,width,length,height\n";
    outfile << nsteps << "," << nparticles << ",";
    outfile << width << "," << length << "," << height;
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
}
