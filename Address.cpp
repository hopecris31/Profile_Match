#include <Python.h>
#include <unordered_map>
#include <sstream>
#include "Address.h"

using namespace std;

Address::Address(string city, string state) : city_(std::move(city)), state_(std::move(state)){
}

double Address::get_distance(const Address& other) {
    Py_Initialize();

    PyObject *pName;
    PyObject *pLoadModule;
    PyObject *pFunc;
    PyObject *pCallFunc;
    PyObject *pArgs;

    PyObject* sysPath = PySys_GetObject((char*)"path");
    // Replace with the current directory of the python file if running on another system
    PyList_Append(sysPath, PyUnicode_FromString("/Users/hopecrisafi/CLionProjects/app"));

    pName = PyUnicode_FromString((char*)"PythonAddress");
    pLoadModule = PyImport_Import(pName);

    if (pLoadModule == nullptr) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"PythonAddress\"\n");
        return 1;
    }

    pFunc = PyObject_GetAttrString(pLoadModule, (char*)"get_distance");
    pArgs = PyTuple_Pack(4, PyUnicode_FromString(city_.c_str()), PyUnicode_FromString(state_.c_str()),
                         PyUnicode_FromString(other.city_.c_str()), PyUnicode_FromString(other.state_.c_str()));
    pCallFunc = PyObject_CallObject(pFunc, pArgs);

    double data = PyFloat_AsDouble(pCallFunc);

    Py_DECREF(pName);
    Py_DECREF(pLoadModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pCallFunc);

    Py_Finalize();

    return data;
}

