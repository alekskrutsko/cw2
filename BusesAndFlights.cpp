#include "BusesAndFlights.h"
#include "Order.h"

void CityFlights::showTable(bool flag) {
	if (copyCityFlightsFile(*this)) return;
	if (this->croute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; return; }
	system("cls");
	if (flag) cout << "Для выхода нажмите Esc" << '\n';
	else cout << "Для выхода введите esc" << '\n';
	cout << "--------------------------------------------------------------------------------------------------\n" <<
		" №|ПУНКТ ОТПРАВЛЕНИЯ|ПУНКТ ПРИБЫТИЯ|ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ|ДАТА И ВРЕМЯ ПРИБЫТИЯ|НОМЕР МАРШРУТА|\n" <<
		"--------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < this->croute.size(); ++i) {
		cout.width(2);
		cout << i + 1 << "|";
		cout.width(17);
		cout << this->croute[i].pointOfDeparture << "|";
		cout.width(14);
		cout << this->croute[i].arrivalPoint << "|";
		cout.width(10);
		cout << this->croute[i].dateOfDeparture.day << '.' << this->croute[i].dateOfDeparture.month << '.' << this->croute[i].dateOfDeparture.year << " "
			<< this->croute[i].dateOfDeparture.hour << ":" << this->croute[i].dateOfDeparture.minutes << "|";
		cout.width(7);
		cout << this->croute[i].dateOfArrival.day << '.' << this->croute[i].dateOfArrival.month << '.' << this->croute[i].dateOfArrival.year << " "
			<< this->croute[i].dateOfArrival.hour << ":" << this->croute[i].dateOfArrival.minutes << "|";
		cout.width(9);
		cout << this->croute[i].routeNumber << "     |\n";
		cout << "--------------------------------------------------------------------------------------------------\n";
	}
}
void InternationalFlights::showTable(bool flag) {
	if (copyInternationalFlightsFile(*this)) return;
	if (this->iroute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; return; }
	system("cls");
	if (flag) cout << "Для выхода нажмите Esc" << '\n';
	else cout << "Для выхода введите esc" << '\n';
	cout << "------------------------------------------------------------------------------------------------------------------------------------\n" <<
		" №|ПУНКТ ОТПРАВЛЕНИЯ|ПУНКТ ПРИБЫТИЯ|ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ|ДАТА И ВРЕМЯ ПРИБЫТИЯ|СТРАНА ПРИБЫТИЯ|ТРЕБУЕТСЯ ЛИ ВИЗА|НОМЕР МАРШРУТА|\n" <<
		"------------------------------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < this->iroute.size(); ++i) {
		cout.width(2);
		cout << i + 1 << "|";
		cout.width(17);
		cout << this->iroute[i].pointOfDeparture << "|";
		cout.width(14);
		cout << this->iroute[i].arrivalPoint << "|";
		cout.width(10);
		cout << this->iroute[i].dateOfDeparture.day << '.' << this->iroute[i].dateOfDeparture.month << '.' << this->iroute[i].dateOfDeparture.year << " "
			<< this->iroute[i].dateOfDeparture.hour << ":" << this->iroute[i].dateOfDeparture.minutes << "|";
		cout.width(8);
		cout << this->iroute[i].dateOfArrival.day << '.' << this->iroute[i].dateOfArrival.month << '.' << this->iroute[i].dateOfArrival.year << " "
			<< this->iroute[i].dateOfArrival.hour << ":" << this->iroute[i].dateOfArrival.minutes << "|";

		cout.width(15);
		cout << this->iroute[i].countryOfArrival << "|";
		cout.width(10);
		cout << this->iroute[i].visa << "       |";
		cout.width(9);
		cout << this->iroute[i].routeNumber << "    |\n";
		cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
	}
}
void Buses::showTable(bool flag) {
	if (copyBusesFile(*this)) return;
	if (this->buses.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; return; }
	system("cls");
	if (flag) cout << "Для выхода нажмите Esc" << '\n';
	else cout << "Для выхода введите esc" << '\n';
	cout << "-------------------------------------------------------------------------------------------------------------\n" <<
		" № |ТИП ТРАНСПОРТА|НОМЕР МАРШРУТА|МАРКА ТРАНСПОРТА|ЦЕНА БИЛЕТА(BYN)|КОЛ-ВО МЕСТ|КЛАСС АВТОБУСА|КОЛ-ВО ЭТАЖЕЙ|\n" <<
		"-------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < this->buses.size(); ++i) {
		cout.width(2);
		cout << i + 1 << " |";
		cout.width(14);
		cout << this->buses[i].transportType << "|";
		cout.width(14);
		cout << this->buses[i].routeNumber << "|";
		cout.width(16);
		cout << this->buses[i].brand << "|";
		cout.width(16);
		cout << this->buses[i].price << "|";
		cout.width(11);
		cout << this->buses[i].number_of_seats << "|";
		cout.width(14);
		cout << this->buses[i].bus_class << "|";
		cout.width(13);
		cout << this->buses[i].number_of_floors << "|\n";
		cout << "-------------------------------------------------------------------------------------------------------------\n";
	}
}
void dataManagementMenu(){
	int8_t row = 0, row1;

	CityFlights cflight;
	InternationalFlights iflight;
	Buses bus;
	if (copyCityFlightsFile(cflight)) { waitingForEsc(); return; }
	if (copyInternationalFlightsFile(iflight)) { waitingForEsc(); return; }
	if (copyBusesFile(bus)) { waitingForEsc(); return; }
	while (true) {
		system("cls");
		arrowMenu({ " Добавить данные", "\n\n Удалить данные",
					"\n\n Поиск/сортировка/фильтрация данных", "\n\n Изменить данные", "\n\n Назад" }, row);

		char a = getPushedCharCode();

		if (a == VK_UP) row = (row + 5 - 1) % 5;
		else if (a == VK_DOWN) row = (row + 1) % 5;
		else if (a == 13) {
			if (row == 0) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << " Выберете пункт, информацию по которому, вы хотите добавить:\n\n";
					arrowMenu({ " Добавить информацию о международных рейсах","\n\n Добавить информацию о региональных ресах",
						"\n\n Добавить информацию об автобусах", "\n\n Назад" }, row1);

					char a = getPushedCharCode();

					if (a == VK_UP) row1 = (row1 + 4 - 1) % 4;
					else if (a == VK_DOWN) row1 = (row1 + 1) % 4;
					else if (a == 13) {
						if (row1 == 0) {
							InternationalRoute iroute;
							iflight.addElement(iroute, string(), string());
						}
						if (row1 == 1) {
							CityRoute croute;
							cflight.addElement(croute, string(), string());
						}
						if (row1 == 2) {
							Buses bus1;
							bus.addElement(bus1);
						}
						if (row1 == 3) { row = 0; break; }
					}
				}
			}
			else if (row == 1) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << " Выберете пункт, который хотите удалить:\n\n";
					arrowMenu({ " Удалить информацию о международных рейсах","\n\n Удалить информацию о региональных ресах",
						"\n\n Удалить информацию об автобусах", "\n\n Назад" }, row1);

					char a = getPushedCharCode();

					if (a == VK_UP) row1 = (row1 + 4 - 1) % 4;
					else if (a == VK_DOWN) row1 = (row1 + 1) % 4;
					else if (a == 13) {
						if (row1 == 0) {
							//if (copyInternationalFlightsFile(iflight)) { waitingForEsc(); continue; }
							if (iflight.iroute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							deleteData(iflight.iroute, 1);
						}
						if (row1 == 1) {
							//if (copyCityFlightsFile(iflight)) { waitingForEsc(); continue; }
							if (cflight.croute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							deleteData(cflight.croute, 2);
						}
						if (row1 == 2) {
							//if (copyBusesFile(bus)) { waitingForEsc(); continue; }
							if (bus.buses.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							deleteData(bus.buses, 3);
						}
						if (row1 == 3) { row = 0; break; }
					}
				}
			}
			else if (row == 2) menuSearch(iflight, false);
			else if (row == 3) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << " Выберете пункт, информацию о которому, вы хотите изменить:\n\n";
					arrowMenu({ " Изменить информацию о международных рейсах","\n\n Изменить информацию о региональных ресах",
						"\n\n Изменить информацию об автобусах", "\n\n Назад" }, row1);

					char a = getPushedCharCode();

					if (a == VK_UP) row1 = (row1 + 4 - 1) % 4;
					else if (a == VK_DOWN) row1 = (row1 + 1) % 4;
					else if (a == 13) {
						if (row1 == 0) { 
							//if (copyInternationalFlightsFile(iflight)) { waitingForEsc(); continue; }
							if (iflight.iroute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							iflight.changeData(iflight.iroute); 
						}
						if (row1 == 1) { 
							//if (copyCityFlightsFile(iflight)) { waitingForEsc(); continue; }
							if (cflight.croute.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							cflight.changeData(cflight.croute); 
						}
						if (row1 == 2) {
							//if (copyBusesFile(bus)) { waitingForEsc(); continue; }
							if (bus.buses.empty()) { system("cls"); cout << "Файл пуст. Для выхода нажмите Esc"; waitingForEsc(); continue; }
							bus.changeData(bus);
						}
						if (row1 == 3) { row = 0; break; }
					}
				}
			}
			else if (row == 4) {
				system("cls");
				break;
			}
		}
	}
}
void CityFlights::addElement(CityRoute& cityRoute, string dateOfArrival, string dateOfDeparture, bool flag) {
	int8_t row = 0;
	while (true) {
		system("cls");
		cout << "\n----------------------------------------------------\n";
		cout << (!row ? " -->  " : "") << "  ПУНКТ ОТПРАВЛЕНИЯ:         ";
		cout << cityRoute.pointOfDeparture << string(14 - cityRoute.pointOfDeparture.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 1 ? " -->  " : "") << "  ПУНКТ ПРИБЫТИЯ:            ";
		cout << cityRoute.arrivalPoint << string(14 - cityRoute.arrivalPoint.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 2 ? " -->  " : "");
		cout << "  ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ:  "; displayDate(dateOfDeparture, 1); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 3 ? " -->  " : "");
		cout << "  ДАТА И ВРЕМЯ ПРИБЫТИЯ:     "; displayDate(dateOfArrival, 1); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 4 ? " -->  " : "");
		cout << "  НОМЕР МАРШРУТА:     ";
		cout << cityRoute.routeNumber << string(14 - cityRoute.routeNumber.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 5 ? " -->  " : "") << "  Ввести      ";
		int16_t a = _getch();
		if (a == 224 && GetAsyncKeyState('F') != -32767) {
			a = _getch();
			if (a == 'H') row = (row + 5) % 6;
			else if (a == 'P') row = (row + 1) % 6;
		}else {
			if (a == 13 && row == 5) {
				if (checkingFileInputOutput::cityRouteCorrect(cityRoute, dateOfDeparture, dateOfArrival)) {
					if (flag) {
						ofstream file("files/CityFlights.txt", ios::app);
						file << cityRoute.pointOfDeparture << ' ' << cityRoute.arrivalPoint << ' '
							<< dateOfDeparture[0] << dateOfDeparture[1] << ' ' << dateOfDeparture[2] << dateOfDeparture[3]
							<< ' ' << dateOfDeparture[4] << dateOfDeparture[5] << dateOfDeparture[6] << dateOfDeparture[7] << ' '
							<< dateOfDeparture[8] << dateOfDeparture[9] << ' ' << dateOfDeparture[10] << dateOfDeparture[11] << ' '
							<< dateOfArrival[0] << dateOfArrival[1] << ' ' << dateOfArrival[2] << dateOfArrival[3]
							<< ' ' << dateOfArrival[4] << dateOfArrival[5] << dateOfArrival[6] << dateOfArrival[7] << ' '
							<< dateOfArrival[8] << dateOfArrival[9] << ' ' << dateOfArrival[10] << dateOfArrival[11] << ' ' << cityRoute.routeNumber << '\n';

						file.close();
						cityRoute.dateOfDeparture = Date(dateOfDeparture);
						cityRoute.dateOfArrival = Date(dateOfArrival);
						this->croute.push_back(cityRoute);
						waitingForChar("Запись успешно добавлена. Для продолжения нажмите любую клавишу");
						return;
					}
					else {
						cityRoute.dateOfDeparture = Date(dateOfDeparture);
						cityRoute.dateOfArrival = Date(dateOfArrival);
						waitingForChar("Запись успешно изменена. Для продолжения нажмите любую клавишу");
						return;
					}
				}
			}
			if ((a >= '0' && a <= '9') && (row == 2 || row == 3)) {
				if (row == 2 && dateOfDeparture.size() < 12) dateOfDeparture += a;
				else if (row == 3 && dateOfArrival.size() < 12) dateOfArrival += a;
			}
			if (((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223) || (a >= '0' && a <= '9'))
				&& row == 4 && cityRoute.routeNumber.size() < 4) cityRoute.routeNumber += a;
			else if ((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) {
				if (!row && cityRoute.pointOfDeparture.size() < 14) cityRoute.pointOfDeparture += a;
				else if (row == 1 && cityRoute.arrivalPoint.size() < 14) cityRoute.arrivalPoint += a;
			}
			else if (a == 8 && row < 5) {
				if (!row && !cityRoute.pointOfDeparture.empty()) cityRoute.pointOfDeparture.erase(cityRoute.pointOfDeparture.end() - 1);
				else if (row == 1 && !cityRoute.arrivalPoint.empty())cityRoute.arrivalPoint.erase(cityRoute.arrivalPoint.end() - 1);
				else if (row == 2 && !dateOfDeparture.empty()) dateOfDeparture.erase(dateOfDeparture.end() - 1);
				else if (row == 3 && !dateOfArrival.empty()) dateOfArrival.erase(dateOfArrival.end() - 1);
				else if (row == 4 && !cityRoute.routeNumber.empty())cityRoute.routeNumber.erase(cityRoute.routeNumber.end() - 1);
			}
		}
	}
}
void InternationalFlights::addElement(InternationalRoute& iroute, string dateOfArrival, string dateOfDeparture, bool flag) {
	int8_t row = 0, c = 0, d = 0;
	while (true) {
		system("cls");
		cout << "\n----------------------------------------------------\n";
		cout << (!row ? " -->  " : "") << "  ПУНКТ ОТПРАВЛЕНИЯ:         ";
		cout << iroute.pointOfDeparture << string(14 - iroute.pointOfDeparture.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 1 ? " -->  " : "") << "  ПУНКТ ПРИБЫТИЯ:            ";
		cout << iroute.arrivalPoint << string(14 - iroute.arrivalPoint.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 2 ? " -->  " : "");
		cout << "  ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ:  "; displayDate(dateOfDeparture, 1); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 3 ? " -->  " : "");
		cout << "  ДАТА И ВРЕМЯ ПРИБЫТИЯ:     "; displayDate(dateOfArrival, 1); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 4 ? " -->  " : "") << "  СТРАНА ПРИБЫТИЯ:           ";
		cout << iroute.countryOfArrival << string(14 - iroute.countryOfArrival.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 5 ? " -->  " : "") << "  ТРЕБУЕТСЯ ЛИ ВИЗА Да/Нет:         ";
		cout << iroute.visa << string(14 - iroute.visa.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 6 ? " -->  " : "") << "  НОМЕР МАРШРУТА:         ";
		cout << iroute.routeNumber << string(14 - iroute.routeNumber.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 7 ? " -->  " : "") << "  Ввести      ";
		int16_t a = _getch();
		if (a == 224 && GetAsyncKeyState('F') != -32767) {
			a = _getch();
			if (a == 'H') row = (row + 7) % 8;
			else if (a == 'P') row = (row + 1) % 8;
		}else {
			if (a == 13 && row == 7) {
				if (checkingFileInputOutput::InternationalRouteCorrect(iroute, dateOfDeparture, dateOfArrival)) {
					if (flag) {
						ofstream file("files/InternationalFlights.txt", ios::app);
						file << iroute.pointOfDeparture << ' ' << iroute.arrivalPoint << ' '
							<< dateOfDeparture[0] << dateOfDeparture[1] << ' ' << dateOfDeparture[2] << dateOfDeparture[3]
							<< ' ' << dateOfDeparture[4] << dateOfDeparture[5] << dateOfDeparture[6] << dateOfDeparture[7] << ' '
							<< dateOfDeparture[8] << dateOfDeparture[9] << ' ' << dateOfDeparture[10] << dateOfDeparture[11] << ' '
							<< dateOfArrival[0] << dateOfArrival[1] << ' ' << dateOfArrival[2] << dateOfArrival[3]
							<< ' ' << dateOfArrival[4] << dateOfArrival[5] << dateOfArrival[6] << dateOfArrival[7] << ' '
							<< dateOfArrival[8] << dateOfArrival[9] << ' ' << dateOfArrival[10] << dateOfArrival[11] << ' '
							<< iroute.countryOfArrival << ' ' << iroute.visa << ' ' << iroute.routeNumber << '\n';

						file.close();
						iroute.dateOfDeparture = Date(dateOfDeparture);
						iroute.dateOfArrival = Date(dateOfArrival);
						this->iroute.push_back(iroute);
						waitingForChar("Запись успешно добавлена. Для продолжения нажмите любую клавишу");
						return;
					}
					else {
						iroute.dateOfDeparture = Date(dateOfDeparture);
						iroute.dateOfArrival = Date(dateOfArrival);
						waitingForChar("Запись успешно изменена. Для продолжения нажмите любую клавишу");
						return;
					}
				}
			}
			if (((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) && (row == 0 || row == 1)) {
				if (!row && iroute.pointOfDeparture.size() < 14) iroute.pointOfDeparture += a;
				else if (row == 1 && iroute.arrivalPoint.size() < 14) iroute.arrivalPoint += a;
			}
			if ((((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) || (a >= '0' && a <= '9'))
				&& row == 6 && iroute.routeNumber.size() < 4) iroute.routeNumber += a;
			if ((a >= '0' && a <= '9') && (row == 2 || row == 3)) {
				if (row == 2 && dateOfDeparture.size() < 12) dateOfDeparture += a;
				else if (row == 3 && dateOfArrival.size() < 12) dateOfArrival += a;
			}
			if (((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) && (row == 4 || row == 5)) {
				if (iroute.countryOfArrival.size() < 14 && row == 4) iroute.countryOfArrival += a;
				else if (row == 5) {
					if (a == 196 && c == 0 && d == 0) { c = 1; iroute.visa += a; }
					if (a == 224 && c == 1) { c = 2; iroute.visa += a; }
					if (a == 205 && d == 0 && c == 0) { d = 1; iroute.visa += a; }
					if (a == 229 && d == 1) { d = 2; iroute.visa += a; }
					if (a == 242 && d == 2) { d = 3; iroute.visa += a; }
				}
			}
			if (a == 8 && row < 7) {
				if (!row && !iroute.pointOfDeparture.empty()) iroute.pointOfDeparture.erase(iroute.pointOfDeparture.end() - 1);
				else if (row == 1 && !iroute.arrivalPoint.empty())iroute.arrivalPoint.erase(iroute.arrivalPoint.end() - 1);
				else if (row == 2 && !dateOfDeparture.empty()) dateOfDeparture.erase(dateOfDeparture.end() - 1);
				else if (row == 3 && !dateOfArrival.empty()) dateOfArrival.erase(dateOfArrival.end() - 1);
				else if (row == 4 && !iroute.countryOfArrival.empty()) iroute.countryOfArrival.erase(iroute.countryOfArrival.end() - 1);
				else if (row == 5 && !iroute.visa.empty()) { iroute.visa.erase(iroute.visa.end() - 1); if (c > 0) c--; else if (d > 0) d--; }
				else if (row == 6 && !iroute.routeNumber.empty()) iroute.routeNumber.erase(iroute.routeNumber.end() - 1);
			}
		}
	}
}
void Buses::addElement(Buses& bus, bool flag) {
	int8_t row = 0, i = 0, j = 0, c = 0, d = 0, e = 0, f = 0, r = 0, z = 0;
	string str1("Международный"), str2("Региональный"), str3("Бизнес"), str4("Эконом");
	while (true) {
		system("cls");
		cout << "\n----------------------------------------------------\n";
		cout << (!row ? " -->  " : "") << "  ТИП ТРАНСПОРТА:          ";
		cout << bus.transportType << string(14 - bus.transportType.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 1 ? " -->  " : "") << "  НОМЕР МАРШРУТА:          ";
		cout << bus.routeNumber << string(14 - bus.routeNumber.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 2 ? " -->  " : "") << "  МАРКА ТРАНСПОРТА:        ";
		cout << bus.brand << string(14 - bus.brand.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 3 ? " -->  " : "") << "  ЦЕНА БИЛЕТА(BYN):        ";
		cout << bus.price << string(14 - bus.price.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 4 ? " -->  " : "") << "  КОЛ-ВО МЕСТ:             ";
		cout << bus.number_of_seats << string(14 - bus.number_of_seats.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 5 ? " -->  " : "") << "  КЛАСС АВТОБУСА:          ";
		cout << bus.bus_class << string(14 - bus.bus_class.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 6 ? " -->  " : "") << "  КОЛ-ВО ЭТАЖЕЙ:           ";
		cout << bus.number_of_floors << string(14 - bus.number_of_floors.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 7 ? " -->  " : "") << "  Ввести      ";
		int16_t a = _getch();
		if (a == 224 && GetAsyncKeyState('F') != -32767) {
			a = _getch();
			if (a == 'H') row = (row + 7) % 8;
			else if (a == 'P') row = (row + 1) % 8;
		}else {
			if (a == 13 && row == 7) {
				if (checkingFileInputOutput::busCorrect(bus)) {
					if (flag) {
						ofstream file("files/Buses.txt", ios::app);
						file << bus.transportType << ' ' << bus.routeNumber << ' ' << bus.brand << ' ' << bus.price << ' ' << bus.number_of_seats
							<< ' ' << bus.bus_class << ' ' << bus.number_of_floors << '\n';
						file.close();
						this->buses.push_back(bus);
						waitingForChar("Запись успешно добавлена. Для продолжения нажмите любую клавишу");
						return;
					}
					else {
						waitingForChar("Запись успешно изменена. Для продолжения нажмите любую клавишу");
						return;
					}
				}
			}
			if (((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) || (a >= '0' && a <= '9')) {
				if (row == 1 && bus.routeNumber.size() < 4) bus.routeNumber += a;
			}
			if (((a >= '0' && a <= '9') || a == '.') && row == 3) {
				if (bus.price.size() < 14) bus.price += a;
			}
			if ((a >= '0' && a <= '9') && (row == 4 || row == 6)) {
				if (row == 4 && bus.number_of_seats.size() < 14) bus.number_of_seats += a;
				else if (row == 6 && bus.number_of_floors.size() < 14) bus.number_of_floors += a;
			}
			if (((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) && (row == 0 || row == 2 || row == 5)) {
				if (row == 0 && bus.transportType.size() < 14) bus.transportType += a;
				else if (row == 2 && bus.brand.size() < 14) bus.brand += a;
				else if (row == 5 && bus.bus_class.size() < 14) bus.bus_class += a;
			}
			if (a == 8 && row < 7) {
				if (!row && !bus.transportType.empty()) { bus.transportType.erase(bus.transportType.end() - 1); if (e > 0) { e--; r--; } else if (f > 0) { f--; z--; } }
				else if (row == 1 && !bus.routeNumber.empty())bus.routeNumber.erase(bus.routeNumber.end() - 1);
				else if (row == 2 && !bus.brand.empty()) bus.brand.erase(bus.brand.end() - 1);
				else if (row == 3 && !bus.price.empty()) bus.price.erase(bus.price.end() - 1);
				else if (row == 4 && !bus.number_of_seats.empty()) bus.number_of_seats.erase(bus.number_of_seats.end() - 1);
				else if (row == 5 && !bus.bus_class.empty()) { bus.bus_class.erase(bus.bus_class.end() - 1); if (c > 0) { c--; i--; } else if (d > 0) { d--; j--; } }
				else if (row == 6 && !bus.number_of_floors.empty()) bus.number_of_floors.erase(bus.number_of_floors.end() - 1);
			}
		}
	}
}
void header(vector<InternationalRoute>& iroute) {
	cout << "------------------------------------------------------------------------------------------------------------------------------------\n" <<
		" №|ПУНКТ ОТПРАВЛЕНИЯ|ПУНКТ ПРИБЫТИЯ|ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ|ДАТА И ВРЕМЯ ПРИБЫТИЯ|СТРАНА ПРИБЫТИЯ|ТРЕБУЕТСЯ ЛИ ВИЗА|НОМЕР МАРШРУТА|\n" <<
		"------------------------------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < iroute.size(); ++i) {
		cout.width(2);
		cout << i + 1 << "|";
		cout.width(17);
		cout << iroute[i].pointOfDeparture << "|";
		cout.width(14);
		cout << iroute[i].arrivalPoint << "|";
		cout.width(10);
		cout << iroute[i].dateOfDeparture.day << '.' << iroute[i].dateOfDeparture.month << '.' << iroute[i].dateOfDeparture.year << " "
			<< iroute[i].dateOfDeparture.hour << ":" << iroute[i].dateOfDeparture.minutes << "|";
		cout.width(7);
		cout << iroute[i].dateOfArrival.day << '.' << iroute[i].dateOfArrival.month << '.' << iroute[i].dateOfArrival.year << " "
			<< iroute[i].dateOfArrival.hour << ":" << iroute[i].dateOfArrival.minutes << "|";

		cout.width(15);
		cout << iroute[i].countryOfArrival << "|";
		cout.width(10);
		cout << iroute[i].visa << "       |";
		cout.width(10);
		cout << iroute[i].routeNumber << "    |\n";
		cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
	}
}
void header(vector<CityRoute>& croute) {
	cout << "--------------------------------------------------------------------------------------------------\n" <<
		" №|ПУНКТ ОТПРАВЛЕНИЯ|ПУНКТ ПРИБЫТИЯ|ДАТА И ВРЕМЯ ОТПРАВЛЕНИЯ|ДАТА И ВРЕМЯ ПРИБЫТИЯ|НОМЕР МАРШРУТА|\n" <<
		"--------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < croute.size(); ++i) {
		cout.width(2);
		cout << i + 1 << "|";
		cout.width(17);
		cout << croute[i].pointOfDeparture << "|";
		cout.width(14);
		cout << croute[i].arrivalPoint << "|";
		cout.width(10);
		cout << croute[i].dateOfDeparture.day << '.' << croute[i].dateOfDeparture.month << '.' << croute[i].dateOfDeparture.year << " "
			<< croute[i].dateOfDeparture.hour << ":" << croute[i].dateOfDeparture.minutes << "|";
		cout.width(7);
		cout << croute[i].dateOfArrival.day << '.' << croute[i].dateOfArrival.month << '.' << croute[i].dateOfArrival.year << " "
			<< croute[i].dateOfArrival.hour << ":" << croute[i].dateOfArrival.minutes << "|";
		cout.width(10);
		cout << croute[i].routeNumber << "    |\n";
		cout << "--------------------------------------------------------------------------------------------------\n";
	}
}
template<class T>
void showIFlightsSearchTable(vector<T>& route, bool& exit, const string& str) {
	system("cls");
	char a;
	if (route.empty()) {
		while (true) {
			system("cls");
			cout << "Совпадений не найдено. Нажмите Enter, чтобы повторить поиск, и Esc, чтобы выйти";
			a = getPushedCharCode();
			if (a == VK_ESCAPE) { exit = true; return; }
			if (a == VK_RETURN) return;
		}
	}
	header(route);
	cout << "Для выхода нажмите Esc, а если желаете найти, работающие по данному(ым) маршруту(там) автобусы, нажмите Enter";
	while (true) {
		a = getPushedCharCode();
		if (a == VK_ESCAPE) { exit = true; return; }
		if (a == VK_RETURN) {
			int c = 0, f = 0;
			system("cls");
			Buses bus;
			bool d;
			if (!copyBusesFile(bus)) {
				for (int i = 0; i < route.size(); ++i) {
					d = true;
					for (int k = i + 1; k < route.size(); k++) {
						if (route[i].routeNumber == route[k].routeNumber) { k = route.size(); d = false; }
					}
					if (d) {
						for (int j = 0; j < bus.buses.size(); ++j)
							if ((bus.buses[j].transportType == str) && (bus.buses[j].routeNumber == route[i].routeNumber)) {
								if (c == 0) {
									system("cls");
									cout << "-------------------------------------------------------------------------------------------------------------\n" <<
										" № |ТИП ТРАНСПОРТА|НОМЕР МАРШРУТА|МАРКА ТРАНСПОРТА|ЦЕНА БИЛЕТА(BYN)|КОЛ-ВО МЕСТ|КЛАСС АВТОБУСА|КОЛ-ВО ЭТАЖЕЙ|\n" <<
										"-------------------------------------------------------------------------------------------------------------\n";
									c = 1;
								}

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
					}
					if (c) {
						cout << "Нажмите Enter, чтобы повторить поиск, и Esc, чтобы выйти";
						while (true) {
							a = getPushedCharCode();
							if (a == VK_ESCAPE) { exit = true; return; }
							if (a == VK_RETURN) return;
						}
					}
					else if (!c) {
						system("cls");
						cout << "Не найдено автобусов, работающих на данном маршруте. Нажмите Enter, чтобы повторить поиск, и Esc, чтобы выйти";
						while (true) {
							a = getPushedCharCode();
							if (a == VK_ESCAPE) { exit = true; return; }
							if (a == VK_RETURN) return;
						}
					}
				}
			}
		}
	}
}
void menuSearch(Flights& flight, bool user) {
	int8_t row = 0, row1;

	while (true) {
		system("cls");
		arrowMenu({ " Найти информацию об автобусах, работающих на международных рейсах","\n\n Найти информацию об автобусах, работающих на региональных ресах",
			"\n\n Отфильтровать информацию по стоимости забронированных международных билетов", "\n\n Отфильтровать информацию по стоимости забронированных региональных билетов",
			"\n\n Сортировать информацию о всех забронированных билетах по дате отправления(по возрастанию даты)", 
			"\n\n Сортировать информацию о всех забронированных билетах по дате прибытия(по возрастанию даты)", 
			"\n\n Сортировать информацию о всех забронированных билетах по цене(по убыванию цены)", "\n\n Назад" }, row);

		char a = getPushedCharCode();

		if (a == VK_UP) row = (row + 8 - 1) % 8;
		else if (a == VK_DOWN) row = (row + 1) % 8;
		else if (a == 13) {
			if (row == 0) {
				InternationalRoute iroute;
				if (!copyInternationalFlightsFile(flight)) {
					if (flight.iroute.empty()) waitingForChar("Файл пуст. Для возвращения нажмите любую кнопку");
					else searchCommonPointsTable(flight.iroute, iroute, string(), string(), 1);
				}
			}
			else if (row == 1) {
				CityRoute croute;
				if (!copyCityFlightsFile(flight)) {
					if (flight.croute.empty()) waitingForChar("Файл пуст. Для возвращения нажмите любую кнопку");
					else searchCommonPointsTable(flight.croute, croute, string(), string(), 2);
				}
			}
			else if (row == 2) {
				bool quit = false;
				Order<InternationalFlights> order;
				order.filterPrice(1, user, quit);
				while (!quit) {
					char a = getPushedCharCode();
					if (a == VK_ESCAPE) break;
				}
			}
			else if (row == 3) {
				bool quit = false;
				Order<CityFlights> order;
				order.filterPrice(2, user, quit);
				while (!quit) {
					char a = getPushedCharCode();
					if (a == VK_ESCAPE) break;
				}
			}
			else if (row == 4) {
				Order<InternationalFlights> order;
				order.sortDate(user);
				waitingForEsc();
			}
			else if (row == 5) {
				Order<InternationalFlights> order;
				order.sortDate(user, 1);
				waitingForEsc();
			}
			else if (row == 6) {
				Order<InternationalFlights> order;
				order.sortPrice(user);
				waitingForEsc();
			}
			else if (row == 7) break;
		}
	}
}
template <class T1, class T2>
void searchCommonPointsTable(vector<T1>& route, T2& route1, string dateOfDeparture, string dateOfArrival, int8_t b) {
	int8_t row = 0;
	while (true) {
		system("cls");
		cout << "\n----------------------------------------------------\n";
		cout << (!row ? " -->  " : "") << "  ПУНКТ ОТПРАВЛЕНИЯ:         ";
		cout << route1.pointOfDeparture << string(14 - route1.pointOfDeparture.size(), ' ') << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 1 ? " -->  " : "") << "  ПУНКТ ПРИБЫТИЯ:            ";
		cout << route1.arrivalPoint << string(14 - route1.arrivalPoint.size(), ' ') << "\n";

		cout << "\n----------------------------------------------------\n";
		cout << (row == 2 ? " -->  " : "");
		cout << "  ДАТА ОТПРАВЛЕНИЯ:          "; displayDate(dateOfDeparture, 2); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 3 ? " -->  " : "");
		cout << "  ДАТА ПРИБЫТИЯ:             "; displayDate(dateOfArrival, 2); cout << "\n";
		cout << "\n----------------------------------------------------\n";
		cout << (row == 4 ? " -->  " : "") << "  Ввести      ";

		uint8_t a = _getch();

		if (a == 224 && GetAsyncKeyState('F') != -32767) {
			a = _getch();
			if (a == 'H') row = (row + 4) % 5;
			else if (a == 'P') row = (row + 1) % 5;
		}
		if (a == 13 && row == 4) {
			if (b == 1) {
				if (routeCorrect(route1, dateOfDeparture, dateOfArrival)) {
					vector<T1> iroute;
					route1.dateOfDeparture = Date(dateOfDeparture, 1);
					route1.dateOfArrival = Date(dateOfArrival, 1);
					for (int i = 0; i < route.size(); ++i) {
						if (route1.pointOfDeparture == route[i].pointOfDeparture && route1.arrivalPoint == route[i].arrivalPoint && 
							route1.dateOfDeparture == route[i].dateOfDeparture && route1.dateOfArrival == route[i].dateOfArrival) {
							iroute.push_back(route[i]);
						}
					}
					bool exit = false;
					showIFlightsSearchTable(iroute, exit, "Международный");
					if (exit) return;
				}
			}
			else if (b == 2) {
				if (routeCorrect(route1, dateOfDeparture, dateOfArrival)) {
					vector<T1> croute;
					route1.dateOfDeparture = Date(dateOfDeparture, 1);
					route1.dateOfArrival = Date(dateOfArrival, 1);
					for (int i = 0; i < route.size(); ++i) {
						if (route1.pointOfDeparture == route[i].pointOfDeparture && route1.arrivalPoint == route[i].arrivalPoint && 
							route1.dateOfDeparture == route[i].dateOfDeparture && route1.dateOfArrival == route[i].dateOfArrival) {
							croute.push_back(route[i]);		
						}
					}
					bool exit = false;
					showIFlightsSearchTable(croute, exit, "Региональный");
					if (exit) return;
				}
			}
		}
		if ((a >= '0' && a <= '9') && (row == 2 || row == 3)) {
			if (row == 2 && dateOfDeparture.size() < 8) dateOfDeparture += a;
			else if (row == 3 && dateOfArrival.size() < 8) dateOfArrival += a;
		}
		else if ((a >= 224 && a <= 255) || a == 184 || a == 168 || (a >= 192 && a <= 223)) {
			if (!row && route1.pointOfDeparture.size() < 14) route1.pointOfDeparture += a;
			else if (row == 1 && route1.arrivalPoint.size() < 14) route1.arrivalPoint += a;
		}
		else if (a == 8 && row < 4) {
			if (!row && !route1.pointOfDeparture.empty()) route1.pointOfDeparture.erase(route1.pointOfDeparture.end() - 1);
			else if (row == 1 && !route1.arrivalPoint.empty())route1.arrivalPoint.erase(route1.arrivalPoint.end() - 1);
			else if (row == 2 && !dateOfDeparture.empty()) dateOfDeparture.erase(dateOfDeparture.end() - 1);
			else if (row == 3 && !dateOfArrival.empty()) dateOfArrival.erase(dateOfArrival.end() - 1);
		}
	}
}
template<class T>
bool routeCorrect(T& route, const string& dateOfDeparture, const string& dateOfArrival) {
	if (route.pointOfDeparture.empty() || route.arrivalPoint.empty()) {
		waitingForChar("Вы заполнили не все поля. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	if (dateOfDeparture.size() != 8 || dateOfArrival.size() != 8) {
		waitingForChar("Дата должна содержать 8 цифр. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	Date tmp(dateOfDeparture, 1), tmp1(dateOfArrival, 1);
	if (!checkingFileInputOutput::dateCorrect(stringToInt(tmp.day), stringToInt(tmp.month), stringToInt(tmp.year)) ||
		!checkingFileInputOutput::dateCorrect(stringToInt(tmp1.day), stringToInt(tmp1.month), stringToInt(tmp1.year))) {
		waitingForChar("Введенной даты не существует. Для продолжения нажмите любую клавишу");
		return false;
	}

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string currTime = (ltm->tm_mday < 10 ? "0" + to_string(ltm->tm_mday) : to_string(ltm->tm_mday))
		+ (ltm->tm_mon < 9 ? "0" + to_string(1 + ltm->tm_mon) : to_string(1 + ltm->tm_mon))
		+ to_string(1900 + ltm->tm_year) + to_string(ltm->tm_hour) + to_string(ltm->tm_min);

	if (tmp < Date(currTime) || tmp1 < Date(currTime)) {
		waitingForChar("Введенная дата меньше настоящей даты. Для продолжения нажмите любую клавишу");
		return false;
	}
	if (tmp > tmp1) {
		waitingForChar("Дата отправления больше даты прибытия. Для продолжения нажмите любую клавишу");
		return false;
	}
	return true;
}
void CityFlights::changeData(vector<CityRoute>& croute) {
	string a;
	
	do {
		showTable(false);
		if (croute.empty()) { waitingForEsc(); return; }
		cout << "Введите номер рейса, информацию о котором вы хотите изменить ";
		getline(cin, a);
		if (a == "esc") return;
		if (a.empty()) continue;
		if (stringToInt(a) == -1 || stringToInt(a) > croute.size() || stringToInt(a) == 0) {
			waitingForChar("Вы ввели неверное значение. Для повторного ввода нажмите любую клавишу");
		}
		else break;
	} while (true);
	int b = stringToInt(a) - 1;
	string dateOfDeparture = croute[b].dateOfDeparture.day + croute[b].dateOfDeparture.month + croute[b].dateOfDeparture.year + croute[b].dateOfDeparture.hour + croute[b].dateOfDeparture.minutes;
	string dateOfArrival = croute[b].dateOfArrival.day + croute[b].dateOfArrival.month + croute[b].dateOfArrival.year + croute[b].dateOfArrival.hour + croute[b].dateOfArrival.minutes;
	addElement(croute[b], dateOfArrival, dateOfDeparture, false);
	rewriteFile(croute);
}
void InternationalFlights::changeData(vector<InternationalRoute>& iroute) {
	string a;
	
	do {
		showTable(false);
		if (iroute.empty()) { waitingForEsc(); return; }
		cout << "Введите номер рейса, информацию о котором вы хотите изменить ";
		getline(cin, a);
		if (a == "esc") return;
		if (a.empty()) continue;
		else if (stringToInt(a) == -1 || stringToInt(a) > iroute.size() || stringToInt(a) == 0) {
			waitingForChar("Вы ввели неверное значение. Для повторного ввода нажмите любую клавишу");
		}
		else break;
	} while (true);
	int b = stringToInt(a) - 1;
	string dateOfDeparture = iroute[b].dateOfDeparture.day + iroute[b].dateOfDeparture.month + iroute[b].dateOfDeparture.year + iroute[b].dateOfDeparture.hour + iroute[b].dateOfDeparture.minutes;
	string dateOfArrival = iroute[b].dateOfArrival.day + iroute[b].dateOfArrival.month + iroute[b].dateOfArrival.year + iroute[b].dateOfArrival.hour + iroute[b].dateOfArrival.minutes;
	addElement(iroute[b], dateOfArrival, dateOfDeparture, false);
	rewriteFile(iroute);
}
void Buses::changeData(Buses& bus) {
	string a;	
	do {
		showTable(false);
		if (bus.buses.empty()) { waitingForEsc(); return; }
		cout << "Введите номер автобуса, информацию о котором вы хотите изменить ";
		getline(cin, a);
		if (a == "esc") return;
		if (a.empty()) continue;
		else if (stringToInt(a) == -1 || stringToInt(a) > bus.buses.size() || stringToInt(a) == 0) {
			waitingForChar("Вы ввели неверное значение. Для повторного ввода нажмите любую клавишу");
		}
		else break;
	} while (true);
	int b = stringToInt(a) - 1;
	addElement(bus.buses[b], false);
	rewriteFile(bus.buses);
}
template<class T>
void deleteData(vector<T>& dataDel, int8_t c) {
	string a, temp;
	
	do {
		if (c == 1) { InternationalFlights iflight; iflight.showTable(false);}
		else if (c == 2) { CityFlights cflight;  cflight.showTable(false); }
		else if (c == 3) { Buses bus;  bus.showTable(false); }

		cout << "Введите номер элемента, который хотите удалить ";
		getline(cin, a);
		if (a == "esc") return;
		if (a.empty()) continue;
		if (stringToInt(a) == -1 || stringToInt(a) > dataDel.size() || stringToInt(a) == 0) {
			waitingForChar("Вы ввели неверное значение. Для повторного ввода нажмите любую клавишу");
		}
		else break;
	} while (true);
	int b = stringToInt(a) - 1;

	do {
		temp = getLoginOrString("Введите \"Да\" для удаления элемента. Для выхода введите esc");
		if (temp == "esc" || temp == "Да") break;
	} while (temp.empty());
	if (temp == "Да") {
		dataDel.erase(dataDel.begin() + b);
		rewriteFile(dataDel);
		waitingForChar("Элемент успешно удален. Нажмите любую клавишу");
	}
	else if (temp == "esc") return;
}
void addOrderToFile(CityRoute& croute, Buses& bus) {
	ofstream file("files/Orders.txt", ios::app);
	string str;
	User::getCurrentUser(str);
	file << "1" << ' ' << croute.pointOfDeparture << ' ' << croute.arrivalPoint << ' '
		<< croute.dateOfDeparture.day << ' ' << croute.dateOfDeparture.month << ' ' << croute.dateOfDeparture.year << ' ' << croute.dateOfDeparture.hour << ' ' << croute.dateOfDeparture.minutes << ' '
		<< croute.dateOfArrival.day << ' ' << croute.dateOfArrival.month << ' ' << croute.dateOfArrival.year << ' ' << croute.dateOfArrival.hour << ' ' << croute.dateOfArrival.minutes << ' ' << croute.routeNumber
		<< ' ' << str << ' ' << bus.transportType << ' ' << bus.routeNumber << ' ' << bus.brand << ' ' << bus.price << ' ' << bus.number_of_seats << ' ' << bus.bus_class << ' ' << bus.number_of_floors << '\n';

	file << flush;
	file.close();
}
void addOrderToFile(InternationalRoute& iroute, Buses& bus) {
	ofstream file("files/Orders.txt", ios::app);
	string str;
	User::getCurrentUser(str);
	file << "2" << ' ' << iroute.pointOfDeparture << ' ' << iroute.arrivalPoint << ' '
		<< iroute.dateOfDeparture.day << ' ' << iroute.dateOfDeparture.month << ' ' << iroute.dateOfDeparture.year << ' ' << iroute.dateOfDeparture.hour
		<< ' ' << iroute.dateOfDeparture.minutes << ' ' << iroute.dateOfArrival.day << ' ' << iroute.dateOfArrival.month << ' ' << iroute.dateOfArrival.year << ' '
		<< iroute.dateOfArrival.hour << ' ' << iroute.dateOfArrival.minutes << ' ' << iroute.countryOfArrival << ' ' << iroute.visa << ' ' << iroute.routeNumber << ' ' << str << ' '
		<< bus.transportType << ' ' << bus.routeNumber << ' ' << bus.brand << ' ' << bus.price << ' ' << bus.number_of_seats << ' ' << bus.bus_class << ' ' << bus.number_of_floors << '\n';

	file << flush;
	file.close();
}
