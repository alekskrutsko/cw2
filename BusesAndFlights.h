#pragma once
#include "Namespace.h"


class Buses {
private:
void addElement(Buses&, bool = true);
void changeData(Buses&);
public:
    vector<Buses> buses;
    string transportType, routeNumber, brand, price, number_of_seats, bus_class, number_of_floors;
    void showTable(bool = true);
    friend void dataManagementMenu();
};
class CityRoute {
public:
    string pointOfDeparture, arrivalPoint, routeNumber;
    Date dateOfDeparture, dateOfArrival;

};
class InternationalRoute : public CityRoute {
public:
    string countryOfArrival, visa;   
};
class Flights {     
public:
    vector<CityRoute> croute;
    vector<InternationalRoute> iroute;
    virtual void showTable(bool = true) = 0;    
};
class CityFlights : public  Flights {
private:
    void addElement(CityRoute&, string, string, bool = true);
    void changeData(vector<CityRoute>&);
public:
    void showTable(bool = true) override;
    friend void dataManagementMenu();
};
class InternationalFlights : public  Flights {
private:
    void addElement(InternationalRoute&, string, string, bool = true);
    void changeData(vector<InternationalRoute>&);
public:
    void showTable(bool = true) override;
    friend void dataManagementMenu();
   
};
