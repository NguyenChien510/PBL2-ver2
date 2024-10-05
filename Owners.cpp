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
string Owners::GetName(){
	return this->Name;
}
string Owners::GetPhone(){
	return this->Phone;
}
string Owners::GetEmail(){
	return this->Email;
}
void Owners::SetName(string name){
	this->Name = name;
}
void Owners::SetPhone(string phone){
	this->Phone = phone;
}
void Owners::SetEmail(string mail){
	this->Email = mail;
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
			getline(filein,email);
			Owners own(id,name,phone,email);
			listown.push_back(own);
		}
		filein.close();
	}
}


Owners::Owners(){
	ReadFromFile();
}
void Owners::Show(string user)
{
	cout << "------Infomation------"<<endl;
	for(auto own : listown){
		if(own.OwnerID == user)
		{
			cout << "Owner ID : " << own.OwnerID << endl;
			cout << "Name     : " << own.Name << endl;
			cout << "Phone    : " << own.Phone << endl;
			cout << "Email    : " << own.Email << endl;
		}
	}
}
