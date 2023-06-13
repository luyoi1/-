#include "LoginWindowUser.h"

LoginWindowUser::LoginWindowUser(StudentInfo* User_,QWidget* parent)
	: QWidget(parent), QbackPB(nullptr), User(User_),InfoWin(new InformationDisplayWindow(this))
	,InputDia(new InputStudentIDdialog(luyoi::SELECT,this)),pDB(QtMySQLClass::GetDataBase())
{
	ui.setupUi(this);
	QbackPB = ui.BackPB;
	InfoWin->setAttribute(Qt::WA_ShowModal, true);
	InputDia->setAttribute(Qt::WA_ShowModal, true);
	SetIntroductionText();
	StudentInfoConnectText();
	GradeInfoConnectText();
	CourseInfoConnectText();
	SelectOtherStudentInfoConnectText();
}

void LoginWindowUser::SetIntroductionText()
{
	QString str{};
	str += u8"���:\r\n";
	str += u8"����:" + User->Name + "\r\n";
	str += u8"ѧ��:" + QString(std::to_string(User->ID).c_str()) + "\r\n";
	str += u8"Ȩ�޵ȼ�:" + QString(std::to_string(User->Permissions).c_str()) + "\r\n";
	ui.IntroductionText->setText(str);
}

void LoginWindowUser::StudentInfoConnectText()
{
	QString str{};
	str = u8"������Ϣ:\r\n";
	str += u8"ID: " + QString("%1").arg(User->ID) + QString("\r\n");
	str += u8"����: " + QString(User->Name)+ QString("\r\n");
	str += u8"רҵ: " + QString(User->Profession) + QString("\r\n");
	str += u8"����: " + QString("%1").arg(User->age) + QString("\r\n");
	str += u8"E-mail: " + QString(User->Email) + QString("\r\n");
	str += u8"����: " + QString(std::to_string(User->GradePoint).c_str()) + QString("\r\n");
	str += u8"Ȩ�޵ȼ�: " + QString("%1").arg(User->Permissions) + QString("\r\n");
	str += u8"�༶ID: " + QString("%1").arg(User->ClassID) + QString("\r\n");
	connect(ui.StudentInfoPB, &QPushButton::clicked, this, [=] {
		InfoWin->Textl->setText(str);
		InfoWin->show();
		});
	
}
void LoginWindowUser::GradeInfoConnectText()
{
	QString str{};
	str = QString("select Score,Course_ID from Student_Grade where Student_ID = %1;").arg(User->ID);
	
	connect(ui.GradeInfoPB, &QPushButton::clicked, this, [=] {
		QString str1{};
		if (pDB->sqlQue->exec(str))
		{
			if(pDB->sqlQue->size()==0)
				QMessageBox::warning(this, u8"����", u8"��ѯ������Ϣ!");
			else
			{
				str1 = u8"�ɼ�����:\r\n";
				pDB->sqlQue->next();
				for (unsigned i = 0;i < pDB->sqlQue->size();pDB->sqlQue->next(),i++)
				{
					str1 += QString(u8"�γ�ID: %1 \r����: %2 \r\n").arg(pDB->sqlQue->value("Course_ID").toString(), pDB->sqlQue->value("Score").toString());
					str1 += "\r\n\r\n"; 
				}
				
			}
		}
		else
			QMessageBox::warning(this, u8"����", u8"��ѯʧ��!");
		InfoWin->Textl->setText(str1);
		InfoWin->show();
		});
}
void LoginWindowUser::CourseInfoConnectText()
{
	QString str{};
	str = QString("select student_course.Course_ID,course.Name from student_course,course where student_course.Student_ID = %1 AND student_course.Course_ID = course.ID;").arg(User->ID);
	connect(ui.CourseInfoPB, &QPushButton::clicked, this, [=] {
		QString str1{};
		if (pDB->sqlQue->exec(str))
		{
			if (pDB->sqlQue->size() == 0)
				QMessageBox::warning(this, u8"����", u8"��ѯ������Ϣ!");
			else
			{
				str1 = u8"�γ���Ϣ����:\r\n";
				pDB->sqlQue->next();
				for (unsigned i = 0;i < pDB->sqlQue->size();pDB->sqlQue->next(), i++)
				{
					str1 += QString(u8"�γ�ID: %1\r�γ�����:%2").arg(pDB->sqlQue->value("student_course.Course_ID").toString(),pDB->sqlQue->value("course.Name").toString());
					str1 += "\r\n\r\n";
				}

			}
		}
		else
			QMessageBox::warning(this, u8"����", u8"��ѯʧ��!");
		InfoWin->Textl->setText(str1);
		InfoWin->show();
		});
}
void LoginWindowUser::SelectOtherStudentInfoConnectText()
{
	
	connect(ui.SelectStudentInfoPB, &QPushButton::clicked, this, [=] {
		if (User->Permissions >= 2)
		{
			InputDia->show();
		}
		else
			QMessageBox::critical(this, u8"����", u8"Ȩ�޲���!");
		});
}

LoginWindowUser::~LoginWindowUser()
{
	if (User != nullptr)
		delete User;
	if (InfoWin != nullptr)
		delete InfoWin;
	if (InputDia != nullptr)
		delete InputDia;
}
