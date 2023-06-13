#pragma once

#include <QWidget>
#include<qpushbutton.h>
#include<qdebug.h>
#include<qstring.h>
#include<qdialog.h>
#include<qmessagebox.h>
#include "ui_RegistWindow.h"
#include"RegistInsertInfoDialog.h"
#include"RegistInsertAdminInfoDialog.h"
#include"QtMySQLClass.h"


struct Admin;
struct User;

class RegistWindow : public QWidget
{
	Q_OBJECT

public:
	RegistWindow(QWidget *parent = nullptr);
	void AdminRegistReady();
	void UserRegistReady();
	void AdminRegist(std::shared_ptr<Admin> name);
	void UserRegist(std::shared_ptr<User> name);
	void InsertPBConnect(std::shared_ptr<User> name);
	void InsertPBAdminConnect(std::shared_ptr<Admin> name);
	void clearText();
	~RegistWindow();

private:
	Ui::RegistWindowClass ui;
	RegistInsertInfoDialog* InsertDialog;
	RegistInsertAdminInfoDialog* InsertAdminDialog;
	bool RegistIsTrue = true;
	QtMySQLClass* pDB;

};

struct Admin
{
	int StudentID;
	QString Password;
	QString Email;
	QString Key;
};

struct User
{
	int StudentID;
	QString Password;
	QString Email;
};