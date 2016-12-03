#include <vector>
using namespace std;

class Particle {
  public:
    Particle();
    ~Particle();
    void insertRow(double* posx, double* posy, double* posz, double* velx, double* vely, double* velz);
    void insertMatrix();
    double getFirstRow();
    double getFirstMatrix();
    void insertRadius(double* radius);
    void insertNumberAtoms(int* numberAtoms);
    void setBoundary(double* lowx, double* lowy, double* lowz, double* upx, double* upy, double* upz);
  private:
    vector<double*> atomPosRow_;
    vector< vector<double*> > atomPosMatrix_;
    vector<double*> atomVelRow_;
    vector< vector<double*> > atomVelMatrix_;
    double *radius_;
    int *numberAtoms_;
    vector<double*> boundaryLow_;
    vector<double*> boundaryUp_; 
};
