#pragma once

#include "User.h"

class Employees : public User
{
public:
	// Constructor - destructor
	Employees(string _strAccount = "", string _strPassword = "111111", string _strName = "",
		string _strAddress = "", string _strPhone = "", string _strEmail = "");
	Employees(const Employees& empl);
	~Employees();

	// Đọc thông tin
	void inputInfo();

	// Đọc file tài khoản và mật khẩu
	void readFileLogin(ifstream& inFile);

	// Tạo file
	void createFile(ofstream& outFile, string strFileName);

	// Kiểm tra tài khoản và mật khẩu khi đăng nhập có đúng hay không
	bool operator == (Employees empl);
};