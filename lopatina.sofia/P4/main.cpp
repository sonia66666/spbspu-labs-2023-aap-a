#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

//input_arrey.cpp
size_t inputArray(std::istream & in, int * matrix, size_t amount, size_t toread)
{
  for (size_t i = 0; i < std::min(toread, amount); ++i)
  {
    if (!(in >> matrix[i]))
    {
      return i;
    }
  }
  return std::min(toread, amount);
}

//is_lower_tri_matrix.cpp
int isLowerTriMatrix(int * matrix, size_t rows, size_t cols)
{
  if (rows != cols || rows == 0 || rows == 1)
  {
    return 0;
  }
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (i < j && matrix[i * rows + j] != 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

//num_diag_without_zero.cpp
size_t countDiagWithoutZero(int * matrix, size_t rows, size_t cols)
{
  if (rows != cols || rows == 0)
  {
    return 0;
  }
  size_t counter = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    if (i == 0)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (i != j)
        {
          counter += 1;
          size_t n1 = i, n2 = j;
          for (size_t k = 0; k < cols - j; ++k)
          {
            if (matrix[n1 * rows + n2] == 0)
            {
              counter -= 1;
              break;
            }
            n1 += 1;
            n2 += 1;
          }
        }
      }
    }
    else if (i > 0)
    {
      counter += 1;
      size_t n1 = i;
      for (size_t k = 0; k < rows - i; ++k)
      {
        if (matrix[n1 * rows + k] == 0)
        {
          counter -= 1;
          break;
        }
        n1 += 1;
      }
    }
  }
  return counter;
}

//main.cpp
int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  //argv[1] - номер задания (1 - массив фикс размера; 2 - динамический)
  int num = 0;
  try
  {
    num = std::stoll(argv[1]);
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  catch (const std::invalid_argument &)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  //argv[2] - имя файла с массивом
  size_t rows = 0, cols = 0;

  std::ifstream input(argv[2]);
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "Cannot read rows or cols\n";
    return 2;
  }

  //----------Работа с массивом--------------
  int res1 = 0;
  size_t res2 = 0;
  if (num == 1)
  {
    int matrix[10000] = {};
    size_t result =  inputArray(input, matrix, rows * cols, rows * cols);
    if (result != rows * cols)
    {
      std::cerr << "Invalid input array\n";
      return 2;
    }

    res1 = isLowerTriMatrix(matrix, rows, cols);
    res2 = countDiagWithoutZero(matrix, rows, cols);
  }

  if (num == 2)
  {
    int * matrix = new int[rows * cols];
    size_t result =  inputArray(input, matrix, rows * cols, rows * cols);
    if (result != rows * cols)
    {
      std::cerr << "Invalid input array\n";
      delete[] matrix;
      return 2;
    }

    res1 = isLowerTriMatrix(matrix, rows, cols);
    res2 = countDiagWithoutZero(matrix, rows, cols);
    delete[] matrix;
  }

  //argv[3] - имя файла для результата
  std::ofstream output(argv[3]);
  if (res1 == 0)
  {
    output << "LWR-TRI-MTRX: " << "false\n" << "CNT-NZR-DIG: " << res2 << '\n';
  }
  else if (res1 == 1)
  {
     output << "LWR-TRI-MTRX: " << "true\n" << "CNT-NZR-DIG: " << res2 << '\n';
  }
  return 0;
}
