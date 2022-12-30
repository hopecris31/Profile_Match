
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
Profile::Profile(string name, int age, string city, string state, string country, vector<string> hobbies, Gender gender) :
name_(std::move(name)), age_(age), city_(std::move(city)), state_(std::move(state)), country_(std::move(country)),
hobbies_(std::move(hobbies)), gender_(gender) {
}


Profile Profile::get_user_info(){

    string name = input_name();
    int age = input_age();
    string city = input_city();
    string state = input_state();
    string country = input_country();
    vector<string> hobbies = input_hobbies();
    Gender gender = input_gender();

    return Profile(name, age, city, state, country, hobbies, gender);
}

int Profile::percent_match(const Profile& other) {

    //if profile age difference is <= 2 years: +13
    //if profile age difference is <= 4 years: +11
    //if profile age difference is <= 6 years: +9
    //if profile age difference is <= 8 years: +7
    //if profile age difference is > 8 years: +3
    //
    //if profiles within 10 miles: +15
    //if profiles within 25 miles: +13
    //if profiles within 50 miles: +10
    //if profile within 200 miles: +5
    //
    //if profiles in same city: +7
    //
    //if profiles in the same country: +9
    //
    //1 hobby in common: +20
    //2 hobbies in common: +25
    //3 hobbies in common: +30
    //4+ hobbies in common: +35
    //
    //1 quality in common: +5
    //2 qualities in common: +10
    //3 qualities in common: +15
    //4+ qualities in common: +20



    return 0;
}

string Profile::to_string(){
    ostringstream to_return;
    to_return << "----USER PROFILE---- \n" <<
        "😮‍💨Name: " << name_ << "\n" <<
        "👶Gender: " << gender_string() << "\n" <<
        "📜Age: " << age_ << "\n" <<
        "🌆City: " << city_ << " " << "\n" <<
        "🏛️State/Province: " << state_ << " " << "\n" <<
        "🇺🇸Country: " << country_ << "\n" <<
        "🥳Hobbies: " << hobbies_string();
    return to_return.str();
}


/**_____________________________
 *
 *     PRIVATE HELPER METHODS
 *
 * _____________________________
 */


string Profile::gender_string() {
    switch (gender_) {
        case MALE:
            return "Male";
        case FEMALE:
            return "Female";
        default:
            return "Other";
    }
}

string Profile::hobbies_string() {
    ostringstream to_return;
    for(int i=0; i < hobbies_.size(); i++){
        to_return << hobbies_[i] << "";
        if(i < hobbies_.size() - 1){
            to_return << ", ";
        }
    }
    return to_return.str();
}

string Profile::input_name() {
    string name;
    cout << "enter name: ";
    getline(cin, name);
    return name;
}

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

string Profile::input_city() {
    string city;
    cout << "enter city: ";
    cin.ignore(MAX_CHARS, '\n');
    getline(cin, city);

    return city;
}

string Profile::input_state() {
    string state;
    cout << "enter state: ";
    cin.ignore(MAX_CHARS, '\n');
    getline(cin, state);

    return state;
}

string Profile::input_country() {
    string country;
    cout << "enter country: ";
    getline(cin, country);

    return country;
}

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

vector<string> Profile::input_hobbies() {
    vector<string> to_return;
    string user_input;
    cout << "enter hobby (or 'done' when finished): \n";
    cin >> user_input;
    while(user_input != "done"){
        to_return.push_back(user_input);
        cout << "enter a hobby OR 'done': \n";
        cin >> user_input;
    }
    return to_return;

}


int Profile::get_age_difference(const Profile& other) {
    int difference = this->age_ - other.age_;
    return abs(difference);
}

int Profile::get_distance(const Profile& other) {
    Py_Initialize();

    PyObject *pName;
    PyObject *pLoadModule;
    PyObject *pFunc;
    PyObject *pCallFunc;
    PyObject *pArgs;

    PyObject* sysPath = PySys_GetObject((char*)"path");
    // Replace with the current directory of the python file if running on another system
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
    pArgs = PyTuple_Pack(4, PyUnicode_FromString(city_.c_str()), PyUnicode_FromString(state_.c_str()),
                         PyUnicode_FromString(other.city_.c_str()), PyUnicode_FromString(other.state_.c_str()));
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

bool Profile::same_country(const Profile& other) {
    std::transform(this->country_.begin(), this->country_.end(), this->country_.begin(), ::tolower);
    return this->country_ == other.country_;
}

bool Profile::same_city(const Profile& other) {
    return this->city_ == other.city_;
}

int Profile::get_hobby_points(const Profile& other){
    Py_Initialize();

    PyObject *pName;
    PyObject *pLoadModule;
    PyObject *pFunc;
    PyObject *pCallFunc;
    PyObject *pArgs;

    PyObject* sysPath = PySys_GetObject((char*)"path");
    // Replace with the current directory of the python file if running on another system
    string full_path = __FILE__;
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

    PyObject* this_hobbies_list = PyList_New(hobbies_.size());
    for (std::size_t i = 0; i < hobbies_.size(); ++i) {
        PyList_SetItem(this_hobbies_list, i, PyUnicode_FromString(hobbies_[i].c_str()));
    }
    PyObject* other_hobbies_list = PyList_New(other.hobbies_.size());
    for (std::size_t i = 0; i < other.hobbies_.size(); ++i) {
        PyList_SetItem(other_hobbies_list, i, PyUnicode_FromString(other.hobbies_[i].c_str()));
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

