/** @file   write.cpp
 *  @brief  Implementation of the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "parse.h"

static Btype ConvertStringToEnum(const std::string& str) {
  if (str == "none") {
    return none;
  } else if (str == "reflecting") {
    return reflecting;
  } else {
    std::cout << "Invalid boundary condition name!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void ParseParams(Parameters *params) {
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream in("../../input/params.json");
    bool parsingSuccessful = reader.parse(in, root);
    if ( !parsingSuccessful ) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration: ";
        std::cout << reader.getFormattedErrorMessages();
        exit(EXIT_FAILURE);
    }

    // Set simulation parameters
    params->nparticles = root["simulation"]["nparticles"].asInt();
    params->nsteps = root["simulation"]["nsteps"].asInt();
    params->dt = root["simulation"]["dt"].asDouble();

    // Set gravity parameters
    params->include_gravity = root["forces"]["gravity"]["include"].asBool();
    params->G = root["forces"]["gravity"]["G"].asDouble();

    // Set drag parameters
    params->include_drag = root["forces"]["drag"]["include"].asBool();
    params->gamma = root["forces"]["drag"]["gamma"].asDouble();

    // Set flocking parameters
    params->include_flocking = root["forces"]["flocking"]["include"].asBool();
    params->beta = root["forces"]["flocking"]["beta"].asDouble();

    // Set boundary parameters
    Btype type = ConvertStringToEnum(root["boundary"]["type"].asString());
    params->boundary.type = type;
    params->boundary.limits[0][0] = root["boundary"]["x_lim"][0].asDouble();
    params->boundary.limits[0][1] = root["boundary"]["x_lim"][1].asDouble();
    params->boundary.limits[1][0] = root["boundary"]["y_lim"][0].asDouble();
    params->boundary.limits[1][1] = root["boundary"]["y_lim"][1].asDouble();
    params->boundary.limits[2][0] = root["boundary"]["z_lim"][0].asDouble();
    params->boundary.limits[2][1] = root["boundary"]["z_lim"][1].asDouble();
}

void ParseParticles(int nparticles,
                    const std::string filename,
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

    if (rows != nparticles) {
        std::cout << "nparticles does not match number of particles in ";
        std::cout << filename.substr(12, 9) << " : " << nparticles << " != ";
        std::cout << rows << std::endl;
        exit(EXIT_FAILURE);
    }

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
