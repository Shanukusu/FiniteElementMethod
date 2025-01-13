#ifndef _STIFFNESS_MATRIX_HPP_
#define _STIFFNESS_MATRIX_HPP_

#include <cmath>

#include "Matrix.hpp"
#include "Structures.hpp"

class StiffnessMatrix {
    public:
    
    Matrix getStiffnessMatrix(Triangle triangle)
    {
        Matrix result(3);

        Sijk x, y, b, c;
        // a -> i : b -> j : c -> k //

        // y-es
        y.i = triangle.a.y; 
        y.j = triangle.b.y; 
        y.k = triangle.c.y;
        
        // x-es
        x.i = triangle.a.x; 
        x.j = triangle.b.x; 
        x.k = triangle.c.x;

        // Support params 

        // b-es
        b.i = y.j - y.k;
        b.j = y.k - y.i;
        b.k = y.i - y.j;
        
        // std::cout << "b: " << b.i << " " << b.j << " " << b.k << std::endl;

        // c-es
        c.i = -x.j + x.k;
        c.j = -x.k + x.i;
        c.k = -x.i + x.j;

        
        // std::cout << "c: " << c.i << " " << c.j << " " << c.k << std::endl;

        double bArr[3] = {b.i, b.j, b.k};
        double cArr[3] = {c.i, c.j, c.k};

        // std::cout << "I: " << triangle.a.index << " J:" << triangle.b.index << " K:" << triangle.c.index << std::endl;  

        // calculate square
        double aEdge = sqrt(std::pow(x.i - x.j, 2) + std::pow(y.i - y.j, 2));
        double bEdge = sqrt(std::pow(x.j - x.k, 2) + std::pow(y.j - y.k, 2));
        double cEdge = sqrt(std::pow(x.k - x.i, 2) + std::pow(y.k - y.i, 2));

        double halfP = (aEdge + bEdge + cEdge) * 1.0f / 2.0f;

        double square = sqrt(halfP * (halfP - aEdge) * (halfP - bEdge) * (halfP - cEdge));

        // std::cout << aEdge << " " << bEdge << " " << cEdge << " --- " << halfP << " : " << square << std::endl;
        // calculate Matrix
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                double cellValue = (bArr[j] * bArr[i] + cArr[j] * cArr[i]) * 1.0f / (4.0f * square);
                // std::cout << i << ":" << j << " --- " << cellValue << std::endl;
                result.setCell(i, j, cellValue);
            }
        }

        return result;
    }
};


#endif /* _STIFFNESS_MATRIX_HPP_ */