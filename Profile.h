
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
    /**
     * Instance Variables
     */
    string name_;
    int age_;
    string city_;
    string state_;
    string country_;
    vector<string> hobbies_;
    vector<string> qualities_;
    Gender gender_;
    bool dating_;

    /**
     * String Methods
     */
    [[nodiscard]] string hobbies_string() const;
    [[nodiscard]] string gender_string() const;
    [[nodiscard]] string dating_string() const;

    /**
     * Input Methods
     */
    static string input_name();
    static int input_age();
    static string input_city();
    static string input_state();
    static string input_country();
    static vector<string> input_hobbies();
    static Gender input_gender();
    static bool input_dating();

    /**
     * Calc Points Methods
     */
    int calc_age_points(const Profile& other);
    int calc_distance_points(const Profile& other);
    int calc_city_points(const Profile& other);
    int calc_country_points(const Profile& other);
    int calc_hobby_points(const Profile& other);

    /**
     * Calc Points Methods Helpers
     */
    int get_age_difference(const Profile& other);
    [[nodiscard]] bool is_under_30() const;
    int calc_under_30_age_points(const Profile& other);
    int calc_age_points_default(const Profile& other);
    [[nodiscard]] float get_distance(const Profile& other) const;
    [[nodiscard]] bool in_same_city(const Profile& other) const;
    [[nodiscard]] bool in_same_country(const Profile& other) const;
    [[nodiscard]] int get_hobbies_similarity(const Profile& other) const;


public:
   /**
    * Constructor
    */
    explicit Profile(string name="", int age=0, string city="", string state="", string country="", vector<string> hobbies={},
            Gender gender=OTHER, bool dating=false);

    string to_string();
    static Profile get_user_info();
    int calc_match_points(const Profile& other);
    [[nodiscard]] string get_name() const;
    [[nodiscard]] int get_age() const;
    [[nodiscard]] string get_city () const;
    [[nodiscard]] string get_state() const;
    [[nodiscard]] string get_country() const;
    [[nodiscard]] vector<string> get_hobbies() const;
    [[nodiscard]] Gender get_gender() const;
    [[nodiscard]] bool is_dating() const;
};

#endif //UNTITLED2_PROFILE_H
