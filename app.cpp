#include <iostream>
#include "profile.h"

using namespace std;

int main() {
    Profile hope = Profile::get_user_info();
    cout << hope.to_string() << endl;
    return 0;
}
