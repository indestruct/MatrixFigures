//
// Author: mitkovulkov@gmail.com (Mitko Valkov)
// Created on 09.04.19.
//
// This file contains the implementation of the MatrixFigure class.
// The LoadMatrix operation is with complexity O(n*m), where n is the
// height of the matrix, and m is the width of the matrix.
// The GetFiguresCount operation is with complexity O(1).
//

#include "MatrixFigure.h"

MatrixFigure::MatrixFigure() :
    m_matrix(0, 0), m_totalFiguresCount(0)
{
}

MatrixFigure::~MatrixFigure()
{
}

void MatrixFigure::LoadMatrix(const TDGrid<MatrixElement>& matrix)
{
    m_matrix = matrix;

    CalculateFiguresCount();
}

void MatrixFigure::LoadMatrix(TDGrid<MatrixElement>&& matrix)
{
    m_matrix = matrix;

    CalculateFiguresCount();
}

uint32_t MatrixFigure::GetFiguresCount()
{
    return m_totalFiguresCount;
}

void MatrixFigure::CalculateFiguresCount()
{
    for (auto rowIter = 0; rowIter < m_matrix.GetHeight(); ++rowIter)
    {
        for (auto colIter = 0; colIter < m_matrix.GetWidth(); ++colIter)
        {
            // Check if the element is marked and still haven't been visited
            // If such element exist, this means we have found a new figure
            if ((!m_matrix[rowIter][colIter].isVisited) && (m_matrix[rowIter][colIter].isMarked))
            {
                // Add the newly found marked element to the visiting queue
                auto newElement = GridPoint(rowIter, colIter);
                m_elementsToVisit.push(newElement);

                // Inspect all elements that are neighbors and part of this figure
                while (!m_elementsToVisit.empty())
                {
                    InspectNeighborElements();
                }

                m_totalFiguresCount++;
            }
        }
    }
}

void MatrixFigure::InspectNeighborElements()
{
    auto elementPos = m_elementsToVisit.front();

    // Check if the upper element is marked
    if (elementPos.rowNumber > 0)
    {
        auto& matrixRef = m_matrix[elementPos.rowNumber - 1][elementPos.colNumber];

        if ((!matrixRef.isVisited) && (matrixRef.isMarked))
        {
            // If the element is marked, add it to the queue for visiting
            auto newElement = GridPoint(elementPos.rowNumber - 1, elementPos.colNumber);
            m_elementsToVisit.push(newElement);
        }
    }

    // Check if the left element is marked
    if (elementPos.colNumber > 0)
    {
        auto& matrixRef = m_matrix[elementPos.rowNumber][elementPos.colNumber - 1];

        if ((!matrixRef.isVisited) && (matrixRef.isMarked))
        {
            // If the element is marked, add it to the queue for visiting
            auto newElement = GridPoint(elementPos.rowNumber, elementPos.colNumber - 1);
            m_elementsToVisit.push(newElement);
        }
    }

    // Check if the bottom element is marked
    if (elementPos.rowNumber < (m_matrix.GetHeight() - 1))
    {
        auto& matrixRef = m_matrix[elementPos.rowNumber + 1][elementPos.colNumber];

        if ((!matrixRef.isVisited) && (matrixRef.isMarked))
        {
            // If the element is marked, add it to the queue for visiting
            auto newElement = GridPoint(elementPos.rowNumber + 1, elementPos.colNumber);
            m_elementsToVisit.push(newElement);
        }
    }

    // Check if the right element is marked
    if (elementPos.colNumber < (m_matrix.GetWidth() - 1))
    {
        auto& matrixRef = m_matrix[elementPos.rowNumber][elementPos.colNumber + 1];

        if ((!matrixRef.isVisited) && (matrixRef.isMarked))
        {
            // If the element is marked, add it to the queue for visiting
            auto newElement = GridPoint(elementPos.rowNumber, elementPos.colNumber + 1);
            m_elementsToVisit.push(newElement);
        }
    }

    // Remove the element from the visiting queue and mark it as visited
    m_elementsToVisit.pop();
    m_matrix[elementPos.rowNumber][elementPos.colNumber].isVisited = true;
}