
#ifndef UNTITLED2_PROFILE_H
#define UNTITLED2_PROFILE_H

#include <vector>

using namespace std;

int const MAX_CHARS = 32767;

enum Gender {
    MALE,
    FEMALE,
    OTHER
};

enum Orientation {
    HETEROSEXUAL,
    HOMOSEXUAL,
    BISEXUAL,
};

class Profile {

private:
    string name_;
    int age_;
    string city_;
    string state_;
    string country_;
    vector<string> hobbies_;
    vector<string> qualities_;
    Gender gender_;

    static string input_name();
    static int input_age();
    static string input_city();
    static string input_state();
    static string input_country();
    static vector<string> input_hobbies();
    static Gender input_gender();

    int get_age_difference(const Profile& other);
    int get_distance(const Profile& other);
    bool same_country(const Profile& other);
    bool same_city(const Profile& other);



    string hobbies_string();
    string gender_string();

public:
    explicit Profile(string name="", int age=0, string city="", string state="", string country="", vector<string> hobbies={},
            Gender gender=OTHER);
    string to_string();
    static Profile get_user_info();
    int percent_match(const Profile& other);
    int get_hobby_points(const Profile& other);

};

#endif //UNTITLED2_PROFILE_H
