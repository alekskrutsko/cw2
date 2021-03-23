#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include "./lib/SHA256.h"
using namespace std;

class User;
class Flights;
class CityRoute;
class InternationalRoute;
class Buses;
template<class T>
class Order;
void mainMenu();
void arrowMenu(vector<string>, int8_t&);
int8_t getPushedCharCode();
void readFile(vector<User>&, const string&);
void adminAccount();
void userAccount();
string getLoginOrString(const string&);
string setLogin(int8_t, bool&, bool&);
string setPassword(bool&, bool = true); 
string passwordStars(const string&);
void waitingForChar(const string&);
void rewriteFile(vector<User>&, const string&);
void rewriteFile(const vector<CityRoute>&);
void rewriteFile(const vector<InternationalRoute>&);
void rewriteFile(const vector<Buses>&);
bool copyCityFlightsFile(Flights&);
bool copyInternationalFlightsFile(Flights&);
bool copyBusesFile(Buses&);
void waitingForEsc();
void dataManagementMenu();
template<class T>
void deleteData(vector<T>&, int8_t);
int stringToInt(const string&);
void displayDate(string, int8_t);
void menuSearch(Flights&, bool);
template<class T1, class T2> 
void searchCommonPointsTable(vector<T1>&, T2&, string, string, int8_t);
template<class T>
bool routeCorrect(T&, const string&, const string&);
template<class T>
void showIFlightsSearchTable(vector<T>&, bool&, const string&);
void header(vector<InternationalRoute>&);
void header(vector<CityRoute>&);
void addOrderToFile(CityRoute&, Buses&);
void addOrderToFile(InternationalRoute&, Buses&);
template<class T>
bool readOrdersFile(Order<T>&);
template<class T>
void rewriteFile(Order<T>&);


class Date {
private:
    int countDays() const;
public:
    string day;
    string month;
    string year;
    string hour;
    string minutes;

    Date();
    Date(const string&); 
    Date(const string&, int8_t);
    
    friend bool operator==(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
};
