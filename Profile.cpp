/**
 * Creates a Profile object.  A Profile object contains a user's name, city, country, age, gender, and a list of hobbies.
 */

#include <iostream>
#include <utility>
#include <sstream>
#include <Python.h>
#include "Profile.h"

using namespace std;


/**
 * Default constructor for Profile class.
 */
Profile::Profile(string name, int age, string city, string state, string country, vector<string> hobbies, Gender gender, bool dating) :
name_(std::move(name)), age_(age), city_(std::move(city)), state_(std::move(state)), country_(std::move(country)),
hobbies_(std::move(hobbies)), gender_(gender), dating_(dating) {
}


/**
 * Used to prompt the user and collect profile information
 * @return a profile object with user's inputted information
 */
Profile Profile::get_user_info(){
    string name = input_name();
    int age = input_age();
    string city = input_city();
    string state = input_state();
    string country = input_country();
    vector<string> hobbies = input_hobbies();
    Gender gender = input_gender();
    bool dating = input_dating();

    return Profile(name, age, city, state, country, hobbies, gender, dating);
}


/**
 * Calculated the match points based on compatability criteria between two profiles
 * @param other another profile to compare to
 * @return the total number of match points
 */
int Profile::calc_match_points(const Profile& other) {

    if (this->is_dating() && this->get_gender() == other.get_gender()) { //if dating and other is same gender
        return 0;
    } else {
        int match_points = 0;
        match_points += this->calc_age_points(other);
        cout << other.get_name() << " age points: " << this->calc_age_points(other) << "\n";
        match_points += this->calc_distance_points(other);
        cout << other.get_name() << " distance points: " <<this->calc_distance_points(other)<< "\n";
        match_points += this->calc_city_points(other);
        cout << other.get_name() << " city points: " <<this->calc_city_points(other)<< "\n";
        match_points += this->calc_country_points(other);
        cout << other.get_name() << " country points: " <<this->calc_country_points(other)<< "\n";
        match_points += this->calc_hobby_points(other);
        cout << other.get_name() << " hobby points: " <<this->calc_hobby_points(other)<< "\n";
        return match_points;
    }
}


/**
 * @return string representation of a Profile object
 */
string Profile::to_string(){
    ostringstream to_return;
    to_return << "----USER PROFILE---- \n" <<
        "😮‍💨Name: " << this->get_name() << "\n" <<
        "👶Gender: " << gender_string() << "\n" <<
        "📜Age: " << this->get_age() << "\n" <<
        "🌆City: " << this->get_city() << " " << "\n" <<
        "🏛️State/Province: " << this->get_state() << " " << "\n" <<
        "🇺🇸Country: " << this->get_country() << "\n" <<
        "🥳Hobbies: " << hobbies_string()<< "\n" <<
        "❤️Dating: " << dating_string();
    return to_return.str();
}


/**
 * Getter.
 * @return the name instance variable of the current Profile object
 */
string Profile::get_name() const {
    return this->name_;
}


/**
 * Getter.
 * @return the *age* instance variable of the current Profile object
 */
 int Profile::get_age() const {
     return this->age_;
 }


/**
* Getter.
* @return the *city* instance variable of the current Profile object
*/
string Profile::get_city() const {
    return this->city_;
}


/**
* Getter.
* @return the *state* instance variable of the current Profile object
*/
string Profile::get_state() const {
    return this->state_;
}


/**
* Getter.
* @return the *country* instance variable of the current Profile object
*/
string Profile::get_country() const {
    return this->country_;
}


/**
* Getter.
* @return the *hobbies* instance variable of the current Profile object
*/
vector<string> Profile::get_hobbies() const {
    return this->hobbies_;
}


/**
* Getter.
* @return the *gender* instance variable of the current Profile object
*/
Gender Profile::get_gender() const {
    return this->gender_;
}


/**
* Getter.
* @return true or false, according to the *dating* instance variable of the current Profile object
*/
bool Profile::is_dating() const {
    return this->dating_;
}


