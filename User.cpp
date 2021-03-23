#include "Namespace.h"
#include "User.h"
#include "BusesAndFlights.h"
#include "Order.h"

void userAccount() {
	int8_t row = 0;
	User user;
	vector<User> users;
	readFile(users, "files/users.txt");
	while (true) {
		system("cls");
		if (users.empty()) arrowMenu({ "  Создать аккаунт","  Назад" }, row);
		else arrowMenu({ "  Войти в аккаунт", "\n\n  Создать аккаунт","\n\n  Назад" }, row);

		char a=getPushedCharCode();
		if (a == VK_UP) row = (row + 2) % 3;
		else if (a == VK_DOWN) row = (row + 1) % 3;
		else if (a == 13) {
			if (users.empty()) {
				if (row == 0) user.createUserAccount(users);
				else if (row == 1) {
					system("cls");
					break;
				}
				return;
			}
			else {
				if (row == 0) user.enterAccount(users);
				else if (row == 1) user.createUserAccount(users);
				else if (row == 2) {
					system("cls");
					break;
				}
				return;
			}
		}
	}
}
User::User() {}
User::User(string login, string password) {
	this->login = login;
	this->password = password;
}
void User::setCurrentUser(const string& str){
	currentUser = str;
}
void User::getCurrentUser(string& str) {
	str = currentUser;
}
void User:: setLoginAndPassword(const string& log, const string& pas) {
	login = log;
	password = pas;
}
string User::getLogin() {
	return login;
}
string User::getPassword() {
	return password;
}
bool operator==(const User& left, const User& right) {
	return (left.login == right.login && left.password == right.password);
}
void readFile(vector<User>& users, const string& path) {
	ifstream file(path);
	while (file) {
		User user;
		string login, password;
		getline(file, login);
		getline(file, password);
		user.setLoginAndPassword(login, password); 
		users.push_back(user);
	}
	if (!users.empty()) users.erase(users.end() - 1);
	file.close();
}
void User::enterAccount(vector<User>& users) {
	system("cls");
	bool accessGranted = true;
	bool quit = false;
	string login, password;
	do {
		if (accessGranted) login = setLogin(0, accessGranted, quit);
		else login = setLogin(1, accessGranted, quit);
		if (quit) return;
		password = setPassword(quit);
		if (quit) return;
		accessGranted = true;
		
		User tmp(login, sha256(password));
		if (find(users.begin(), users.end(), tmp) == users.end()) accessGranted = false;
	} while (!accessGranted);
	setLoginAndPassword(login, password);
	menuUser(users);
}
void User::createUserAccount(vector<User>& user) {
	system("cls");
	bool accessGranted = true;
	bool quit = false;
	do {
		if (accessGranted) this->login = setLogin(0, accessGranted, quit);
		else this->login = setLogin(2, accessGranted, quit);
		if (quit) return;
		this->password = setPassword(quit);
		if (quit) return;
		accessGranted = true;

		vector<User> admin;
		readFile(admin, "files/admin.txt");
		for (const auto& i : admin) {
			if (i.login == this->login) {
				accessGranted = false;
				break;
			}
		}

		vector<User> users;
		readFile(users, "files/users.txt");
		for (const auto& i : users) {
			if (i.login == this->login) {
				accessGranted = false;
				break;
			}
		}
	} while (!accessGranted);
	system("cls");
	cout << "Регистрация прошла успешно";
	Sleep(500);
	ofstream file("files/users.txt", ios::app);

	file << this->login << '\n' << sha256(this->password) << endl;
	file.close();
	menuUser(user);
}
void User::menuUser(vector<User>& users) {
	int8_t row = 0, row1;
	User::setCurrentUser(this->login);
	CityFlights cityFlights;
	InternationalFlights internationalFlights;
	Buses bus;
	while (true) {
		system("cls");
		arrowMenu({ " Просмотр рейсов", "\n\n Просмотр транспорта", "\n\n Просмотр забронированных билетов", "\n\n Забронировать билет", "\n\n Отмена брони","\n\n Поиск/сортировка/фильтрация данных",
			"\n\n Удалить учетную запись",	"\n\n Сменить пароль от учетной записи", "\n\n Назад" }, row);

		char a = getPushedCharCode();
		if (a == VK_UP) row = (row + 9 - 1) % 9;
		else if (a == VK_DOWN) row = (row + 1) % 9;
		else if (a == 13) {
			if (row == 0) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << "Выберете информацию о каких рейсах вы хотите просмотреть:\n\n";
					arrowMenu({ " о международных рейсах","\n\n о региональных рейсах", "\n\n о всех рейсах", "\n\n Назад" }, row1);

					char a = getPushedCharCode();

					if (a == VK_UP) row1 = (row1 + 4 - 1) % 4;
					else if (a == VK_DOWN) row1 = (row1 + 1) % 4;
					else if (a == 13) {
						if (row1 == 0) {
							internationalFlights.showTable();
							waitingForEsc();
						}
						if (row1 == 1) {
							cityFlights.showTable();
							waitingForEsc();
						}
						if (row1 == 2) {
							CityFlights cityFlights;
							bool error1 = false, error2 = false;
							if (copyCityFlightsFile(cityFlights)) error1 = true;
							if (copyInternationalFlightsFile(cityFlights)) error2 = true;
							if(cityFlights.croute.empty()) error1 = true;
							if(cityFlights.iroute.empty()) error2 = true;
							if (!error1) {
								system("cls");
								cout << "Для выхода нажмите Esc\n\n";
								cout << "    Региональные рейсы\n";
								header(cityFlights.croute);
							}
							if (!error2) {
								if (error1) {
									system("cls");
									cout << "Для выхода нажмите Esc\n\n";
								}
								cout << "\n    Международные рейсы\n";
								header(cityFlights.iroute);
							}
							if (error1 && error2) { system("cls"); cout << "Оба файла пусты. Для выхода нажмите Esc"; }
							waitingForEsc();
						}
						if (row1 == 3) { row = 0; break; }
					}
				}
			}
			else if (row == 1) {
				bus.showTable();
				waitingForEsc();
			}
			if (row == 2) {
				Order<InternationalRoute> orders;
				orders.showTable(true);
				waitingForEsc();
			}
			else if (row == 3) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << "Выберете билет на какой рейс вы хотите забронировать:\n\n";
					arrowMenu({ " на международный рейс","\n\n на региональный рейс", "\n\n Назад" }, row1);

					char a = getPushedCharCode();

					if (a == VK_UP) row1 = (row1 + 3 - 1) % 3;
					else if (a == VK_DOWN) row1 = (row1 + 1) % 3;
					else if (a == 13) {
						if (row1 == 0) {
							bool quit;
							Order<InternationalRoute> order;
							do {
								quit = false; 
								if (copyInternationalFlightsFile(internationalFlights)) { waitingForEsc(); break; }
								internationalFlights.showTable(false);
								order.addOrder(internationalFlights.iroute, quit, "Международный");
							} while (!quit);
						}
						if (row1 == 1) {
							bool quit;
							Order<CityRoute> order;
							do {
								quit = false;
								if (copyCityFlightsFile(cityFlights)) { waitingForEsc(); break; }
								cityFlights.showTable(false);
								order.addOrder(cityFlights.croute, quit, "Региональный");
							} while (!quit);
						}
						if (row1 == 2) { row = 0; break; }
					}
				}
			}
			else if (row == 4) {
				Order<InternationalRoute> order;
				order.orderCancellation();
			}
			else if (row == 5) {
				CityFlights cflights;
				menuSearch(cflights, true);
			}
			else if (row == 6) { bool quit = false; deleteAccount(users, quit); if (quit) return; }
			else if (row == 7) changePassword(users, "files/users.txt");
			else if (row == 8) { system("cls"); break; }
		}
	}
}
void User::changePassword(vector<User>& users, const string& path) {
	
	do {
		string pass = passwordStars("Введите пароль от аккаунта. Для выхода введите esc");
		if (pass == "esc") return;
		if (pass != this->password) {
			waitingForChar("Неправильный пароль. Для продолжения нажмите любую клавишу");
			return;
		}

		User tmp(this->login, sha256(this->password));

		auto search = find(users.begin(), users.end(), tmp);
		if (search != users.end()) {
			
			bool quit = false;
			this->password = setPassword(quit, false);
			if (quit) return;

			search->password = sha256(password);
			rewriteFile(users, path);
			waitingForChar("Пароль успешно изменен. Для продолжения нажмите любую клавишу");
			return;
		}
	} while (true);
}
void User::deleteAccount(vector<User>& users, bool& quit) {
	string str;
	while(true) {
		str = getLoginOrString("Введите \"Да\" для подтверждения удаления учетной записи и \"esc\" для выхода");
		if (str.empty()) continue;
		if (str == "Да") {
			User tmp(this->login, sha256(this->password));
			auto search = find(users.begin(), users.end(), tmp);
			if (search != users.end()) {
				users.erase(search);
				rewriteFile(users, "files/users.txt");
				waitingForChar("Учетная запись успешно удалена. Для выхода нажмите любую кнопку");
				quit = true; return;
			}
		}
		else if (str == "esc") return;
	} 
}