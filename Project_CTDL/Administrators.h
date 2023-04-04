#pragma once

#include "User.h"

class Administrators : public User
{
public:
	// Constructor - destructor
	Administrators(string _strAccount = "", string _strPassword = "111111", string _strName = "",
		string _strAddress = "", string _strPhone = "", string _strEmail = "");
	Administrators(const Administrators& admin);
	~Administrators();

	// Đọc file tài khoản và mật khẩu
	void readFileLogin(ifstream& inFile);

	// Tạo file
	void createFile(ofstream& outFile, string strFileName);

	// Kiểm tra tài khoản và mật khẩu khi đăng nhập có đúng hay không
	bool operator == (Administrators admin);
};