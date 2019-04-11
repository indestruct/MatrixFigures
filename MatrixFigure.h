//
// Author: mitkovulkov@gmail.com (Mitko Valkov)
// Created on 09.04.19.
//
// This file contains the implementation of the MatrixFigure class.
// The LoadMatrix operation is with complexity O(n*m), where n is the
// height of the matrix, and m is the width of the matrix.
// The GetFiguresCount operation is with complexity O(1).
//

#ifndef MATRIXFIGURE_H
#define MATRIXFIGURE_H

#include <cstdint>
#include <queue>

#include "Grid.h"

// Class that represents single element in the matrix.
class MatrixElement
{
public:
    // Provides information if the element have been visited
    // when the algorithm is ran for finding all figures in the matrix
    bool isVisited;
    // Provides information if the element is part of a figure
    bool isMarked;

    MatrixElement& operator=(const MatrixElement& other)
    {
        if (this != &other)
        {
            isVisited = other.isVisited;
            isMarked = other.isMarked;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const MatrixElement& el)
    {
        os << "[" << el.isMarked << "]";
    }
};

class MatrixFigure
{
public:
    MatrixFigure();

    virtual ~MatrixFigure();

    // Loads matrix in the MatrixFigure class and scans for
    // all figures within it. Operation complexity is O(n*m)
    void LoadMatrix(const TDGrid<MatrixElement>& matrix);

    // Loads matrix in the MatrixFigure class and scans for
    // all figures within it. Operation complexity is O(n*m)
    void LoadMatrix(TDGrid<MatrixElement>&& matrix);

    // Gets the count of figures in the previously loaded matrix
    // Operation complexity is O(1)
    uint32_t GetFiguresCount();

private:
    TDGrid<MatrixElement> m_matrix; // Contains the matrix with all elements

    uint32_t m_totalFiguresCount; // Stores the total figures count in the matrix

    std::queue<GridPoint> m_elementsToVisit; // Temporally stores elements that needs to be visited.

    // Calculates the count of figures in the matrix
    void CalculateFiguresCount();

    // Inspects all neighbor elements for the element in front of the ElementsToVisit queue.
    void InspectNeighborElements();
};

#endif //MATRIXFIGURE_H
