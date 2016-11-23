#include <Python.h>

#if 0
#define PY_ARRAY_UNIQUE_SYMBOL nptype
#define NO_IMPORT_ARRAY
#define NPY_NO_DEPRECATED_API NPY_API_VERSION

#include <numpy/arrayobject.h>
#include <numpy/npy_3kcompat.h>
#endif

double const SCALE = 1.0 / (1l << 32);

typedef struct {
  PyObject_HEAD
  int whole;
  unsigned int fractional;
} Fixed;


static int
tp_init(
  Fixed* self, 
  PyObject* args, 
  PyObject* kwds)
{
  int whole;
  unsigned int fractional;
  if (! PyArg_ParseTuple(args, "iI", &whole, &fractional))
    return -1;
  else {
    self->whole = whole;
    self->fractional = fractional;
    return 0;
  }
}

static PyObject*
tp_repr(
  Fixed* obj)
{
  return PyUnicode_FromFormat("Fixed(%u, %d)", obj->whole, obj->fractional);
}

static PyObject*
tp_str(
  Fixed* obj)
{
  double const val = obj->whole + obj->fractional * SCALE;
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.11f", val);
  return PyUnicode_FromString(buffer);
}

PyTypeObject
type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char const*)         "Fixed",                        // tp_name
    (Py_ssize_t)          sizeof(Fixed) ,                 // tp_basicsize
    (Py_ssize_t)          0,                              // tp_itemsize
    (destructor)          NULL,                           // tp_dealloc
    (printfunc)           NULL,                           // tp_print
    (getattrfunc)         NULL,                           // tp_getattr
    (setattrfunc)         NULL,                           // tp_setattr
                          NULL,                           // tp_reserved
    (reprfunc)            tp_repr,                        // tp_repr
    (PyNumberMethods*)    NULL,                           // tp_as_number
    (PySequenceMethods*)  NULL,                           // tp_as_sequence
    (PyMappingMethods*)   NULL,                           // tp_as_mapping
    (hashfunc)            NULL,                           // tp_hash
    (ternaryfunc)         NULL,                           // tp_call
    (reprfunc)            tp_str,                         // tp_str
    (getattrofunc)        NULL,                           // tp_getattro
    (setattrofunc)        NULL,                           // tp_setattro
    (PyBufferProcs*)      NULL,                           // tp_as_buffer
    (unsigned long)       Py_TPFLAGS_DEFAULT
                          | Py_TPFLAGS_BASETYPE,          // tp_flags
    (char const*)         NULL,                           // tp_doc
    (traverseproc)        NULL,                           // tp_traverse
    (inquiry)             NULL,                           // tp_clear
    (richcmpfunc)         NULL,                           // tp_richcompare
    (Py_ssize_t)          0,                              // tp_weaklistoffset
    (getiterfunc)         NULL,                           // tp_iter
    (iternextfunc)        NULL,                           // tp_iternext
    (PyMethodDef*)        NULL,                           // tp_methods
    (struct PyMemberDef*) NULL,                           // tp_members
    (PyGetSetDef*)        NULL,                           // tp_getset
    (PyTypeObject*)       NULL,                           // tp_base
    (PyObject*)           NULL,                           // tp_dict
    (descrgetfunc)        NULL,                           // tp_descr_get
    (descrsetfunc)        NULL,                           // tp_descr_set
    (Py_ssize_t)          0,                              // tp_dictoffset
    (initproc)            tp_init,                        // tp_init
    (allocfunc)           NULL,                           // tp_alloc
    (newfunc)             PyType_GenericNew,              // tp_new
    (freefunc)            NULL,                           // tp_free
    (inquiry)             NULL,                           // tp_is_gc
    (PyObject*)           NULL,                           // tp_bases
    (PyObject*)           NULL,                           // tp_mro
    (PyObject*)           NULL,                           // tp_cache
    (PyObject*)           NULL,                           // tp_subclasses
    (PyObject*)           NULL,                           // tp_weaklist
    (destructor)          NULL,                           // tp_del
    (unsigned int)        0,                              // tp_version_tag
    (destructor)          NULL,                           // tp_finalize
};

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
  type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&type) < 0)
    return NULL;
  module = PyModule_Create(&module_def);
  if (module == NULL)
    return NULL;

  Py_INCREF(&type);
  PyModule_AddObject(module, "Fixed", (PyObject*) &type);
  return module;
}
