#pragma once

//------------------------------------------------------------------------------

struct Fixed {
  int whole;
  unsigned int fractional;
};

extern PyTypeObject
Fixed_type;

