#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>

#include "User.h"
#include "Administrators.h"
#include "Employees.h"
#include "Menu.h"

using namespace std;

void setColor(int iBackgroundColor, int iTextColor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int iColor = iBackgroundColor * 16 + iTextColor; 
	// Có 16 mã màu chính, dùng công thức i * 16 + j để kết hợp và tạo ra nhiều màu mới
	SetConsoleTextAttribute(hStdout, iColor);
}

void loginInterface()
{
	// setw dùng để thay đổi độ rộng của bề rộng được lấy từ thư viện iomanip
	setColor(0, 14);
	cout << endl;
	cout << setw(10) << "*" << "****************************************" << endl;
	cout << setw(10) << "*" << setw(40) << "*" << endl;
	cout << setw(10) << "*";

	setColor(0, 9);
	cout << setw(24) << "DANG NHAP";

	setColor(0, 14);
	cout << setw(16) << "*" << endl;
	cout << setw(10) << "*" << setw(40) << "*" << endl;
	cout << setw(10) << "*" << "****************************************" << endl;
}

void menuAdmin()
{
	setColor(0, 14);
	cout << endl;
	cout << setw(10) << "*" << "*************";

	setColor(0, 9);
	cout << " MENU ADMIN ";

	setColor(0, 14);
	cout << "***************" << endl;

	setColor(0, 13);
	cout << endl << setw(18) << "1. " << "Them Nhan vien" << endl;
	cout << setw(18) << "2. " << "Xoa Nhan vien" << endl;
	cout << setw(18) << "3. " << "Tim Nhan vien" << endl;
	cout << setw(18) << "4. " << "Cap nhat Nhan vien" << endl;
	cout << setw(18) << "5. " << "Hien thi thong tin Nhan vien" << endl;
	cout << setw(18) << "6. " << "Thoat!" << endl;

	setColor(0, 14);
	cout << endl << setw(10) << "*" << "****************************************" << endl;
}

void menuEmployee()
{
	setColor(0, 14);
	cout << endl;
	cout << setw(10) << "*" << "************";

	setColor(0, 9);
	cout << " MENU EMPLOYEE ";

	setColor(0, 14);
	cout << "*************" << endl;

	setColor(0, 13);
	cout << endl << setw(18) << "1. " << "Xem thong tin tai khoan" << endl;
	cout << setw(18) << "2. " << "Doi mat khau" << endl;
	cout << setw(18) << "3. " << "Thoat!" << endl;

	setColor(0, 14);
	cout << endl << setw(10) << "*" << "****************************************" << endl;
}

string encodePassword()
{
	string strPass;
	for (char cPass; cPass = _getch(); )
	{
		// nhấn enter để đăng nhập
		if (cPass == '\n' || cPass == '\r')
		{
			cout << '\n';
			break;
		}
		// nhấn backspace để xóa ký tự
		else if (cPass == '\b')
		{
			cout << "\b \b";
			if (!strPass.empty())
			{
				strPass.erase(strPass.size() - 1);
			}
		}
		// mã hóa password thành '*' và xét số lượng ký tự password nhập được tối đa là 14
		else if (isprint(cPass) && strPass.size() < 14)
		{
			cout << "*";
			strPass += cPass;
		}
	}
	return strPass;
}

void loginUser(string& strAccount, string& strPassword)
{
	setColor(0, 11);
	cout << setw(15) << "" << "User name:\t";
	cin >> strAccount;
	cout << endl;

	cout << setw(15) << "" << "Password:\t";
	strPassword = encodePassword();
	cout << endl;
}

bool isLoginSuccess(User* user, string strFileName, string& strAcc, string& strPass)
{
	ifstream inFile;
	inFile.open(strFileName, ios_base::in); // Mở file

	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user = new User();
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		if (user->getAccount() + user->getPassword() == strAcc + " " + strPass)
		{
			return true;
		}
		delete user;
	}
	inFile.close();
	return false;
}

