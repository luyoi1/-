#include "StudentSystem.h"

StudentSystem::StudentSystem(QWidget* parent)
    : QMainWindow(parent), LGWadmin(nullptr), LGWuser(nullptr),RGW(nullptr),pDB(QtMySQLClass::GetDataBase())
{
    ui.setupUi(this);
    loginConnect();
    RegistConnect();
    

}

void StudentSystem::loginConnect()
{
    //链接登录注册按钮
    connect(ui.loginPB, &QPushButton::clicked, this, [=] {
        if (ui.adminPB->isChecked())
        {
            AdminInfo* Admin = new AdminInfo{ 1314627,u8"lk4r0s",u8"计算机通信学院",20,4,u8"你好" };
            if (!AdminLoginDetection(Admin))
            {
                QMessageBox::warning(this, u8"警告", u8"登录失败！请检查密码或账号是否正确");
                this->BackSlot();
                return;
            }
            else
                QMessageBox::information(this, u8"提醒", u8"登录成功!");


            if (LGWadmin == nullptr)
                LGWadmin = new LoginWindow(Admin);
            connect(LGWadmin->QbackPB, &QPushButton::clicked, this, [=] {
                this->back();
                LGWadmin->close();
                delete LGWadmin;
                LGWadmin = nullptr;
                this->show();
                });
            LGWadmin->show();
            this->hide();
        }
        else if (ui.userPB->isChecked())
        {
            StudentInfo* User=new StudentInfo{};
            if (!UserLoginDetection(User))
            {
                QMessageBox::warning(this, u8"警告", u8"登录失败！请检查密码或账号是否正确");
                this->BackSlot();
                return;
            }
            else
                QMessageBox::information(this, u8"提醒", u8"登录成功!");
            
            if (LGWuser == nullptr)
                LGWuser = new LoginWindowUser(User);

            //连接返回按钮
            connect(LGWuser->QbackPB, &QPushButton::clicked, this, [=] {
                this->back();
                LGWuser->close();
                delete LGWuser;
                LGWuser = nullptr;
                this->show();
                });


            LGWuser->show();
            this->hide();
        }
        else
        {
            QMessageBox::warning(this, u8"警告", u8"请选择你的登录角色！",QMessageBox::Ok);
        }
        });
    //绑定返回信号
    connect(this, &StudentSystem::back, this, &StudentSystem::BackSlot);
}

bool StudentSystem::UserLoginDetection(StudentInfo* User)
{
    QString str{"SELECT Student_ID FROM user_info where "};
    QString ID = ui.AccountText->text();
    QString Password = ui.PasswordText->text();
    str += "Student_ID = " + ID + " AND Password = '" + Password+"'";
    if (pDB->sqlExecute(str))
    {
        if (pDB->sqlQue->size() == 0)
        {
            return false;
        }
        else
        {
            return LoginGetUserInfo(User,ID);
        }
    }
    else
    {
        //QMessageBox::critical(this, u8"错误", pDB->sqlQue->lastError().text());
        return false;
    }
}

bool StudentSystem::LoginGetUserInfo(StudentInfo* User,QString ID)
{
    QString str{};
    str = "SELECT * FROM student where ";
    str += "ID = ";
    str+=ID + QString(";");
    if (pDB->sqlQue->exec(str))
    {
        if (pDB->sqlQue->size() != 0)
        {
            pDB->sqlQue->next();
            User->ID = pDB->sqlQue->value("ID").toInt();
            User->Name = pDB->sqlQue->value("Name").toString();
            User->age = pDB->sqlQue->value("Age").toInt();
            User->ClassID = pDB->sqlQue->value("ClassID").toInt();
            User->Permissions = pDB->sqlQue->value("StuPermissions").toInt();
            User->Profession = pDB->sqlQue->value("ProFession").toString();
            User->Email = pDB->sqlQue->value("Email").toString();
            return true;
        }
        else
        {
            return false;
        }
            
    }
    else
    {
        return false;
    }
}

bool StudentSystem::AdminLoginDetection(AdminInfo* Admin)
{
    QString str{ "SELECT Admin_ID FROM admin_info where " };
    QString ID = ui.AccountText->text();
    QString Password = ui.PasswordText->text();
    str += "Admin_ID = " + ID + " AND Password = '" + Password + "'";
    if (pDB->sqlExecute(str))
    {
        if (pDB->sqlQue->size() == 0)
        {
            return false;
        }
        else
        {
            pDB->sqlQue->next();
            Admin->Key = pDB->sqlQue->value("RegisterKey").toString();
            return LoginGetAdminInfo(Admin,ID);
        }
    }
    else
    {
        //QMessageBox::critical(this, u8"错误", pDB->sqlQue->lastError().text());
        return false;
    }
}

bool StudentSystem::LoginGetAdminInfo(AdminInfo* Admin, QString ID)
{
    QString str{};
    str = "SELECT * FROM Admin where ";
    str += "ID = ";
    str += ID + QString(";");
    if (pDB->sqlQue->exec(str))
    {
        if (pDB->sqlQue->size() != 0)
        {
            pDB->sqlQue->next();
            Admin->ID = pDB->sqlQue->value("ID").toInt();
            Admin->Name = pDB->sqlQue->value("Name").toString();
            Admin->age = pDB->sqlQue->value("Age").toInt();
            Admin->Permissions = pDB->sqlQue->value("Permissions").toInt();
            Admin->Department = pDB->sqlQue->value("Department").toString();
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}


void StudentSystem::RegistConnect()
{
    //链接注册按钮
    connect(ui.registPB, &QPushButton::clicked, this, [=] {
        if(RGW==nullptr)
            RGW = new RegistWindow();
        RGW->setAttribute(Qt::WA_ShowModal, true);
        RGW->clearText();
        RGW->show();
        });
}

void StudentSystem::BackSlot()
{
    ui.AccountText->clear();
    ui.PasswordText->clear();
}

StudentSystem::~StudentSystem()
{
    if (LGWadmin != nullptr)
        delete LGWadmin;
    if (LGWuser != nullptr)
        delete LGWuser;
    if (RGW != nullptr)
        delete RGW;
}
