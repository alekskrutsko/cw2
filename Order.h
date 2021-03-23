#pragma once
#include "Namespace.h"
#include "User.h"

template<class T>
class Order {  
public:
	vector<CityRoute> croute;
	vector<InternationalRoute> iroute;
	vector<string> cityRouteUsers;
	vector<string> InternationalRouteUsers;
	vector<Buses> cbuses;
	vector<Buses> ibuses;
	void addOrder(vector<T>&, bool&, const string&);
	void showTable(bool, bool = false);
	void orderCancellation();
	void filterPrice(int8_t, bool, bool&);
	void sortDate(bool);
	void sortDate(bool, int8_t);
	void sortPrice(bool);
};
template <class T>
void Order<T>::addOrder(vector<T>& orders, bool& quit, const string& str) { // orders ��� ���� ������������ ���� ������������� ����
	string b, k;
	bool search;
	do {
		cout << "\n������� ����� �����, ����� �� ������� �� ������ ������������� ";
		getline(cin, b);
		if (b == "esc") { quit = true; return; }
		if (b.empty()) continue;
		if (stringToInt(b) == -1 || stringToInt(b) > orders.size() || stringToInt(b) == 0) {
			cout << "\n�� ����� �������� ��������. ��� ���������� ����� ������� ����� �������";
			quit = false;  return;
		}
		else break;
	} while (true);

	int c = 0, f = 0;
	system("cls");
	Buses bus;
	vector<Buses> buses;
	int g = stringToInt(b) - 1;
	if (!copyBusesFile((Buses&)bus)) {

		for (int j = 0; j < bus.buses.size(); ++j)
			if ((bus.buses[j].transportType == str) && (bus.buses[j].routeNumber == orders[g].routeNumber)) {
				if (c == 0) {
					system("cls");
					cout << "-------------------------------------------------------------------------------------------------------------\n" <<
						" � |��� ����������|����� ��������|����� ����������|���� ������(BYN)|���-�� ����|����� ��������|���-�� ������|\n" <<
						"-------------------------------------------------------------------------------------------------------------\n";
					c = 1;
				}
				buses.push_back(bus.buses[j]);
				cout.width(2);
				cout << f + 1 << " |";
				f++;
				cout.width(14);
				cout << bus.buses[j].transportType << "|";
				cout.width(14);
				cout << bus.buses[j].routeNumber << "|";
				cout.width(16);
				cout << bus.buses[j].brand << "|";
				cout.width(16);
				cout << bus.buses[j].price << "|";
				cout.width(11);
				cout << bus.buses[j].number_of_seats << "|";
				cout.width(14);
				cout << bus.buses[j].bus_class << "|";
				cout.width(13);
				cout << bus.buses[j].number_of_floors << "|\n";
				cout << "-------------------------------------------------------------------------------------------------------------\n";
			}
		if (c == 0) {
			waitingForChar("�� ������� ��������� �� �������  ��������. ��� ������ ������� ����� �������");
			quit = true; return;
		}
		do {
			cout << "\n������� ����� ��������, ����� �� ������� �� ������ �������������. ��� ������ ������� esc ";
			getline(cin, b);
			if (b == "esc") { quit = true; return; }
			if (b.empty()) continue;
			if (stringToInt(b) == -1 || stringToInt(b) > buses.size() || stringToInt(b) == 0) {
				cout << "�� ����� �������� ��������. ��� ���������� ����� ������� ����� �������\n"; 
				_getch();
			}
			else break;
		} while (true);
		do {
			cout << "\n������� ���������� �������, ������� ������ �������������. ��� ������ ������� esc ";
			getline(cin, k);
			if (k == "esc") { quit = true; return; }
			if (k.empty()) continue;
			if (stringToInt(k) == -1 || stringToInt(k) == 0) {
				cout << "�� ����� �������� ��������. ��� ���������� ����� ������� ����� �������\n"; _getch();
			}
			else break;
		} while (true);
		f = stringToInt(b) - 1;
		for (int i = 0; i < stringToInt(k); i++) addOrderToFile(orders[g], buses[f]);
		
		waitingForChar("����� ������ �������. ��� ����������� � ���� ������� ����� �������");
		quit = true;
		return;
	}
	else {
		system("cls");
		cout << "\n���������� �� �������. ������� Enter, ����� ��������� �����, � Esc, ����� �����" << endl;
		while (true) {
			char a = getPushedCharCode();
			if (a == VK_ESCAPE) { return; quit = true; }
			if (a == VK_RETURN) { return; quit = false; }
		}
	}
}
template <class T>
void Order<T>::showTable(bool user, bool filterOrCancellation) {
	if (!filterOrCancellation) if (readOrdersFile(*this)) return;
	int d = 0;
	string str;
	int numberOfTickets = 0;
	User::getCurrentUser(str);
	system("cls");

	if (find(this->cityRouteUsers.begin(), this->cityRouteUsers.end(), str) != this->cityRouteUsers.end() ||
		find(this->InternationalRouteUsers.begin(), this->InternationalRouteUsers.end(), str) != this->InternationalRouteUsers.end() && user) cout << "������ ����� ������. ��� ������ ������� Esc\n\n";
	else cout << "��� ������ ������� Esc\n\n";

	if (!this->croute.empty()) {
		if (user) {
			if (find(this->cityRouteUsers.begin(), this->cityRouteUsers.end(), str) != this->cityRouteUsers.end()) cout << "    ������������ �����";
		}
		else cout << "    ������������ �����";

		for (int i = 0; i < this->croute.size(); ++i) {
			numberOfTickets = 1;
			if ((this->cityRouteUsers[i] == str && user) || !user) {
				for (int k = i + 1; k < this->croute.size(); k++) {
					if (this->croute[i].arrivalPoint == this->croute[k].arrivalPoint && this->croute[i].pointOfDeparture == this->croute[k].pointOfDeparture && this->croute[i].dateOfArrival == this->croute[k].dateOfArrival &&
						this->croute[i].dateOfDeparture == this->croute[k].dateOfDeparture && this->croute[i].routeNumber == this->croute[k].routeNumber && this->cbuses[i].transportType == this->cbuses[k].transportType &&
						this->cbuses[i].brand == this->cbuses[k].brand && this->cbuses[i].price == this->cbuses[k].price && this->cbuses[i].number_of_seats == this->cbuses[k].number_of_seats &&
						this->cbuses[i].bus_class == this->cbuses[k].bus_class && this->cbuses[i].number_of_floors == this->cbuses[k].number_of_floors) {

						if (this->cityRouteUsers[i] == this->cityRouteUsers[k]) { 
							this->croute.erase(this->croute.begin() + k); 
							this->cbuses.erase(this->cbuses.begin() + k);
							this->cityRouteUsers.erase(this->cityRouteUsers.begin() + k);
							k--;
							numberOfTickets++; 
						}					
					}		
				}
				d = 1;
				cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------\n";
				cout << "\n  ����� �����������: ";
				cout << this->croute[i].pointOfDeparture;
				cout << "     ����� ��������: ";
				cout << this->croute[i].arrivalPoint;
				cout << "    ���� � ����� �����������:  ";
				cout << this->croute[i].dateOfDeparture.day << '.' << this->croute[i].dateOfDeparture.month << '.' << this->croute[i].dateOfDeparture.year << " "
					<< this->croute[i].dateOfDeparture.hour << ":" << this->croute[i].dateOfDeparture.minutes;
				cout << "    ���� � ����� ��������:  ";
				cout << this->croute[i].dateOfArrival.day << '.' << this->croute[i].dateOfArrival.month << '.' << this->croute[i].dateOfArrival.year << " "
					<< this->croute[i].dateOfArrival.hour << ":" << this->croute[i].dateOfArrival.minutes;

				cout << "\n  ���������:  ";
				cout << "\n  ��� ����������:  ";
				cout << this->cbuses[i].transportType;
				cout << "    ����� ��������: ";
				cout << this->cbuses[i].routeNumber;
				cout << "    ����� ����������:  ";
				cout << this->cbuses[i].brand;
				cout << "    ���� ������(BYN): ";
				cout << this->cbuses[i].price << "(BYN)";
				cout << "\n  ���-�� ����:  ";
				cout << this->cbuses[i].number_of_seats;
				cout << "    ����� ��������: ";
				cout << this->cbuses[i].bus_class;
				cout << "    ���-�� ������: ";
				cout << this->cbuses[i].number_of_floors;
				cout << "    ����� �������:  ";
				cout << this->cityRouteUsers[i];
				cout << "\n  ���-�� ����� ��������������� �������: ";
				cout << numberOfTickets;
				cout << "    �������� ����� �����(��)(BYN): ";
				string price = this->cbuses[i].price;
				if (numberOfTickets > 1) {
					price = to_string(stod(this->cbuses[i].price) * numberOfTickets);
					int k = 0;
					for (int j = 0; j < price.size(); j++) {
						if (price[j] == '.') k = j;
					}
					if (k)price.erase(k + 3);
				}
				cout << price << "(BYN)\n";
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------\n";
			}
		}
	}
	
	if (!this->iroute.empty()) {
		if (user) {
			if (find(this->InternationalRouteUsers.begin(), this->InternationalRouteUsers.end(), str) != this->InternationalRouteUsers.end()) cout << "\n\n    ������������� �����";
		}
		else cout << "\n\n    ������������� �����";

		for (int i = 0; i < this->iroute.size(); ++i) {
			numberOfTickets = 1;
			if ((this->InternationalRouteUsers[i] == str && user) || !user) {
				for (int k = i + 1; k < this->iroute.size(); k++) {
					if (this->iroute[i].arrivalPoint == this->iroute[k].arrivalPoint && this->iroute[i].pointOfDeparture == this->iroute[k].pointOfDeparture && this->iroute[i].dateOfArrival == this->iroute[k].dateOfArrival &&
						this->iroute[i].dateOfDeparture == this->iroute[k].dateOfDeparture && this->iroute[i].routeNumber == this->iroute[k].routeNumber && this->iroute[i].countryOfArrival == this->iroute[k].countryOfArrival
						&& this->iroute[i].visa == this->iroute[k].visa && this->ibuses[i].transportType == this->ibuses[k].transportType &&
						this->ibuses[i].brand == this->ibuses[k].brand && this->ibuses[i].price == this->ibuses[k].price && this->ibuses[i].number_of_seats == this->ibuses[k].number_of_seats &&
						this->ibuses[i].bus_class == this->ibuses[k].bus_class && this->ibuses[i].number_of_floors == this->ibuses[k].number_of_floors) {

						if (this->InternationalRouteUsers[i] == this->InternationalRouteUsers[k]) {
							this->iroute.erase(this->iroute.begin() + k);
							this->ibuses.erase(this->ibuses.begin() + k);
							this->InternationalRouteUsers.erase(this->InternationalRouteUsers.begin() + k);
							k--;
							numberOfTickets++;
						}
					}
				}
				d = 1;
				cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------\n";
				cout << "\n  ����� �����������:   ";
				cout << this->iroute[i].pointOfDeparture;
				cout << "     ����� ��������:   ";
				cout << this->iroute[i].arrivalPoint;
				cout << "     ���� � ����� �����������:   ";
				cout << this->iroute[i].dateOfDeparture.day << '.' << this->iroute[i].dateOfDeparture.month << '.' << this->iroute[i].dateOfDeparture.year << " "
					<< this->iroute[i].dateOfDeparture.hour << ":" << this->iroute[i].dateOfDeparture.minutes;
				cout << "\n  ���� � ����� ��������:   ";
				cout << this->iroute[i].dateOfArrival.day << '.' << this->iroute[i].dateOfArrival.month << '.' << this->iroute[i].dateOfArrival.year << " "
					<< this->iroute[i].dateOfArrival.hour << ":" << this->iroute[i].dateOfArrival.minutes;
				cout << "   ������ ��������:   ";
				cout << this->iroute[i].countryOfArrival;
				cout << "   ��������� �� ����:   ";
				cout << this->iroute[i].visa;

				cout << "\n  ���������:   ";
				cout << "\n  ��� ����������:   ";
				cout << this->ibuses[i].transportType;
				cout << "    ����� ��������: ";
				cout << this->ibuses[i].routeNumber;
				cout << "    ����� ����������:   ";
				cout << this->ibuses[i].brand;
				cout << "    ���� ������(BYN): ";
				cout << this->ibuses[i].price << "(BYN)";
				cout << "\n  ���-�� ����:   ";
				cout << this->ibuses[i].number_of_seats;
				cout << "    ����� ��������:   ";
				cout << this->ibuses[i].bus_class;
				cout << "    ���-�� ������:   ";
				cout << this->ibuses[i].number_of_floors;
				cout << "    ����� �������:   ";
				cout << this->InternationalRouteUsers[i];
				cout << "\n  ���-�� ����� ��������������� �������: ";
				cout << numberOfTickets;
				cout << "    �������� ����� �����(��)(BYN): ";
				string price = this->ibuses[i].price;
				if (numberOfTickets > 1) {
					price = to_string(stod(this->ibuses[i].price) * numberOfTickets);
					int k = 0;
					for (int j = 0; j < price.size(); j++) {
						if (price[j] == '.') k = j;
					}
					if(k)price.erase(k+3);
				}
				cout << price << "(BYN)\n";
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------\n";
			}
		}
	}
	if (!d && user) { system("cls");  cout << "�� ��� �� ������������� �� ������ ������. ��� ������ ������� Esc"; }
}
template<class T>
void Order<T>::orderCancellation() {
	int8_t row = 0;
	string str;
	User::getCurrentUser(str);
	do {
		if (readOrdersFile(*this)) { waitingForEsc();  return; }
		int irouteSize = 0, �routeSize = 0;
		showTable(true, true);

		for (int i = 0; i < this->iroute.size(); ++i)
			if (this->InternationalRouteUsers[i] == str) irouteSize++;
		for (int i = 0; i < this->croute.size(); ++i)
			if (this->cityRouteUsers[i] == str) �routeSize++;
		if (!irouteSize && !�routeSize) { waitingForEsc(); return; }

		cout << "\n\n�������� �� ����� ���� �� ������ �������� �����\n";
		arrowMenu({ "\n �� ������������ ����", "\n\n �� ������������ ����" }, row);

		char a = getPushedCharCode();

		if (a == VK_UP) row = (row + 1) % 2;
		else if (a == VK_DOWN) row = (row + 1) % 2;
		else if (a == VK_ESCAPE) return;
		else if (a == 13) {
			if (row == 0) {
				if (irouteSize) {
					string c, temp;
					irouteSize = 0;
					for (int i = 0; i < this->iroute.size(); ++i)
						if (this->InternationalRouteUsers[i] == str) irouteSize++;
					while (irouteSize) {
						cout << "������� ����� �����, ������� ������ �������� ";
						getline(cin, c);
						if (c == "esc") return;
						if (c.empty()) continue;
						if (stringToInt(c) == -1 || stringToInt(c) > irouteSize || stringToInt(c) == 0) {
							cout << "�� ����� �������� ��������. ��� ���������� ����� ������� ����� �������\n";
							_getch();
						}
						else break;
					}
					int b = stringToInt(c);

					do {
						temp = getLoginOrString("������� \"��\" ��� ������ �����. ��� ������ ������� esc");
						if (temp == "esc" || temp == "��") break;
					} while (temp.empty());
					if (temp == "��") {
						irouteSize = 0;
						for (int i = 0; i < this->iroute.size(); ++i) {
							if (this->InternationalRouteUsers[i] == str) irouteSize++;
							if (irouteSize == b) {
								InternationalRoute interroute = this->iroute[i];
								Buses interbus = this->ibuses[i];
								readOrdersFile(*this);
								for (int k = 0; k < this->iroute.size(); k++) {
									if (interroute.arrivalPoint == this->iroute[k].arrivalPoint && interroute.pointOfDeparture == this->iroute[k].pointOfDeparture && interroute.dateOfArrival == this->iroute[k].dateOfArrival &&
										interroute.dateOfDeparture == this->iroute[k].dateOfDeparture && interroute.routeNumber == this->iroute[k].routeNumber && interroute.countryOfArrival == this->iroute[k].countryOfArrival
										&& interroute.visa == this->iroute[k].visa && interbus.transportType == this->ibuses[k].transportType &&
										interbus.brand == this->ibuses[k].brand && interbus.price == this->ibuses[k].price && interbus.number_of_seats == this->ibuses[k].number_of_seats &&
										interbus.bus_class == this->ibuses[k].bus_class && interbus.number_of_floors == this->ibuses[k].number_of_floors) {

										if (this->InternationalRouteUsers[i] == this->InternationalRouteUsers[k]) {
											this->iroute.erase(this->iroute.begin() + k);
											this->ibuses.erase(this->ibuses.begin() + k);
											this->InternationalRouteUsers.erase(this->InternationalRouteUsers.begin() + k);
											k--;
										}
									}
								}
								rewriteFile(*this);
								waitingForChar("����� ������� ��������. ������� ����� �������");
								break;
							}
						}
					}
					else if (temp == "esc") return;
				}
				else {
					cout << "\n�� ��� �� �������� �� ����� ����� �� ������������� �����. ��� ����������� ������� ����� �������";
					_getch();
				}
			}
			else if (row == 1) {
				if (�routeSize) {
					string c, temp;
					�routeSize = 0;
					for (int i = 0; i < this->croute.size(); ++i)
						if (this->cityRouteUsers[i] == str) �routeSize++;

					while (�routeSize) {
						cout << "������� ����� �����, ������� ������ �������� ";
						getline(cin, c);
						if (c == "esc") return;
						if (c.empty()) continue;
						if (stringToInt(c) == -1 || stringToInt(c) > �routeSize || stringToInt(c) == 0) {
							cout << "�� ����� �������� ��������. ��� ���������� ����� ������� ����� �������\n";
							_getch();
						}
						else break;
					}
					int b = stringToInt(c);

					do {
						temp = getLoginOrString("������� \"��\" ��� ������ �����. ��� ������ ������� esc");
						if (temp == "esc" || temp == "��") break;
					} while (temp.empty());
					if (temp == "��") {
						�routeSize = 0;
						for (int i = 0; i < this->croute.size(); ++i) {
							if (this->cityRouteUsers[i] == str) �routeSize++;
							if (�routeSize == b) {
								CityRoute cityroute = this->croute[i];
								Buses citybus = this->cbuses[i];
								readOrdersFile(*this);
								for (int k = 0; k < this->croute.size(); k++) {
									if (cityroute.arrivalPoint == this->croute[k].arrivalPoint && cityroute.pointOfDeparture == this->croute[k].pointOfDeparture && cityroute.dateOfArrival == this->croute[k].dateOfArrival &&
										cityroute.dateOfDeparture == this->croute[k].dateOfDeparture && cityroute.routeNumber == this->croute[k].routeNumber && citybus.transportType == this->cbuses[k].transportType &&
										citybus.brand == this->cbuses[k].brand && citybus.price == this->cbuses[k].price && citybus.number_of_seats == this->cbuses[k].number_of_seats &&
										citybus.bus_class == this->cbuses[k].bus_class && citybus.number_of_floors == this->cbuses[k].number_of_floors) {

										if (str == this->cityRouteUsers[k]) {
											this->croute.erase(this->croute.begin() + k);
											this->cbuses.erase(this->cbuses.begin() + k);
											this->cityRouteUsers.erase(this->cityRouteUsers.begin() + k);
											k--;
										}
									}
								}
								rewriteFile(*this);
								waitingForChar("����� ������� ��������. ������� ����� �������");
								break;
							}
						}

					}
					else if (temp == "esc") return;
				}
				else {
					cout << "\n�� ��� �� �������� �� ����� ����� �� ������������ �����. ��� ����������� ������� ����� �������";
					_getch();
				}
			}
		}
	} while (true);
}
template<class T>
void Order<T>::filterPrice(int8_t a, bool user, bool& quit) {
	if (readOrdersFile(*this)) return;
	if (this->croute.empty() && this->iroute.empty() && this->cbuses.empty() && this->ibuses.empty()) { system("cls"); cout << "���� ����. ��� ����������� ������� Esc"; return; }
	string priceFrom, priceTo;
	while (true) {
		system("cls");
		cout << "������� �������� ���, � �������� �������� �� ������ ����� ��������������� �����. ��� ������ ������� esc\n";
		do {
			cout << "������� ������ ������: ";
			getline(cin, priceFrom);
			if (priceFrom == "esc") { quit = true; return; }
			if (priceFrom.empty()) continue;
			if (stringToInt(priceFrom) == 0 || stringToInt(priceFrom) == -1 || priceFrom.size() > 4) cout << "\n��������� ������ ������ ��������� ������ ����� � ���� ������ 0, �� ������ 9999\n";
			else break;
		} while (true);
		do {
			cout << "������� ������ ������: ";
			getline(cin, priceTo);
			if (priceTo == "esc") { quit = true; return; }
			if (priceTo.empty()) continue;
			if (stringToInt(priceTo) == 0 || stringToInt(priceTo) == -1 || priceTo.size() > 4) cout << "\n��������� ������ ������ ��������� ������ ����� � ���� ������ 0, �� ������ 9999\n";
			else if (stringToInt(priceTo) < stringToInt(priceFrom)) cout << "\n������� ������ ������ ���� ������ ���� ����� �������\n";
			else break;
		} while (true);

		if (a == 1) {
			int j = 0;
			Order filterOrder;
			for (int i = 0; i < this->ibuses.size(); ++i) {
				if (stod(this->ibuses[i].price) >= stringToInt(priceFrom) && stod(this->ibuses[i].price) <= stringToInt(priceTo)) {
					filterOrder.iroute.push_back(this->iroute[i]);
					filterOrder.InternationalRouteUsers.push_back(this->InternationalRouteUsers[i]);
					filterOrder.ibuses.push_back(this->ibuses[i]);
					j++;
				}
			}
			if (j == 0) {
				system("cls");
				cout << "������ � ����� �� ����� ��������� �� �������. ��� ������ ������� Esc, ��� ������� ������� Enter";
				while (true) {
					char a = getPushedCharCode();
					if (a == VK_ESCAPE) { quit = true; return; }
					if (a == VK_RETURN) { system("cls"); break; }
				}
			}
			else {
				this->cbuses.clear(); this->cityRouteUsers.clear(); this->croute.clear();
				this->ibuses.clear(); this->InternationalRouteUsers.clear(); this->iroute.clear();
				this->ibuses.insert(this->ibuses.begin(), filterOrder.ibuses.begin(), filterOrder.ibuses.end());
				this->InternationalRouteUsers.insert(this->InternationalRouteUsers.begin(), filterOrder.InternationalRouteUsers.begin(), filterOrder.InternationalRouteUsers.end());
				this->iroute.insert(this->iroute.begin(), filterOrder.iroute.begin(), filterOrder.iroute.end());

				showTable(user, true);
				return;
			}
		
		}
		if (a == 2) {
			int j = 0;
			Order filterOrder;
			for (int i = 0; i < this->cbuses.size(); ++i) {
				if (stod(this->cbuses[i].price) >= stringToInt(priceFrom) && stod(this->cbuses[i].price) <= stringToInt(priceTo)) {
					filterOrder.croute.push_back(this->croute[i]);
					filterOrder.cityRouteUsers.push_back(this->cityRouteUsers[i]);
					filterOrder.cbuses.push_back(this->cbuses[i]);
					j++;
				}
			}
			if (j == 0) {
				system("cls");
				cout << "������ � ����� �� ����� ��������� �� �������. ��� ������ ������� Esc, ��� ������� ������� Enter";
				while (true) {
					char a = getPushedCharCode();
					if (a == VK_ESCAPE) { quit = true; return; }
					if (a == VK_RETURN) { system("cls"); break; }
				}
			}
			else {
				this->cbuses.clear(); this->cityRouteUsers.clear(); this->croute.clear();
				this->ibuses.clear(); this->InternationalRouteUsers.clear(); this->iroute.clear();
				this->cbuses.insert(this->cbuses.begin(), filterOrder.cbuses.begin(), filterOrder.cbuses.end());
				this->cityRouteUsers.insert(this->cityRouteUsers.begin(), filterOrder.cityRouteUsers.begin(), filterOrder.cityRouteUsers.end());
				this->croute.insert(this->croute.begin(), filterOrder.croute.begin(), filterOrder.croute.end());

				showTable(user, true);
				return;
			}
		}
	}
}
template<class T>
void Order<T>::sortDate(bool user) {
	if (readOrdersFile(*this)) return;
	if (this->croute.empty() && this->iroute.empty() && this->cbuses.empty() && this->ibuses.empty()) { system("cls"); cout << "���� ����. ��� ����������� ������� Esc"; return; }

	for (int i = 0; i < this->croute.size() - 1; i++) {
		for (int j = 0; j < this->croute.size() - i - 1; j++) {
			if (this->croute[j].dateOfDeparture > this->croute[j + 1].dateOfDeparture) {
				swap(this->croute[j], this->croute[j + 1]);
				swap(this->cbuses[j], this->cbuses[j + 1]);
				swap(this->cityRouteUsers[j], this->cityRouteUsers[j + 1]);
			}
		}
	}
	for (int i = 0; i < this->iroute.size() - 1; i++) {
		for (int j = 0; j < this->iroute.size() - i - 1; j++) {
			if (this->iroute[j].dateOfDeparture > this->iroute[j + 1].dateOfDeparture) {
				swap(this->iroute[j], this->iroute[j + 1]);
				swap(this->ibuses[j], this->ibuses[j + 1]);
				swap(this->InternationalRouteUsers[j], this->InternationalRouteUsers[j + 1]);
			}
		}
	}
	showTable(user, true);
}
template<class T>
void Order<T>::sortDate(bool user, int8_t a) {
	if (readOrdersFile(*this)) return;
	if (this->croute.empty() && this->iroute.empty() && this->cbuses.empty() && this->ibuses.empty()) { system("cls"); cout << "���� ����. ��� ����������� ������� Esc"; return; }

	for (int i = 0; i < this->croute.size() - 1; i++) {
		for (int j = 0; j < this->croute.size() - i - 1; j++) {
			if (this->croute[j].dateOfArrival > this->croute[j + 1].dateOfArrival) {
				swap(this->croute[j], this->croute[j + 1]);
				swap(this->cbuses[j], this->cbuses[j + 1]);
				swap(this->cityRouteUsers[j], this->cityRouteUsers[j + 1]);
			}
		}
	}
	for (int i = 0; i < this->iroute.size() - 1; i++) {
		for (int j = 0; j < this->iroute.size() - i - 1; j++) {
			if (this->iroute[j].dateOfArrival > this->iroute[j + 1].dateOfArrival) {
				swap(this->iroute[j], this->iroute[j + 1]);
				swap(this->ibuses[j], this->ibuses[j + 1]);
				swap(this->InternationalRouteUsers[j], this->InternationalRouteUsers[j + 1]);
			}
		}
	}
	showTable(user, true);
}
template<class T>
void Order<T>::sortPrice(bool user) {
	if (readOrdersFile(*this)) return;
	if (this->croute.empty() && this->iroute.empty() && this->cbuses.empty() && this->ibuses.empty()) { system("cls"); cout << "���� ����. ��� ����������� ������� Esc"; return; }

	for (int i = 0; i < this->cbuses.size() - 1; i++) {
		for (int j = 0; j < this->cbuses.size() - i - 1; j++) {
			if (stod(this->cbuses[j].price) < stod(this->cbuses[j + 1].price)) {
				swap(this->croute[j], this->croute[j + 1]);
				swap(this->cbuses[j], this->cbuses[j + 1]);
				swap(this->cityRouteUsers[j], this->cityRouteUsers[j + 1]);
			}
		}
	}
	for (int i = 0; i < this->ibuses.size() - 1; i++) {
		for (int j = 0; j < this->iroute.size() - i - 1; j++) {
			if (stod(this->ibuses[j].price) < stod(this->ibuses[j + 1].price)) {
				swap(this->iroute[j], this->iroute[j + 1]);
				swap(this->ibuses[j], this->ibuses[j + 1]);
				swap(this->InternationalRouteUsers[j], this->InternationalRouteUsers[j + 1]);
			}
		}
	}
	showTable(user, true);
}
template<class T>
bool readOrdersFile(Order<T>& order) {
	ifstream file("files/Orders.txt");
	if (!order.iroute.empty()) order.iroute.clear();
	if (!order.croute.empty()) order.croute.clear();
	if (!order.cityRouteUsers.empty()) order.cityRouteUsers.clear();
	if (!order.InternationalRouteUsers.empty()) order.InternationalRouteUsers.clear();
	if (!order.cbuses.empty()) order.cbuses.clear();
	if (!order.ibuses.empty()) order.ibuses.clear();
	string a;
	int8_t f = 0;
	while (file) {

		file >> a;
		if (a != "1" && a != "2") {
			system("cls");
			cout << "���� ���������/����. ��� ����������� � ���� ������� Esc";
			return true;
		}
		if (a == "1") {
			CityRoute T1;
			CityRoute* temp1;
			string str;
			Buses temp;
			temp1 = &T1;

			file >> T1.pointOfDeparture >> T1.arrivalPoint >> T1.dateOfDeparture.day >> T1.dateOfDeparture.month >> T1.dateOfDeparture.year
				>> T1.dateOfDeparture.hour >> T1.dateOfDeparture.minutes >> T1.dateOfArrival.day >> T1.dateOfArrival.month >> T1.dateOfArrival.year
				>> T1.dateOfArrival.hour >> T1.dateOfArrival.minutes >> T1.routeNumber >> str;



			file >> temp.transportType >> temp.routeNumber >> temp.brand >> temp.price >> temp.number_of_seats >>
				temp.bus_class >> temp.number_of_floors;

			if (checkingFileInputOutput::BusesVerification(temp)) order.cbuses.push_back(temp);
			else {
				system("cls");
				cout << "���� ���������. ��� ����������� � ���� ������� Esc";
				return true;
			}

			for (auto i : str)
				if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9') || i != ' ')) return false;
			order.cityRouteUsers.push_back(str);

			if (checkingFileInputOutput::CityFlightsVerification(*temp1)) order.croute.push_back(*temp1);
			else {
				system("cls");
				cout << "���� ���������. ��� ����������� � ���� ������� Esc";
				return true;
			}
			f = 1;
		}
		if (a == "2") {
			InternationalRoute temp1;
			CityRoute* T1;
			T1 = &temp1;
			Buses temp;
			string str;
			file >> temp1.pointOfDeparture >> temp1.arrivalPoint >> temp1.dateOfDeparture.day >> temp1.dateOfDeparture.month >> temp1.dateOfDeparture.year >>
				temp1.dateOfDeparture.hour >> temp1.dateOfDeparture.minutes
				>> temp1.dateOfArrival.day >> temp1.dateOfArrival.month >> temp1.dateOfArrival.year >> temp1.dateOfArrival.hour >> temp1.dateOfArrival.minutes >>
				temp1.countryOfArrival >> temp1.visa >> temp1.routeNumber >> str;

			file >> temp.transportType >> temp.routeNumber >> temp.brand >> temp.price >> temp.number_of_seats >>
				temp.bus_class >> temp.number_of_floors;

			if (checkingFileInputOutput::BusesVerification(temp)) order.ibuses.push_back(temp);
			else {
				system("cls");
				cout << "���� ���������. ��� ����������� � ���� ������� Esc";
				return true;
			}

			for (auto i : str)
				if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9'))) return false;
			order.InternationalRouteUsers.push_back(str);
			if (checkingFileInputOutput::InternationalFlightsVerification((InternationalRoute*)&temp1) &&
				checkingFileInputOutput::CityFlightsVerification(*T1))	order.iroute.push_back(temp1);
			else {
				system("cls");
				cout << "���� ���������. ��� ����������� � ���� ������� Esc";
				return true;
			}
			f = 2;
		}
	}
	if (!order.cbuses.empty() && !order.croute.empty() && f == 1) {
		order.cbuses.pop_back();
		order.croute.pop_back();
		order.cityRouteUsers.pop_back();
	}
	if (!order.ibuses.empty() && !order.iroute.empty() && f == 2) {
		order.ibuses.pop_back();
		order.iroute.pop_back();
		order.InternationalRouteUsers.pop_back();
	}
	file.close();
	return false;
}
template<class T>
void rewriteFile(Order<T>& order) {
	ofstream file("files/Orders.txt", ios::trunc);
	for (int i = 0; i < order.croute.size(); i++)
		file << "1" << ' ' << order.croute[i].pointOfDeparture << ' ' << order.croute[i].arrivalPoint << ' '
		<< order.croute[i].dateOfDeparture.day << ' ' << order.croute[i].dateOfDeparture.month << ' ' << order.croute[i].dateOfDeparture.year << ' ' << order.croute[i].dateOfDeparture.hour << ' '
		<< order.croute[i].dateOfDeparture.minutes << ' ' << order.croute[i].dateOfArrival.day << ' ' << order.croute[i].dateOfArrival.month << ' ' << order.croute[i].dateOfArrival.year << ' '
		<< order.croute[i].dateOfArrival.hour << ' ' << order.croute[i].dateOfArrival.minutes << ' ' << order.croute[i].routeNumber << ' ' << order.cityRouteUsers[i] << ' ' << order.cbuses[i].transportType
		<< ' ' << order.cbuses[i].routeNumber << ' ' << order.cbuses[i].brand << ' ' << order.cbuses[i].price << ' ' << order.cbuses[i].number_of_seats << ' ' << order.cbuses[i].bus_class << ' '
		<< order.cbuses[i].number_of_floors << '\n';

	for (int i = 0; i < order.iroute.size(); i++)
		file << "2" << ' ' << order.iroute[i].pointOfDeparture << ' ' << order.iroute[i].arrivalPoint << ' '
		<< order.iroute[i].dateOfDeparture.day << ' ' << order.iroute[i].dateOfDeparture.month << ' ' << order.iroute[i].dateOfDeparture.year << ' ' << order.iroute[i].dateOfDeparture.hour
		<< ' ' << order.iroute[i].dateOfDeparture.minutes << ' ' << order.iroute[i].dateOfArrival.day << ' ' << order.iroute[i].dateOfArrival.month << ' ' << order.iroute[i].dateOfArrival.year << ' '
		<< order.iroute[i].dateOfArrival.hour << ' ' << order.iroute[i].dateOfArrival.minutes << ' ' << order.iroute[i].countryOfArrival << ' ' << order.iroute[i].visa << ' ' << order.iroute[i].routeNumber
		<< ' ' << order.InternationalRouteUsers[i] << ' ' << order.ibuses[i].transportType << ' ' << order.ibuses[i].routeNumber << ' ' << order.ibuses[i].brand << ' ' << order.ibuses[i].price << ' ' << order.ibuses[i].number_of_seats << ' '
		<< order.ibuses[i].bus_class << ' ' << order.ibuses[i].number_of_floors << '\n';

	file.close();
}