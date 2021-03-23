#include "Namespace.h"
#include "Admin.h"
#include "BusesAndFlights.h"
#include "Order.h"


void adminAccount() {
	int8_t row = 0;
	Admin admin;
	vector<User> admins;
	readFile(admins, "files/admin.txt");
	while (true) {
		system("cls");
		if (admins.empty()) arrowMenu({ "  ������� �������","\n\n  �����" }, row);
		else arrowMenu({ "  ����� � �������","\n\n  �����" }, row);

		char a=getPushedCharCode();
		if (a == VK_UP) row = (row + 1) % 2;
		else if (a == VK_DOWN) row = (row + 1) % 2;
		else if (a == 13) {
			if (admins.empty()) {
				if (row == 0) admin.createAdminAccount(admins);
				else if (row == 1) {
					system("cls");
					break;
				}
				return;
			}
			else {
				if (row == 0) admin.enterAccount(admins);
				else if (row == 1) {
					system("cls");
					break;
				}
				return;
			}
		}
	}
}
void Admin::createAdminAccount(vector<User>& admin) {
	system("cls");
	bool accessGranted = true;
	bool quit = false;
	string login, password;
	do {
		if (accessGranted) login = setLogin(0, accessGranted, quit);
		else login = setLogin(2, accessGranted, quit);
		if (quit) return;
		password = setPassword(quit);
		if (quit) return;

		vector<User> users;
		readFile(users, "files/users.txt");
		for (auto& i : users) {
			if (i.getLogin() == login) {
				accessGranted = false;
				break;
			}
		}
	} while (!accessGranted);

	system("cls");
	cout << "����������� ������ �������";
	Sleep(500);
	ofstream file("files/admin.txt", ios::trunc);
	
	file << login << '\n' << sha256(password) << endl;
	file.close();
	setLoginAndPassword(login, password);
	menuUser(admin);
}
void Admin::menuUser(vector<User>& admins) {
	int8_t row = 0, row1;
	
	CityFlights cityFlights;
	InternationalFlights internationalFlights;
	Buses bus;
	while (true) {
		system("cls");
		arrowMenu({ " �������� ������","\n\n �������� ����������", "\n\n �������� ��������������� �������",
			"\n\n ���������� �������", "\n\n ���������� ��������������", "\n\n ������� ������� ������ ��������������", "\n\n ������� ������ �� ������� ������ ��������������", "\n\n �����" }, row);

		char a = getPushedCharCode();

		if (a == VK_UP) row = (row + 8 - 1) % 8;
		else if (a == VK_DOWN) row = (row + 1) % 8;
		else if (a == 13) {
			if (row == 0) {
				row1 = 0;
				while (true) {
					system("cls");
					cout << "�������� ���������� � ����� ������ �� ������ �����������:\n\n";
					arrowMenu({ " � ������������� ������","\n\n � ������������ ������", "\n\n � ���� ������", "\n\n �����" }, row1);

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
							if (cityFlights.croute.empty()) error1 = true;
							if (cityFlights.iroute.empty()) error2 = true;
							if (!error1) {
								system("cls");
								cout << "��� ������ ������� Esc\n\n";
								cout << "    ������������ �����\n";
								header(cityFlights.croute);
							}
							if (!error2) {
								if (error1) {
									system("cls");
									cout << "��� ������ ������� Esc\n\n";
								}
								cout << "\n    ������������� �����\n";
								header(cityFlights.iroute);
							}
							if (error1 && error2) { system("cls"); cout << "��� ����� �����. ��� ������ ������� Esc"; }
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
			else if (row == 2) {
				Order<InternationalRoute> orders;
				orders.showTable(false);
				waitingForEsc();
			}
			else if (row == 3) dataManagementMenu();
			else if (row == 4) menuUserControl();
			else if (row == 5) { bool quit = false; deleteAccount(admins, quit);  if (quit) return; }
			else if (row == 6) changePassword(admins, "files/admin.txt");
			else if (row == 7) {system("cls"); break;}
		}
	}
}
void Admin:: menuUserControl() {
	int8_t row = 0;
	while (true) {
		system("cls");
		cout << "�������� ��������, ������� ������ ���������\n\n";
		arrowMenu({ " �������� �������������","\n\n �������� ������������", "\n\n ���������� ������������",
			"\n\n ���������� ������ ��������������", "\n\n �����" }, row);

		char a = getPushedCharCode();

		if (a == VK_UP) row = (row + 5 - 1) % 5;
		else if (a == VK_DOWN) row = (row + 1) % 5;
		else if (a == 13) {
			if (row == 0) viewUsers();
			else if (row == 1) deleteUsers();
			else if (row == 2) addUsers();
			else if (row == 3) changeAdmin();
			else if (row == 4) { system("cls"); break; }
		}
	}
}
void Admin::viewUsers() {
	vector<User> users;
	vector<User> admin;
	char a;
	readFile(users, "files/users.txt");
	readFile(admin, "files/admin.txt");
	system("cls");
	
	cout <<"\n-------------------------------------------"
		"\n|       �����        |       ������       |\n"
		"-------------------------------------------\n";
	if (!users.empty()) {
		for (int i = 0; i < users.size(); i++) {
			cout << "|";
			cout.width(20);
			cout << users[i].getLogin();
			cout << "|";
			cout.width(17);
			cout << "������������"<<"   |\n";
			cout << "-------------------------------------------\n";
		}
	}
	for (int i = 0; i < admin.size(); i++) {
		cout << "|";
		cout.width(20);
		cout << admin[i].getLogin();
		cout << "|";
		cout.width(17);
		cout << "�������������" << "   |\n";
		cout << "-------------------------------------------\n";
	}
	cout << "��� ������ ������� esc";
	while (true) {
		a = getPushedCharCode();
		if (a == VK_ESCAPE) return;
	}

}
void Admin::deleteUsers() {
	vector<User> users;
	readFile(users, "files/users.txt");
	if (users.empty()) {
		system("cls");
		waitingForChar("������ ������������� ����. ��� ����������� ������� ����� ������");
		return;
	}
	string str = getLoginOrString("������� ����� ������������, �������� ������ �������. ������� esc ��� ������");
	if (str == "esc") return;
	auto it = users.begin();

	for (; it != users.end(); ++it)
		if (it->getLogin() == str) break;

	if (it != users.end()) {
		users.erase(it);
		rewriteFile(users, "files/users.txt");
		waitingForChar("������������ ������� ������. ��� ����������� � ���� ������� ����� �������");
		return;
	}
	else waitingForChar("������������ �� ������. ��� ����������� � ���� ������� ����� �������");
}
void Admin::addUsers() {
	system("cls");
	User users;
	string tmp, login, password;

	bool accessGranted = true;
	bool quit = false;
	do {
		if (accessGranted) login = setLogin(0, accessGranted, quit);
		else login = setLogin(2, accessGranted, quit);
		if (quit) return;
		password = setPassword(quit);
		if (quit) return;
		accessGranted = true;

		ifstream file("files/admin.txt");
		while (file) {
			getline(file, tmp);
			if (tmp == login) {
				accessGranted = false;
				break;
			}
			getline(file, tmp);
		}
		file.close();
		file.open("files/users.txt");
		while (file) {
			getline(file, tmp);
			if (tmp == login) {
				accessGranted = false;
				break;
			}
			getline(file, tmp);
		}
	} while (!accessGranted);

	ofstream file("files/users.txt", ios::app);
	
	file << login << '\n' << sha256(password) << endl;
	file.close();
	waitingForChar("������������ ������� ��������. ��� ����������� ������� ����� �������");
}
void Admin::deleteAccount(vector<User>& admins, bool& quit) {
	string temp;
	while(true) {
		temp = getLoginOrString("������� \"��\" ��� ������������� �������� �������������� � \"esc\" ��� ������");
		if (temp.empty()) continue;
		if (temp == "��") {
			admins.clear();
			ofstream file("files/admin.txt", ios::trunc);
			file.close();
			break;
		}
		else if (temp == "esc") return; 
	} 
	waitingForChar("������������� ������� ������.��� ������\n");
	quit = true;

}
void Admin::changeAdmin() {
	string str = getLoginOrString("������� ����� ������������, �������� ������ ������� ���������������,\n��� ���� ������� ������������� ������ ������� �������������. ������� esc ��� ������");
	if (str == "esc") return;
	vector<User> users;
	vector<User> admins;
	readFile(users, "files/users.txt");
	readFile(admins, "files/admin.txt");
	if (admins.size() > 1) {
		cout << "���� ���������(����� ���� ������ ������). ��� ������ ������� esc";
		while (true) {
			char a = getPushedCharCode();
			if (a == VK_ESCAPE) return;
		}
	}
	
	int i;
	for ( i = 0; i < users.size(); i++) {
		if (users[i].getLogin() == str) break;
	}
	if (i != users.size()) {
		ofstream file("files/admin.txt", ios::trunc);
		file << users[i].getLogin() << '\n' << users[i].getPassword() << endl;
		file.close();
		users.erase(users.begin() + i);
		users.push_back(admins[0]);
		rewriteFile(users, "files/users.txt");
		waitingForChar("������������� ������� �������. ��� ����������� � ���� ������� ����� �������");
		return;
	}
	else waitingForChar("������������ �� ������. ��� ����������� � ���� ������� ����� �������");
}
