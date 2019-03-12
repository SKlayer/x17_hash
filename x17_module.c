#include <Python.h>

#include "x17.h"

static PyObject *x17_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    x17hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x17hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef X17Methods[] = {
    { "getPoWHash", x17_getpowhash, METH_VARARGS, "Returns the proof of work hash using X17 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef X17Module = {
    PyModuleDef_HEAD_INIT,
    "x17hash",
    "...",
    -1,
    X17Methods
};

PyMODINIT_FUNC PyInit_x17hash(void) {
    return PyModule_Create(&X17Module);
}

#else

PyMODINIT_FUNC initx17_hash(void) {
    (void) Py_InitModule("x17hash", X17Methods);
}
#endif
