#include <iostream>
#include <iomanip>
#include <algorithm>
#include "unique_sym_array.hpp"
#include "input_string.hpp"

int main()
{
  using namespace namestnikov;
  char * firstString = nullptr;
  size_t first = 0;
  try
  {
    firstString = inputString(std::cin, first);
  }
  catch (...)
  {
    delete [] firstString;
    std::cerr << "Not enough memory\n";
    return 2;
  }
  size_t firstSize = getSizeOfString(firstString);
  const char * secondString = "abc_ef";
  const size_t secondSize = 6;
  char * result = nullptr;
  try
  {
     result = new char[5];
  }
  catch (const std::bad_alloc & e)
  {
    delete [] firstString;
    std::cerr << "Not enough memory\n";
    return 2;
  }
  getUniqueSymArray(result, firstString, secondString, firstSize, secondSize);
  size_t length = 0;
  sortUniqueSymArray(result, length);
  std::cout << result << "\n";
  delete [] firstString;
  delete [] result;
}
