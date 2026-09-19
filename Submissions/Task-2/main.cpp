#include "gener.h"
#include <iostream>
using namespace std;



class TMovie{
private: 
  string title;
  string director;
  int year;
  int generFlags;
  float score;

public:
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

public:
  TMovieNode(TMovie* m){
    movie = m; 
    nextMovie = nullptr;
  };

  ~TMovieNode(){
    delete movie;
  }

};


int main() {

  return 0;
}