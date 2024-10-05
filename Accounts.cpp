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

void Accounts::SetPassword(string pass){
 	this->password = pass;
}

bool Accounts::Login(string user,string pass)
{
	ReadFromFile();
	while(true)
	{
	for(auto acc : listacc)
	{
		if(acc.username == user && acc.password == pass && acc.role == 1)	//ADMIN
		{
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
					ParkingLots pl;Vehicles veh;Registrations rg;Owners owner;
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
						case 3:{
							Edit(owner,user,pass);
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

string GetPassword() {
    string pass = "";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' là ki tu Enter
        if (ch == '\b' && !pass.empty()) { // Xoa ki tu neu nhin Backspace
            pass.pop_back();
            cout << "\b \b"; // Xoa ki tu hien thi tren man hinh
        } else if (ch != '\b') { // Neu khong phai ki tu Backspace
            pass.push_back(ch);
            cout << '*'; // Hien thi '' thay vi ki tu thuc te
        }
    }
    cout << endl;
    return pass;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void drawButton(int x, int y, string label, bool isSelected) {
    gotoxy(x, y);
    if (isSelected) {
        setColor(10); // Green color
        cout << "[ " << label << " ]"; // Button is selected
        setColor(7); // Return to default color
    } else {
        cout << "[ " << label << " ]"; // Button is not selected
    }
}
void drawBox(int x, int y, int width, int height) {
    // Ve khung dang nhap
    gotoxy(x, y);
    cout << char(218); // Goc tren trai
    for (int i = 0; i < width - 2; i++) cout << char(196); // Duong ngang
    cout << char(191); // Goc tren phai

    for (int i = 0; i < height - 2; i++) {
        gotoxy(x, y + i + 1);
        cout << char(179); // Duong doc ben trai
        gotoxy(x + width - 1, y + i + 1);
        cout << char(179); // Duong doc ben phai
    }

    gotoxy(x, y + height - 1);
    cout << char(192); // Goc duoi trai
    for (int i = 0; i < width - 2; i++) cout << char(196); // Duong ngang duoi
    cout << char(217); // Goc duoi phai
}

void Accounts::loginForm() {
    here:
    string user, pass;
    char ch;
    int formWidth = 40;
    int formHeight = 10;
    int startX = 35;
    int startY = 5;
    int selectedOption = 0; // 0: Login, 1: Back
    bool isSelected[2] = { true, false }; // To track the selected option
    while (true) {
        drawBox(startX, startY, formWidth, formHeight);
        gotoxy(startX + 12, startY + 1);
        cout << "HE THONG BAI DO XE";
        gotoxy(startX + 5, startY + 3);
        cout << "Username: ";
        gotoxy(startX + 5, startY + 4);
        cout << "Password: ";
        drawButton(startX + 15, startY + 6, "Login", isSelected[0]);
        drawButton(startX + 15, startY + 8, "Back", isSelected[1]);
        // Capture key press
        char key = _getch(); 
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) { // Enter key
            if (selectedOption == 0) {
                gotoxy(startX + 15, startY + 3);
                getline(cin, user);
                gotoxy(startX + 15, startY + 4);
                pass = GetPassword();
                bool validLogin = false;
                ReadFromFile();
                for (auto acc : listacc) {
                    if (user == acc.username && pass == acc.password) {
                        gotoxy(startX + 12, startY + 6);
                        cout << "Login successful!";
                        _getch();
                        system("cls");
                        Login(user, pass);
                        validLogin = true;
                        break;
                    }
                }
                if (!validLogin) {
                    gotoxy(startX + 5, startY + 6);
                    cout << "Invalid username or password!";
                    _getch();
                    system("cls");
                    continue; // Redraw the login form
                }
            } else if (selectedOption == 1) {
                system("cls");
                Welcome();
                return;
            }
        }
    }
}

void Accounts::Welcome() {
    const int boxWidth = 40;
    const int boxHeight = 8;
    const int boxX = 35;
    const int boxY = 5;
    int selectedValue;
    drawBox(boxX, boxY, boxWidth, boxHeight);
    int selectedOption = 0; // 0: Sign In, 1: Sign Up
    bool isSelected[2] = { true, false }; // To track the selected button
    while (true) {
    	gotoxy(boxX + 11, boxY + 1);
    	cout << "HE THONG BAI DO XE";
        drawButton(boxX + 14, boxY + 3, "Sign In", isSelected[0]);
        drawButton(boxX + 14, boxY + 5, "Sign Up", isSelected[1]);
        // Capture key press
        char key = _getch(); 
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Switch to the upper option
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Switch to the lower option
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) { // Enter key
            selectedValue = (selectedOption == 0) ? 1 : 2; // Assign value to variable
            break; 
        }
    }
    if(selectedValue == 1){
    	system("cls");loginForm();
	}
	else if (selectedValue == 2) {
    system("cls");
    int formWidth = 50;
    int formHeight = 17;
    int startX = 30;
    int startY = 3;
    int selectedOption = 0; // 0: Sign Up, 1: Back
    bool isSelected[2] = { true, false }; // To track the selected option
    string user, pass, name, phone, mail;
    while (true) {
        drawBox(startX, startY, formWidth, formHeight); 
        gotoxy(startX + 15, startY + 1);
        cout << "------ SIGN UP ------";
        gotoxy(startX + 5, startY + 3);
        cout << "Username: ";
        gotoxy(startX + 5, startY + 5);
        cout << "Password: ";
        gotoxy(startX + 5, startY + 7);
        cout << "Name    : ";
        gotoxy(startX + 5, startY + 9);
        cout << "Phone   : ";
        gotoxy(startX + 5, startY + 11);
        cout << "Mail    : ";
        drawButton(startX + 19, startY + 13, "Sign Up", isSelected[0]);
        drawButton(startX + 19, startY + 15, "Back", isSelected[1]);
        // Capture key press
        char key = _getch();
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) {
            if (selectedOption == 0) {
                gotoxy(startX + 15, startY + 3);
                getline(cin, user);
                gotoxy(startX + 15, startY + 5);
                getline(cin, pass);
                gotoxy(startX + 15, startY + 7);
                getline(cin, name);
                gotoxy(startX + 15, startY + 9);
                getline(cin, phone);
                gotoxy(startX + 15, startY + 11);
                getline(cin, mail);
                // Display success message
                gotoxy(startX + 15, startY + 13);
                cout << "Sign up success!!";
                _getch();
                system("cls");
                ofstream file("Accounts.txt", ios::app);
                file << user << ";" << pass << ";" << "0" << endl;
                file.close();
                ofstream fileown("Owners.txt", ios::app);
                fileown << user << ";" << name << ";" << phone << ";" << mail << endl;
                fileown.close();
                Welcome();
                return;
            } else if (selectedOption == 1) {
                system("cls");
                Welcome();
                return;
            }
        }
    }
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

void Accounts::Edit(Owners owner,string user,string pass)
{
	here:
	string name,phone,email,oldpass,newpass,option;
	owner.Show(user);
	cout << endl << endl;
	cout << "------Select information to update---"<<endl;
	cout << "*          1.Name                   *"<<endl;
	cout << "*          2.Phone                  *"<<endl;
	cout << "*          3.Email                  *"<<endl;
	cout << "*          4.Change Password        *"<<endl;
	cout << "*          5.Exit                   *"<<endl;
	cout << "-------------------------------------"<<endl;
	cout << "Select : ";
	getline(cin,option);
	int check = checkinput(option);
	switch(check){
		case 1:{
			cout << "Enter new Name : ";
			getline(cin,name);
			for(auto &own : listown){
				if(own.GetOwnerID() == user){
					own.SetName(name);
				}
			}
			cout << "Update Name Success!!"<<endl;
			break;
		}
		case 2:{
			cout << "Enter new Phone : ";
			getline(cin,phone);
			for(auto &own : listown){
				if(own.GetOwnerID() == user){
					own.SetPhone(phone);
				}
			}
			cout << "Update Phone Success!!"<<endl;
			break;
		}
		case 3:{
			cout << "Enter new email : ";
			getline(cin,email);
			for(auto &own : listown){
				if(own.GetOwnerID() == user){
					own.SetEmail(email);
				}
			}
			cout << "Update Email Success!!"<<endl;
			break;
		}
		case 4:{
			cout << "Enter old password : ";getline(cin,oldpass);
			if(oldpass != pass){
				cout << "Wrong Password!!!"<<endl;cout << "Press any key to continue";_getch();system("cls");goto here;
			}
			else{
				cout << "Enter new password : ";getline(cin,newpass);
				for(auto &acc : listacc){
					if(acc.username == user){
						acc.SetPassword(newpass);break;
					}
				}
				ofstream fileacc("Accounts.txt",ios::out);
				for(auto acc : listacc){
					fileacc << username << ";" << password << ";" << role << endl;
				}
				fileacc.close();
				cout << "Update Password Success!!"<<endl;
			}
			break;
		}
		default:{
			cout << "Invalid Option!!!"<<endl;
			cout << "Press any key to continue"<<endl;_getch();system("cls");
			break;
		}
	}
	ofstream file("Owners.txt",ios::out);
	for(auto own:listown){
		file << own.GetOwnerID() <<";"<<own.GetName() << ";" << own.GetPhone() << ";" << own.GetEmail() << endl;
	}
	file.close();
}
