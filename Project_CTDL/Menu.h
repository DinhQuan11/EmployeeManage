#pragma once

#include <string>

#include "User.h"

using namespace std;

// Thay đổi màu chữ và nền
void setColor(int iBackgroundColor, int iTextColor);

// Giao diện đăng nhập User
void loginInterface();

// Giao diện menu Admin
void menuAdmin();

// Giao diện menu Employee
void menuEmployee();

// Mã hóa mật khẩu thành '*'
string encodePassword();

// Đăng nhập User
void loginUser(string& strAccount, string& strPassword);

// Kiểm tra đăng nhập có đúng hay không
bool isLoginSuccess(User* user, string strFileName, string& strAcc, string& strPass);

// Kiểm tra tên user name có tồn tại
bool isUsernameEmployee(User* user, string strUserName);

// Thêm Employee
void addEmployee(User* user);

// Xóa Employee
void removeEmployee(User* user, string strUserName);

// Tìm Employee
void searchEmployee(User* user, string strUserName);

// Cập nhật Employee
void updateEmployee(User* user);

// Hiển thị thông tin tất cả Employee
void showAllEmployee(User* user);

// Hiển thị thông tin Employee
void showMyInfo(User* user, string strUserName);

// Thực hiện thay đổi mật khẩu
void changePassword(User* user, string strUserName, string strCurrentPass, string strNewPass);

// Thay đổi mật khẩu người dùng
void changePasswordUser(User* user, string strUserName);

// Giao diện menu đã liên kết
void mainMenu(User* listUser[]);