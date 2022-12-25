#include <iostream>
#include "Address.h"
#include <Python.h>
#include "PythonAddress.h"

using namespace std;

int main() {

    Address spacex = Address("Hawthorne", "CA");
    Address tesla = Address("Palo Alto", "CA");

    double distance = spacex.get_distance(tesla);
    cout << distance << endl;

    return 0;
}
