#include <assert.h>
#include <Python.h>
#include <stdalign.h>

#define PY_ARRAY_UNIQUE_SYMBOL fixed_numpy
#define NO_IMPORT_ARRAY
#define NPY_NO_DEPRECATED_API NPY_API_VERSION

#include <numpy/arrayobject.h>
#include <numpy/npy_math.h>
#include <numpy/ufuncobject.h>
#include <numpy/npy_3kcompat.h>

#include "fixed.h"

//------------------------------------------------------------------------------

PyArray_Descr*
descr;

void
copyswap(
  struct Fixed* const dst,
  struct Fixed const* const src,
  int const swap,
  PyArrayObject* const arr)
{
  if (swap) {
    dst->whole = __builtin_bswap32(src->whole);
    dst->fractional = __builtin_bswap32(src->fractional);
  }
  else 
    *dst = *src;
}

/*
void
copyswapn(
  struct Fixed* const dst,
  npy_intp const dst_stride,
  struct Fixed const* const src,
  npy_intp const src_stride,
  npy_intp const n,
  int const swap,
  PyArrayObject* const arr)
{
}
*/

PyObject*
getitem(
  struct Fixed const* const data,
  PyArrayObject* const arr)
{
  PyFixed* const obj = (PyFixed*) Fixed_type.tp_alloc(&Fixed_type, 0);
  obj->fixed = *data;
  fprintf(stderr, "getitem: obj->fixed = %u %d\n", obj->fixed.whole, obj->fixed.fractional);
  return (PyObject*) obj;
}

int
setitem(
  PyObject* item,
  struct Fixed* const data,
  PyArrayObject* const arr)
{
  if (!PyObject_IsInstance(item, (PyObject*) &Fixed_type)) {
    PyErr_SetString(PyExc_TypeError, "setitem: can't set value; not a Fixed");
    return -1;
  }
  *data = ((PyFixed*) item)->fixed;
  fprintf(stderr, "setitem: data = %u %d\n", data->whole, data->fractional);
  return 0;
}

int
compare(
  struct Fixed const* const lhs,
  struct Fixed const* const rhs,
  PyArrayObject* const arr)
{
  return 0; // FIXME
}

PyArray_Descr*
get_Fixed_descr()
{
  static PyArray_Descr* descr = NULL;
  if (descr == NULL) {
    static PyArray_ArrFuncs arr_funcs;
    PyArray_InitArrFuncs(&arr_funcs);
    arr_funcs.copyswap  = (PyArray_CopySwapFunc*) copyswap;
 // arr_funcs.copyswapn = (PyArray_CopySwapNFunc*) copyswapn;
    arr_funcs.getitem   = (PyArray_GetItemFunc*) getitem;
    arr_funcs.setitem   = (PyArray_SetItemFunc*) setitem;
    arr_funcs.compare   = (PyArray_CompareFunc*) compare;

    descr = PyObject_New(PyArray_Descr, &PyArrayDescr_Type);
    Py_INCREF((PyObject*) &Fixed_type);
    descr->typeobj      = &Fixed_type;
    descr->kind         = 'V';  // FIXME: ??
    descr->type         = 'j';  // FIXME: ??
    descr->byteorder    = '=';
    descr->flags        = 0;
    descr->type_num     = 0;
    descr->elsize       = sizeof(struct Fixed);
    descr->alignment    = alignof(struct Fixed);
    descr->subarray     = NULL;
    descr->fields       = NULL;
    descr->names        = NULL;
    descr->f            = &arr_funcs;
    descr->metadata     = NULL;
    descr->c_metadata   = NULL;
    descr->hash         = -1;

    if (PyArray_RegisterDataType(descr) < 0)
      return NULL;
  }
  return descr;
}

