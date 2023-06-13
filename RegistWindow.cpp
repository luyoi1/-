#include "RegistWindow.h"

RegistWindow::RegistWindow(QWidget *parent)
	: QWidget(parent),InsertDialog(nullptr),InsertAdminDialog(nullptr),pDB(QtMySQLClass::GetDataBase())
{
	ui.setupUi(this);
	connect(ui.RegistConfirmationPB, &QPushButton::clicked, this, [=] {
		if (ui.RadioAdminPB->isChecked())
		{
			AdminRegistReady();
		}
		else if (ui.RadioUserPB->isChecked())
		{
			UserRegistReady();
		}
		else
		{
			QMessageBox::warning(this, u8"����", u8"��ѡ������Ҫע��Ľ�ɫ!");
		}
		});
	
}

void RegistWindow::AdminRegistReady()//����Աע��׼������
{
	static std::shared_ptr<Admin> a{ new Admin };
	if (ui.lineEdit->text().size() == 0)
	{
		QMessageBox::warning(this, u8"����", u8"����д��ţ�");
		return;
	}
	if (ui.lineEdit_2->text().size() == 0)
	{
		QMessageBox::warning(this, u8"����", u8"���������룡");
		return;
	}
	if (ui.lineEdit_2->text() != ui.lineEdit_3->text())
	{
		QMessageBox::warning(this, u8"����", u8"������������Ƿ���ظ�����һ��!");
		return;
	}
	if (ui.lineEdit_5->text().size() == 0)
	{
		QMessageBox::warning(this, u8"����", u8"����д��Կ��");
		return;
	}
	a->StudentID = ui.lineEdit->text().toInt();
	a->Password = ui.lineEdit_2->text();
	a->Email = ui.lineEdit_4->text();
	a->Key = ui.lineEdit_5->text();
	AdminRegist(a);
}

void RegistWindow::UserRegistReady()//�û�ע��׼������
{
	static std::shared_ptr<User> a{ new User };
	if (ui.lineEdit->text().size() == 0)
	{
		QMessageBox::warning(this, u8"����", u8"����дѧ�ţ�");
		return;
	}
	if (ui.lineEdit_2->text().size() == 0)
	{
		QMessageBox::warning(this, u8"����", u8"���������룡");
		return;
	}
	if (ui.lineEdit_2->text() != ui.lineEdit_3->text())
	{
		QMessageBox::warning(this, u8"����", u8"������������Ƿ���ظ�����һ��!");
		return;
	}
	if (ui.lineEdit_5->text().size()!=0)
	{
		QMessageBox::warning(this, u8"����", u8"�벻Ҫ��д��Կ��");
		return;
	}
	a->StudentID = ui.lineEdit->text().toInt();
	a->Password = ui.lineEdit_2->text();
	a->Email = ui.lineEdit_4->text();
	UserRegist(a);
}

void RegistWindow::AdminRegist(std::shared_ptr<Admin> name)//����Աע�ắ��
{
	QString str = QString("select isUse from key_info where '%1' = RegisterKey ;").arg(name->Key);
	if (pDB->sqlExecute(str))
	{
		if (pDB->sqlQue->size() == 0)
		{
			QMessageBox::warning(this, u8"����", u8"��Կ����!");
			return;
		}
		else
		{
			pDB->sqlQue->next();
			if (pDB->sqlQue->value("isUse").toInt() == 1)
			{
				QMessageBox::information(this, u8"����", u8"����Կ�Ѿ���ʹ�ù���!");
				return;
			}
		}
	}
	else
	{
		QMessageBox::warning(this, u8"����", u8"��ѯʧ��!");
		return;
	}
	InsertAdminDialog = new RegistInsertAdminInfoDialog(this);
	InsertAdminDialog->setAttribute(Qt::WA_DeleteOnClose);
	InsertPBAdminConnect(name);
	InsertAdminDialog->exec();
	//���Ͼ��������Ϣ���̣������Ϣ������������ݿ�

	
}

void RegistWindow::UserRegist(std::shared_ptr<User> name)//�û�ע�ắ��
{
	InsertDialog = new RegistInsertInfoDialog(this);
	InsertDialog->setAttribute(Qt::WA_DeleteOnClose);
	InsertPBConnect(name);
	InsertDialog->exec();
	
}

void RegistWindow::InsertPBConnect(std::shared_ptr<User> name)
{
	connect(InsertDialog->ConfirmationPB, &QPushButton::clicked, this, [=] {
		StudentInfo stuInfo{};
		InsertDialog->ConnectAfter(stuInfo);
		QString str{};
		str = QString("insert into student(ID,Name,ProFession,Age,Email,ClassID) values(%1,'%2','%3',%4,'%5',%6);").arg(
			QString("%1").arg(name->StudentID), stuInfo.Name, stuInfo.Profession, QString("%1").arg(stuInfo.age), name->Email
			, QString("%1").arg(stuInfo.ClassID));
		if (pDB->sqlExecute(str))
		{
			str = QString("insert into user_info(Student_ID,Password) values(%1,'%2');").arg(QString("%1").arg(name->StudentID), name->Password);
			if(pDB->sqlExecute(str))
				QMessageBox::information(this, u8"��ʾ", u8"ע��ɹ�!", QMessageBox::Ok);
			else
				QMessageBox::warning(this, u8"����", pDB->sqlQue->lastError().text());
		}
		else
			QMessageBox::warning(this, u8"����", pDB->sqlQue->lastError().text());
		InsertDialog->close();
		this->close();
		});
	connect(InsertDialog->CancelPB, &QPushButton::clicked, this, [=] {
		InsertDialog->close();
		});
}

void RegistWindow::InsertPBAdminConnect(std::shared_ptr<Admin> name)
{
	connect(InsertAdminDialog->ConfirmationPB, &QPushButton::clicked, this, [=] {
		AdminInfo AdmInfo{};
		InsertAdminDialog->ConnectAfter(AdmInfo);
		QString str{};
		str = QString("insert into admin(ID,Name,Department,Email,Age) values(%1,'%2','%3','%4',%5);").arg(
			QString("%1").arg(name->StudentID), AdmInfo.Name, AdmInfo.Department, name->Email,QString("%1").arg(AdmInfo.age));
		if (pDB->sqlExecute(str))
		{
			str = QString("insert into admin_info(Admin_ID,Password,RegisterKey) values(%1,'%2','%3');").arg(QString("%1").arg(name->StudentID), name->Password,name->Key);
			if (pDB->sqlExecute(str))
				QMessageBox::information(this, u8"��ʾ", u8"ע��ɹ�!", QMessageBox::Ok);
			else
				QMessageBox::warning(this, u8"����", pDB->sqlQue->lastError().text());
		}
		else
			QMessageBox::warning(this, u8"����", pDB->sqlQue->lastError().text());
		InsertAdminDialog->close();
		this->close();
		});
	connect(InsertAdminDialog->CancelPB, &QPushButton::clicked, this, [=] {
		InsertAdminDialog->close();
		});
}

void RegistWindow::clearText()
{
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();
	ui.lineEdit_5->clear();
}

RegistWindow::~RegistWindow()
{}
