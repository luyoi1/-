#pragma once

#include <QWidget>
#include<qpushbutton.h>
#include<sstream>
#include<qstring.h>
#include<string>
#include<qtextedit.h>
#include<qmessagebox.h>
#include<string>
#include "ui_LoginWindowUser.h"
#include"InformationDisplayWindow.h"
#include"InputStudentIDdialog.h"
#include"QtMySQLClass.h"

struct StudentInfo;

class LoginWindowUser : public QWidget
{
	Q_OBJECT

public:
	LoginWindowUser(StudentInfo*,QWidget *parent = nullptr);
	void SetIntroductionText();
	void StudentInfoConnectText();
	void GradeInfoConnectText();
	void CourseInfoConnectText();
	void SelectOtherStudentInfoConnectText();
	~LoginWindowUser();

private:
	Ui::LoginWindowUserClass ui;
	InformationDisplayWindow* InfoWin;
	InputStudentIDdialog* InputDia;
	QtMySQLClass* pDB;
public:
	StudentInfo* User;
	QPushButton* QbackPB;
};

struct StudentInfo
{
	unsigned ID;
	QString Name;
	QString Profession;
	QString Email;
	int age;
	int Permissions;
	float GradePoint;
	int ClassID;
};
