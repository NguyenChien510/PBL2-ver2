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
	Vehicles::ReadFromFile();
	if(user == "admin"){
		cout<< setw(15) << "Registration ID :  "<<" | "
        << setw(10) << "Owner ID : " << " | "
        << setw(5) << "Lot ID" << " | "
        << setw(15) << "License Plate" << " | "
        << setw(5) << "Brand" << " | "
        << setw(5) << "Model" << " | "
        << setw(5) << "Color" << " | "
        << setw(7) << "Ticket Type" << " | "
        << setw(7) << "Price" << " | "
        << setw(15) << "Start Time" << endl;
	cout<< setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    for (auto& rg : listregis) {
    	for(auto& veh:listveh){
    	cout<< setw(15) << rg.RegistrationID<< " | "
            << setw(10) << rg.OwnerID <<" | "
            << setw(5) << rg.LotID <<" | "
            << setw(15) << rg.LicensePlate <<" | "
            << setw(5) << veh.GetBrand() <<" | "
            << setw(5) << veh.GetModel() <<" | "
            << setw(5) << veh.GetColor() <<" | "
        	<< setw(7) << ((rg.TicketType == 1) ? "DAILY" : ((rg.TicketType ==2) ? "WEEKLY" : "MONTHLY") ) << " | "
        	<< rg.TicketPrice
        	<< setw(15) << rg.StartTime << endl;
        }
    }
	}
	}
	else{
	for(auto rg:listregis){
	for(auto veh : listveh){
	if(rg.OwnerID==user && rg.LicensePlate == veh.GetLicensePlate()){
	cout << "--------------------------------------"<<endl;
	cout <<	"Registration ID : " << rg.RegistrationID << endl;
	cout << "Owner        ID : " << rg.OwnerID<<endl;
	cout << "Lot          ID : " << rg.LotID << endl;
	cout << "License Plate   : " << rg.LicensePlate <<endl;
	cout << "Brand           : " << veh.GetBrand()<<endl;
	cout << "Model           : " << veh.GetModel()<<endl;
	cout << "Color           : " << veh.GetColor()<<endl;
	cout << "Ticket Type     : " <<((rg.TicketType == 1) ? "DAILY" : ((rg.TicketType ==2) ? "WEEKLY" : "MONTHLY") )<<endl;
	cout << "Price           : " << rg.TicketPrice <<endl;
	cout << "Start Time      : " <<rg.StartTime<<endl;
	cout << "--------------------------------------"<<endl;	
		}
	}
  }
}
}
