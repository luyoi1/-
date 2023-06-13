#pragma once

#include <QWidget>
#include<qstring.h>
#include<qpushbutton.h>
#include "ui_LoginWindow.h"
#include"InformationDisplayWindow.h"
#include"InputStudentIDdialog.h"
#include"QtMySQLClass.h"
#include"AdminInsertWindow.h"

struct AdminInfo;

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(AdminInfo*,QWidget *parent = nullptr);
	void OneConnect();
	void SetIntroductionText();
	void GradeConnectText();
	void ProfessionalConnectText();
	void SelectConnectInputID();
	void UpdateConnectInputID();
	void InsertConnectInputID();
	void DeleteConnectInputID();
	~LoginWindow();

private:
	Ui::LoginWindowClass ui;
	InformationDisplayWindow* InfoWin;
	//InputStudentIDdialog* InputID;
	QtMySQLClass* pDB;
	std::shared_ptr<AdminInsertWindow> AdmWinInsert;
public:
	QPushButton* QbackPB;
	AdminInfo* Admin;
	
};

struct AdminInfo
{
	unsigned ID;
	QString Name;
	QString Department;
	int age;
	int Permissions;
	QString Key;
};