bool isUsernameEmployee(User* user, string strUserName)
{
	ifstream inFile;
	inFile.open("Employees.txt", ios_base::in); // Mở file
	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user = new Employees();
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		if (strUserName == user->getAccount()) // So sánh tên user name nhập vào với tài khoản có sẵn
		{
			return true;
		}
		delete user;
	}
	inFile.close();
	return false;
}

void addEmployee(User* user)
{
	setColor(0, 13);
	cout << endl << setw(19) << "" << "~~~~~ Them Nhan vien ~~~~~\n" << endl;
	setColor(0, 9);
	cout << setw(18) << "" << "Nhap Username Nhan vien muon them: " << endl;
	cout << setw(18) << " -> ";

	string strAcc;
	cin >> strAcc;

	if (isUsernameEmployee(user, strAcc)) // Nếu user đã tồn tại
	{
		setColor(0, 12);
		cout << endl << setw(18) << " (!) " << "Username Nhan vien da ton tai!";
	}
	else
	{
		ofstream outFile;
		Employees* empl = new Employees();
		outFile.open("Employees.txt", ios_base::app); // Tìm đến cuối dòng trước khi ghi user mới
		outFile << endl << strAcc << ", " << "111111";
		outFile.close();

		empl->createFile(outFile, strAcc); // Tạo file thông tin của Employee
		empl->inputInfo(); // Nhập thông tin của Employee
		outFile << empl->getName() << endl << empl->getAddress() << endl
			<< empl->getPhone() << endl << empl->getEmail();
		outFile.close();

		setColor(0, 10);
		cout << endl << setw(18) << " (!) " << "Them Nhan vien thanh cong!" << endl;
		delete empl;
	}
}

void removeEmployee(User* user, string strUserName)
{
	ifstream inFile;
	inFile.open("Employees.txt", ios_base::in); // Mở file
	ofstream outFile;
	outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt

	int iCountUser = 0; // Đếm số lượng Employee
	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user = new Employees();
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		if (user->getAccount() != strUserName) // Nếu user name không trùng
		{
			outFile << user->getAccount() << "," << user->getPassword() << endl;
		}
		iCountUser++;
		delete user;
	}
	inFile.close();
	outFile.close();

	remove("Employees.txt"); // Xóa file Employees

	inFile.open("Temp.txt", ios_base::in); // Mở file Temp.txt
	outFile.open("Employees.txt", ios_base::out); // Tạo lại file Employees

	while (iCountUser > 1)
	{
		user = new Employees();
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		if (iCountUser == 2)
		{
			outFile << user->getAccount() << "," << user->getPassword();
			break;
		}
		outFile << user->getAccount() << "," << user->getPassword() << endl;
		iCountUser--;
		delete user;
	}

	inFile.close();
	outFile.close();

	user->deleteFile(strUserName); // Xóa file thông tin của Employee


	setColor(0, 10);
	cout << endl << setw(18) << " (!) " << "Xoa Nhan vien thanh cong!" << endl;

	remove("Temp.txt"); // Xóa file Employees copy
}

void searchEmployee(User* user, string strUserName)
{
	ifstream inFile;
	user = new Employees();
	user->openFile(inFile, strUserName); // Mở file Employee cần tìm
	user->readFileUser(inFile); // Đọc file

	setColor(0, 11);
	cout << endl << setw(18) << "" << "Thong tin cua Nhan vien muon tim:" << endl << endl;

	cout << setw(10) << left << "";
	cout << setw(25) << left << "Ho ten";
	cout << setw(25) << left << "Dia chi";
	cout << setw(15) << left << "So dien thoai";
	cout << setw(35) << right << "Email" << endl;

	cout << setw(10) << left << "";
	cout << setfill('_'); // Set fill bằng ký tự '-'
	cout << setw(100) << "_" << endl; // fill 100 ký tự '-'
	cout << setfill(' '); // Reset fill bằng ký tự ' '

	// In thông tin như format trên
	cout << setw(10) << left << "";
	cout << setw(25) << left << user->getName();
	cout << setw(25) << left << user->getAddress();
	cout << setw(15) << left << user->getPhone();
	cout << setw(35) << right << user->getEmail() << endl;

	delete user;
	inFile.close();
}

