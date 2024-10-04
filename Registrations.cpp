#include "Registrations.h"
const int DAILY = 50000;
const int WEEKLY = 100000;
const int MONTHLY = 200000;
Registrations::Registrations(string regisid,string ownid,string lp,string lotid,int tickettype,int price,string stime)
	:ParkingLots("",'A',0),Vehicles("","","","","")
{	
	this->RegistrationID = regisid;
	this->TicketType = tickettype;
	this->TicketPrice = price;
	this->StartTime = stime;
	this->OwnerID = ownid;
	this->LicensePlate = lp;
	this->LotID = lotid;
}

void Registrations::ReadFromFile()
{
	ifstream filein("Registrations.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Registrations.txt"<<endl;
	}
	else
	{
		string regisid,lp,lotid,stime,ownid;
		int type, price;
		while(getline(filein,regisid,';'))
		{
			getline(filein,ownid,';');
			getline(filein,lp,';');
			getline(filein,lotid,';');
			filein>>type;filein.ignore();
			getline(filein,stime);
			price = (type == 1) ? DAILY : ((type == 2) ? WEEKLY : MONTHLY);
 			Registrations regis(regisid,ownid,lp,lotid,type,price,stime);
			listregis.push_back(regis);
		}
		filein.close();
	}
}

Registrations::Registrations()
	: Vehicles("","","","","")
{
	ReadFromFile();
}

void Registrations::Show(string user)
{
	for(auto rg:listregis){
	if(rg.OwnerID==user){
	cout << "--------------------------------------"<<endl;
	cout <<	"Registration ID : " << rg.RegistrationID << endl;
	cout << "Owner        ID : " << rg.OwnerID<<endl;
	cout << "Lot          ID : " << rg.LotID << endl;
	cout << "License Plate   : " << rg.LicensePlate <<endl;
	cout << "TicketType      : " <<((rg.TicketType == 1) ? "DAILY" : ((rg.TicketType ==2) ? "WEEKLY" : "MONTHLY") )<<endl;
	cout << "Price           : " << rg.TicketPrice <<endl;
	cout << "Start Time      : " <<rg.StartTime<<endl;
	cout << "--------------------------------------"<<endl;	
		}
	}
}
