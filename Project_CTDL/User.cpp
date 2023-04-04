#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "User.h"
#include "Menu.h"

using namespace std;

string User::getAccount()
{
	return strAccount;
}
string User::getPassword()
{
	return strPassword;
}
string User::getName()
{
	return strName;
}
string User::getAddress()
{
	return strAddress;
}
string User::getPhone()
{
	return strPhone;
}
string User::getEmail()
{
	return strEmail;
}
void User::setAccount(string _strAccount)
{
	strAccount = _strAccount;
}
void User::setPassword(string _strPassword)
{
	strPassword = _strPassword;
}
void User::setName(string _strName)
{
	strName = _strName;
}
void User::setAddress(string _strAddress)
{
	strAddress = _strAddress;
}
void User::setPhone(string _strPhone)
{
	strPhone = _strPhone;
}
void User::setEmail(string _strEmail)
{
	strEmail = _strEmail;
}

User::User(string _strAccount, string _strPassword, string _strName,
	string _strAddress, string _strPhone, string _strEmail)
{
	strAccount = _strAccount;
	strPassword = _strPassword;
	strName = _strName;
	strAddress = _strAddress;
	strPhone = _strPhone;
	strEmail = _strEmail;
}
User::User(const User& user)
{
	strAccount = user.strAccount;
	strPassword = user.strPassword;
	strName = user.strName;
	strAddress = user.strAddress;
	strPhone = user.strPhone;
	strEmail = user.strEmail;
}
User::~User(){}

void User::inputInfo()
{
	cin.ignore();

	setColor(0, 11);
	cout << endl << setw(18) << "" << "Nhap thong tin User:" << endl;

	cout << setw(18) << " -> " << "Ho ten: \t";
	getline(cin, strName);

	cout << setw(18) << " -> " << "Dia chi: \t";
	getline(cin, strAddress);

	cout << setw(18) << " -> " << "So dien thoai:";
	getline(cin, strPhone);

	cout << setw(18) << " -> " << "Email: \t";
	getline(cin, strEmail);
}

void User::readFileLogin(ifstream& inFile)
{
	getline(inFile, strAccount, ',');
	getline(inFile, strPassword);
}

void User::readFileUser(ifstream& inFile)
{
	getline(inFile, strName);
	getline(inFile, strAddress);
	getline(inFile, strPhone);
	getline(inFile, strEmail);
}

void User::openFile(ifstream& inFile, string strFileName)
{
	char szFileName[20];
	char szFileExtension[5] = ".txt";

	strcpy_s(szFileName, strFileName.c_str()); // Copy chuỗi strFileName đã ép kiểu vào szFileName
	strcat_s(szFileName, szFileExtension); // Ghép chuỗi - ghép phần mở rộng của tệp

	if (szFileName != NULL) // Nếu không NULL thì mở file
	{
		inFile.open(szFileName, ios_base::in);
	}
}

void User::createFile(ofstream& outFile, string strFileName)
{
	char szFileName[20];
	char szFileExtension[5] = ".txt";

	strcpy_s(szFileName, strFileName.c_str()); // Copy chuỗi strFileName đã ép kiểu vào szFileName
	strcat_s(szFileName, szFileExtension); // Ghép chuỗi - ghép phần mở rộng của tệp

	if (szFileName != NULL) // Nếu không NULL thì tạo file
	{
		outFile.open(szFileName, ios_base::out);
	}
}

void User::deleteFile(string strFileName)
{
	char szFileName[20];
	char szFileExtension[5] = ".txt";

	strcpy_s(szFileName, strFileName.c_str()); // Copy chuỗi strFileName đã ép kiểu vào szFileName
	strcat_s(szFileName, szFileExtension); // Ghép chuỗi - ghép phần mở rộng của tệp
	remove(szFileName); // Xóa file
}