void updateEmployee(User* user)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open("Employees.txt", ios_base::in); // Mở file

	setColor(0, 13);
	cout << endl << setw(19) << "" << "~~~~~ Cap nhat Nhan vien ~~~~~\n" << endl;

	setColor(0, 9);
	cout << setw(18) << "" << "Nhap Username Nhan vien muon cap nhat:" << endl;
	cout << setw(18) << " -> ";

	string strUserName;
	cin >> strUserName;

	inFile.close();

	if (isUsernameEmployee(user, strUserName))
	{
		setColor(0, 11);
		cout << endl << setw(18) << "" << "1. Ho ten" << endl;
		cout << setw(18) << "" << "2. Dia chi" << endl;
		cout << setw(18) << "" << "3. So dien thoai" << endl;
		cout << setw(18) << "" << "4. Email" << endl;
		cout << endl << setw(18) << " -> " << "Chon thuoc tinh muon cap nhat: ";

		int iOptionUpdate;
		cin >> iOptionUpdate;

		switch (iOptionUpdate)
		{
			case 1:
			{
				system("cls"); // Clear màn hình console
				setColor(0, 13);
				cout << endl << setw(18) << "" << "~~~ Cap nhat ho ten ~~~" << endl;
				setColor(0, 11);
				cout << endl << setw(18) << "" << "Nhap ho ten muon thay doi:" << endl;
				cout << setw(18) << " -> ";

				cin.ignore();
				string strEdit;
				getline(cin, strEdit);

				user = new Employees();
				user->openFile(inFile, strUserName); // Mở file thông tin Employee
				user->readFileUser(inFile); // Đọc file thông tin Employee

				outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt
				outFile << strEdit << endl << user->getAddress() << endl << user->getPhone()	
					<< endl << user->getEmail(); // Nhập thông tin mới vào file Temp.txt
				inFile.close();
				outFile.close();
				user->deleteFile(strUserName); // Xóa file thông tin Employee cũ
				delete user;

				inFile.open("Temp.txt", ios_base::in); // Mở file Temp.txt
				user = new Employees();
				user->readFileUser(inFile); // Đọc file thông tin Employee
				user->createFile(outFile, strUserName); // Tạo file thông tin Employee mới

				// Lấy thông tin từ file Temp.txt để cập nhật vào file thông tin Employee
				outFile << user->getName() << endl << user->getAddress() << endl 
					<< user->getPhone() << endl << user->getEmail(); 
				inFile.close();
				outFile.close();
				delete user;

				setColor(0, 10);
				cout << endl << setw(18) << " (!) " << "Cap nhat ho ten Nhan vien thanh cong!" << endl;
				remove("Temp.txt"); // Xóa file Temp.txt
				break;
			}
			case 2:
			{
				system("cls"); // Clear màn hình console
				setColor(0, 13);
				cout << endl << setw(18) << "" << "~~~ Cap nhat dia chi ~~~" << endl;
				setColor(0, 11);
				cout << endl << setw(18) << "" << "Nhap dia chi muon thay doi:" << endl;
				cout << setw(18) << " -> ";

				cin.ignore();
				string strEdit;
				getline(cin, strEdit);

				user = new Employees();
				user->openFile(inFile, strUserName); // Mở file thông tin Employee
				user->readFileUser(inFile); // Đọc file thông tin Employee

				outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt
				outFile << user->getName() << endl << strEdit << endl << user->getPhone() 
					<< endl << user->getEmail(); // Nhập thông tin mới vào file Temp.txt
				inFile.close();
				outFile.close();
				user->deleteFile(strUserName); // Xóa file thông tin Employee cũ
				delete user;

				inFile.open("Temp.txt", ios_base::in); // Mở file Temp.txt
				user = new Employees();
				user->readFileUser(inFile); // Đọc file thông tin Employee
				user->createFile(outFile, strUserName); // Tạo file thông tin Employee mới

				// Lấy thông tin từ file Temp.txt để cập nhật vào file thông tin Employee
				outFile << user->getName() << endl << user->getAddress() << endl
					<< user->getPhone() << endl << user->getEmail(); 
				inFile.close();
				outFile.close();
				delete user;

				setColor(0, 10);
				cout << endl << setw(18) << " (!) " << "Cap nhat dia chi Nhan vien thanh cong!" << endl;
				remove("Temp.txt"); // Xóa file Temp.txt
				break;
			}
			case 3:
			{
				system("cls"); // Clear màn hình console
				setColor(0, 13);
				cout << endl << setw(18) << "" << "~~~ Cap nhat so dien thoai ~~~" << endl;
				setColor(0, 11);
				cout << endl << setw(18) << "" << "Nhap so dien thoai muon thay doi:" << endl;
				cout << setw(18) << " -> ";

				cin.ignore();
				string strEdit;
				getline(cin, strEdit);

				user = new Employees();
				user->openFile(inFile, strUserName); // Mở file thông tin Employee
				user->readFileUser(inFile); // Đọc file thông tin Employee

				outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt
				outFile << user->getName() << endl << user->getAddress() << endl << strEdit
					<< endl << user->getEmail(); // Nhập thông tin mới vào file Temp.txt
				inFile.close();
				outFile.close();
				user->deleteFile(strUserName); // Xóa file thông tin Employee cũ
				delete user;

				inFile.open("Temp.txt", ios_base::in); // Mở file Temp.txt
				user = new Employees();
				user->readFileUser(inFile); // Đọc file thông tin Employee
				user->createFile(outFile, strUserName); // Tạo file thông tin Employee mới

				// Lấy thông tin từ file Temp.txt để cập nhật vào file thông tin Employee
				outFile << user->getName() << endl << user->getAddress() << endl
					<< user->getPhone() << endl << user->getEmail();
				inFile.close();
				outFile.close();
				delete user;

				setColor(0, 10);
				cout << endl << setw(18) << " (!) " << "Cap nhat so dien thoai Nhan vien thanh cong!" << endl;
				remove("Temp.txt"); // Xóa file Temp.txt
				break;
			}
			case 4:
			{
				system("cls"); // Clear màn hình console
				setColor(0, 13);
				cout << endl << setw(18) << "" << "~~~ Cap nhat email ~~~" << endl;
				setColor(0, 11);
				cout << endl << setw(18) << "" << "Nhap email muon thay doi:" << endl;
				cout << setw(18) << " -> ";

				cin.ignore();
				string strEdit;
				getline(cin, strEdit);

				user = new Employees();
				user->openFile(inFile, strUserName); // Mở file thông tin Employee
				user->readFileUser(inFile); // Đọc file thông tin Employee

				outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt
				outFile << user->getName() << endl << user->getAddress() << endl << user->getPhone()
					<< endl << strEdit; // Nhập thông tin mới vào file Temp.txt
				inFile.close();
				outFile.close();
				user->deleteFile(strUserName); // Xóa file thông tin Employee cũ
				delete user;

				inFile.open("Temp.txt", ios_base::in); // Mở file Temp.txt
				user = new Employees();
				user->readFileUser(inFile); // Đọc file thông tin Employee
				user->createFile(outFile, strUserName); // Tạo file thông tin Employee mới

				// Lấy thông tin từ file Temp.txt để cập nhật vào file thông tin Employee
				outFile << user->getName() << endl << user->getAddress() << endl
					<< user->getPhone() << endl << user->getEmail();
				inFile.close();
				outFile.close();
				delete user;

				setColor(0, 10);
				cout << endl << setw(18) << " (!) " << "Cap nhat email Nhan vien thanh cong!" << endl;
				remove("Temp.txt"); // Xóa file Temp.txt
				break;
			}
			default:
			{
				setColor(0, 12);
				cout << endl << setw(18) << " (!) " << "Khong co thuoc tinh nay!" << endl;
				break;
			}
		}
	}
	else
	{
		setColor(0, 12);
		cout << endl << setw(18) << " (!) " << "Username Nhan vien khong ton tai!" << endl;
	}
}

