#include "gener.h"
#include <iostream>
using namespace std;

class TMovie{
private: 
  string title;
  string director;
  int year;
  EMovieGenreType genreFlags;
  float score;

public:
  TMovie(string t, string d, int y, EMovieGenreType g, float s){
    title       = t; 
    director    = d;
    year        = y;
    genreFlags  = g;
    score       = s;
  }

  string GetTitle(){
    return title;
  }
  string GetDirector(){
    return director;
  }
  int GetYear(){
    return year;
  }
  string GetGenreFlags(){
    return GenerToFlagStrings(genreFlags);
  }
  float GetScore(){
    return score;
  }
  bool HasGenre(EMovieGenreType flag) {
    return (static_cast<int>(genreFlags) & static_cast<int>(flag)) != 0;
}


  void PrintInfo() const {
		std::cout << "Title: " << title << "\nDirector: " << director
			<< "\nYear: " << year << "\nGenres: " << GenerToFlagStrings(genreFlags)
			<< "\nRating: " << score << "/10\n";
	}
};


class TMovieNode{
private:
  TMovie* movie;
  TMovieNode* nextMovie; 
  TMovieNode* prevMovie; 

public:
  TMovieNode(TMovie* m){
    movie = m; 
    nextMovie = nullptr;
    prevMovie = nullptr; 
  };

  ~TMovieNode(){
    delete movie;
  }

  TMovie* GetMovie(){
    return movie;
  }

  TMovieNode* GetNext(){
    return nextMovie;
  }

  void SetNext(TMovieNode* n){
    nextMovie = n;
  }

  TMovieNode* GetPrev(){
    return prevMovie;
  }

  void SetPrev(TMovieNode* n){
    prevMovie = n;
  }


};

typedef bool (*FCheckMovie)(TMovie*, void*);

class TMovieList{
private:
  TMovieNode* head;
  TMovieNode* tail;
  int size;
  
public:
  TMovieList(){
    head =  new TMovieNode(nullptr); // initilise one dummy node
    tail = head; // starts at the same place in a empthy "list"
    size = 0; 
  }

  ~TMovieList(){
    TMovieNode* current = head;
    while (current != nullptr) {
        TMovieNode* nextNode = current->GetNext();  
        delete current;                           
        current = nextNode;                      
    }     
    }

  int GetSize(){    
    return size;
  }

  //Time complexity is O(1) and in singel linked version it was O(n)
  void Append(TMovie* addMovie){
    TMovieNode* newNode = new TMovieNode(addMovie);
    tail->SetNext(newNode);
    newNode->SetPrev(tail);
    tail = newNode;
    size++;
  }
    
  void Prepend(TMovie* addMovie){ // Prepend - To add or attach something to the beginning of something else
    TMovieNode* newNode = new TMovieNode(addMovie);
    newNode->SetNext(head->GetNext());
    newNode->SetPrev(head);
    if(head->GetNext() != nullptr){
      head->GetNext()->SetPrev(newNode); 
    }else{
      tail = newNode;
    }
    head->SetNext(newNode);
    size++;
  }

  TMovie* GetAtIndex(int index){
    TMovieNode* theMovie = head;
    if (index < 0 ){
      return nullptr;
    }else{
      int position = index;
      for(int i = 0; i <= position; i ++){
        theMovie = theMovie->GetNext();
        if (theMovie == nullptr) return nullptr;
    }
    }

    return  theMovie->GetMovie();
  }

  void Remove(int index){
    TMovieNode* prevMovie = head;

    if (index < 0){
       return;
    }else{
    for(int i = 0; i < index; i++){
        prevMovie = prevMovie->GetNext();
        if(prevMovie == nullptr){
          cout << "Ther is no movie that can be removed here" << endl;
          return;
        }
    }}

    TMovieNode* rmMovie = prevMovie->GetNext();

    if(rmMovie == nullptr) {return;}

    prevMovie->SetNext( rmMovie->GetNext() );
    if (rmMovie->GetNext() != nullptr){
        rmMovie->GetNext()->SetPrev( prevMovie);

    } else {
        tail = prevMovie ;
    }

    delete rmMovie;
    size --;
}


TMovie* SearchFor(FCheckMovie check, void* criteria) {
    TMovieNode* current = head->GetNext();      
    while (current != nullptr) {
        if ( check(current->GetMovie(), criteria) ) {             
            return current->GetMovie();
        }
        current = current->GetNext();
    }
    return nullptr;
}

};  


bool SearchByTitle(TMovie* movie, void* criteria) {
    string* match = static_cast<string*>(criteria); 
    return movie->GetTitle() == *match;
}

bool SearchByDirector(TMovie* movie, void* criteria) {
    string* match = static_cast<string*>(criteria);  
    return movie->GetDirector() == *match;
}

bool SearchByGenre(TMovie* movie, void* criteria) {
    EMovieGenreType* match = static_cast<EMovieGenreType*>(criteria);
    return movie->HasGenre(*match);
}


void PrintAllMovies(TMovieList& movieList) {
    if (movieList.GetSize() == 0) {
        cout << "The movie list is empty." << endl;
        return;
    }

    for (int i = 0; i < movieList.GetSize(); i++) {
        TMovie* movie = movieList.GetAtIndex(i);

        cout << "Movie " << i + 1 << endl;
        movie->PrintInfo();
        cout << "-------------------" << endl;
    }
}


