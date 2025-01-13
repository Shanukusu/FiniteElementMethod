#ifndef _GLOBAL_STIFFNESS_MATRIX_HPP_
#define _GLOBAL_STIFFNESS_MATRIX_HPP_

#include "StiffnessMatrix.hpp"

#include <vector>

class GlobalStiffnessMatrix: public StiffnessMatrix {
    public:
    Matrix getGlobalStiffnessMatrix(size_t num_vericies, std::vector<Triangle> &triangles)
    {
        Matrix resultMatrix(num_vericies);

        for(size_t i = 0; i < triangles.size(); i++) {
            Matrix localStiffnessMatrix = getStiffnessMatrix(triangles[i]);


            int elementPosition[3] = {triangles[i].a.index, triangles[i].b.index, triangles[i].c.index};
            for(size_t j = 0; j < 3; j++) {
                for(size_t k = 0; k < 3; k++) {
                    size_t rowIndex = elementPosition[j];
                    size_t colIndex = elementPosition[k];

                    // std::cout << "STATUS:" << rowIndex << " " << colIndex << " : " << j << " " << k << std::endl;

                    resultMatrix.setCell(rowIndex, colIndex, localStiffnessMatrix.getCell(j, k));
                }
            }
        }
        return resultMatrix;
    }

};
void printTriangle(Triangle triangle)
{
    std::cout << "Triangle" << std::endl;
    std::cout << "1: x:" << triangle.a.x << " - y:" << triangle.a.y << std::endl;
    std::cout << "2: x:" << triangle.b.x << " - y:" << triangle.b.y << std::endl;
    std::cout << "3: x:" << triangle.c.x << " - y:" << triangle.c.y << std::endl;
}

void example() {
    Point v1, v2, v3, v4, v5;

    v1 = {4, 0.5, 0.5};
    v2 = {1,   0,   1};
    v3 = {0,   0,   0};
    v4 = {2,   1,   1};
    v5 = {3,   1,   0};

    Triangle triangle_1(v5, v2, v1);
    Triangle triangle_2(v5, v3, v2);
    Triangle triangle_3(v5, v4, v3);
    Triangle triangle_4(v5, v1, v4);

    std::vector<Triangle> triangles;
    // printTriangle(triangle);

    triangles.push_back(triangle_1);
    triangles.push_back(triangle_2);
    triangles.push_back(triangle_3);
    triangles.push_back(triangle_4);


    GlobalStiffnessMatrix Test;
    Matrix result = Test.getGlobalStiffnessMatrix(5, triangles);

    // StiffnessMatrix Test;
    // Matrix result = Test.getStiffnessMatrix(triangle);

    result.printMatrix(1);
}

#endif /* _GLOBAL_STIFFNESS_MATRIX_HPP_ */