void showAllEmployee(User* user)
{
	ifstream inFile;
	user = new Employees();
	inFile.open("Employees.txt", ios_base::in); // Mở file
	string strUser[100];
	int iCountUser = 0; // Đếm số lượng Employee
	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		strUser[iCountUser] = user->getAccount(); // Lấy tất cả tên tài khoản Employee lưu vào mảng
		iCountUser++;
	}
	inFile.close();

	setColor(0, 13);
	cout << endl << setw(18) << "" << "~~~~~ Hien thi thong tin Nhan vien ~~~~~" << endl;
	setColor(0, 11);
	cout << endl << setw(23) << "" << "Thong tin cua tat ca Nhan vien:" << endl << endl;

	cout << setw(10) << left << "";
	cout << setw(25) << left << "Ho ten";
	cout << setw(25) << left << "Dia chi";
	cout << setw(15) << left << "So dien thoai";
	cout << setw(35) << right << "Email" << endl;

	cout << setw(10) << left << "";
	cout << setfill('_'); // Set fill bằng ký tự '-'
	cout << setw(100) << "_" << endl; // fill 100 ký tự '-'
	cout << setfill(' '); // Reset fill bằng ký tự ' '

	for (int i = 0; i < iCountUser; i++)
	{
		string strFileName = strUser[i];
		user->openFile(inFile, strFileName); // Mở file
		user->readFileUser(inFile); // Đọc file thông tin user
		cout << setw(10) << left << "";
		cout << setw(25) << left << user->getName();
		cout << setw(25) << left << user->getAddress();
		cout << setw(15) << left << user->getPhone();
		cout << setw(35) << right << user->getEmail() << endl;
		inFile.close();
	}

	delete user;
}

