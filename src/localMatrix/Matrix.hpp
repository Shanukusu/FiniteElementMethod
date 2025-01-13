#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iomanip>
#include <iostream>
#include <vector>


#define SPACE_FOR_NUMBERS 5
#define CONVERT_PRINT_TO_FILE 0


class Matrix {
    // Data in matrix
    std::vector<std::vector<double>> data;
    // Sizes of matrix
    size_t rows;
    size_t cols;

    public:
    
    Matrix(size_t size) : rows(size), cols(size)              { data.resize(size, std::vector<double>(size, 0)); }
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) { data.resize(cols, std::vector<double>(rows, 0)); }
    Matrix(size_t rows, size_t cols, std::vector<std::vector<double>> *new_data) : rows(rows), cols(cols) {
        data = *new_data;   
    }

    size_t getRows() { return rows; }
    size_t getCols() { return cols; }

    size_t getDim() {
        if(isSquareMatrix()) {
            return rows;
        } else {
            return 0;
        }
    }

    bool isCellRestricted(size_t row, size_t col) {
        return (data[row][col] == std::numeric_limits<double>::max());
    }

    int8_t setCell(size_t row, size_t col, double val) {
        if(row < rows && col < cols) {
            if(!isCellRestricted(row, col)) {
                data[row][col] = val;
                return 0;
            } else {
                // std::cout << "Restricted cell!" << std::endl;
                return -2;
            }

        } else {
            std::cout << "No such cell! (" << row << "," << col << ")" << std::endl;
            return -1;
        }
    }

    double getCell(size_t row, size_t col)
    {
        if(row < rows && col < cols) {
            return data[row][col];
        } else {
            std::cout << "No such cell! (" << row << "," << col << ")" << std::endl;
            return 0;
        }
    }

    bool isSquareMatrix() { return (cols == rows); }

    void printMatrixFile(size_t visibleX = 0) {
        std::cout<< "┌"; // "┌";
        // Upper edge
        for(size_t index = 0; index < cols; index++) {
            for(size_t jndex = 0; jndex < SPACE_FOR_NUMBERS; jndex++) {
                std::cout << "―"; // "―";
            }
            if(index == cols - 1) {
                std::cout << "┐" << std::endl; // "┐"
            } else {
                std::cout << "┬"; // "┬";
            }
        }
        for(size_t index = 0; index < rows; index++) {
            for(size_t jndex = 0; jndex < cols; jndex++) {
                std::cout << "│" << std::setw(SPACE_FOR_NUMBERS);
                if(!isCellRestricted(index, jndex) || visibleX) {
                    std::cout << data[index][jndex]; //  "│"
                } else {
                    std::cout << "x";
                }
            }
            // start cut the cells
            if(index == rows - 1) {
                std::cout << "│" << std::endl << "└"; 
            } else {
                std::cout << "│" << std::endl << "├"; //"├";
            }
            /* Line between two rows */
            for(size_t jndex = 0; jndex < cols; jndex++) {
                for(size_t kndex = 0; kndex < SPACE_FOR_NUMBERS; kndex++) {
                    std::cout << "―"; // "―";
                }
                // Is the end of matrix?
                if(index == rows - 1) {
                    if(jndex == cols - 1) {
                        std::cout << "┘";
                    } else {
                        std::cout << "┴"; // "┴";
                    }
                } else {
                    if(jndex == cols - 1) {
                        std::cout << "┤";
                    } else {
                        std::cout << "┼"; // "┼";
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    void printMatrixConsole(size_t visibleX = 0) {
        std::cout<< char(0xDA); // "┌";
        // Upper edge
        for(size_t index = 0; index < cols; index++) {
            for(size_t jndex = 0; jndex < SPACE_FOR_NUMBERS; jndex++) {
                std::cout << char(0xC4); // "―";
            }
            if(index == cols - 1) {
                std::cout << char(0xBF) << std::endl; // "┐"
            } else {
                std::cout << char(0xC2); // "┬";
            }
        }
        for(size_t index = 0; index < rows; index++) {
            for(size_t jndex = 0; jndex < cols; jndex++) {
                std::cout << char(0xB3) << std::setw(SPACE_FOR_NUMBERS);
                if(!isCellRestricted(index, jndex) || visibleX) {
                    std::cout << data[index][jndex]; //  "│"
                } else {
                    std::cout << "x";
                }
            }
            // start cut the cells
            if(index == rows - 1) {
                std::cout << char(0xB3) << std::endl << char(0xC0); 
            } else {
                std::cout << char(0xB3) << std::endl << char(0xC3); //"├";
            }
            /* Line between two rows */
            for(size_t jndex = 0; jndex < cols; jndex++) {
                for(size_t kndex = 0; kndex < SPACE_FOR_NUMBERS; kndex++) {
                    std::cout << char(0xC4); // "―";
                }
                // Is the end of matrix?
                if(index == rows - 1) {
                    if(jndex == cols - 1) {
                        std::cout << char(0xD9);
                    } else {
                        std::cout << char(0xC1); // "┴";
                    }
                } else {
                    if(jndex == cols - 1) {
                        std::cout << char(0xB4);
                    } else {
                        std::cout << char(0xC5); // "┼";
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    void printMatrix(size_t visibleX = 0) {
        if(CONVERT_PRINT_TO_FILE) {
            printMatrixFile(visibleX);
        } else {
            printMatrixConsole(visibleX);
        }
    }

    double getMinInRow(size_t row)
    {
        if(row < rows) {
            double min_row = data[row][0];
            for(size_t index = 1; index < cols; index++) {
                double cur_data = data[row][index];
                min_row = (min_row < 0) || ((min_row > cur_data) && (cur_data >= 0))? cur_data: min_row;
            }
            return min_row;
        } else {
            std::cout << "No such row!" << std::endl;
            return 0;
        }
    }

    double getMinInCol(size_t col)
    {
        if(col < cols) {
            double min_col = data[0][col];
            for(size_t index = 1; index < rows; index++) {
                double cur_data = data[index][col];
                min_col = (min_col < 0) || ((min_col > cur_data) && (cur_data >= 0))? cur_data: min_col;
            }
            return min_col;
        } else {
            std::cout << "No such col!" << std::endl;
            return 0;
        }
    }   

};

#endif //  _MATRIX_HPP_
