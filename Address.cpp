//
// Created by Hope Crisafi on 12/16/22.
//

#include <Python/Python.h>
#include "ProfileDistanceFunctions.h"
#include "Address.h"

using namespace std;

Address::Address(string city, string state) :
        city_(std::move(city)),state_(std::move(state)){}


string Address::get_data() {
    Py_Initialize();

    PyObject* module = PyImport_ImportModule("ProfileDistanceFunctions");
    if (module == NULL) {
        // Handle error
        return "Error importing module";
    }

    // Get the get_city_data function from the module
    PyObject* func = PyObject_GetAttrString(module, "get_city_data");
    if (func == NULL) {
        // Handle error
        return "Error getting function";
    }

    // Call the function with the city and state arguments
    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(city_.c_str()));
    PyTuple_SetItem(args, 1, PyUnicode_FromString(state_.c_str()));
    PyObject* result = PyObject_CallObject(func, args);
    if (result == NULL) {
        // Handle error
        return "Error calling function";
    }

    // Convert the result to a C++ string
    PyObject* str_obj = PyObject_Str(result);
    char* str_result = PyUnicode_AsUTF8(str_obj);
    string result_str(str_result);

    // Clean up
    Py_DecRef(str_obj);
    Py_DecRef(result);
    Py_DecRef(args);
    Py_DecRef(func);
    Py_DecRef(module);
    Py_Finalize();

    return result_str;
}


