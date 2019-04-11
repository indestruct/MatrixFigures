//
// Author: mitkovulkov@gmail.com (Mitko Valkov)
// Created on 09.04.19.
//
// This file contains the driver code for testing of
// Grid and MatrixFigure implementation.
//

#include <iostream>
#include "MatrixFigure.h"

void compareResult(const uint32_t testNum, const uint32_t expected, const uint32_t result);

int main() {
    uint32_t testNumber = 1;
    {
        MatrixElement initElement;
        initElement.isVisited = false;
        initElement.isMarked = false;

        TDGrid<MatrixElement> matrix(5, 5, initElement);
        MatrixFigure matrixFigure;

        // First figure
        matrix[0][0].isMarked = true;

        matrix.PrintGrid();

        matrixFigure.LoadMatrix(std::move(matrix));

        auto count = matrixFigure.GetFiguresCount();

        std::cout << "The count of the figures is " << count << std::endl;
        compareResult(testNumber, 1, count);
        testNumber++;
    }
    {
        MatrixElement initElement;
        initElement.isVisited = false;
        initElement.isMarked = false;

        TDGrid<MatrixElement> matrix(5, 5, initElement);
        MatrixFigure matrixFigure;

        // First figure
        matrix[0][0].isMarked = true;
        // Second figure
        matrix[4][0].isMarked = true;
        // Third figure
        matrix[0][4].isMarked = true;
        // Forth figure
        matrix[4][4].isMarked = true;

        matrix.PrintGrid();

        matrixFigure.LoadMatrix(std::move(matrix));

        auto count = matrixFigure.GetFiguresCount();

        std::cout << "The count of the figures is " << count << std::endl;
        compareResult(testNumber, 4, count);
        testNumber++;
    }
    {
        MatrixElement initElement;
        initElement.isVisited = false;
        initElement.isMarked = false;

        TDGrid<MatrixElement> matrix(5, 5, initElement);
        MatrixFigure matrixFigure;

        // First figure
        matrix[0][0].isMarked = true;
        matrix[1][0].isMarked = true;
        matrix[2][0].isMarked = true;
        matrix[3][0].isMarked = true;
        matrix[4][0].isMarked = true;
        // Second figure
        matrix[0][4].isMarked = true;
        // Third figure
        matrix[4][4].isMarked = true;

        matrix.PrintGrid();

        matrixFigure.LoadMatrix(std::move(matrix));

        auto count = matrixFigure.GetFiguresCount();

        std::cout << "The count of the figures is " << count << std::endl;
        compareResult(testNumber, 3, count);
        testNumber++;
    }
    {
        MatrixElement initElement;
        initElement.isVisited = false;
        initElement.isMarked = false;

        TDGrid<MatrixElement> matrix(5, 5, initElement);
        MatrixFigure matrixFigure;

        // First figure
        matrix[0][0].isMarked = true;
        matrix[1][0].isMarked = true;
        // Second figure
        matrix[1][2].isMarked = true;
        matrix[1][3].isMarked = true;
        matrix[2][1].isMarked = true;
        matrix[2][3].isMarked = true;
        matrix[3][1].isMarked = true;
        matrix[3][2].isMarked = true;
        matrix[3][3].isMarked = true;
        // Third figure
        matrix[4][4].isMarked = true;

        matrix.PrintGrid();

        matrixFigure.LoadMatrix(std::move(matrix));

        auto count = matrixFigure.GetFiguresCount();

        std::cout << "The count of the figures is " << count << std::endl;
        compareResult(testNumber, 3, count);
        testNumber++;
    }

    return 0;
}

void compareResult(const uint32_t testNum, const uint32_t expected, const uint32_t result)
{
    if (expected == result)
    {
        std::cout << "Test " << testNum << " passed" << std::endl;
    }
    else
    {
        std::cout << "Test " << testNum << " failed" << std::endl;
    }
}