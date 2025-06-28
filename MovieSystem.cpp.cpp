#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Tree Node class structure
class TreeNode {
public:
    unordered_map<char, TreeNode*> children;
    vector<string> movies; // Store movies that end at this node
};

class MovieRecommendationSystem {
private:
    // A map of movie moods to a Tree root (for movie suggestions)
    unordered_map<string, TreeNode*> movieDatabase;

    // Insert a movie into the Tree
    void insertMovie(TreeNode* root, const string& movie) {
        TreeNode* current = root;
        for (char c : movie) {
            if (!current->children.count(c)) {
                current->children[c] = new TreeNode();
            }
            current = current->children[c];
        }
        current->movies.push_back(movie); // Store the movie name
    }

    // Search for movies based on a prefix
    void searchMovies(TreeNode* root, const string& prefix, vector<string>& result) {
        TreeNode* current = root;
        for (char c : prefix) {
            if (!current->children.count(c)) return; // No match for the prefix
            current = current->children[c];
        }
        collectMovies(current, result); // Collect all movies starting with the prefix
    }

    // Collect all movies from a given Tree node
    void collectMovies(TreeNode* node, vector<string>& result) {
        result.insert(result.end(), node->movies.begin(), node->movies.end());
        for (auto& child : node->children) {
            collectMovies(child.second, result);
        }
    }

public:
    MovieRecommendationSystem() {
        // Populate movie database for different moods with Tree roots
        movieDatabase["action"] = new TreeNode();
        movieDatabase["comedy"] = new TreeNode();
        movieDatabase["horror"] = new TreeNode();
        movieDatabase["romance"] = new TreeNode();
        movieDatabase["sci-fi"] = new TreeNode();
        movieDatabase["drama"] = new TreeNode();

        // Insert movies into corresponding Tree for each mood
        insertMovie(movieDatabase["action"], "John Wick");
        insertMovie(movieDatabase["action"], "Gladiator");
        insertMovie(movieDatabase["action"], "War");
        insertMovie(movieDatabase["action"], "Mad Max: Fury Road");
        insertMovie(movieDatabase["action"], "Dhoom 3");
        insertMovie(movieDatabase["action"], "Baaghi");
        insertMovie(movieDatabase["action"], "KGF:Chp-2");
        insertMovie(movieDatabase["action"], "Shershaah");

        insertMovie(movieDatabase["comedy"], "Chup Chup Ke ");
        insertMovie(movieDatabase["comedy"], "The Hangover");
        insertMovie(movieDatabase["comedy"], "Superbad");
        insertMovie(movieDatabase["comedy"], "Hera Pheri");
        insertMovie(movieDatabase["comedy"], "Step Brothers");
        insertMovie(movieDatabase["comedy"], "Dhamaal ");
        insertMovie(movieDatabase["comedy"], "Golmaal: Fun Unlimited");
        insertMovie(movieDatabase["comedy"], "Fukrey");
        insertMovie(movieDatabase["comedy"], "Golmaal: Fun Unlimited");
        insertMovie(movieDatabase["comedy"], "Bhool Bhulaiyaa");

        insertMovie(movieDatabase["horror"], "Tumbbad");
        insertMovie(movieDatabase["horror"], "Bhool Bhulaiyaa 2");
        insertMovie(movieDatabase["horror"], "A Quiet Place");
        insertMovie(movieDatabase["horror"], "1920 ");
        insertMovie(movieDatabase["horror"], "Raaz");
        insertMovie(movieDatabase["horror"], "The House Next Door");
        insertMovie(movieDatabase["horror"], "Stree");

        insertMovie(movieDatabase["romance"], "Kabir Singh");
        insertMovie(movieDatabase["romance"], "Pride and Prejudice");
        insertMovie(movieDatabase["romance"],"Tamasha");
        insertMovie(movieDatabase["romance"], "The Notebook");
        insertMovie(movieDatabase["romance"], "Kabir Singh");
        insertMovie(movieDatabase["romance"],"Yeh Jawaani Hai Deewani");

        insertMovie(movieDatabase["sci-fi"], "Inception");
        insertMovie(movieDatabase["sci-fi"], "Interstellar");
        insertMovie(movieDatabase["sci-fi"], "The Matrix");
        insertMovie(movieDatabase["sci-fi"], "Robot ");
        insertMovie(movieDatabase["sci-fi"], "2.0 ");
        insertMovie(movieDatabase["sci-fi"], "Ra.One");
        insertMovie(movieDatabase["sci-fi"], "Koi... Mil Gaya");
        

        insertMovie(movieDatabase["drama"], "Taare Zameen Par");
        insertMovie(movieDatabase["drama"], "Forrest Gump");
        insertMovie(movieDatabase["drama"], "Forrest Gump");
        insertMovie(movieDatabase["drama"], "Forrest Gump");
        insertMovie(movieDatabase["drama"], "The Shawshank Redemption");
        insertMovie(movieDatabase["drama"], "Fight Club");
    }

