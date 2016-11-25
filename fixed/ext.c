#include <Python.h>

#define PY_ARRAY_UNIQUE_SYMBOL fixed_numpy
#define NPY_NO_DEPRECATED_API NPY_API_VERSION

#include <numpy/arrayobject.h>
#include <numpy/npy_math.h>
#include <numpy/ufuncobject.h>
#include <numpy/npy_3kcompat.h>

#include "fixed.h"

//------------------------------------------------------------------------------

static PyModuleDef 
module_def = {
    PyModuleDef_HEAD_INIT,
    "ext",
    "Example module that creates an extension type.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

// FIXME
extern PyArray_Descr*
get_Fixed_descr();

PyMODINIT_FUNC
PyInit_ext()
{
  PyObject* module;
  module = PyModule_Create(&module_def);
  if (module == NULL)
    return NULL;

  // Add the Fixed Python type.
  Fixed_type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&Fixed_type) < 0)
    return NULL;
  Py_INCREF(&Fixed_type);
  PyModule_AddObject(module, "Fixed", (PyObject*) &Fixed_type);

  // Import numpy stuff.
  if (_import_array() < 0) 
    return NULL;
  if (_import_umath() < 0) 
    return NULL;

  // Attach the numpy dtype.
  PyArray_Descr* Fixed_descr = get_Fixed_descr();
  if (Fixed_descr == NULL)
    return NULL;
  PyDict_SetItemString(Fixed_type.tp_dict, "dtype", (PyObject*) Fixed_descr);

  return module;
}


