/** @file   boundary.h
 *  @brief  Header for boundary structure
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

#ifndef SRC_BOUNDARY_H_
#define SRC_BOUNDARY_H_

/* -- Includes -- */

#define DIM 3

/** 
 *  @brief Enum for the possible boundary types
 */
enum Btype { none, reflecting, periodic };

/**
 *  @brief Boundary structure
 *
 *  Structure used to store boundary condition and boundary dimensions
 */
typedef struct {
    Btype type;
    double limits[DIM][2];
} Boundary;

#endif  // SRC_BOUNDARY_H_
