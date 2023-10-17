#ifndef LOCATION_H
#define LOCATION_H

#include <iosfwd>

class Location
{
public:
  int row;
  int column;

  Location(int initRow, int initColumn);
  Location(const Location & other);
  bool operator==(const Location & other) const;
  bool operator!=(const Location & other) const;
};

std::ostream& operator<<(std::ostream& out, const Location & location);

#endif 