#include "AdminInsertWindow.h"

AdminInsertWindow::AdminInsertWindow(luyoi1::option Option_,QWidget *parent)
	: QWidget(parent),Option(Option_),pDB(QtMySQLClass::GetDataBase())
{
	ui.setupUi(this);
	this->ConfirmationPB = ui.ConfirmationPB;
	this->CancelPB = ui.CancelPB;
	this->IDText = ui.IDText;
	connect(this->ConfirmationPB, &QPushButton::clicked, [=] {
		AfterConfirmationWork();
		this->close();
		});
	connect(this->CancelPB, &QPushButton::clicked, [=] {
		this->close();
		//this->ClearText();
		});
}

void AdminInsertWindow::AfterConfirmationWork()
{
	std::vector<QString> v1{};
	//QLineEdit::text;
	
	v1.push_back(ui.IDText->text());
	v1.push_back(ui.NameText->text());
	v1.push_back(ui.ProfessionText->text());
	v1.push_back(ui.AgeText->text());
	v1.push_back(ui.EmailText->text());
	v1.push_back(ui.PermissionText->text());
	v1.push_back(ui.ClassIDText->text());
	v1.push_back(ui.PasswordText->text());
	switch (Option)
	{
	case luyoi1::INSERT:
	{
		if (ui.IDText->text().size() == 0)
		{
			QMessageBox::warning(this, u8"警告", u8"ID不能为空");
			return;
		}
		if (ui.PasswordText->text().size() == 0)
		{
			QMessageBox::warning(this, u8"警告", u8"密码不能为空");
			return;
		}
		if (ui.NameText->text().size() == 0)
		{
			QMessageBox::warning(this, u8"警告", u8"姓名不能为空");
			return;
		}
		QString str{};
		str = "insert into student(ID,Name,ProFession,Age,Email,StuPermissions,ClassID) values";
		str += QString("(%1,'%2','%3',%4,'%5',%6,%7);").arg(v1[0],v1[1],v1[2],v1[3],v1[4],v1[5],v1[6]);
		if (pDB->sqlExecute(str))
		{
			str = "insert into user_info(student_id,password,stupermissions)values";
			str += QString("(%1,'%2',%3);").arg(v1[0],v1[7],v1[5]);
			if (pDB->sqlExecute(str))
			{
				QMessageBox::information(this, u8"提醒", u8"插入成功!");
				this->ClearText();
			}
			else
				QMessageBox::warning(this, u8"警告", u8"插入信息失败!");
		}
		else
			QMessageBox::warning(this, u8"警告", u8"插入信息失败!");
		break;
	}
	case luyoi1::UPDATE:
	{
		QString str = "update student set ";
		if (ui.NameText->text().size() != 0)
		{
			str += QString("Name = '%1',").arg(ui.NameText->text());
		}
		if (ui.ProfessionText->text().size() != 0)
		{
			str += QString("ProFession = '%1',").arg(ui.ProfessionText->text());
		}
		if (ui.AgeText->text().size() != 0)
		{
			str += QString("Age = %1,").arg(ui.AgeText->text());
		}
		if (ui.EmailText->text().size() != 0)
		{
			str += QString("Email = '%1',").arg(ui.EmailText->text());
		}
		if (ui.PermissionText->text().size() != 0)
		{
			str += QString("StuPermissions = %1,").arg(ui.PermissionText->text());
		}
		if (ui.ClassIDText->text().size() != 0)
		{
			str += QString("ClassID = %1 ").arg(ui.ClassIDText->text());
		}
		else
		{
			QMessageBox::warning(this, u8"警告", u8"ClassID不能为空");
			return;
		}
		str += QString("where ID = %1;").arg(ui.IDText->text());
		if (pDB->sqlExecute(str))
		{
			QMessageBox::information(this, u8"提醒", u8"更新成功!");
		}
		else
			QMessageBox::warning(this, u8"警告", str +pDB->sqlQue->lastError().text());
		this->ClearText();
		break;
	}
	default:
	{
		QMessageBox::critical(this, u8"错误", u8"选项错误！(调试用)");
		break;
	}
	}
}

void AdminInsertWindow::ClearText()
{
	ui.IDText->clear();
	ui.NameText->clear();
	ui.ProfessionText->clear();
	ui.AgeText->clear();
	ui.EmailText->clear();
	ui.PermissionText->clear();
	ui.ClassIDText->clear();
	ui.PasswordText->clear();
}

AdminInsertWindow::~AdminInsertWindow()
{}
