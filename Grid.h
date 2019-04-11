//
// Author: mitkovulkov@gmail.com (Mitko Valkov)
// Created on 09.04.19.
//
// This file contains two-dimension Grid data structure class.
// The class provides operations for creating new grid,
// initializing the grid with an initial value, and element
// access using indexing operator - [].
//

#ifndef GRID_H
#define GRID_H

#include <cstdint>
#include <iostream>

// Data structure that represents the position of a single
// element in the grid
struct GridPoint
{
    uint32_t rowNumber;
    uint32_t colNumber;

    GridPoint(const uint32_t inRow, const uint32_t inCol):
        rowNumber(inRow), colNumber(inCol)
    {
    }
};

template <class GridContainer>
class TDGrid
{
private:
    // Forward declaration of ODGrid
    struct ODGrid;
public:
    // Constructor of Grid with initial value for each element in the grid
    TDGrid(const uint32_t width, const uint32_t height, const GridContainer& initValue);

    // Constructor of grid with dimensions only
    TDGrid(const uint32_t width, const uint32_t height);

    // Copy constructor for the grid
    TDGrid(const TDGrid& other);

    // Move constructor for the grid
    TDGrid(TDGrid&& other);

    ~TDGrid();

    // Gets the height of the grid
    uint32_t GetHeight() const;

    // Gets the width of the grid
    uint32_t GetWidth() const;

    // Fills the entire grid with the provided value
    void FillGrid(const GridContainer value);

    // Prints the grid on the standard output
    void PrintGrid() const;

    ODGrid& operator[](const int index);

    TDGrid& operator=(const TDGrid& other);

    TDGrid& operator=(TDGrid&& other);

private:
    // Structure for representing the one-dimension grid
    struct ODGrid
    {
        GridContainer *s_grid;

        GridContainer& operator[](const uint32_t index)
        {
            return s_grid[index];
        }
    };

    ODGrid *m_grid;   // Contains a list of one-dimension grid
    uint32_t m_width; // The width of the grid
    uint32_t m_height; // The height of the grid
};

//
// Code below contains the implementation of Grid class.
//
template <class GridContainer>
TDGrid<GridContainer>::TDGrid(const uint32_t width, const uint32_t height, const GridContainer& initValue):
        TDGrid(width, height)
{
    FillGrid(initValue);
}

template <class GridContainer>
TDGrid<GridContainer>::TDGrid(const uint32_t width, const uint32_t height):
        m_width(width), m_height(height)
{
    try
    {
        m_grid = new ODGrid[height];

        for (uint32_t i = 0; i < height; ++i)
        {
            m_grid[i].s_grid = new GridContainer[width];
        }
    }
    catch (const std::bad_alloc)
    {
        std::cout << "Bad Alloc exception catch.";
    }
}

template <class GridContainer>
TDGrid<GridContainer>::TDGrid(const TDGrid<GridContainer>& other) :
    TDGrid(other.m_width, other.m_height)
{
    if (this != &other)
    {
        // Copy all elements from the provided Grid
        for (auto rowIter = 0; rowIter < other.m_height; ++rowIter)
        {
            for (auto colIter = 0; colIter < other.m_width; ++colIter)
            {
                m_grid[rowIter][colIter] = other.m_grid[rowIter][colIter];
            }
        }
    }
}

template <class GridContainer>
TDGrid<GridContainer>::TDGrid(TDGrid<GridContainer>&& other)
{
    if (this != &other)
    {
        // Get the data from the provided grid
        m_width  = other.m_width;
        m_height = other.m_height;
        m_grid   = other.m_grid;

        // Invalidate the data for the provided grid
        other.m_width  = 0;
        other.m_height = 0;
        other.m_grid   = nullptr;
    }
}

template <class GridContainer>
TDGrid<GridContainer>::~TDGrid()
{
    for (auto iter = 0; iter < m_height; ++iter)
    {
        delete[] m_grid[iter].s_grid;
    }

    delete[] m_grid;
}

template <class GridContainer>
uint32_t TDGrid<GridContainer>::GetHeight() const
{
    return m_height;
}

template <class GridContainer>
uint32_t TDGrid<GridContainer>::GetWidth() const
{
    return m_width;
}

template <class GridContainer>
void TDGrid<GridContainer>::FillGrid(const GridContainer value)
{
    if (m_grid)
    {
        for (auto rowIter = 0; rowIter < m_height; ++rowIter)
        {
            for (auto colIter = 0; colIter < m_width; ++colIter)
            {
                m_grid[rowIter][colIter] = value;
            }
        }
    }
}

template <class GridContainer>
void TDGrid<GridContainer>::PrintGrid() const
{
    if (m_grid)
    {
        for (auto rowIter = 0; rowIter < m_height; ++rowIter)
        {
            for (auto colIter = 0; colIter < m_width; ++colIter)
            {
                std::cout << m_grid[rowIter][colIter] << " ";
            }

            std::cout << std::endl;
        }
    }
}

template <class GridContainer>
typename TDGrid<GridContainer>::ODGrid& TDGrid<GridContainer>::operator[](const int index)
{
    return m_grid[index];
}

template <class GridContainer>
TDGrid<GridContainer>& TDGrid<GridContainer>::operator=(const TDGrid<GridContainer>& other)
{
    if (this != &other)
    {
        // Deallocate the current grid
        if (nullptr != m_grid)
        {
            for (auto iter = 0; iter < m_height; ++iter)
            {
                delete[] m_grid[iter].s_grid;
            }

            delete[] m_grid;
        }

        // Construct the new grid as a copy from the provided Grid
        m_height = other.m_height;
        m_width  = other.m_width;

        m_grid = new ODGrid[m_height];

        for (auto iter = 0; iter < m_height; ++iter)
        {
            m_grid[iter].s_grid = new GridContainer[m_width];
        }

        // Copy all elements from the provided Grid
        for (auto rowIter = 0; rowIter < other.m_height; ++rowIter)
        {
            for (auto colIter = 0; colIter < other.m_width; ++colIter)
            {
                m_grid[rowIter][colIter] = other.m_grid[rowIter][colIter];
            }
        }
    }
}

template <class GridContainer>
TDGrid<GridContainer>& TDGrid<GridContainer>::operator=(TDGrid<GridContainer>&& other){

    if (this != &other)
    {
        // Get the data for the provided grid
        m_width  = other.m_width;
        m_height = other.m_height;
        m_grid   = other.m_grid;

        // Invalidate the data for the provided grid
        other.m_width  = 0;
        other.m_height = 0;
        other.m_grid   = nullptr;
    }

    return *this;
}

#endif //GRID_H
