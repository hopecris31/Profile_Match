#include <Python/Python.h>
#include <string>
#include <map>
#include "Address.h"

using namespace std;

Address::Address(string city, string state) : city_(std::move(city)), state_(std::move(state)){
}

string Address::get_data() {
    Py_Initialize();

    PyObject *pName, *pLoadModule, *pFunc;
    PyObject *pCallFunc, *pArgs;

    // Set the path to the Python script
    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyUnicode_FromString("/Users/hopecrisafi/app"));

    pName = PyUnicode_FromString((char*)"ProfileDistanceFunctions");
    pLoadModule = PyImport_Import(pName);

    pFunc = PyObject_GetAttrString(pLoadModule, (char*)"get_city_data");
    pArgs = PyTuple_Pack(2, PyUnicode_FromString(city_.c_str()), PyUnicode_FromString(state_.c_str()));
    pCallFunc = PyObject_CallObject(pFunc, pArgs);
    string data = PyString_AsString(pCallFunc);

    Py_DECREF(pName);
    Py_DECREF(pLoadModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pCallFunc);

    Py_Finalize();

    return data;
}


//std::string result;
//
// Convert the city and state strings to Python objects
//pName = PyUnicode_FromString("ProfileDistanceFunctions");
//pArgs = PyTuple_New(2);
//PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(city_.c_str()));
//PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(state_.c_str()));
//
// Load the module and the function
//pModule = PyImport_Import(pName);
//pFunc = PyObject_GetAttrString(pModule, "get_city_data");
//
// Call the function with the arguments
//pValue = PyObject_CallObject(pFunc, pArgs);
//
// Convert the return value to a string
//PyObject* pUtf8String = PyUnicode_AsUTF8String(pValue);
//if (pUtf8String != NULL) {
//result = PyBytes_AsString(pUtf8String);
//Py_DECREF(pUtf8String);
//}
//
// Clean up
//Py_DECREF(pName);
//Py_DECREF(pModule);
//Py_DECREF(pFunc);
//Py_DECREF(pArgs);
//Py_DECREF(pValue);
//
//Py_Finalize();
//
//return result;