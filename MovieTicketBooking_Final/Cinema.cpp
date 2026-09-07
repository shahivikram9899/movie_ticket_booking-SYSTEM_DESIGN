#include <string>
#include <vector>
using namespace std;

class Screen;
class Movie;
class Show;

class Cinema {
private:
    string name;
    vector<Screen> screens; // Composition
    vector<Movie> movies;
    vector<Show> shows;

public:
    Cinema(string name) {
        this->name = name;
    }

    string getName() const { return name; }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void addShow(const Show& show) {
        shows.push_back(show);
    }

    vector<Screen>& getScreens() { return screens; }
    vector<Movie>& getMovies() { return movies; }
    vector<Show>& getShows() { return shows; }
};
