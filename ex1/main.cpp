// This file is released into public domain.
// Terms of CC0 1.0 (Creative Commons Zero 1.0) apply,
// see <https://creativecommons.org/publicdomain/zero/1.0/legalcode> for details,
// <https://creativecommons.org/publicdomain/zero/1.0/> for summary

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>


// *************************************************************************************
// * Problem 1: delete zeroes from the vector. Functions delete + erase                *
// *   eg  result.erase(std::remove(result.begin(), result.end(), '"'), result.end()); *
// *************************************************************************************


void removeZerosStd(std::vector<int>& vec)
{
    vec.erase(std::remove(vec.begin(), vec.end(), 0), vec.end());
}


// ************************************************************************
// * Problem 2: delete zeroes from the vector without standard functions. *
// ************************************************************************


// A generic function which implements an algorithm similar to std::remove.
// Relatively container-agnostic, works only with indices
template <typename Predicate, typename Swapper>
size_t removeByPredicate(size_t n, Predicate predicate, Swapper swap)
{
    // `left` points past the last element to keep,
    // `right` is incremented on each iteration.
    // Clearly, `right` >= `left`
    size_t left = 0;
    size_t right = 0;

    while (right < n)
    {
        if (predicate(left))
        {
            // The current element is to remove
            swap(left, right);
            ++right;

            if (!predicate(left))
            {
                ++left;
            }
        }
        else
        {
            // The current element is to keep
            ++left;
            ++right;
        }
    }

    // Finally, `left` stores the number of kept elements.
    return left;
}


void removeZerosNoStd(std::vector<int>& vec)
{
    size_t numElementsToKeep = removeByPredicate(
        vec.size(),
        [&vec](size_t index) { return vec[index] == 0; },           // predicate
        [&vec](size_t a, size_t b) { std::swap(vec[a], vec[b]); }   // swapper
    );

    vec.resize(numElementsToKeep);
}


// ***************************************************************
// * Problem 3: delete columns from the matrix which have zeroes *
// ***************************************************************


using Row = std::vector<int>;
using Matrix = std::vector<Row>;


bool columnContainsZeros(const Matrix& matrix, size_t columnIndex)
{
    for (size_t rowIndex = 0; rowIndex < matrix.size(); ++rowIndex)
    {
        if (matrix[rowIndex][columnIndex] == 0)
        {
            return true;
        }
    }
    return false;
}


void swapColumns(Matrix& matrix, size_t columnA, size_t columnB)
{
    for (size_t rowIndex = 0; rowIndex < matrix.size(); ++rowIndex)
    {
        std::swap(matrix[rowIndex][columnA], matrix[rowIndex][columnB]);
    }
}


void removeColumnsWithZeros(Matrix& matrix)
{
    if (matrix.empty())
    {
        return;
    }

    size_t numElementsToKeep = removeByPredicate(
        matrix[0].size(),
        [&matrix](size_t index) { return columnContainsZeros(matrix, index); }, // predicate
        [&matrix](size_t a, size_t b) { swapColumns(matrix, a, b); }            // swapper
    );

    for (Row& row : matrix)
    {
        row.resize(numElementsToKeep);
    }
}


// ******************************
// * I/O helpers and test cases *
// ******************************


void writeMatrix(const Matrix& matrix)
{
    for (const Row& row : matrix)
    {
        for (int element : row)
        {
            std::cout << std::setw(3) << element;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void writeVector(const std::vector<int>& vec)
{
    for (int element : vec)
    {
        std::cout << std::setw(3) << element;
    }
    std::cout << std::endl;
}


template <typename F>
void testRemoveZeros(F remove, std::vector<int>& initial, const std::vector<int>& expected, int num)
{
    remove(initial);
    std::cout << "  [" << num << "] Expected: ";
    writeVector(expected);
    std::cout << "      Actual:   ";
    writeVector(initial);
    if (initial == expected)
    {
        std::cout << "      (passed)" << std::endl;
    }
    else
    {
        std::cout << "      (FAILED)" << std::endl;
    }
}


void testTask1()
{
    std::vector<int> v1 {1, 0, 0, 5, 2, 4, 1};
    std::vector<int> v2 {0, 4, 0, 7, 8, 0, 2};
    std::vector<int> v3 {0, 5, 0, 3, 0, 0, 0, 0};
    std::vector<int> v4 {0, 0, 0};
    std::vector<int> v5 {0, 1, 0};

    std::cout << "== Test task 1 ==" << std::endl;

    testRemoveZeros(removeZerosStd, v1, {1, 5, 2, 4, 1}, 1);
    testRemoveZeros(removeZerosStd, v2, {4, 7, 8, 2}, 2);
    testRemoveZeros(removeZerosStd, v3, {5, 3}, 3);
    testRemoveZeros(removeZerosStd, v4, {}, 4);
    testRemoveZeros(removeZerosStd, v5, {1}, 5);

    std::cout << std::endl;
}


void testTask2()
{
    std::vector<int> v1 {1, 0, 0, 5, 2, 4, 1};
    std::vector<int> v2 {0, 4, 0, 7, 8, 0, 2};
    std::vector<int> v3 {0, 5, 0, 3, 0, 0, 0, 0};
    std::vector<int> v4 {0, 0, 0};
    std::vector<int> v5 {0, 1, 0};

    std::cout << "== Test task 2 ==" << std::endl;

    testRemoveZeros(removeZerosNoStd, v1, {1, 5, 2, 4, 1}, 1);
    testRemoveZeros(removeZerosNoStd, v2, {4, 7, 8, 2}, 2);
    testRemoveZeros(removeZerosNoStd, v3, {5, 3}, 3);
    testRemoveZeros(removeZerosNoStd, v4, {}, 4);
    testRemoveZeros(removeZerosNoStd, v5, {1}, 5);

    std::cout << std::endl;
}


void testTask3()
{
    Matrix matrix {
        {1, 4, 0, 5, 1, 6},
        {0, 5, 8, 1, 4, 1},
        {5, 7, 0, 5, 2, 0},
    };

    Matrix expected {
        {4, 5, 1},
        {5, 1, 4},
        {7, 5, 2},
    };

    removeColumnsWithZeros(matrix);
    std::cout << "== Test task 3 ==" << std::endl;
    std::cout << "Expected:" << std::endl;
    writeMatrix(expected);
    std::cout << "Actual:" << std::endl;
    writeMatrix(matrix);
    if (matrix == expected)
    {
        std::cout << "(passed)" << std::endl;
    }
    else
    {
        std::cout << "(FAILED)" << std::endl;
    }
}


int main()
{
    testTask1();
    testTask2();
    testTask3();
}
