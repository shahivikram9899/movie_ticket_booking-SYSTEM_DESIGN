#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie;
class Screen;
class ShowSeat;

class Show {
private:
    int showId;
    Movie* movie;             // Aggregation
    Screen* screen;           // Association/reference to existing screen
    string startTime;
    vector<ShowSeat> showSeats; // Composition

public:
    Show(int showId, Movie* movie, Screen* screen, string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }

    void createShowSeats();
    vector<ShowSeat>& getShowSeats() { return showSeats; }
    void displaySeats() const;
};
