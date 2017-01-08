#ifndef SRC_PARSE_H_
#define SRC_PARSE_H_
#include <string>  // for input

class Parse {
 public:
    explicit Parse(std::string filename);
    ~Particles();
    int nsteps;
    double dt;
    int output_period;
    double xlow, ylow, zlow, xhigh, yhigh, zhigh; 
    void fill(std::string filename);
};

#endif  // SRC_PARSE_H_
