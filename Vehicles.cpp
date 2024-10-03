#include "Vehicles.h"
Vehicles::Vehicles(string ownid,string lp,string brand,string model,string color)
	:Owners("","","","")
{
	this->LicensePlate = lp;
	this->Brand = brand;
	this->Model = model;
	this->Color = color;
}

string Vehicles::GetOwnerID()
{
	return Owners::GetOwnerID();
}

string Vehicles::GetLicensePlate()
{
	return this->LicensePlate;
}

void Vehicles::ReadFromFile()
{
	ifstream filein("Vehicles.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Vehicles.txt"<<endl;
	}
	else
	{
		string ownid,lp,brand,model,color;
		while(getline(filein,ownid,';'))
		{
			getline(filein,lp,';');
			getline(filein,brand,';');
			getline(filein,model,';');
			getline(filein,color);
			Vehicles veh(ownid,lp,brand,model,color);
			listveh.push_back(veh);
		}
		filein.close();
	}
}

Vehicles::Vehicles()
	:Owners("","","","")
{
	ReadFromFile();
}
