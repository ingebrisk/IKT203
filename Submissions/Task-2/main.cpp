#include "gener.h"
#include <iostream>
using namespace std;



class TMovie{
private: 
  string title;
  string director;
  int year;
  EMovieGenreType generFlags;
  float score;

public:
  TMovie(string t, string d, int y, EMovieGenreType g, float s){
    title       = t; 
    director    = d;
    year        = y;
    generFlags  = g;
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
  string GetGenerFlags(){
    return GenerToFlagStrings(generFlags);
  }
  float GetScore(){
    return score;
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

class TMovieList{
private:
  TMovieNode* head;
  TMovieNode* tail;
  
  
public:
  TMovieList(){
    head =  new TMovieNode(nullptr); // initilise one dummy node
    tail = head; // starts at the same place in a empthy "list"
  }

  ~TMovieList(){
    TMovieNode* current = head;
    while (current != nullptr) {
        TMovieNode* nextNode = current->GetNext();  
        delete current;                           
        current = nextNode;                      
    }     
    tail = head;
    }

  void Append(TMovie* addMovie){
    TMovieNode* newNode = new TMovieNode(addMovie);
    tail->SetNext(newNode);
    newNode->SetPrev(tail);
    tail = newNode;
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
    tail->SetPrev(newNode);
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
      cout << "no valid input"<<endl; return;
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
    
}

  void Reverse(){
    TMovieNode* reverseList = head;
    TMovieNode* origlList = head; 

    while(origlList->GetNext() != nullptr){
      reverseList ->SetNext(head->GetNext());
      origlList = origlList->GetNext();
    }

    //not done and wrong 
  }
  


};   


int main() {
  TMovieList list;
  list.Append(new TMovie("A", "Dir", 2000, Action, 7.5f));
  list.Append(new TMovie("B", "Dir", 2001, Comedy, 8.0f));
  list.Append(new TMovie("C", "Dir", 2002, Drama, 6.0f));

  list.Remove(1);   // fjern B (midten)
  cout << list.GetAtIndex(0)->GetTitle() << endl;   // A
  cout << list.GetAtIndex(1)->GetTitle() << endl;   // C

  list.Remove(1);   // fjern C (siste)
  list.Append(new TMovie("D", "Dir", 2003, Horror, 7.0f));
  cout << list.GetAtIndex(1)->GetTitle() << endl;   // D
}