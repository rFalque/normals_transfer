/* Author: R. Falque
 * 
 * main for transfering normals
 * by R. Falque
 * 12/11/2019
 */

#include "IO/readOBJ.h"
#include "IO/readOFF.h"
#include "IO/readPLY.h"
#include "IO/writePLY.h"

#include <Eigen/Dense>
#include <vector>

#include "EigenTools/nanoflannWrapper.hpp"

int main(int argc, char* argv[])
{
    std::string source_path, target_path, output_path;

    // check input
    if (argc == 1) {
        std::cout << "Files defined as default setting and should be:\n";
        source_path = "../data/source.ply";
        target_path = "../data/target.ply";
        output_path = "../data/output.ply";
    } else if (argc == 4) {
        std::cout << "Files provided as command line argument and are defend as:\n";
        source_path = argv[1];
        target_path = argv[2];
        output_path = argv[3];
    } else {
        std::cout << "ERROR, wrong number of arguments: the program arguments should be source_path, target_path, output_path.\n";
        exit (EXIT_FAILURE);
    }

    std::cout << "Source file: " << source_path << "\n";
    std::cout << "Target file: " << target_path << "\n";
    std::cout << "Output file: " << output_path << "\n";

    Eigen::MatrixXd source_V, target_V; // V: vertex of the surface
    Eigen::MatrixXi source_UV, target_UV; // not used but required for IO
    Eigen::MatrixXd source_N, target_N; // N: normal of the surface
    Eigen::MatrixXi source_F, target_F; // F: faces of the surface (used for plots)

    igl::readPLY(source_path, source_V, source_F, source_N, source_UV);
    igl::readPLY(target_path, target_V, target_F, target_N, target_UV);

    std::cout << "\nBefore normals transfer:\n";
    std::cout << "size of V: " << source_V.rows() << std::endl;
    std::cout << "size of F: " << source_F.rows() << std::endl;
    std::cout << "size of N: " << source_N.rows() << std::endl;

    source_N = source_V; // lazy initialization
    nanoflann_wrapper knn_search(target_V);
    for (int i=0; i<source_V.rows(); i++) {
        std::vector < int > closest_vertex;
        closest_vertex = knn_search.return_k_closest_points(source_V.row(i), 1);
        source_N.row(i) = target_N.row(closest_vertex[0]);
        if (target_N.row(i)(0) == 0 && target_N.row(i)(2) == 0 && target_N.row(i)(2) == 0)
        {

            std::cout << "Warning, zero value normal found\n";
        }
        if (target_N.row(i).norm() == 0)
        {
            std::cout << "Warning, zero value normal found\n";
        }
        if (target_N.row(i).norm() != 1)
        {
            std::cout << "Warning, non unit normal found: normal length:" << target_N.row(i).norm() << "\n";
            source_N.row(i) = source_N.row(i) / source_N.row(i).norm();
        }

    }

    std::cout << "\nAfter normals transfer:\n";
    std::cout << "size of V: " << source_V.rows() << std::endl;
    std::cout << "size of F: " << source_F.rows() << std::endl;
    std::cout << "size of N: " << source_N.rows() << std::endl;
    
    std::cout << "\nNormals transfered\n";
    igl::writePLY(output_path, source_V, source_F, source_N, source_UV, false);
    std::cout << "File succesfully saved\n";

    return 0;
}

