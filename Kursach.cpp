#include "Namespace.h"
#include "BusesAndFlights.h"
#include "Admin.h"


int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    mainMenu();
    return 0;
}
void mainMenu() {
	int8_t row = 0;

	while (true) {
		system("cls");
		arrowMenu({"Войти как администратор","\n\nВойти как пользователь","\n\nВыход" }, row);

		int8_t a = getPushedCharCode();

		if (a == VK_UP) row = (row + 2) % 3;
		else if (a == VK_DOWN) row = (row + 1) % 3;
		else if (a == 13) {
			if (row == 0) adminAccount();
			else if (row == 1) userAccount();
			else if (row == 2) {
				system("cls");
				break;
			}
		}
	}
}
void arrowMenu(vector<string> message, int8_t& row) {
	for (int i = 0; (unsigned long long)i < message.size(); ++i) {
		cout << message.at(i);
		if (row == i) cout <<"   <--";
	}
	cout << "\n\n" << flush;
}
int8_t getPushedCharCode() {
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD rec;
	DWORD numRead;
	while (ReadConsoleInput(hIn, &rec, 1, &numRead) && numRead == 1) {
		if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown) {
			return rec.Event.KeyEvent.wVirtualKeyCode;
		}
	}
	return 0;
}
string getLoginOrString(const string& message) {
	system("cls");
	string login;
	cout << message << endl;
	getline(cin, login);
	return login;
}
string passwordStars(const string& message) {
	string password;
	char a = '1';
	system("cls");
	cout << message << '\n';
	while ((a = _getch()) != 13) {
		if ((int)a == 8) {
			if (password.empty()) continue;
			password.erase(password.size() - 1, password.size());
			cout << '\b' << ' ' << '\b';
		}
		else {
			password += a;
			cout << '*';
		}
	}
	return password;
}
string setLogin(int8_t a, bool& accessGranted, bool& quit) {
	string login;
	bool error;
	if (a == 0) { if (accessGranted) { 
		login = getLoginOrString("Введите логин. Для выхода введите esc"); 
	} 
	else login = getLoginOrString("Введите заново логин. Для выхода введите esc"); }
	else if (a == 1) { 
		login = getLoginOrString("Неправильный логин и/или пароль. Повторите ввод логина и пароля. Для выхода введите esc"); 
	}
	else if (a == 2) {
		login = getLoginOrString("Аккаунт с таким логином уже существует. Повторите ввод логина и пароля. Для выхода введите esc");
	}
	else if (a == 3) {
		if (accessGranted) { 
			login = getLoginOrString("Введите новый логин. Для выхода введите esc"); 
		} 
		else login = getLoginOrString("Введите заново логин. Для выхода введите esc");
	}
	do {
		error = false;
		if (login == "esc") {
			quit = true;
			return "";
		}
		if (login[0] == ' ') {
			error = true;
			login = getLoginOrString("Логин не может начинаться с пробела. Повторите ввод логина. Для выхода введите esc");
			continue;
		}
		if (login.size() < 4 || login.size() > 20) {
			error = true;
			if (!login.empty())	login = getLoginOrString("Длина логина должна быть не менее 4 символов и не более 20 символов. Повторите ввод логина. Для выхода введите esc");
			else login = getLoginOrString("Логин не может быть пустым. Повторите ввод логина. Для выхода введите esc");
			continue;
		}
		for (auto a : login) {
			if (!((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || a == ' ')) {
				error = true;
				login = getLoginOrString("Логин содержит недопустимые символы. Повторите ввод логина. Для выхода введите esc");
				break;
			}
		}
	} while (error);
	return login;
}
string setPassword(bool& quit, bool flag) {
	bool error;
	string password;
	if(flag) password = passwordStars("Введите пароль. Для выхода введите esc");
	else  password = passwordStars("Введите новый пароль. Для выхода введите esc");
	do {
		error = false;
		if (password == "esc") {
			quit = true;
			return "";
		}
		if (password.size() < 8 || password.size() > 20) {
			error = true;
			if (!password.empty()) password = passwordStars("Пароль должен содержать минимум 8 и максимум 20 символов. Повторите ввод пароля. Для выхода введите esc");
			else password = passwordStars("Пароль не может быть пустым");
			continue;
		}
		for (auto a : password) {
			if (!((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))) {
				error = true;
				password = passwordStars("Пароль содержит недопустимые символы. Повторите ввод пароля. Для выхода введите esc");
				break;
			}
		}
	} while (error);
	return password;
}
void waitingForEsc() {
	while (true) {
		char a = getPushedCharCode();
		if (a == VK_ESCAPE) break;
	}
}
void waitingForChar(const string& message) {
	system("cls");
	string login;
	cout << message << endl;
	char a = getPushedCharCode();
}
void rewriteFile(const vector<CityRoute>& croute) {
	ofstream file("files/CityFlights.txt", ios::trunc);
	for (const auto& i : croute)
		file << i.pointOfDeparture << ' ' << i.arrivalPoint << ' '
		<< i.dateOfDeparture.day << ' ' << i.dateOfDeparture.month << ' ' << i.dateOfDeparture.year << ' ' << i.dateOfDeparture.hour
		<< ' ' << i.dateOfDeparture.minutes << ' ' << i.dateOfArrival.day << ' ' << i.dateOfArrival.month << ' ' << i.dateOfArrival.year << ' '
		<< i.dateOfArrival.hour << ' ' << i.dateOfArrival.minutes << ' ' << i.routeNumber << '\n';
	file << flush;
	file.close();
}
void rewriteFile(const vector<InternationalRoute>& iroute) {
	ofstream file("files/InternationalFlights.txt", ios::trunc);
	for (const auto& i : iroute)
		file << i.pointOfDeparture << ' ' << i.arrivalPoint << ' '
		<< i.dateOfDeparture.day << ' ' << i.dateOfDeparture.month << ' ' << i.dateOfDeparture.year << ' ' << i.dateOfDeparture.hour
		<< ' ' << i.dateOfDeparture.minutes << ' ' << i.dateOfArrival.day << ' ' << i.dateOfArrival.month << ' ' << i.dateOfArrival.year << ' '
		<< i.dateOfArrival.hour << ' ' << i.dateOfArrival.minutes << ' ' << i.countryOfArrival << ' ' << i.visa << ' ' << i.routeNumber << '\n';
	file << flush;
	file.close();
}
void rewriteFile(const vector<Buses>& bus) {
	ofstream file("files/Buses.txt", ios::trunc);
	for (const auto& i : bus)
		file << i.transportType << ' ' << i.routeNumber << ' ' << i.brand << ' ' << i.price << ' ' << i.number_of_seats
		<< ' ' << i.bus_class << ' ' << i.number_of_floors << '\n';
	file << flush;
	file.close();
}
void rewriteFile(vector<User>& users, const string& path) {
	ofstream file(path, ios::trunc);
	for (auto& i : users)
		file << i.getLogin() << '\n' << i.getPassword() << endl;
	file.close();
}
bool copyCityFlightsFile(Flights& cityFlights) {
	ifstream file("files/cityflights.txt");
	if (!cityFlights.croute.empty()) cityFlights.croute.erase(cityFlights.croute.begin(), cityFlights.croute.end());
	while (file) {
		CityRoute T;
		CityRoute *temp;
		temp = &T;

		file >> T.pointOfDeparture >> T.arrivalPoint >> T.dateOfDeparture.day >> T.dateOfDeparture.month >> T.dateOfDeparture.year
			>> T.dateOfDeparture.hour>> T.dateOfDeparture.minutes >> T.dateOfArrival.day >> T.dateOfArrival.month >> T.dateOfArrival.year
			>> T.dateOfArrival.hour >> T.dateOfArrival.minutes >> T.routeNumber;
		
		if (checkingFileInputOutput::CityFlightsVerification(*temp)) cityFlights.croute.push_back(*temp);
		else {
			system("cls");
			cout << "Файл поврежден. Для возвращения нажмите Esc";
			return true;
		}
	}
	if (!cityFlights.croute.empty()) cityFlights.croute.pop_back();
	file.close();
	return false;
}
bool copyInternationalFlightsFile(Flights& internationalFlights) {
	ifstream file("files/internationalflights.txt");
	if (!internationalFlights.iroute.empty()) internationalFlights.iroute.erase(internationalFlights.iroute.begin(), internationalFlights.iroute.end());
	while (file) {
		InternationalRoute temp;
		CityRoute* T;
		T = &temp;

		file >> temp.pointOfDeparture >> temp.arrivalPoint >> temp.dateOfDeparture.day >> temp.dateOfDeparture.month >> temp.dateOfDeparture.year >>
			temp.dateOfDeparture.hour >> temp.dateOfDeparture.minutes
			>> temp.dateOfArrival.day >> temp.dateOfArrival.month >> temp.dateOfArrival.year >> temp.dateOfArrival.hour >> temp.dateOfArrival.minutes >>
			temp.countryOfArrival >> temp.visa >> temp.routeNumber;

		if (checkingFileInputOutput::InternationalFlightsVerification(&temp) && checkingFileInputOutput::CityFlightsVerification(*T))
			internationalFlights.iroute.push_back(temp);
		else {
			system("cls");
			cout << "Файл поврежден. Для возвращения нажмите Esc";
			return true;
		}
	}
	if (!internationalFlights.iroute.empty()) internationalFlights.iroute.pop_back();
	file.close();
	return false;
}
bool copyBusesFile(Buses& bus) {
	ifstream file("files/Buses.txt");
	if (!bus.buses.empty()) bus.buses.erase(bus.buses.begin(), bus.buses.end());
	while (file) {
		Buses temp;

		file >> temp.transportType >> temp.routeNumber >> temp.brand >> temp.price >> temp.number_of_seats >>
			temp.bus_class >> temp.number_of_floors;

		if (checkingFileInputOutput::BusesVerification(temp))
			bus.buses.push_back(temp);
		else {
			system("cls");
			cout << "Файл поврежден. Для возвращения нажмите Esc";
			return true;
		}
	}
	if (!bus.buses.empty()) bus.buses.pop_back();
	file.close();
	return false;
}
int Date::countDays() const {
	return 372 * stringToInt(year) + 31 * stringToInt(month) + stringToInt(day);
}
bool operator==(const Date& l, const Date& r) {
	if (l.hour.empty() && l.minutes.empty()) return (l.day == r.day && l.year == r.year && l.month == r.month);
	else return (l.day == r.day && l.month == r.month && l.year == r.year && l.hour == r.hour && l.minutes == r.minutes);
}
bool operator<(const Date& l, const Date& r) {
	if(l.hour.empty() && l.minutes.empty())	return l.countDays() < r.countDays();
	else {
		if(l.countDays() < r.countDays()) return true;
		if (l.countDays() == r.countDays()) {
			if (l.hour < r.hour) return true;
			if (l.hour == r.hour) {
				if (l.minutes < r.minutes) return true;
				return false;
			}
			else return false;
		}
		else return false;
	}
}
bool operator>(const Date& l, const Date& r) {
	if (l.hour.empty() && l.minutes.empty())	return l.countDays() > r.countDays();
	else {
		if (l.countDays() > r.countDays()) return true;
		if (l.countDays() == r.countDays()) {
			if (l.hour > r.hour) return true;
			if (l.hour == r.hour) {
				if (l.minutes > r.minutes) 
					return true;
				return false;
			}
			else return false;
		}
		else return false;
	}
}
int stringToInt(const string& str) {
	int res = 0;
	if (str.size() < 10) {
		for (auto i : str)
			if (i >= '0' && i <= '9') res = 10 * res + i - '0';
			else return -1;
		return res;
	}
	return -1;
}
Date::Date(){}
Date::Date(const string& str) {
	if (str.size() == 12) {
		day += str[0];
		day += str[1];
		month += str[2];
		month += str[3];
		year += str[4];
		year += str[5];
		year += str[6];
		year += str[7];
		hour += str[8];
		hour += str[9];
		minutes += str[10];
		minutes += str[11];
	}
}
Date::Date(const string& str, int8_t a) {
	if (str.size() == 8) {
		day += str[0];
		day += str[1];
		month += str[2];
		month += str[3];
		year += str[4];
		year += str[5];
		year += str[6];
		year += str[7];
	}
}
void displayDate(string date, int8_t a) {
	int8_t index = 0;
	if (a == 1) {
		string str = "ДД.ММ.ГГГГ ЧЧ:ММ";
		for (int8_t i = 0; i < 16; ++i) {
			if (index + 1 > date.size() || index == 12) cout << str[i];
			else {
				if (i == 2 || i == 5) cout << '.';
				else if (i == 10) cout << ' ';
				else if (i == 13) cout << ':';
				else cout << date[index++];
			}
		}
	}
	else if (a == 2) {
		string str = "ДД.ММ.ГГГГ";
		for (int8_t i = 0; i < 10; ++i) {
			if (index + 1 > date.size() || index == 8) wcout << str[i];
			else {
				if (i == 2 || i == 5) cout << '.';
				else cout << date[index++];
			}
		}
	}
}
