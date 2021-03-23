#include "Namespace.h"
#include "BusesAndFlights.h"

bool checkingFileInputOutput::CityFlightsVerification(const CityRoute& croute) {
	string dateOfDeparture = croute.dateOfDeparture.day + croute.dateOfDeparture.month + croute.dateOfDeparture.year + croute.dateOfDeparture.hour + croute.dateOfDeparture.minutes;
	string dateOfArrival = croute.dateOfArrival.day + croute.dateOfArrival.month + croute.dateOfArrival.year + croute.dateOfArrival.hour + croute.dateOfArrival.minutes;

	if (croute.pointOfDeparture.empty() && croute.arrivalPoint.empty() && dateOfDeparture.empty() && dateOfArrival.empty() && croute.routeNumber.empty()) return true;
	if (croute.pointOfDeparture.empty() || croute.arrivalPoint.empty() || dateOfDeparture.empty() || dateOfArrival.empty() || croute.routeNumber.empty()) return false;

	if (croute.dateOfDeparture.day.size() != 2 || croute.dateOfDeparture.month.size() != 2 || croute.dateOfDeparture.year.size() != 4 ||
		croute.dateOfDeparture.hour.size() != 2 || croute.dateOfDeparture.minutes.size() != 2 || croute.dateOfArrival.day.size() != 2 ||
		croute.dateOfArrival.month.size() != 2 || croute.dateOfArrival.year.size() != 4 ||
		croute.dateOfArrival.hour.size() != 2 || croute.dateOfArrival.minutes.size() != 2) return false;

	for (const auto& str : vector<string>{ croute.pointOfDeparture, croute.arrivalPoint })
		for (auto i : str)
			if (!((i >= 'а' && i <= 'я') || (i >= 'А' && i <= 'Я'))) return false;

	for (auto i : croute.routeNumber)
		if (!((i >= 'а' && i <= 'я') || (i >= 'А' && i <= 'Я') || (i >= '0' && i <= '9'))) return false;
	if (croute.routeNumber.size() > 4) return false;
	for (auto a : dateOfDeparture)
		if (a < '0' || a > '9') return false;
	for (auto a : dateOfArrival)
		if (a < '0' || a > '9') return false;

	if (!checkingFileInputOutput::dateCorrect(stringToInt(croute.dateOfDeparture.day), stringToInt(croute.dateOfDeparture.month), stringToInt(croute.dateOfDeparture.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(croute.dateOfDeparture.hour), stringToInt(croute.dateOfDeparture.minutes)) ||
		!checkingFileInputOutput::dateCorrect(stringToInt(croute.dateOfArrival.day), stringToInt(croute.dateOfArrival.month), stringToInt(croute.dateOfArrival.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(croute.dateOfArrival.hour), stringToInt(croute.dateOfArrival.minutes))) return false;

	time_t now = time(nullptr);
	tm* ltm = localtime(&now);

	string currTime = (ltm->tm_mday < 10 ? "0" + to_string(ltm->tm_mday) : to_string(ltm->tm_mday))
		+ (ltm->tm_mon < 9 ? "0" + to_string(1 + ltm->tm_mon) : to_string(1 + ltm->tm_mon))
		+ to_string(1900 + ltm->tm_year) + to_string(ltm->tm_hour) + to_string(ltm->tm_min);
	if (croute.dateOfDeparture < Date(currTime) || croute.dateOfArrival < Date(currTime)) 
		return false;

	return true;
}
bool checkingFileInputOutput::InternationalFlightsVerification(const InternationalRoute* iroute) {
	string dateOfDeparture = iroute->dateOfDeparture.day + iroute->dateOfDeparture.month + iroute->dateOfDeparture.year + iroute->dateOfDeparture.hour + iroute->dateOfDeparture.minutes;
	string dateOfArrival = iroute->dateOfArrival.day + iroute->dateOfArrival.month + iroute->dateOfArrival.year + iroute->dateOfArrival.hour + iroute->dateOfArrival.minutes;

	if (iroute->pointOfDeparture.empty() && iroute->arrivalPoint.empty() && dateOfDeparture.empty() && dateOfArrival.empty()
		&& iroute->countryOfArrival.empty() && iroute->visa.empty() && iroute->routeNumber.empty()) return true;
	if (iroute->pointOfDeparture.empty() || iroute->arrivalPoint.empty() || dateOfDeparture.empty() || dateOfArrival.empty()
		|| iroute->countryOfArrival.empty() || iroute->visa.empty() || iroute->routeNumber.empty()) return false;
	if (iroute->routeNumber.size() > 4) return false;
	for (const auto& str : vector<string>{ iroute->countryOfArrival, iroute->visa })
		for (auto i : str)
			if (!((i >= 'а' && i <= 'я') || (i >= 'А' && i <= 'Я'))) return false;

	return true;
}
bool checkingFileInputOutput::BusesVerification(const Buses& bus) {
	if (bus.transportType.empty() && bus.routeNumber.empty() && bus.brand.empty() && bus.price.empty() && bus.number_of_seats.empty() && bus.bus_class.empty() && bus.number_of_floors.empty()) return true;
	if (bus.transportType.empty() || bus.routeNumber.empty() || bus.brand.empty() || bus.price.empty() || bus.number_of_seats.empty() || bus.bus_class.empty() || bus.number_of_floors.empty()) return false;

	for (const auto& str : vector<string>{ bus.transportType, bus.brand, bus.bus_class })
		for (auto i : str)
			if (!((i >= 'а' && i <= 'я') || (i >= 'А' && i <= 'Я'))) return false;

	int g = 0, k = 0;
	for (int i = 0; i < bus.price.size(); i++) {
		if (bus.price[i] == '.') {
			if (g == 0) { k = i; g = 1; continue; }
			else return false;
		}
	}
	if (g == 1) { 
		string price, price1; 
		for (int i = 0; i < k; i++) {
			price += bus.price[i];
		}
		for (int i = k + 1; i < bus.price.size(); i++) {
			price1 += bus.price[i];
		}
		if(price.empty() || price1.empty()) return false;
		if (stringToInt(price) == 0 || stringToInt(price) == -1 || price.size() > 4) return false;
		if (stringToInt(price1) == -1 || price1.size() > 2) return false;
	}
	else {
		if (stringToInt(bus.price) == 0 || stringToInt(bus.price) == -1 || bus.price.size() > 4) return false;
	}
	if (bus.routeNumber.size() > 4) return false;
	if (!(bus.transportType == "Международный" || bus.transportType == "Региональный")) return false;
	if (!(bus.bus_class == "Бизнес" || bus.bus_class == "Эконом")) return false;
	if (stringToInt(bus.number_of_floors) == 0 || stringToInt(bus.number_of_floors) == -1 || stringToInt(bus.number_of_floors) > 3) return false;
	if (stringToInt(bus.number_of_seats) == 0 || stringToInt(bus.number_of_seats) == -1 || stringToInt(bus.number_of_seats) > 200) return false;

	for (auto i : bus.routeNumber)
		if (!((i >= 'а' && i <= 'я') || (i >= 'А' && i <= 'Я') || (i >= '0' && i <= '9'))) return false;
	for (const auto& str : vector<string>{ bus.number_of_seats, bus.number_of_floors })
		for (auto i : str)
			if (!(i >= '0' && i <= '9'))return false;

	return true;
}
bool checkingFileInputOutput::dateCorrect(int8_t day, int8_t month, int16_t year) {
	if (day > 31 || day == 0 || month == 0 || month > 12 || year == 0) return false;
	if (day < 29) return true;
	if (month == 2) {
		if (day == 29) {
			if (year % 4) return false;
			if (!(year % 400)) return true;
			return year % 100 != 0;
		}
		return false;
	}
	if (month <= 7) {
		if (month % 2) return true;
		else if (day != 31) return true;
		else return false;
	}
	else {
		if (!month % 2) return true;
		else if (day != 31) return true;
		else return false;
	}
}
bool checkingFileInputOutput::timeCorrect(int8_t hour, int8_t minutes) {
	if (hour > 23 || minutes > 59) return false;
	return true;
}
bool checkingFileInputOutput::cityRouteCorrect(const CityRoute& cityRoute, const string& dateOfDeparture, const string& dateOfArrival) {
	if (cityRoute.pointOfDeparture.empty() || cityRoute.arrivalPoint.empty() || cityRoute.routeNumber.empty()) {
		waitingForChar("Вы заполнили не все поля. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	if (dateOfDeparture.size() != 12 || dateOfArrival.size() != 12) {
		waitingForChar("Дата и время должна содержать 12 цифр. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	Date depdate(dateOfDeparture), arrdate(dateOfArrival);
	if (!checkingFileInputOutput::dateCorrect(stringToInt(depdate.day), stringToInt(depdate.month), stringToInt(depdate.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(depdate.hour), stringToInt(depdate.minutes)) ||
		!checkingFileInputOutput::dateCorrect(stringToInt(arrdate.day), stringToInt(arrdate.month), stringToInt(arrdate.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(arrdate.hour), stringToInt(arrdate.minutes))) {
		waitingForChar("Введенной даты не существует. Для продолжения нажмите любую клавишу");
		return false;
	}

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string currTime = (ltm->tm_mday < 10 ? "0" + to_string(ltm->tm_mday) : to_string(ltm->tm_mday))
		+ (ltm->tm_mon < 9 ? "0" + to_string(1 + ltm->tm_mon) : to_string(1 + ltm->tm_mon))
		+ to_string(1900 + ltm->tm_year) + to_string(ltm->tm_hour) + to_string(ltm->tm_min);

	if (depdate < Date(currTime) || arrdate < Date(currTime)) {
		waitingForChar("Введенная дата меньше настоящей даты. Для продолжения нажмите любую клавишу");
		return false;
	}
	if (depdate > arrdate) {
		waitingForChar("Дата и время отправления больше даты и времени прибытия. Для продолжения нажмите любую клавишу");
		return false;
	}
	return true;
}
bool checkingFileInputOutput::InternationalRouteCorrect(const InternationalRoute& iroute, const string& dateOfDeparture, const string& dateOfArrival) {
	if (iroute.pointOfDeparture.empty() || iroute.arrivalPoint.empty() || iroute.countryOfArrival.empty() || iroute.visa.empty() || iroute.routeNumber.empty()) {
		waitingForChar("Вы заполнили не все поля. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}

	if (dateOfDeparture.size() != 12 || dateOfArrival.size() != 12) {
		waitingForChar("Дата и время должна содержать 12 цифр. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	Date depdate(dateOfDeparture), arrdate(dateOfArrival);
	if (!checkingFileInputOutput::dateCorrect(stringToInt(depdate.day), stringToInt(depdate.month), stringToInt(depdate.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(depdate.hour), stringToInt(depdate.minutes)) ||
		!checkingFileInputOutput::dateCorrect(stringToInt(arrdate.day), stringToInt(arrdate.month), stringToInt(arrdate.year)) ||
		!checkingFileInputOutput::timeCorrect(stringToInt(arrdate.hour), stringToInt(arrdate.minutes))) {
		waitingForChar("Введенной даты не существует. Для продолжения нажмите любую клавишу");
		return false;
	}

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string currTime = (ltm->tm_mday < 10 ? "0" + to_string(ltm->tm_mday) : to_string(ltm->tm_mday))
		+ (ltm->tm_mon < 9 ? "0" + to_string(1 + ltm->tm_mon) : to_string(1 + ltm->tm_mon))
		+ to_string(1900 + ltm->tm_year) + to_string(ltm->tm_hour) + to_string(ltm->tm_min);

	if (depdate < Date(currTime) || arrdate < Date(currTime)) {
		waitingForChar("Введенная дата меньше настоящей даты. Для продолжения нажмите любую клавишу");
		return false;
	}
	if (depdate > arrdate) {
		waitingForChar("Дата и время отправления больше даты и времени прибытия. Для продолжения нажмите любую клавишу");
		return false;
	}
	return true;
}
bool checkingFileInputOutput::busCorrect(const Buses& bus) {
	if (bus.transportType.empty() || bus.routeNumber.empty() || bus.brand.empty()
		|| bus.price.empty() || bus.number_of_seats.empty() || bus.bus_class.empty() || bus.number_of_floors.empty()) {
		waitingForChar("Вы заполнили не все поля. Для повторного ввода данных нажмите любую клавишу");
		return false;
	}
	if (!(bus.transportType == "Международный" || bus.transportType == "Региональный")) {
		waitingForChar("Тип транспорта должен быть Международный или Региональный. Для продолжения намите любую клавишу");
		return false;
	}
	int g = 0, k = 0;
	for (int i = 0; i < bus.price.size(); i++) {
		if (bus.price[i] == '.') {
			if (g == 0) { k = i; g = 1; continue; }
			else { waitingForChar("Стоимость билета должна быть меньше 10000, содержать только цифры или цифры разделённые точкой, но после точки должно быть не более двух цифр. Для продолжения нажмите любую клавишу"); return false; }
		}
	}
	if (g == 1) {
		string price, price1;
		for (int i = 0; i < k; i++) {
			price += bus.price[i];
		}
		for (int i = k + 1; i < bus.price.size(); i++) {
			price1 += bus.price[i];
		}
		if (price.empty() || price1.empty()) {
			waitingForChar("Стоимость билета должна быть меньше 10000, содержать только цифры или цифры разделённые точкой, но после точки должно быть не более двух цифр. Для продолжения нажмите любую клавишу"); return false;
		}
		if (stringToInt(price) == 0 || stringToInt(price) == -1 || price.size() > 4) { 
			waitingForChar("Стоимость билета должна быть меньше 10000 и не должна начинаться с 0, она содержать только цифры или цифры разделённые точкой, но после точки должно быть не более двух цифр. Для продолжения нажмите любую клавишу"); return false;
		}
		if (stringToInt(price1) == -1 || price1.size() > 2) { 
			waitingForChar("Стоимость билета должна быть меньше 10000, содержать только цифры или цифры разделённые точкой, но после точки должно быть не более двух цифр. Для продолжения нажмите любую клавишу"); return false;
		}
	}
	else {
		if (stringToInt(bus.price) == 0 || stringToInt(bus.price) == -1 || bus.price.size() > 4) {
			waitingForChar("Стоимость билета должна быть меньше 10000, содержать только цифры или цифры разделённые точкой, но после точки должно быть не более двух цифр. Для продолжения нажмите любую клавишу"); return false;
		}
	}
	if (stringToInt(bus.number_of_seats) > 200 || stringToInt(bus.number_of_seats) == 0) {
		waitingForChar("Количество мест должно быть больше 0 но меньше 200. Для продолжения намите любую клавишу");
		return false;
	}
	if (!(bus.bus_class == "Бизнес" || bus.bus_class == "Эконом")) {
		waitingForChar("Класс автобуса должен быть Бизнес или Эконом. Для продолжения намите любую клавишу");
		return false;
	}
	if (stringToInt(bus.number_of_floors) == 0 || stringToInt(bus.number_of_floors) > 3) {
		waitingForChar("Количество этажей должно быть больше 0 но меньше 4. Для продолжения намите любую клавишу");
		return false;
	}
	return true;
}