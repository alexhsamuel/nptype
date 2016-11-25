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

extern int compare(struct Fixed const* lhs, struct Fixed const* rhs);

