#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include "Registrations.h"
using namespace std;
class Accounts : public ParkingLots
{
	private:
		string username;
		string password;
		bool role;
		vector<Accounts>listacc;
	public:
		Accounts();
		Accounts(string,string,bool);
		void ReadFromFile();
		bool Login();	
		int checkinput(string); 
		void Check();
		void Register(ParkingLots,Vehicles,Registrations,string,int);
};
