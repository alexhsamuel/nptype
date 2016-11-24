#include <Python.h>

extern void add_Fixed_to_module(PyObject*);

static PyModuleDef 
module_def = {
    PyModuleDef_HEAD_INIT,
    "ext",
    "Example module that creates an extension type.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_ext()
{
  PyObject* module;
  module = PyModule_Create(&module_def);
  if (module == NULL)
    return NULL;

  add_Fixed_to_module(module);

  return module;
}

