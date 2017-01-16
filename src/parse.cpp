/** @file   write.cpp
 *  @brief  Implementation of the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "parse.h"
void ParseParams(int *nparticles,
                 int *nsteps,
                 double *dt,
                 bool *include_gravity,
                 double *G) {
    Json::Value params;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream in("../../input/params.json");
    bool parsingSuccessful = reader.parse(in, params);
    if ( !parsingSuccessful ) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration: ";
        std::cout << reader.getFormattedErrorMessages();
        exit(EXIT_FAILURE);
    }
    std::cout << params << std::endl;

    *nparticles = params["simulation"]["nparticles"].asInt();
    *nsteps = params["simulation"]["nsteps"].asInt();
    *dt = params["simulation"]["dt"].asDouble();

    *include_gravity = params["forces"]["gravity"]["include"].asBool();
}

void ParseParticles(const std::string filename,
                    double (*positions)[DIM],
                    double (*velocities)[DIM],
                    double *masses,
                    double *radii) {
    std::ifstream in(filename);
    if (in.fail()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line, field;
    std::vector< std::vector<std::string> > array;  // the 2D array
    std::vector<std::string> v;           // array of values for one line only

    while ( getline(in, line) ) {   // get next line in file
        v.clear();
        std::stringstream ss(line);

        while (getline(ss, field, ',')) {
            v.push_back(field);
        }

        array.push_back(v);  // add the 1D array to the 2D array
    }

    // Assign values to particles
    const int rows = array.size() - 1;

    for (int i = 0; i < rows; i++) {
        positions[i][0] = ::atof(array[i+1][0].c_str());
        positions[i][1] = ::atof(array[i+1][1].c_str());
        positions[i][2] = ::atof(array[i+1][2].c_str());

        velocities[i][0] = ::atof(array[i+1][3].c_str());
        velocities[i][1] = ::atof(array[i+1][4].c_str());
        velocities[i][2] = ::atof(array[i+1][5].c_str());

        masses[i] = ::atof(array[i+1][6].c_str());
        radii[i] = ::atof(array[i+1][7].c_str());
    }
}
