
#ifndef UNTITLED2_PROFILE_H
#define UNTITLED2_PROFILE_H

#include <vector>
#include <string>

using namespace std;

int const MAX_CHARS = 32767;

enum Gender {
    MALE,
    FEMALE,
    OTHER
};

class Profile {

private:
    //instance variables
    string name_;
    int age_;
    string city_;
    string state_;
    string country_;
    vector<string> hobbies_;
    vector<string> qualities_;
    Gender gender_;
    bool dating_;

    //string methods
    string hobbies_string();
    string gender_string();

    //input methods
    static string input_name();
    static int input_age();
    static string input_city();
    static string input_state();
    static string input_country();
    static vector<string> input_hobbies();
    static Gender input_gender();
    static bool input_dating();

    //calc points methods
    int calc_age_points(const Profile& other);
    int calc_distance_points(const Profile& other);
    int calc_city_points(const Profile& other);
    int calc_country_points(const Profile& other);
    int calc_hobby_points(const Profile& other);

    //calc points method helpers
    int get_age_difference(const Profile& other);
    [[nodiscard]] bool is_under_30() const;
    int calc_under_30_age_points(const Profile& other);
    int calc_age_points_default(const Profile& other);
    float get_distance(const Profile& other);
    bool in_same_city(const Profile& other);
    bool in_same_country(const Profile& other);
    int get_hobbies_similarity(const Profile& other);


public:
    //Constructor
    explicit Profile(string name="", int age=0, string city="", string state="", string country="", vector<string> hobbies={},
            Gender gender=OTHER, bool dating=false);

    string to_string();
    static Profile get_user_info();
    int calc_match_points(const Profile& other);
    string get_name();
};

#endif //UNTITLED2_PROFILE_H
