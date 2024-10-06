#include "ParkingLots.h"
ParkingLots::ParkingLots(string ID,char area,bool status)
{
	this->LotID = ID;
	this->Area  = area;
	this->Status= status;
}
void ParkingLots::ReadFromFile()
{
	ifstream filein("ParkingLots.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open ParkingLots.txt"<<endl;
	}
	else
	{
		string id;
		char area;
		bool status;
		while(getline(filein, id, ';'))
		{
			filein >> area;
			filein.ignore();
			filein >> status;
			filein.ignore();
			ParkingLots park(id,area,status);
			listpark.push_back(park);
		}
		filein.close();
	}
}

ParkingLots::ParkingLots() {ReadFromFile();}

string ParkingLots::GetLotID()
{
	return this->LotID;
}
bool ParkingLots::GetStatus()
{
	return this->Status;
}
void ParkingLots::SetStatus(bool x)
{
	this->Status = x;
}
char ParkingLots::GetArea()
{
	return this->Area;
}
void ParkingLots::Show(int option)
{
	switch(option)
	{
		case 1:
			for(auto park:listpark)
		{
			if(park.Area == 'C'){
			cout << "LotID : " << park.LotID << endl;
			cout << "Area  : " << park.Area  << endl;
			cout << "Status: " << ((park.Status) ? "ORDER" : "EMPTY") << endl;
			cout << "-------------------"<<endl;
			}
		}
			break;
		case 2:
			for(auto park:listpark)
		{
			if(park.Area == 'B'){
			cout << "LotID : " << park.LotID << endl;
			cout << "Area  : " << park.Area  << endl;
			cout << "Status: " << ((park.Status) ? "ORDER" : "EMPTY") << endl;
			cout << "-------------------"<<endl;
			}
		}
			break;
		case 3:
			for(auto park:listpark)
		{
			if(park.Area == 'A'){
			cout << "LotID : " << park.LotID << endl;
			cout << "Area  : " << park.Area  << endl;
			cout << "Status: " << ((park.Status) ? "ORDER" : "EMPTY") << endl;
			cout << "-------------------"<<endl;
			}
		}
			break;
		case 4:
			for(auto park:listpark)
		{
			cout << "LotID : " << park.LotID << endl;
			cout << "Area  : " << park.Area  << endl;
			cout << "Status: " << ((park.Status) ? "ORDER" : "EMPTY") << endl;
			cout << "-------------------"<<endl;
		}
			cout << "Nhap LotID can xem : ";
			break;
	}

}