void showMyInfo(User* user, string strUserName)
{
	ifstream inFile;
	user = new Employees();
	user->openFile(inFile, strUserName); // Mở file thông tin Employee
	user->readFileUser(inFile); // Đọc file thông tin

	setColor(0, 13);
	cout << endl << setw(18) << "" << "~~~ Xem thong tin tai khoan ~~~" << endl;

	setColor(0, 11);
	cout << endl << setw(24) << "" << "Thong tin cua ban:" << endl << endl;

	cout << setw(10) << left << "";
	cout << setw(25) << left << "Ho ten";
	cout << setw(25) << left << "Dia chi";
	cout << setw(15) << left << "So dien thoai";
	cout << setw(35) << right << "Email" << endl;

	cout << setw(10) << left << "";
	cout << setfill('_'); // Set fill bằng ký tự '-'
	cout << setw(100) << "_" << endl; // fill 100 ký tự '-'
	cout << setfill(' '); // Reset fill bằng ký tự ' '

	// In thông tin như format trên
	cout << setw(10) << left << "";
	cout << setw(25) << left << user->getName();
	cout << setw(25) << left << user->getAddress();
	cout << setw(15) << left << user->getPhone();
	cout << setw(35) << right << user->getEmail() << endl;

	inFile.close();
	delete user;
}