/**_____________________________
 *
 *     PRIVATE HELPER METHODS
 *
 * _____________________________
 */


/**
 * @return string representation of the *hobies* vector instance variable
 */
string Profile::hobbies_string() const {
    ostringstream to_return;
    for(int i=0; i < this->get_hobbies().size(); i++){
        to_return << this->get_hobbies()[i] << "";
        if(i < this->get_hobbies().size() - 1){
            to_return << ", ";
        }
    }
    return to_return.str();
}


/**
 * @return  string representation of the *gender* enum instance variable
 */
string Profile::gender_string() const {
    switch (gender_) {
        case MALE:
            return "Male";
        case FEMALE:
            return "Female";
        default:
            return "Other";
    }
}


/**
 * @return string representation of the *dating* boolean instance varibale
 */
string Profile::dating_string() const {
    if (this->is_dating()) {
        return "yes";
    }
    return "no";
}


/**
 * prompts the user to input for the *name* instance variable
 * @return user input for *name*
 */
string Profile::input_name() {
    string name;
    cout << "enter name: ";
    getline(cin, name);
    return name;
}


/**
 * prompts the user to input for the *age* instance variable
 * @return user input for *age*
 */
int Profile::input_age(){
    int age;
    cout << "enter age: ";
    cin >> age;
    if (cin.fail()) {
        do{
            cin.clear();
            cin.ignore(MAX_CHARS, '\n');
            cout << "💀Invalid input. Enter an integer value for age: ";
            cin >> age;
        } while (cin.fail());
    }
    return age;
}


/**
 * prompts the user to input for the *city* instance variable
 * @return user input for *city*
 */
string Profile::input_city() {
    string city;
    cout << "enter city: ";
    cin.ignore(MAX_CHARS, '\n');
    getline(cin, city);

    return city;
}


/**
 * prompts the user to input for the *state* instance variable
 * @return user input for *state*
 */
string Profile::input_state() {
    string state;
    cout << "enter state: ";
    getline(cin, state);

    return state;
}


/**
 * prompts the user to input for the *country* instance variable
 * @return user input for *country*
 */
string Profile::input_country() {
    string country;
    cout << "enter country: ";
    getline(cin, country);

    return country;
}


/**
 * prompts the user to input for the *gender* instance variable
 * @return user input for *gender* in the form of the Gender enum
 */
Gender Profile::input_gender(){
    string user_input;
    cout << "enter gender: MALE, FEMALE, or OTHER (invalid input will default to OTHER): \n";
    cin >> user_input;
    std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
    if(user_input == "male"){
        return MALE;
    } else if(user_input == "female"){
        return FEMALE;
    } else{
       return OTHER;
    }
}


/**
 * prompts the user to input for the *dating* instance variable
 * @return user input for *dating* in the form of a bool
 */
bool Profile::input_dating() {
    char user_input;
    cout << "Enter 'y' if looking to match profiles for dating, or any other character if not: " << endl;
    cin >> user_input;
    if (user_input == 'y') {
        return true;
    }
    return false;
}


/**
 * prompts the user to input for the *hobbies* instance variable
 * @return vector containing user input for *hobbies*
 */
vector<string> Profile::input_hobbies() {
    vector<string> to_return;
    string user_input;
    cout << "enter hobby (or 'done' when finished): \n";
    getline(cin, user_input);
    while(user_input != "done"){
        to_return.push_back(user_input);
        cout << "enter a hobby OR 'done': \n";
        getline(cin, user_input);
    }
    return to_return;

}


/**
 * @breif Calculates the compatability points for the age category.
 *
 * This function calculated differently based on age range.  If the user is under 30,
 * then compatability is calculated by considering smaller age differences.  If the user
 * is over 30, then the compatability is calculated to allow for wider differences in age.
 *
 * @param other another profile to compare to
 * @return age compatability points
 */
int Profile::calc_age_points(const Profile &other) {
    if (this->is_under_30()) {
        return calc_under_30_age_points(other);
    } else {
        return calc_age_points_default(other);
    }
}


