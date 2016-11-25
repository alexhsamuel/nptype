#pragma once

//------------------------------------------------------------------------------

struct Fixed {
  int whole;
  unsigned int fractional;
};

extern PyTypeObject
Fixed_type;

typedef struct {
  PyObject_HEAD
  struct Fixed fixed;
} PyFixed;

