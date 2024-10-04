#include "Accounts.h"
#include <fstream>

Accounts::Accounts(string username,string password,bool role)
{
	this->username = username;
	this->password = password;
	this->role = role;
}

Accounts::Accounts() {}

void Accounts::ReadFromFile()
{
	ifstream filein("Accounts.txt");
	if(filein.is_open())
	{
		string user,pass;
		bool role;
		while(!filein.fail())
		{
			getline(filein,user,';');
			getline(filein,pass,';');
			filein>>role;
			filein.ignore();
			Accounts acc(user,pass,role);
			listacc.push_back(acc);
		}
		filein.close();
	}
	else cout << "Cannot open file Accounts.txt" << endl;
}

void AdminInterface()
{
	cout << "-------------- QUAN LI BAI DO XE ---------------"<<endl;
	cout << "*               1.Them ve moi                  *"<<endl;
	cout << "*               2.Xem danh sach bai do         *"<<endl;
	cout << "*               3.Chinh sua ve                 *"<<endl;
	cout << "*               4.Xoa ve                       *"<<endl;
	cout << "*               5.Thong ke                     *"<<endl;
	cout << "*               6.Dang xuat                    *"<<endl;
	cout << "*               7.Thoat                        *"<<endl;
	cout << "------------------------------------------------"<<endl;
	cout << "Nhap lua chon : ";
}

void UserInterface()
{
	cout << "-------------- CHUC NANG -----------------"<<endl;
	cout << "*               1.Dat ve                 *"<<endl;
	cout << "*               2.Xem ve                 *"<<endl;
	cout << "*               3.Chinh sua              *"<<endl;
	cout << "*               4.Dang xuat              *"<<endl;
	cout << "*               5.Thoat                  *"<<endl;
	cout << "LUU Y : Moi user chi dang ki toi da 3 ve!!"<<endl;
	cout << "-----------------------------------------------"<<endl;
	cout <<"Nhap lua chon : ";
}

int	Accounts::checkinput(string s){
	for(char c:s){
		if(!isdigit(c)) return -1;
	}
	if(s=="") return -1;
	else if(s.length()>1) return -1;
	else
	return stoi(s);
}



bool Accounts::Login()
{
	ReadFromFile();
	string user,pass;
	while(true)
	{
	cout << "----- SIGN IN -----"<<endl;
	cout << "Username : ";getline(cin,user);
	cout << "Password : ";getline(cin,pass);
	for(auto acc : listacc)
	{
		if(acc.username == user && acc.password == pass && acc.role == 1)	//ADMIN
		{
			cout << "Login Success!!!!" << endl;
				string option;
				while(1)
				{
					AdminInterface();
					getline(cin,option);
					int check = checkinput(option);
					system("cls");
					switch(check)
					{
						case 1:
							cout << "------ TAO VE MOI ------"<<endl;
							
							break;
						case 2:
							cout << "------ DANH SANH ------"<<endl;
							ParkingLots pl;
							pl.Show(4);
							cout <<endl<<endl<<"BAM PHIM BAT KI DE QUAY TRO LAI....."<<endl;
                    		_getch();
                    		system("cls");
							break;
						
					}
				}
			}
			else if(acc.username == user && acc.password == pass && acc.role == 0)   //USER
			{
				system("cls");
				string option;
				while(1)
				{
					UserInterface();
					getline(cin,option);
					int check = checkinput(option);
					if(check >=1 && check <= 5) system("cls");
					ParkingLots pl;Vehicles veh;Registrations rg;
					switch(check)
					{
						case 1:{
							here:
							cout << "-------- ORDER TICKET -------"<<endl;
							cout << "*         1.DAILY           *"<<endl;
							cout << "*         2.WEEKLY          *"<<endl;
							cout << "*         3.MONTHLY         *"<<endl;
							cout << "-----------------------------"<<endl;
							cout << "SELECT : ";
							getline(cin,option);
							int check = checkinput(option);
							if(check == -1){
								cout << "\nInvalid option!! Select again please"<<endl;
								cout << "Press any key to continue"<<endl;_getch();system("cls");goto here;
							}
							Register(pl,veh,rg,user,check);
							break;
						}
						case 2:{
							rg.Show(user);
							_getch();
							system("cls");
							break;
						}
						default:
							cout << "\nVui long nhap dung so lua chon!!"<<endl;
							cout << "Press any key to coninue..."<<endl;
							_getch();
							system("cls");
							break;	
					}
				}
				
			}
		}
		cout << "Invalid username or password!!!"<<endl;
	}
}


