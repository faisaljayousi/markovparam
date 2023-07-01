/**
 * @file wrapper.cpp
 * @brief Provides a wrapper function for calculating the Markovian parameter.
 *
 * This file contains the implementation of a module for calculating the Markovian parameter.
 * It provides a wrapper function that allows the calculation to be called from Python.
 *
 * @author Faisal Jayousi
 * @date June 29, 2023
 */

#include <Python.h>
#include "main.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Wrapper function for calculating the Markovian parameter.
     *
     * This function serves as a wrapper for the `varCond` function, allowing it to be called from Python.
     *
     * @param self      The module object representing the current module.
     * @param args      The arguments passed to the function.
     *
     * @return          A Python object representing the calculated variance condition as a floating-point value.
     *                  Returns NULL if there was an error.
     */
    static PyObject *stoseg_varCond(PyObject *self, PyObject *args)
    {
        // Declare variables
        PyObject *depObj;
        int dx, dy;

        // Parse arguments
        if (!PyArg_ParseTuple(args, "Oii", &depObj, &dx, &dy))
        {
            // Return NULL if arguments are invalid
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return NULL;
        }

        // Convert input list to C++ vector
        DoubleVec2D dep;
        PyObject *depList = PySequence_Fast(depObj, "Expected a sequence");
        if (!depList)
        {
            PyErr_SetString(PyExc_TypeError, "Invalid input");
            return NULL;
        }
        Py_ssize_t size = PySequence_Fast_GET_SIZE(depList);
        dep.resize(size);
        for (Py_ssize_t i = 0; i < size; i++)
        {
            PyObject *rowObj = PySequence_Fast_GET_ITEM(depList, i);
            if (!PyList_Check(rowObj))
            {
                Py_DECREF(depList);
                PyErr_SetString(PyExc_TypeError, "Invalid input");
                return NULL;
            }
            Py_ssize_t rowSize = PySequence_Fast_GET_SIZE(rowObj);
            dep[i].resize(rowSize);
            for (Py_ssize_t j = 0; j < rowSize; j++)
            {
                PyObject *elemObj = PySequence_Fast_GET_ITEM(rowObj, j);
                if (!PyFloat_Check(elemObj))
                {
                    Py_DECREF(depList);
                    PyErr_SetString(PyExc_TypeError, "Invalid input");
                    return NULL;
                }
                dep[i][j] = PyFloat_AsDouble(elemObj);
            }
        }
        Py_DECREF(depList);

        double result = varCond(dep, dx, dy);
        // Create Python float object to return result
        return PyFloat_FromDouble(result);
    }

    // Method table
    static PyMethodDef StosegMethods[] = {
        {"varCond", stoseg_varCond, METH_VARARGS, "Calculate the Markov parameter."},
        {NULL, NULL, 0, NULL} // Sentinel
    };

    // Module definition
    static struct PyModuleDef stosegmodule = {
        PyModuleDef_HEAD_INIT,
        "stoseg",                                                                // Module name
        "This module provides a function for calculating the Markov parameter.", // Module documentation
        -1,                                                                      // Module keeps state in global variables.
        StosegMethods                                                            // Method table
    };

    /**
     * @brief Module initialization function.
     *
     * This function is called when the module is imported into Python.
     * It creates and returns a new Python module object that represents the module.
     *
     * @return          A new Python module object representing the module.
     */
    PyMODINIT_FUNC PyInit_stoseg(void)
    {
        return PyModule_Create(&stosegmodule);
    }

#ifdef __cplusplus
}
#endif
