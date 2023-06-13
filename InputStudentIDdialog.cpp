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
				QMessageBox::warning(this, u8"����", u8"�����ѧ����Ч��");
			else
			{
				pDB->sqlQue->next();
				str = u8"������Ϣ:\r\n";
				str += u8"ID: " + pDB->sqlQue->value("ID").toString() + QString("\r\n");
				str += u8"����: " + pDB->sqlQue->value("Name").toString() + QString("\r\n");
				str += u8"רҵ: " + pDB->sqlQue->value("ProFession").toString() + QString("\r\n");
				str += u8"����: " + pDB->sqlQue->value("Age").toString() + QString("\r\n");
				str += u8"E-mail: " + pDB->sqlQue->value("Email").toString() + QString("\r\n");
				str += u8"����: " + pDB->sqlQue->value("Grade_Point").toString() + QString("\r\n");
				str += u8"Ȩ�޵ȼ�: " + pDB->sqlQue->value("StuPermissions").toString() + QString("\r\n");
				str += u8"�༶ID: " + pDB->sqlQue->value("ClassID").toString() + QString("\r\n");
				InfoWin->Textl->setText(str);
				InfoWin->show();
			}
		}
		else
			QMessageBox::warning(this, u8"����", u8"��ѯʧ��!");
		break;
	}
	case luyoi::DELETE:
	{
		QString str = QString("delete from user_info where student_id = %1 ;").arg(QString("%1").arg(ID));
		if (pDB->sqlExecute(str))
		{
			QMessageBox::information(this, u8"����", u8"ɾ���ɹ�!");
		}
		else
			QMessageBox::warning(this, u8"����", u8"ɾ��ʧ�ܣ�����ѧ���Ƿ���ȷ");

		break;
	}
	case luyoi::UPDATE:
	{
		QString str = QString("select ID from student where ID = %1;").arg(ID);
		if (pDB->sqlExecute(str))
		{
			if (pDB->sqlQue->size() == 0)
			{
				QMessageBox::warning(this, u8"����", u8"����ʧ�ܣ�����ѧ���Ƿ���ȷ");
			}
			else
			{
				AdmWin->IDText->setText(ID);
				AdmWin->IDText->setFocusPolicy(Qt::NoFocus);
				AdmWin->show();
			}
		}
		else
			QMessageBox::warning(this, u8"����", u8"����ѧ��ʧ��!");
		break;
	}
	default:
	{
		QMessageBox::critical(this, u8"����", u8"�����ã�");
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
