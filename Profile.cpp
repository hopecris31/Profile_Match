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

int Profile::calc_match_points(const Profile& other) {
    int match_points = 0;

    if (this->dating_){
        if (this->gender_ == other.gender_) {
            return 0;
        }
    } else {
        match_points += this->calc_age_points(other);
        match_points += this->calc_distance_points(other);
        match_points += this->calc_city_points(other);
        match_points += this->calc_country_points(other);
        match_points += this->calc_hobby_points(other);

        return match_points;
    }
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

string Profile::get_name() {
    return this->name_;
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
    cin.ignore(MAX_CHARS, '\n');
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

bool Profile::input_dating() {
    char user_input;
    cout << "Enter 'y' if looking to match profiles for dating, or any other character if not: " << endl;
    cin >> user_input;
    if (reinterpret_cast<const char *>(user_input) == "y") {
    }
    return false;
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

int Profile::calc_age_points(const Profile &other) {
    //if age is between 18-29 : youth age criteria
    //if 30 or older: age gap is more tolerated
    if (this->is_under_30()) {
        return calc_under_30_age_points(other);
    } else {
        return calc_age_points_default(other);
    }
}

int Profile::calc_distance_points(const Profile &other) {
    float distance = this->get_distance(other);
    if (distance <= 15) {
        return 13;
    } else if (distance <= 25) {
        return 11;
    } else if (distance <= 50) {
        return 9;
    } else if (distance <= 150) {
        return 7;
    } else if (distance <= 250) {
        return 3;
    } else {
        return 1;
    }
}

int Profile::calc_city_points(const Profile &other) {
    if (this->in_same_city(other)) {
        return 10;
    } else {
        return 0;
    }
}

int Profile::calc_country_points(const Profile &other) {
    if (this->in_same_country(other)) {
        return 10;
    } else {
        return 0;
    }
}

int Profile::calc_hobby_points(const Profile& other) {
    int num_hobby_similarity = this->get_hobbies_similarity(other);

    if(num_hobby_similarity > 3) {
        return 35;
    } else if (num_hobby_similarity == 3) {
        return 30;
    } else if (num_hobby_similarity == 2) {
        return 25;
    } else if (num_hobby_similarity == 1) {
        return 20;
    } else {
        return 0;
    }
}


int Profile::get_age_difference(const Profile& other) {
    int difference = this->age_ - other.age_;
    return abs(difference);
}

bool Profile::is_under_30() const{
    return this->age_ < 30;
}

int Profile::calc_under_30_age_points(const Profile& other) {
    int age_difference = get_age_difference(other);
    if (age_difference <= 2) {
        return 13;
    } else if (age_difference <= 4) {
        return 11;
    } else if (age_difference <= 6) {
        return 9;
    } else if (age_difference <= 8) {
        return 7;
    } else {
        return 3;
    }
}

int Profile::calc_age_points_default(const Profile &other) {
    int age_difference = get_age_difference(other);
    if (age_difference <= 4) {
        return 13;
    } else if (age_difference <= 8) {
        return 11;
    } else if (age_difference <= 12) {
        return 9;
    } else if (age_difference <= 16) {
        return 7;
    } else {
        return 3;
    }
}

float Profile::get_distance(const Profile& other) {
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

bool Profile::in_same_city(const Profile& other) {
    return this->city_ == other.city_;
}

bool Profile::in_same_country(const Profile& other) {
    return this->country_ == other.country_;
}

int Profile::get_hobbies_similarity(const Profile& other){
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

