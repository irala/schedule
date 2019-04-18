// schelude.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <fstream>
#include <string>
#include <stdlib.h>   
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
#include <iostream>
using namespace std;


class Schelude {
public:

	int id;
	string free_text;
	time_t time;
	//day datetime?
};

vector<string> vectorAnswer{ "yes","no","y","n","not" };
enum class Days { Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6, Sunday = 7, Fail = 0 };
//hacer mapa

bool isCorrectAnswer(string answer) {
	bool _answer;
	std::vector<string>::iterator it = std::find(vectorAnswer.begin(), vectorAnswer.end(), answer);
	if (it != vectorAnswer.end())
	{
		std::string expectsString = *it;
		if (expectsString.find("y") != std::string::npos) {
			return	_answer = true;
		}
		else {
			return	_answer = false;
		}
	}
	else {
		cout << "Incorrect answer";
		return	_answer = false;

	}

}


std::ostream& operator << (std::ostream& os, const Days& obj)
{
	os << static_cast<std::underlying_type<Days>::type>(obj);
	return os;
}



Days isCorrectDay(string day) {
	//return day y en caso de ser error (?)
	Days _day;
	if (day == "Monday") {
		_day = Days::Monday;
		return _day;
	}
	else if (day == "Tuesday") {
		_day = Days::Tuesday;
		return _day;
	}
	else if (day == "Wednesday") {
		_day = Days::Wednesday;
		return _day;
	}
	else if (day == "Thursday") {
		_day = Days::Thursday;
		return _day;
	}
	else if (day == "Friday") {
		_day = Days::Friday;
		return _day;
	}
	else if (day == "Saturday") {
		_day = Days::Saturday;
		return _day;
	}
	else if (day == "Sunday") {
		_day = Days::Sunday;
		return _day;
	}
	else {
		_day = Days::Fail;
		return _day;
	}
}


void notOverwriteFile(string _file) {
	list<Schelude> listOfEvents;
	ifstream file(_file);
	string line;
	int count = 0;
	bool isEmpty = false;
	//leer el fichero por si tiene algo, si
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << '\n';
			if (line == "") {
				count++;
				continue;
			}
			else {
				//encontrar 
				Schelude _event;
				_event.id = 0;
				_event.free_text = "";
				//si tiene algo que compruebe lo que tiene escrito para organizar lo que se le añada en una lista para ordenar y sobreescribir el archivo
				listOfEvents.push_back(_event);
			}
		}
		if (count > 1) {
			// no tiene que se sobreescriba sin más
			isEmpty = true;
		}
		file.close();
	}
	else cout << "Unable to open file";

}


int main()
{
	list<Schelude> listOfSchelude;
	auto const filename = "schelude.txt";
	//TODO: Llamar a funcion que compruebe si el fichero esta escrito o no y que se le pueda añadir mas informacion
	//comprobar también que lo que hay en los dias ya guardados se le puede añadir o no 
	notOverwriteFile(filename);

	ofstream file1(filename);
	if (file1.fail())
	{
		cerr << "!Error opening " << filename << endl;
		return EXIT_FAILURE;
	}
	//TODO: controlar que solo edite lo que ya está escrito en el archivo , que no borre lo que no queremos
	//actualmente crea y pisa el archivo cada vez que lo ejecutas




	string answerStr;
	string dayStr;

	cout << "Answer the question to save the event:\n";
	bool answerDay = true;
	//en que dia quieres agendar/a que hora/buscar un identificador para cada evento
	while (answerDay) {
		cout << "On what day do you want to save the events? \n";
		cout << "Select the day : \n Monday \n Tuesday \n Wednesday \n Thursday \n Friday \n Saturday \n Sunday \n";
		cin >> dayStr;
		//comprobar que dia de la semana es para guardarlo en el id del schelude
		Days d = isCorrectDay(dayStr);
		int _dayInt = (int)d;
		//si esta en el enum seguir sino , repetir pregunta (?)
		bool daysB = true;
		bool answer = true;
		while (daysB) {
			if (_dayInt != 0) {

				while (answer)
				{
					Schelude schelude;
					schelude.id = _dayInt;
					cout << "What do you want to schelude ? \n";
					cin >> schelude.free_text;
					listOfSchelude.push_back(schelude);
					cout << "scheduled event! \n";

					cout << "Do you want to schelude anymore? \n";
					cin >> answerStr;
					std::transform(answerStr.begin(), answerStr.end(), answerStr.begin(), ::tolower);
					answer = isCorrectAnswer(answerStr);
					if (answer == false) {
						daysB = false;
					}
				}

			}
			else {
				daysB = false;
				cout << "Incorrect day";
			}

			cout << "Do you want to save more events in other days?";
			cin >> answerStr;
			answerDay = isCorrectAnswer(answerStr);

		}
	}
	for (Schelude s : listOfSchelude) { file1 << s.id << " " << s.free_text << endl; }

	file1.close();
	return 0;
}

