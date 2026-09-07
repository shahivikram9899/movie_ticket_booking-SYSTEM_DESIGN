#include <iostream>
#include <string>
using namespace std;

// Encapsulation: movie data is private.
class Movie {
private:
    string title;
    string language;
    int duration;

public:
    Movie(string title, string language, int duration) {
        this->title = title; // this keyword
        this->language = language;
        this->duration = duration;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }

    void display() const {
        cout << title << " (" << language << ", "
             << duration << " min)" << endl;
    }
};
