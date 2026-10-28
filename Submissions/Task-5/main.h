#pragma once
#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


string GenerateAccountNumber(){
    string accountNumber = "";
     for (int i = 0; i < 11; i++) {
        accountNumber += to_string(rand() % 10);   
        if (i == 3 || i == 5) {
            accountNumber += '.';                 
        }
    }
    return accountNumber;
};


string firstNames[70] = {
    "Frida", "Ole", "Hans", "Mina", "Karin", "Kaja", "Catja", "Conrad", "Bjorn", "Ingrid",
    "Lars", "Sofie", "Emil", "Nora", "Jonas", "Thea", "Henrik", "Ida", "Magnus", "Sara",
    "Erik", "Maja", "Sander", "Emma", "Tobias", "Julie", "Aksel", "Hanna", "Martin", "Vilde",
    "Jakob", "Selma", "Oskar", "Live", "Elias", "Tiril", "Kristian", "Amalie", "Mathias", "Leah",
    "Sindre", "Marte", "Even", "Silje", "Halvor", "Astrid", "Torstein", "Ragnhild", "Vegard", "Eline","Anders", "Ingeborg", "Sigurd", "Hedda", "Filip", "Mathilde", "Adrian", "Aurora", "Johannes", "Linnea",
"Petter", "Signe", "Viktor", "Oda", "Kasper", "Tuva", "Fredrik", "Synne", "Mikkel", "Ronja"
};

string lastNames[70] = {
    "Hansen", "Johansen", "Olsen", "Larsen", "Andersen", "Pedersen", "Nilsen", "Kristiansen", "Jensen", "Karlsen",
    "Johnsen", "Pettersen", "Eriksen", "Berg", "Haugen", "Hagen", "Johannessen", "Andreassen", "Jacobsen", "Dahl",
    "Jorgensen", "Halvorsen", "Lund", "Moen", "Iversen", "Strand", "Solberg", "Bakken", "Lie", "Kristoffersen",
    "Fredriksen", "Foss", "Fjeld", "Fosse", "Finstad", "Flaten", "Sorensen", "Hammerstad", "Nordmann", "Aas",
    "Holm", "Svendsen", "Rasmussen", "Martinsen", "Knutsen", "Berntsen", "Sandvik", "Myhre", "Ruud", "Vik", "Lunde", "Ellingsen", "Nygaard", "Torgersen", "Brekke", "Gundersen", "Mikkelsen", "Eide", "Thorsen", "Antonsen",
    "Ness", "Amundsen", "Wold", "Engen", "Hauge", "Fjellheim", "Fagerli", "Bjerke", "Stene", "Tangen"
};

time_t GenerateRandomTimestamp(){
    tm t = {};
    t.tm_year = 2024 - 1900; // gives 2024
    t.tm_mon = 0;
    t.tm_mday = 1;
    time_t start = mktime(&t);

    int day = rand()%365; // 365 days in a year.  
    int hour = rand()%24; // 24 hours in a day. 
    int minute = rand()%60;
    int second = rand()%60;

    return start + day * 86400 + hour * 3600 + minute * 60 + second;
}


time_t CreateTimestamp(int year, int month, int day, int hour, int minute, int second) {
    tm date = {};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;     // so 1 = January, like on a calendar
    date.tm_mday = day;
    date.tm_hour = hour;
    date.tm_min = minute;
    date.tm_sec = second;
    date.tm_isdst = -1;          // let the system decide summer time
    return mktime(&date);
}