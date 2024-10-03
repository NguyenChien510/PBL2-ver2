#include "Owners.h"
Owners::Owners(string id,string name,string phone,string email)
{
	this->OwnerID = id;
	this->Name = name;
	this->Phone = phone;
	this->Email = email;
}
string Owners::GetOwnerID()
{
	return this->OwnerID;
}
void Owners::ReadFromFile()
{
	ifstream filein("Owners.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Owenrs.txt"<<endl;
	}
	else
	{
		string id,name,phone,email;
		while(getline(filein,id,';'))
		{
			getline(filein,name,';');
			getline(filein,phone,';');
			getline(filein,email,';');
			Owners own(id,name,phone,email);
			listown.push_back(own);
		}
		filein.close();
	}
}