/**
 * @breif Calculated the compatability points for the distance criteria.
 *
 * The closer the two profiles are geographically, the higher the compatability
 * score is between the two
 *
 * @param other another profile to compare to
 * @return distance compatability points
 */
int Profile::calc_distance_points(const Profile &other) {
    float distance = this->get_distance(other);
    if (distance <= 15) {
        return 20;
    } else if (distance <= 25) {
        return 18;
    } else if (distance <= 50) {
        return 15;
    } else if (distance <= 150) {
        return 8;
    } else if (distance <= 250) {
        return 5;
    } else {
        return 1;
    }
}


/**
 * @breif Calculated the compatability points based on the same city criteria.
 *
 * If the two profiles are in the same city, then they will gain extra compatability
 * points.  If not, no additional points are given.
 *
 * @param other another profile to compare
 * @return same city compatability points
 */
int Profile::calc_city_points(const Profile &other) {
    if (this->in_same_city(other)) {
        return 10;
    } else {
        return 0;
    }
}


/**
 * @breif Calculated the compatability points based on the same country criteria.
 *
 * If the two profiles are in the same country, then they will gain extra compatability
 * points.  If not, no additional points are given.
 *
 * @param other another profile to compare
 * @return same country compatability points
 */
int Profile::calc_country_points(const Profile &other) {
    if (this->in_same_country(other)) {
        return 15;
    } else {
        return 0;
    }
}


/**
 * @breif Calculated the compatability points based on the hobbies criteria.
 *
 * The more hobbies and interests the two profiles have in common, the more compatability
 * points will be awarded.  This criteria has the highest weight in determining compatability.
 *
 * @param other another profile to compare
 * @return hobbies compatability points
 */
int Profile::calc_hobby_points(const Profile& other) {
    int num_hobby_similarity = this->get_hobbies_similarity(other);

    if(num_hobby_similarity > 3) {
        return 40;
    } else if (num_hobby_similarity == 3) {
        return 35;
    } else if (num_hobby_similarity == 2) {
        return 30;
    } else if (num_hobby_similarity == 1) {
        return 20;
    } else {
        return 0;
    }
}


/**
 * Gets the difference in age between two profiles
 * @param other another profile to compare
 * @return the difference in age
 */
int Profile::get_age_difference(const Profile& other) {
    int difference = this->get_age() - other.get_age();
    return abs(difference);
}


/**
 * @return true if profile's age is under 30, false if 30 or over
 */
bool Profile::is_under_30() const{
    return this->get_age() < 30;
}


/**
 * calculates the age criteria points for a profile that's age is under 30
 * @param other another profile to compare
 * @return the age compatability points for a user under 30
 */
int Profile::calc_under_30_age_points(const Profile& other) {
    int age_difference = get_age_difference(other);
    if (age_difference <= 2) {
        return 15;
    } else if (age_difference <= 4) {
        return 13;
    } else if (age_difference <= 6) {
        return 11;
    } else if (age_difference <= 8) {
        return 9;
    } else {
        return 0;
    }
}


/**
 * calculates the age criteria points for a profile that's age is 30 or over
 * @param other another profile to compare
 * @return the age compatability points for a user 30 or over
 */
int Profile::calc_age_points_default(const Profile &other) {
    int age_difference = get_age_difference(other);
    if (age_difference <= 4) {
        return 15;
    } else if (age_difference <= 8) {
        return 13;
    } else if (age_difference <= 12) {
        return 11;
    } else if (age_difference <= 16) {
        return 9;
    } else {
        return 0;
    }
}


/**
 * Gets the geographical distance between two profiles.  Calls Python functions.
 * @param other another profile to get distance from
 * @return the distance in miles between the profiles
 */