void changePassword(User* user, string strUserName, string strCurrentPass, string strNewPass)
{
	ifstream inFile;
	ofstream outFile;

	outFile.open("Temp.txt", ios_base::out); // Tạo file Temp.txt
	inFile.open("Employees.txt", ios_base::in); // Mở file Employees.txt
	int iCountUser = 0; // Đếm số lượng user
	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		iCountUser++;
	}
	inFile.close();

	inFile.open("Employees.txt", ios_base::in); // Mở file Employees.txt
	int iCountTemp = iCountUser; // Đếm số lượng user
	while (iCountUser > 0)
	{
		user->readFileLogin(inFile);
		if (iCountUser == 1)
		{
			outFile << user->getAccount() << "," << user->getPassword();
			break;
		}
		outFile << user->getAccount() << "," << user->getPassword() << endl;
		iCountUser--;
	}
	inFile.close();
	outFile.close();
	remove("Employees.txt");

	inFile.open("Temp.txt", ios_base::in);
	outFile.open("Employees.txt", ios_base::out); // Tạo lại file Employees.txt
	while (iCountTemp > 0)
	{
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		if (strUserName == user->getAccount() && 
			" " + strCurrentPass == user->getPassword() && iCountTemp == 1)
		{
			outFile << user->getAccount() << ", " << strNewPass;
			break;
		}
		else if (strUserName == user->getAccount() && " " + strCurrentPass == user->getPassword())
		{
			outFile << user->getAccount() << ", " << strNewPass << endl;
		}
		else
		{
			if (iCountTemp == 1)
			{
				outFile << user->getAccount() << "," << user->getPassword();
				break;
			}
			else if (iCountTemp != 1)
			{
				outFile << user->getAccount() << "," << user->getPassword() << endl;
			}
			else
			{
				break;
			}
		}
		iCountTemp--;
	}
	setColor(0, 10);
	cout << endl << setw(18) << " (!) " << "Thay doi mat khau thanh cong!" << endl;
	inFile.close();
	outFile.close();
	remove("Temp.txt");
}

void changePasswordUser(User* user, string strUserName)
{
	setColor(0, 13);
	cout << endl << setw(15) << "" << "~~~~~ Thay doi mat khau ~~~~~" << endl;

	setColor(0, 11);
	cout << endl << setw(18) << "" << "Nhap mat khau hien tai: " << endl;
	cout << setw(18) << " -> ";
	string strCurrentPass;
	strCurrentPass = encodePassword();

	cout << endl << setw(18) << "" << "Nhap mat khau moi: " << endl;
	cout << setw(18) << " -> ";
	string strNewPass;
	strNewPass = encodePassword();

	cout << endl << setw(18) << "" << "Xac nhan mat khau: " << endl;
	cout << setw(18) << " -> ";
	string strConfirmPass;
	strConfirmPass = encodePassword();

	ifstream inFile;
	inFile.open("Employees.txt", ios_base::in);
	bool bCheckPassword = false;
	while (!inFile.eof()) // Kiểm tra con trỏ trong tệp tin có đang ở cuối tệp không
	{
		user = new Employees();
		user->readFileLogin(inFile); // Đọc file tài khoản và mật khẩu
		// Kiểm tra mật khẩu nhập vô có đúng của tài khoản đó Kiểm tra xác nhận
		//	 mật khẩu và kiểm tra mật khẩu mới phải khác mật khẩu mặc định
		if (" " + strCurrentPass == user->getPassword() && 
			strNewPass == strConfirmPass && strNewPass != "111111")
		{
			bCheckPassword = true;
			break;
		}
		delete user;
	}
	inFile.close();

	if (bCheckPassword)
	{
		changePassword(user, strUserName, strCurrentPass, strNewPass);
	}
	else
	{
		setColor(0, 12);
		cout << endl << setw(18) << " (!) " << "Thay doi mat khau khong thanh cong!" << endl;
		cout << setw(18) << " (!) " << "Vui long kiem tra lai thong tin!" << endl;
	}
}

