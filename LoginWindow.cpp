#include "LoginWindow.h"

LoginWindow::LoginWindow(AdminInfo * Admin_,QWidget* parent)
	: QWidget(parent),Admin(Admin_),InfoWin(new InformationDisplayWindow(this))
	,pDB(QtMySQLClass::GetDataBase()),AdmWinInsert(new AdminInsertWindow(luyoi1::INSERT))
{
	ui.setupUi(this);
	QbackPB = ui.BackPB;
	InfoWin->setAttribute(Qt::WA_ShowModal, true);
	OneConnect();
}

void LoginWindow::OneConnect()
{
	SetIntroductionText();
	ProfessionalConnectText();
	GradeConnectText();
	SelectConnectInputID();
	UpdateConnectInputID();
	InsertConnectInputID();
	DeleteConnectInputID();
}

void LoginWindow::SetIntroductionText()
{
	QString str{};
	str += u8"简介:\r\n";
	str += u8"姓名:" + Admin->Name + "\r\n";
	str += u8"编号:" + QString(std::to_string(Admin->ID).c_str()) + "\r\n";
	str += u8"权限等级:" + QString(std::to_string(Admin->Permissions).c_str()) + "\r\n";
	ui.IntroductionText->setText(str);
}

void LoginWindow::GradeConnectText()
{
	QString str{};
	str = QString("select ID,Name,Grade_Point from student order by Grade_Point desc limit 50;");
	connect(ui.GradePointRankPB, &QPushButton::clicked, this, [=] {
		QString str1{};
		if (pDB->sqlQue->exec(str))
		{
			if (pDB->sqlQue->size() == 0)
				QMessageBox::warning(this, u8"警告", u8"查询不到信息!");
			else
			{
				str1 = u8"排名如下:\r\n";
				pDB->sqlQue->next();
				for (unsigned i = 0;i < pDB->sqlQue->size();pDB->sqlQue->next(), i++)
				{
					str1 += QString(u8"学生ID: %1 \r学生姓名:%2 \r绩点: %3 \r排名: %4\r\n").arg(pDB->sqlQue->value("ID").toString(),
						pDB->sqlQue->value("Name").toString(),pDB->sqlQue->value("Grade_Point").toString(),QString("%1").arg(i+1));
					str1 += "\r\n\r\n";
				}

			}
		}
		else
			QMessageBox::warning(this, u8"警告", u8"查询失败!");
		InfoWin->Textl->setText(str1);
		InfoWin->show();
		});
}

void LoginWindow::ProfessionalConnectText()
{
	QString str{};
	str = QString("select * from class;");
	connect(ui.ProfessionInfoPB, &QPushButton::clicked, this, [=] {
		QString str1{};
		if (pDB->sqlQue->exec(str))
		{
			if (pDB->sqlQue->size() == 0)
				QMessageBox::warning(this, u8"警告", u8"查询不到信息!");
			else
			{
				str1 = u8"专业信息如下:\r\n";
				pDB->sqlQue->next();
				for (unsigned i = 0;i < pDB->sqlQue->size();pDB->sqlQue->next(), i++)
				{
					str1 += QString(u8"专业班级ID: %1 班级名称:%2 \r学生人数:%3 \r\n").arg(pDB->sqlQue->value("ID").toString()
						,pDB->sqlQue->value("Name").toString(),pDB->sqlQue->value("StudentNum").toString());
					str1 += "\r\n\r\n";
				}

			}
		}
		else
			QMessageBox::warning(this, u8"警告", u8"查询失败!");
		InfoWin->Textl->setText(str1);
		InfoWin->show();
		});
}

void LoginWindow::SelectConnectInputID()
{
	InputStudentIDdialog *InputID = new InputStudentIDdialog(luyoi::SELECT,this);
	InputID->setAttribute(Qt::WA_ShowModal, true);
	connect(ui.SelectInfoPB, &QPushButton::clicked, this, [=] {
		InputID->show();
		});
}
void LoginWindow::UpdateConnectInputID()
{
	InputStudentIDdialog* InputID = new InputStudentIDdialog(luyoi::UPDATE, this);
	InputID->setAttribute(Qt::WA_ShowModal, true);
	connect(ui.UpdateInfoPB, &QPushButton::clicked, this, [=] {
		InputID->show();
		});
}
void LoginWindow::InsertConnectInputID()
{
	
	connect(ui.InsertInfoPB, &QPushButton::clicked, this, [&] {
		AdmWinInsert->show();
		});
}
void LoginWindow::DeleteConnectInputID()
{
	InputStudentIDdialog* InputID = new InputStudentIDdialog(luyoi::DELETE);
	InputID->setAttribute(Qt::WA_ShowModal, true);
	connect(ui.DeleteInfoPB, &QPushButton::clicked, this, [=] {
		if (Admin->Permissions == 4)
		{
			InputID->show();
		}
		else
			QMessageBox::critical(this, u8"错误", u8"权限不足!");
		});
}

LoginWindow::~LoginWindow()
{
	if (Admin != nullptr)
		delete Admin;
	if (InfoWin != nullptr)
		delete InfoWin;
}
