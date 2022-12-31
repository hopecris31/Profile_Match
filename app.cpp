#include <iostream>
#include <vector>
#include "Profile.h"

using namespace std;

int main() {
    Profile user = Profile::get_user_info();
    cout << user.to_string() << endl;

    vector<Profile> profiles;

    Profile hope = Profile("Hope Crisafi", 20, "Bay Village", "Ohio", "United States",
                           {"technology", "artificial intelligence", "space", "reading", "coding"}, FEMALE);
    profiles.push_back(hope);
    Profile elon = Profile("Elon Musk", 51, "Austin", "Texas", "United States",
                           {"reading", "coding", "engineering", "rockets", "Artificial Intelligence", "cars"}, MALE);
    profiles.push_back(elon);
    Profile kaitlyn = Profile("Kaitlyn Ehmann", 21, "Bloomingdale", "Illinois", "United States",
                              {"hockey", "netflix", "shopping", "painting", "card games", "science", "genetic science"}, FEMALE);
    profiles.push_back(kaitlyn);
    Profile josh = Profile("Josh Sciba", 37, "Schenectady", "New York", "United States",
                           {"hockey", "family", "coaching", "biking", "music", "coaching"}, MALE);
    profiles.push_back(josh);
    Profile celeste = Profile("Celeste Beaudoin", 20, "Toronto", "Ontario", "Canada",
                              {"hockey", "formula 1", "fashion", "snorkeling"}, FEMALE);
    profiles.push_back(celeste);
    Profile chris = Profile("Chris Ardito", 37, "Schenectady", "New York", "United States",
                            {"hockey", "running", "fitness", "hiking", "organization", "recruiting", "coaching"}, MALE);
    profiles.push_back(chris);
    Profile clugg = Profile("Clugg Nuggman", 40, "Palo Alto", "California", "United States",
                            {"government", "music", "hunting", "renovation", "swimming"}, MALE);
    profiles.push_back(clugg);
    Profile papa = Profile("Papa Makincheese", 70, "Erie", "Pennsylvania", "United States",
                           {"construction", "coding", "sports", "watching tv", "baking"}, MALE);
    profiles.push_back(papa);

    Profile highest_match_profile;
    int highest_match_score = 0;
    for(auto& profile: profiles) {
        int match_points = user.calc_match_points(profile);
        if (match_points > highest_match_score) {
            highest_match_score = match_points;
            highest_match_profile = profile;
        }
    }

    cout << "Your Best Profile Match is: " + highest_match_profile.get_name() << endl;
    cout << "Match points with this profile: " << highest_match_score << endl;
    cout << highest_match_profile.to_string();



    return 0;
}
