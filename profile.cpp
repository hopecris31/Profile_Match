
/**
 * Creates a Profile object.  A Profile object contains a user's name, city, country, age, gender, and a list of hobbies.
 */

#include <iostream>
#include <utility>
#include <sstream>
#include "profile.h"

using namespace std;

int const MAX_CHARS = 32767;

/**
 * Default constructor for Profile class.
 */
Profile::Profile(string name, int age, string city, string country, vector<string> hobbies, Gender gender) :
name_(std::move(name)), age_(age), city_(std::move(city)), country_(std::move(country)),
hobbies_(std::move(hobbies)), gender_(gender){
}


Profile Profile::get_user_info(){

    string name = input_name();
    int age = input_age();
    string city = input_city();
    string country = input_country();
    vector<string> hobbies = input_hobbies();
    Gender gender = input_gender();

    return Profile(name, age, city, country, hobbies, gender);
}

int Profile::percent_match(const Profile& other) {

    //if not same sexual preference:
    //break, profiles not compatible
    // else:
    //
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
    cout << "enter city and state: ";
    cin.ignore(MAX_CHARS, '\n');
    getline(cin, city);

    return city;
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
        cout << "enter hobby OR 'done': \n";
        cin >> user_input;
    }
    return to_return;

}

vector<string> Profile::input_qualities() {
    vector<string> to_return;
    return to_return;
}

int Profile::get_age_difference(const Profile& other) {
    int num_in_common = 0;
    return num_in_common;
}

int Profile::get_distance(const Profile& other) {
    int distance = 1000;
    return distance;
}

bool Profile::same_country(const Profile& other) {
    return false;
}

bool Profile::same_city(const Profile& other) {
    return false;
}

int Profile::get_common_hobbies(const Profile& other){
    int common_hobbies = 0;
    return common_hobbies;
}

int Profile::get_common_qualities(const Profile& other) {
    int common_qualities = 0;
    return common_qualities;
}