void Accounts::Check(){
	string option;
	Accounts acc;int check;
	do{
	cout << "--------------------" << endl;
	cout << "|      Welcome     |" << endl;
	cout << "--------------------" << endl;
	cout << "|    1.Dang Nhap   |" << endl;
	cout << "|    2.Dang Ki     |" << endl;
	cout << "--------------------" << endl;
	cout << "Nhap lua chon: ";
	getline(cin,option);
	check = checkinput(option);
	if(check == -1 || check > 2){
		cout << "Nhap sai lua chon!!!!!"<<endl;
		cout << "Vui long nhap lai!!!!!"<<endl;
		cout << "Press Any Key To Continue......."<<endl<<endl;
		_getch();
		system("cls");
	}
	}while(check!= 1 && check!=2);
	if(check == 1){
		system("cls");
		acc.Login();
	}
	else if(check == 2){
		system("cls");
		string user,pass,name,phone,mail;
		cout << "------ SIGN UP ------" << endl;
		cout << "Enter your username :"; getline(cin,user);
		cout << "Enter your password :"; getline(cin,pass);
		cout << "Enter your name     :"; getline(cin,name);
		cout << "Enter your phone    :"; getline(cin,phone);
		cout << "Enter your mail     :"; getline(cin,mail);
		cout << "Sign up success!!\n";
		_getch();system("cls");
		ofstream file("Accounts.txt",ios::app);
		file << user << ";" << pass << ";" << "0"<<endl;
		file.close();
		ofstream fileown("Owners.txt",ios::app);
		fileown << user << ";" << name << ";" << phone << ";" << mail << endl;
		fileown.close();
		acc.Login();
	}
}

void Accounts::Register(ParkingLots pl,Vehicles veh,Registrations rg,string user,int check){
	string pickLotID,lp,md,br,cl;bool find=false;
	char AreaTemp = ((check == 1) ? 'C' : ((check == 2) ? 'B' : 'A'));
	cout << "---------------------"<<endl;
	pl.Show(check);							
	cout << "Nhap LotID can dat : ";getline(cin,pickLotID);
	for(auto &park : listpark){
		if(park.GetLotID() == pickLotID && park.GetStatus()==0 && park.GetArea()==AreaTemp){
			find = true;
			park.SetStatus(1);
			cout << "Dang ki LotID " << pickLotID << " thanh cong!!"<<endl; cout << "Press any key to continue";_getch();system("cls");
			ofstream filepl("ParkingLots.txt",ios::out);
			ofstream fileveh("Vehicles.txt",ios::app);
			ofstream filerg("Registrations.txt",ios::app);
			for(auto &park:listpark){
				filepl << park.GetLotID() << ";" << park.GetArea() << ";" << park.GetStatus() << endl;
			}
			filepl.close();
			cout << "---- Vehice register ------"<<endl;
			cout << "Enter LicensePlate :" ;getline(cin,lp);
			cout << "Enter Brand        :" ;getline(cin,br);
			cout << "Enter Model        :" ;getline(cin,md);
			cout << "Enter Color        :" ;getline(cin,cl);
			fileveh << user << ";" << lp << ";" << br << ";" << md << ";" << cl << endl;
			cout << "Vehicle Register success!!"<<endl;cout << "Press any key to continue";_getch();system("cls");
			fileveh.close();
			time_t currentTime = time(nullptr);
			tm *timeInfo = localtime(&currentTime);
			filerg << AreaTemp << pickLotID << ";" << user << ";" << lp << ";" << pickLotID << ";" << check << ";" 
       			<< setfill('0') << setw(2) << timeInfo->tm_hour << ":" 
       			<< setfill('0') << setw(2) << timeInfo->tm_min << " " 
       			<< setfill('0') << setw(2) << timeInfo->tm_mday << "-" 
      			<< setfill('0') << setw(2) << (timeInfo->tm_mon + 1) << "-" 
       			<< timeInfo->tm_year + 1900 << endl;
			break;
	}
		else if(park.GetLotID() == pickLotID && park.GetStatus()==1 && park.GetArea()==AreaTemp){
			find=true;
			cout<<"\nLotID already ordered!!!"<<endl;
			cout<<"Press any key to continue";_getch();system("cls");break;
		}
		else if(park.GetLotID()==pickLotID && park.GetArea()!=AreaTemp){
			find=true;
			cout<<"\nPlease select LotID avaiable for Area : " << AreaTemp<<endl;
			cout<<"Press any key to continue";_getch();system("cls");break;
		}
	}
		if(!find){
		cout<<"\nLotID not in list!!"<<endl;
		cout<<"Press any key to continue";_getch();system("cls");}
}