float Profile::get_distance(const Profile& other) const {
    Py_Initialize();

    PyObject *pName;
    PyObject *pLoadModule;
    PyObject *pFunc;
    PyObject *pCallFunc;
    PyObject *pArgs;

    PyObject* sysPath = PySys_GetObject((char*)"path");
    string full_path = __FILE__;
    string directory = full_path.substr(0, full_path.find_last_of("/\\"));
    PyList_Append(sysPath, PyUnicode_FromString(directory.c_str()));

    pName = PyUnicode_FromString((char*)"PythonMapAPIFunctions");
    pLoadModule = PyImport_Import(pName);

    if (pLoadModule == nullptr) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"PythonMapAPIFunctions\"\n");
        return 1;
    }

    pFunc = PyObject_GetAttrString(pLoadModule, (char*)"get_distance");
    pArgs = PyTuple_Pack(4, PyUnicode_FromString(this->get_city().c_str()), PyUnicode_FromString(this->get_state().c_str()),
                         PyUnicode_FromString(other.get_city().c_str()), PyUnicode_FromString(other.get_state().c_str()));
    pCallFunc = PyObject_CallObject(pFunc, pArgs);

    float data = PyFloat_AsDouble(pCallFunc);

    Py_DECREF(pName);
    Py_DECREF(pLoadModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pCallFunc);

    Py_Finalize();

    return data;
}


/**
 * checks to see if two profiles are located in the same city
 * @param other another profile to compare
 * @return trie if profiles are in same city, false if not
 */
bool Profile::in_same_city(const Profile& other) const {
    return this->get_city() == other.get_city();
}


/**
 * checks to see if two profiles are located in the same country
 * @param other another profile to compare
 * @return trie if profiles are in same country, false if not
 */
bool Profile::in_same_country(const Profile& other) const {
    return this->get_country() == other.get_country();
}


/**
 * @breif Gets the number of hobbies/interests that two profiles have in common. Calls Python functions.
 *
 * Gets the similar hobbies/interests by getting synonyms/related words of each hobby/interest, and checking
 * if the nynonym or related word from the "this" profile appear in the "other" profile, then it is counted
 * as a hobby/interest the two profiles have in common.
 *
 * @param other another profile to compare
 * @return total hobbies/interests the two profiles have in common
 */
int Profile::get_hobbies_similarity(const Profile& other) const {
    Py_Initialize();

    PyObject *pName;
    PyObject *pLoadModule;
    PyObject *pFunc;
    PyObject *pCallFunc;
    PyObject *pArgs;

    PyObject* sysPath = PySys_GetObject((char*)"path");
    string full_path = __FILE__; // gets current path of program
    string directory = full_path.substr(0, full_path.find_last_of("/\\"));
    PyList_Append(sysPath, PyUnicode_FromString(directory.c_str()));

    pName = PyUnicode_FromString((char*)"PythonSynonymFunctions");
    pLoadModule = PyImport_Import(pName);

    if (pLoadModule == nullptr) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"PythonSynonymFunctions\"\n");
        return 1;
    }

    pFunc = PyObject_GetAttrString(pLoadModule, (char*)"get_hobby_similarity_score");

    PyObject* this_hobbies_list = PyList_New(this->get_hobbies().size());
    for (std::size_t i = 0; i < this->get_hobbies().size(); ++i) {
        PyList_SetItem(this_hobbies_list, i, PyUnicode_FromString(this->get_hobbies()[i].c_str()));
    }
    PyObject* other_hobbies_list = PyList_New(other.get_hobbies().size());
    for (std::size_t i = 0; i < other.get_hobbies().size(); ++i) {
        PyList_SetItem(other_hobbies_list, i, PyUnicode_FromString(other.get_hobbies()[i].c_str()));
    }

    pArgs = PyTuple_Pack(2, this_hobbies_list, other_hobbies_list);
    pCallFunc = PyObject_CallObject(pFunc, pArgs);

    int points = (int) PyLong_AsLong(pCallFunc);

    Py_DECREF(pName);
    Py_DECREF(pLoadModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pCallFunc);

    Py_Finalize();

    return points;
}