int main() {
  	TMovieList movieList;
    // Hardcoded test data (mix of Append and Prepend)
    movieList.Append(new TMovie("Inception", "Christopher Nolan", 2010, static_cast<EMovieGenreType>(Action | SciFi), 8.8f));
    movieList.Append(new TMovie("Interstellar", "Christopher Nolan", 2014, static_cast<EMovieGenreType>(Drama | SciFi), 8.7f));
    movieList.Append(new TMovie("The Dark Knight", "Christopher Nolan", 2008, static_cast<EMovieGenreType>(Action | Crime | Drama), 9.0f));
    movieList.Prepend(new TMovie("Pulp Fiction", "Quentin Tarantino", 1994, static_cast<EMovieGenreType>(Crime | Drama), 8.9f));
    movieList.Append(new TMovie("Django Unchained", "Quentin Tarantino", 2012, static_cast<EMovieGenreType>(Action | Drama), 8.5f));
    movieList.Prepend(new TMovie("The Shining", "Stanley Kubrick", 1980, Horror, 8.4f));
    movieList.Append(new TMovie("2001: A Space Odyssey", "Stanley Kubrick", 1968, static_cast<EMovieGenreType>(Adventure | SciFi), 8.3f));
    movieList.Prepend(new TMovie("Get Out", "Jordan Peele", 2017, static_cast<EMovieGenreType>(Horror | Thriller), 7.8f));
    movieList.Append(new TMovie("Spirited Away", "Hayao Miyazaki", 2001, static_cast<EMovieGenreType>(Animation | Fantasy | Adventure), 8.6f));
    movieList.Prepend(new TMovie("The Grand Budapest Hotel", "Wes Anderson", 2014, static_cast<EMovieGenreType>(Comedy | Crime), 8.1f));
    movieList.Append(new TMovie("La La Land", "Damien Chazelle", 2016, static_cast<EMovieGenreType>(Comedy | Drama | Romance), 8.0f));
    movieList.Prepend(new TMovie("Free Solo", "Jimmy Chin", 2018, static_cast<EMovieGenreType>(Documentary | Adventure), 8.1f));

    PrintAllMovies(movieList);
    
    int choice = 0;

    while (choice != 7) {
        cout << "\n========== MOVIE MENU ==========" << endl;
        cout << "1. Show all movies" << endl;
        cout << "2. Search by title" << endl;
        cout << "3. Search by director" << endl;
        cout << "4. Search by genre" << endl;
        cout << "5. Remove movie" << endl;
        cout << "6. Get at index" << endl;
        cout << "7. Exit " << endl;
        cout << "Choose an option: ";

        cin >> choice;
        cin.ignore();

        cout << endl;

        if (choice == 1) {
          PrintAllMovies(movieList);
        } else if (choice == 2) {
            string title;
            cout << "Enter title: ";
            getline(cin, title);
            cout << endl;

            TMovie* movie = movieList.SearchFor(SearchByTitle, &title);
            if (movie != nullptr) movie->PrintInfo();
            else cout << "Movie not found." << endl;
        } else if (choice == 3) {
            string director;
            cout << "Enter director: ";
            getline(cin, director);
            cout << endl;


            TMovie* movie = movieList.SearchFor(SearchByDirector, &director);
            if (movie != nullptr){
              movie->PrintInfo();
            } else {
              cout << "Movie not found." << endl;
            }
        } else if (choice == 4){
            for (int i = 0; i < 12; i++) {
                cout << i + 1 << ". " << GenerToFlagStrings(1 << i) << endl;
            }
            int genreChoice;
            cout << "Choose genre: ";
            cin >> genreChoice;
            cout << "--------------" << endl;
            cin.ignore();

            if (genreChoice < 1 || genreChoice > 12) {
                cout << "Invalid genre." << endl;
            } else {
                EMovieGenreType genre = static_cast<EMovieGenreType>(1 << (genreChoice - 1));
                TMovie* movie = movieList.SearchFor(SearchByGenre, &genre);
                if (movie != nullptr) movie->PrintInfo();
                else cout << "Movie not found." << endl;
            }

        } else if (choice == 5){
            string title;
            cout << "Enter title to remove: ";
            getline(cin, title);

            int foundIndex = -1;                      
            for (int i = 0; i < movieList.GetSize(); i++) {
                TMovie* movie = movieList.GetAtIndex(i);
                if (movie->GetTitle() == title) {      
                    foundIndex = i ;                  
                    break;
                }
            }

            if (foundIndex == -1) {
                cout << "Movie not found." << endl;
            } else {
                movieList.Remove(foundIndex);                
                cout << "Removed." << endl;
            }
        
        } else if (choice == 6) {  
            int number;
            cout << "Enter movie number: ";
            cin >> number;
            cin.ignore();

            TMovie* movie = movieList.GetAtIndex(number - 1);
            if (movie != nullptr) movie->PrintInfo();
            else cout << "No movie at that number." << endl;

        } else if (choice == 7){
          break;
        } else {
          cout << "Invalid input" << endl;
        }
      }


}