#pragma once
#include <string>
using namespace std;

enum EMovieGenreType {
    Action      = 0x0001,
    Adventure   = 0x0002,
    Animation   = 0x0004,
    Comedy      = 0x0008,
    Crime       = 0x0010,
    Documentary = 0x0020,
    Drama       = 0x0040,
    Fantasy     = 0x0080,
    Horror      = 0x0100,
    SciFi       = 0x0200,
    Romance     = 0x0400,
    Thriller    = 0x0800,
};

static string GenerToFlagStrings(int generFlags){
    string gener;
    if (generFlags & EMovieGenreType::Action)gener += "Action ";
    if (generFlags & EMovieGenreType::Adventure)gener += "Adventure ";
    if (generFlags & EMovieGenreType::Animation)gener += "Animation ";
    if (generFlags & EMovieGenreType::Comedy)gener += "Comedy ";
    if (generFlags & EMovieGenreType::Crime)gener += "Crime ";
    if (generFlags & EMovieGenreType::Documentary)gener += "Documentary ";
    if (generFlags & EMovieGenreType::Drama)gener += "Drama ";
    if (generFlags & EMovieGenreType::Fantasy)gener += "Fantasy ";
    if (generFlags & EMovieGenreType::Horror)gener += "Horror ";
    if (generFlags & EMovieGenreType::SciFi)gener += "SciFi ";
    if (generFlags & EMovieGenreType::Romance)gener += "Romance ";
    if (generFlags & EMovieGenreType::Thriller)gener += "Thriller ";
    if (gener.empty()) {
        return "Unkown gener or None";
    }
    return gener;
};