    // Recommend movies by mood and optional prefix
    vector<string> recommendMovies(const string& mood, const string& prefix = "") {
        vector<string> result;
        if (movieDatabase.find(mood) != movieDatabase.end()) {
            TreeNode* root = movieDatabase[mood];
            if (!prefix.empty()) {
                searchMovies(root, prefix, result);
            } else {
                collectMovies(root, result);
            }
        }
        return result;
    }

    // Display available moods/genres
    void displayMoods() {
        cout<<"---------------------------------------------------------"<<endl;
        cout << "Available moods/genres: \n";
        for (auto& entry : movieDatabase) {
            cout << "- " << entry.first << endl;
        }
        cout<<"---------------------------------------------------------"<<endl;
    }

    // Interactive menu
    void Menu() {
        int choice;
        string userMood, prefix;

        while (true) {
            cout<<"\n=========================================================";
            cout << "\n------  Movie Recommendation System  -----\n";
            cout << "1. Display available moods/genres\n";
            cout << "2. Get movie recommendations\n";
            cout << "3. Search for movies by prefix\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout<<"========================================================="<<endl;

            switch (choice) {
                case 1:
                    displayMoods();
                    break;

                case 2:
                    
                    cout << "Enter your mood :";
                    cin >> userMood;
                    cout<<"---------------------------------------------------------"<<endl;
                    {
                        vector<string> recommendations = recommendMovies(userMood);
                        if (recommendations.empty()) {
                            cout << "No movies found for '" << userMood << "'.\n";
                        } else {
                            cout<<"Recommended movies for mood '"<<userMood<<"'.\n"<<endl;
                            for (const string& movie : recommendations) {
                                cout << "- " << movie << endl;
                            }
                        }
                    }
                    break;
                    cout<<"---------------------------------------------------------"<<endl;

                case 3:
                    cout << "Enter your mood :";
                    cin >> userMood;
                    cout << "Enter movie prefix : ";
                    cin >> prefix;
                    cout<<"---------------------------------------------------------"<<endl;
                    {
                        vector<string> recommendations = recommendMovies(userMood, prefix);
                        if (recommendations.empty()) {
                            cout << "No movies found for '" << userMood << "' with prefix '" << prefix << "'.\n";
                        } else {
                            cout<<"Movie found..."<<endl;
                            for (const string& movie : recommendations) {
                                cout << "- " << movie << endl;
                            }
                        }
                    }
                    break;
                    cout<<"---------------------------------------------------------"<<endl;

                case 4:
                    cout<<"------|Thanks For Use Movie Recommendation System|-------"<<endl;
                    cout<<"-------------------   Goodbye!   ------------------------\n";
                    cout<<"=========================================================\n\n"<<endl;
                    return;
                    

                default:
                    cout << "Invalid choice. Try again.\n";
            }

            
        }
    }
};

int main() {
    MovieRecommendationSystem system;
    system.Menu(); // Launch interactive menu
    return 0;
}