void mainMenu(User* listUser[])
{
	string strAcc;
	string strPass;
	User* user = NULL;

	int iCountLogin = 0; // Số lần đăng nhập

	while (true)
	{
		system("cls"); // Clear màn hình console
		loginInterface(); // Giao diện đăng nhập
		loginUser(strAcc, strPass); // Đăng nhập

		// Nếu là Admin
		if (isLoginSuccess(user, "Administrators.txt", strAcc, strPass))
		{
			bool bExit = false; // Kiểm tra chức năng thoát
			while (true)
			{
				system("cls"); // Clear màn hình console
				menuAdmin();
				setColor(0, 11);
				cout << setw(18) << " -> " << "Chon chuc nang: ";

				int iOptionAdmin;
				cin >> iOptionAdmin;

				switch (iOptionAdmin)
				{
					case 1:
					{
						system("cls"); // Clear màn hình console
						addEmployee(user);
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 2:
					{
						system("cls"); // Clear màn hình console
						setColor(0, 13);
						cout << endl << setw(19) << "" << "~~~~~ Xoa Nhan vien ~~~~~\n" << endl;
						setColor(0, 9);
						cout << setw(18) << "" << "Nhap ten Username Nhan vien muon xoa:" << endl;
						cout << setw(18) << " -> ";

						string strUserName;
						cin >> strUserName;

						if (isUsernameEmployee(user, strUserName))
						{
							removeEmployee(user, strUserName); // Xóa Employee
						}
						else
						{
							setColor(0, 12);
							cout << endl << setw(18) << " (!) " << "Username Nhan vien khong ton tai!" << endl;
						}
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 3:
					{
						system("cls"); // Clear màn hình console
						setColor(0, 13);
						cout << endl << setw(19) << "" << "~~~~~ Tim Nhan vien ~~~~~\n" << endl;
						setColor(0, 9);
						cout << setw(18) << "" << "Nhap ten Username Nhan vien muon tim:" << endl;
						cout << setw(18) << " -> ";

						string strUserName;
						cin >> strUserName;

						if (isUsernameEmployee(user, strUserName))
						{
							searchEmployee(user, strUserName); // Tìm Employee
						}
						else
						{
							setColor(0, 12);
							cout << endl << setw(18) << " (!) " << "Username Nhan vien khong ton tai!" << endl;
						}
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 4:
					{
						system("cls"); // Clear màn hình console
						updateEmployee(user); // Cập nhật Employee
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 5:
					{
						system("cls"); // Clear màn hình console
						showAllEmployee(user); // Hiển thị tất cả Employee
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 6:
					{
						bExit = true;
						break;
					}
					default:
					{
						setColor(0, 12);
						cout << setw(18) << " (!) " << "Khong co chuc nang nay!" << endl;
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
				}
				if (bExit == true)
				{
					break;
				}
			}
		}

		// Nếu là Employee
		else if (isLoginSuccess(user, "Employees.txt", strAcc, strPass))
		{
			if (strPass == "111111")
			{
				system("cls");
				setColor(0, 12);
				cout << endl << setw(15) << " (!) " 
					<< "Vui long doi mat khau truoc khi su dung!" << endl;
				char cNotification = _getch(); // Dừng màn hình để thông báo
				changePasswordUser(user, strAcc); // Thay đổi mật khẩu
				char cNotification2 = _getch(); // Dừng màn hình để thông báo
			}
			bool bExit = false;
			while (true)
			{
				system("cls");
				menuEmployee();
				setColor(0, 11);
				cout << setw(18) << " -> " << "Chon chuc nang: ";

				int iOptionEmpl;
				cin >> iOptionEmpl;

				switch (iOptionEmpl)
				{
					case 1:
					{
						system("cls"); // Clear màn hình console
						showMyInfo(user, strAcc); // Hiển thị thông tin cá nhân
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 2:
					{
						system("cls"); // Clear màn hình console
						changePasswordUser(user, strAcc); // Thay đổi mật khẩu
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
					case 3:
					{
						bExit = true;
						break;
					}
					default:
					{
						setColor(0, 12);
						cout << endl << setw(18) << " (!) " << "Khong co chuc nang nay!" << endl;
						char cNotification = _getch(); // Dừng màn hình để thông báo
						break;
					}
				}
				if (bExit == true)
				{
					break;
				}
			}
		}

		// Nếu đăng nhập sai tài khoản hoặc mật khẩu
		else
		{
			iCountLogin++; // Tăng số lần đăng nhập
			setColor(0, 12);
			cout << setw(15) << " (!) " << "Tai khoan hoac mat khau khong dung!" << endl;
			char cNotification = _getch(); // Dừng màn hình để thông báo
		}

		// Nếu đăng nhập sai 3 lần
		if (iCountLogin == 3)
		{
			setColor(0, 12);
			cout << endl << setw(15) << " (!) " << "Ban da nhap sai 3 lan!" << endl;
			setColor(0, 0); // Đổi màu lệnh thông báo cuối console trùng với màu background
			return; // Thoát chương trình
		}
	}
}