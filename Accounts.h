#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "Registrations.h"
using namespace std;
class Accounts : public ParkingLots , public Owners
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
		bool Login(string,string);	
		int checkinput(string); 
		void Check();
		void Register(ParkingLots,Vehicles,Registrations,string,int);
		void Edit(Owners,string,string);
		void SetPassword(string);
		void loginForm();
		void Welcome();
};
