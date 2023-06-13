#include "InputStudentIDdialog.h"

InputStudentIDdialog::InputStudentIDdialog(luyoi::option Option_,QWidget *parent)
	: QDialog(parent),InputIDEdit(nullptr),pDB(QtMySQLClass::GetDataBase()),Option(Option_),InfoWin(new InformationDisplayWindow(this)),
	AdmWin (new AdminInsertWindow(luyoi1::UPDATE))
{
	ui.setupUi(this);
	this->ConfirmationPB = ui.ConfirmationPB;
	this->CancelPB = ui.CancelPB;
	this->InputIDEdit = ui.IDTextEdit;
	OneConnect();
}

void InputStudentIDdialog::OneConnect()
{
	connect(this->CancelPB, &QPushButton::clicked, this, [=] {
			this->hide();
			ui.IDTextEdit->clear();
			});
	connect(this->ConfirmationPB, &QPushButton::clicked, this, [=] {
		ID = ui.IDTextEdit->text();
		this->hide();
		AfterConfirmationWork();
		ui.IDTextEdit->clear();
		});
}

void InputStudentIDdialog::AfterConfirmationWork()
{
	switch (Option)
	{
	case luyoi::SELECT:
	{
		QString str = QString("select * from student where ID = %1;").arg(ID);
		if (pDB->sqlExecute(str))
		{
			if (pDB->sqlQue->size() == 0)
				QMessageBox::warning(this, u8"警告", u8"输入的学号无效！");
			else
			{
				pDB->sqlQue->next();
				str = u8"个人信息:\r\n";
				str += u8"ID: " + pDB->sqlQue->value("ID").toString() + QString("\r\n");
				str += u8"姓名: " + pDB->sqlQue->value("Name").toString() + QString("\r\n");
				str += u8"专业: " + pDB->sqlQue->value("ProFession").toString() + QString("\r\n");
				str += u8"年龄: " + pDB->sqlQue->value("Age").toString() + QString("\r\n");
				str += u8"E-mail: " + pDB->sqlQue->value("Email").toString() + QString("\r\n");
				str += u8"绩点: " + pDB->sqlQue->value("Grade_Point").toString() + QString("\r\n");
				str += u8"权限等级: " + pDB->sqlQue->value("StuPermissions").toString() + QString("\r\n");
				str += u8"班级ID: " + pDB->sqlQue->value("ClassID").toString() + QString("\r\n");
				InfoWin->Textl->setText(str);
				InfoWin->show();
			}
		}
		else
			QMessageBox::warning(this, u8"警告", u8"查询失败!");
		break;
	}
	case luyoi::DELETE:
	{
		QString str = QString("delete from user_info where student_id = %1 ;").arg(QString("%1").arg(ID));
		if (pDB->sqlExecute(str))
		{
			QMessageBox::information(this, u8"提醒", u8"删除成功!");
		}
		else
			QMessageBox::warning(this, u8"警告", u8"删除失败！请检查学号是否正确");

		break;
	}
	case luyoi::UPDATE:
	{
		QString str = QString("select ID from student where ID = %1;").arg(ID);
		if (pDB->sqlExecute(str))
		{
			if (pDB->sqlQue->size() == 0)
			{
				QMessageBox::warning(this, u8"警告", u8"查找失败！请检查学号是否正确");
			}
			else
			{
				AdmWin->IDText->setText(ID);
				AdmWin->IDText->setFocusPolicy(Qt::NoFocus);
				AdmWin->show();
			}
		}
		else
			QMessageBox::warning(this, u8"警告", u8"查找学号失败!");
		break;
	}
	default:
	{
		QMessageBox::critical(this, u8"错误", u8"调试用！");
		break;
	}
	}
}

QString InputStudentIDdialog::GetStudentID()
{
	return ID;
}

InputStudentIDdialog::~InputStudentIDdialog()
{
}
