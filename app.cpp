#include <iostream>
#include "Address.h"
#include "Profile.h"

using namespace std;

int main() {

    Address spacex = Address("Hawthorne", "CA");
    Address tesla = Address("Palo Alto", "CA");
    Address hope = Address("Bay Village", "OH");

    double distance = spacex.get_distance(hope);
    cout << distance << endl;

    //string name="", int age=0, string city="", string state="", string country="", vector<string> hobbies={},
    //            Gender gender=OTHER
    Profile hope1 = Profile("hope", 20, "cleveland", "OH", "US", {"reading", "coding", "hockey"}, FEMALE);
    Profile hope2 = Profile("hope", 20, "cleveland", "OH", "US", {"reading", "coding", "sports"}, FEMALE);
    int points = hope1.get_hobby_points(hope2);
    cout << points;

    return 0;
}
