#pragma once

#include <QtWidgets/QMainWindow>
#include<qpushbutton.h>
#include<qdebug.h>
#include<qsqlerror.h>
#include "ui_StudentSystem.h"
#include"LoginWindow.h"
#include"LoginWindowUser.h"
#include "RegistWindow.h"
#include"QtMySQLClass.h"



class StudentSystem : public QMainWindow
{
    Q_OBJECT

public:
    StudentSystem(QWidget *parent = nullptr);
    void loginConnect();
    void RegistConnect();
    void BackSlot();
    bool AdminLoginDetection(AdminInfo*);
    bool UserLoginDetection(StudentInfo*);
    bool LoginGetUserInfo(StudentInfo*,QString);
    bool LoginGetAdminInfo(AdminInfo*,QString);
    ~StudentSystem();
signals:
    void back();

private:
    Ui::StudentSystemClass ui;
    LoginWindow* LGWadmin;
    LoginWindowUser* LGWuser;
    RegistWindow* RGW;
    QtMySQLClass* pDB;
};
