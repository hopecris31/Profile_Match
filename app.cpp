#include <iostream>
#include "Address.h"
#include "Profile.h"

using namespace std;

int main() {
    Profile hope = Profile::get_user_info();
    cout << hope.to_string() << endl;

    Address spacex = Address("Hawthorne", "CA");

    return 0;
}
