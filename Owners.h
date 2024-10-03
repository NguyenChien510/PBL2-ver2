#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Owners
{
	protected:
		string OwnerID;
		string Name;
		string Phone;
		string Email;
		vector<Owners>listown;
	public:
		Owners(string,string,string,string);
		string GetOwnerID();
		void ReadFromFile();
};
