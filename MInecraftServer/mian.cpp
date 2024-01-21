#include <iostream>
#include <fstream>
#include <sstream>
#include "dependencies/include/nlohmann/json.hpp"

/*
	 Hah, I can write this code in bash, but idk what I'm doing.

*HAHAHAHAHAHAHAHSHS*

*/


using namespace std;
using json = nlohmann::json;


#define RED_COLOR "\033[1;31m"
#define GREEN_COLOR "\033[1;32m"
#define YELLOW_COLOR "\033[1;33m"
#define BLUE_COLOR "\033[1;34m"
#define MAGENTA_COLOR "\033[1;35m"
#define CYAN_COLOR "\033[1;36m"
#define RESET_COLOR "\033[0m"


class Server {
	int Xmx = 1024;
	int Xms = 1024;



public:
	void logo()
	{
		cout << MAGENTA_COLOR << "\tSTArT-ErSerVer" << RESET_COLOR << endl;
	}

	void settings()
	{
		int Xmx;
		int Xms;
		bool gui;

		cout << GREEN_COLOR << "1. The maximum amount of memory (Xmx): ";
		cin >> Xmx;

		cout << "2. Initial memory size (Xms): ";
		cin >> Xms;

		cout << "3. With gui? true | fasle: ";
		cin >> gui;


		json settingsJson;
		settingsJson["Xmx"] = Xmx;
		settingsJson["Xms"] = Xms;
		settingsJson["gui"] = gui;

		ofstream file("settings.json");
		file << setw(4) << settingsJson << endl;
		cout << "Settings saved to settings.json" << endl;
	}

	void first_start()
	{
		system("java -Xms1024M -Xmx1024M -jar *.jar nogui");


		system("sed -i.orig 's/eula=false/eula=true/g' eula.txt");
		system("sed -i.orig 's/online-mode=true/online-mode=false/g' server.properties");
	}




	void start() {

		nlohmann::json objson;
		fstream fileInput;

		fileInput.open("settings.json");
		fileInput >> objson;


		system("curl -s https://api64.ipify.org?format=json | grep -oP '\"ip\"\s*:\s*\"\K[^\"]+'");
		cout << ":25565";


		int Xms = objson["Xms"];
		int Xmx = objson["Xmx"];
		bool gui = objson["gui"];


		string command;

		if (gui == true)
			command = "java -Xms" + to_string(Xms) + "M -Xmx" + to_string(Xmx) + "M -jar *.jar gui";
		else
		{
			command = "java -Xms" + to_string(Xms) + "M -Xmx" + to_string(Xmx) + "M -jar *.jar nogui";
		}

		system(command.c_str());


	}


	void check()
	{
		ifstream infile("startup.txt");
		int value;

		if (infile >> value)
		{
			if (value == 0)
			{
				cout << CYAN_COLOR << "Is this your first run?\n" << RESET_COLOR << endl;

				ofstream outfile("startup.txt");
				outfile << 1 << endl;

				settings();
				first_start();

				return check();




			}
			else
			{
				cout << "starting serv";
				start();
			}
		}
		else
		{
			cout << RED_COLOR << "\nFile could not found. " << CYAN_COLOR << "Is this your first run?" << RESET_COLOR << endl;

		}
	}


	int chooser()
	{
		// 
	}

};


int main()
{
	Server myServ;


	myServ.logo();
	myServ.check();
	myServ.start();

}