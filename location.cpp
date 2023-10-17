#include "location.h"
#include <iostream>

Location::Location(int row, int column) 
  : row{row}, column{column} {}

Location::Location(const Location & other) 
  : row{other.row}, column{other.column} {}

bool Location::operator==(const Location & other) const
{
  return row == other.row && column == other.column;
}

bool Location::operator!=(const Location & other) const
{
  return !(row == other.row && column == other.column);
}

std::ostream& operator<<(std::ostream& out, const Location & location)
{
  out << '(' << location.row << ',' << location.column << ')';
  return out;
}