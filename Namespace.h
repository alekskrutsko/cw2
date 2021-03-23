#pragma once
#include"Coursework.h"


namespace checkingFileInputOutput {
	bool CityFlightsVerification(const CityRoute& croute);
	bool InternationalFlightsVerification(const InternationalRoute* iroute);
	bool BusesVerification(const Buses& bus);
	bool dateCorrect(int8_t day, int8_t month, int16_t year);
	bool timeCorrect(int8_t hour, int8_t minutes); 
	bool cityRouteCorrect(const CityRoute& cityRoute, const string& dateOfDeparture, const string& dateOfArrival);
	bool InternationalRouteCorrect(const InternationalRoute& iroute, const string& dateOfDeparture, const string& dateOfArrival);
	bool busCorrect(const Buses& bus);
}