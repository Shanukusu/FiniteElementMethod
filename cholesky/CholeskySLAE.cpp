#include "CholeskySLAE.h"

#include <string>
#include <stdexcept>
#include <iostream>

Cholesky::CholeskySLAE::CholeskySLAE(int L, int rows)
{
    if (L <= 0 || rows < L || rows <= 0) {
        // TODO: make a better error
        throw std::runtime_error("Malformed parameters were passed to the constructor");
    }

    this->rows = rows;  // size
    this->L = L;        // halfband length
    this->strips.resize(2 * (long long)L - 1);
    this->rightSide.resize(rows);
    for (int i = 0; i <  2 * L - 1; i++) {
        // for the ease of use we sacrifice some memory to add those 0filled triangles
        // we did this in the 3rd year, so I don't care
        // There might be a better way, but FU
        this->strips.at(i).resize(rows);  
    }
}


void Cholesky::CholeskySLAE::setElem(int row, int column, double value)
{
    std::pair<int, int> pos = this->convertIndecesToInner(row, column);
    this->strips.at(pos.first).at(pos.second) = value;
}


void Cholesky::CholeskySLAE::setRightSide(int elem, double value)
{
    if (elem < 0 || elem >= this->rows) {
        throw std::runtime_error("Vector of length " + std::to_string(this->rows) + " out of bounds access at elem=" + std::to_string(elem));
    }

    this->rightSide.at(elem) = value;
}


bool Cholesky::CholeskySLAE::isMatrixAccessInBounds(int row, int column)
{
    return row >= 0
        && column >= 0
        && row - column >= 1 - this->L  // is below the upper edge of the band
        && row - column < this->L       // is above the lower edge of the band 
        && column < this->rows
        && row < this->rows;
}


// make a private helper method, that does that
std::pair<int, int> Cholesky::CholeskySLAE::convertIndecesToInner(int row, int column)
{
    if (!this->isMatrixAccessInBounds(row, column)) {
        throw std::runtime_error("Matrix out of bounds access at row=" + std::to_string(row) + " and column=" + std::to_string(column));
    }
    int strip = L + column - row - 1;
    int strip_index = row;


    return std::pair<int, int>(strip, strip_index);
}


std::pair<int, int> Cholesky::CholeskySLAE::convertInnerToIndeces(int strip, int strip_index)
{
    int row = strip_index;
    int column = strip_index - L + strip + 1;

    return std::pair<int, int>(row, column);
}


double Cholesky::CholeskySLAE::getElem(int row, int column, double default_value, bool throwing)
{
    if (this->isMatrixAccessInBounds(row, column)) {
        std::pair<int, int> pos = this->convertIndecesToInner(row, column);
        return this->strips.at(pos.first).at(pos.second);
    }
    else if (!throwing) {
        return default_value;
    }
    else {
        throw std::out_of_range("LOL you ded");
    }
}


void Cholesky::CholeskySLAE::print()
{
    std::cout << "Matrix contents: \n";
    for (int row = 0; row < this->rows; row++) {
        for (int column = 0; column < this->rows; column++) {
            if (this->isMatrixAccessInBounds(row, column)) {
                std::pair<int, int> pos = this->convertIndecesToInner(row, column);
                std::cout << this->strips.at(pos.first).at(pos.second) << "\t";
            }
            else {
                std::cout << "x" << "\t";
            }
        }
        std::cout << "\n";
    }

    //std::cout << "Debug strips: \n";

    //for (int strip = 0; strip < 2 * L - 1; strip++) {
    //    for (int i = 0; i < rows; i++) {
    //        std::cout << strips.at(strip).at(i) << "\t";
    //    }
    //    std::cout << "\n";
    //}
}

Cholesky::CholeskySLAE Cholesky::CholeskySLAE::getLowerMatrix() {
    CholeskySLAE lowerMatrix = CholeskySLAE(L, rows);

    // calculate first column
    lowerMatrix.setElem(0, 0, sqrt(getElem(0, 0, 0, true)));
    for (size_t j = 1; j < this->L; j++) {
        lowerMatrix.setElem(j, 0,
            getElem(j, 0, 0, true) / lowerMatrix.getElem(0, 0)
        );
    }

    // calculate the other part
    for (size_t i = 1; i < this->rows; i++) {
        //calculate diagonal first, squared everything without the diagonal element
        double previousColumnSum = 0.0;
        for (size_t j = 0; j < i; j++) { //FIXME: Im unoptimized as flick boys!!!
            double elem = lowerMatrix.getElem(i, j, 0);
            previousColumnSum += elem * elem;
        }
        lowerMatrix.setElem(i, i,
            sqrt(getElem(i, i, 0, true) - previousColumnSum)
        );

        // calculate nondiagonal elements in the same column
        for (size_t j = i + 1; j < this->L; j++) {
            double convolvedValues = 0.0;
            for (size_t p = 0; p < i; p++) {
                convolvedValues += lowerMatrix.getElem(i, p, 0, true) * lowerMatrix.getElem(j, p, 0, true);
            }
            lowerMatrix.setElem(j, i,
                (getElem(j, i, 0, true) - convolvedValues) / lowerMatrix.getElem(i, i, 0, true)
            );
        }
    }

    return lowerMatrix;
}



std::vector<double> Cholesky::CholeskySLAE::solve(bool verbose)
{

    CholeskySLAE lowerMatrix = getLowerMatrix();
    if (verbose) {
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Lower matrix:\n";
        std::cout << "-----------------------------------------------------\n";
        lowerMatrix.print();
        std::cout << "-----------------------------------------------------\n";
    }

    std::vector<double> solution = std::vector<double>(this->rightSide);
    if (verbose) {
        std::cout << "Right side:\n";
        for (size_t i = 0; i < solution.size(); i++) {
            std::cout << solution.at(i) << ", ";
        }
        std::cout << "\n";
    }
    // solving the resulting system
    for (size_t i = 0; i < this->rows; i++) {
        solution.at(i) /= lowerMatrix.getElem(i, i, 0, true);

        for (size_t j = i + 1; j < this->rows; j++) {
            solution.at(j) -= solution.at(i) * lowerMatrix.getElem(j, i);
        }
    }
    
    if (verbose) {
        std::cout << "First vector:\n";
        for (size_t i = 0; i < solution.size(); i++) {
            std::cout << solution.at(i) << ", ";
        }
        std::cout << "\n";
    }

    for (size_t i = this->rows-1; i < this->rows; i--) {
        solution.at(i) /= lowerMatrix.getElem(i, i, 0, true);

        for (size_t j = i - 1; j < this->rows; j--) {
            solution.at(j) -= solution.at(i) * lowerMatrix.getElem(i, j);
        }
    }

    if (verbose) {
        std::cout << "Solution:\n";
        for (size_t i = 0; i < solution.size(); i++) {
            std::cout << solution.at(i) << ", ";
        }
        std::cout << "\n";
    }

    return solution;
}
