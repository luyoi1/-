#include "QtMySQLClass.h"
#include<qdebug.h>
QtMySQLClass::QtMySQLClass(const char* Host, const char* dbName, const char* User, const char* Password, unsigned Port)
{
	qDB = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
	qDB->setHostName(Host);
	qDB->setDatabaseName(dbName);
	qDB->setUserName(User);
	qDB->setPassword(Password);
	qDB->setPort(Port);
	if (qDB->open())
	{
		QMessageBox::information(this, u8"提醒", u8"数据库连接成功！");
		sqlQue = new QSqlQuery(*qDB);
	}
	else
		QMessageBox::warning(this,u8"警告",QString(u8"数据库连接失败！")+qDB->lastError().text());
}

bool QtMySQLClass::IsFirst = true;
QtMySQLClass* QtMySQLClass::QsqlClassPtr = nullptr;
QSqlDatabase* QtMySQLClass::qDB=nullptr;
QSqlQuery* QtMySQLClass::sqlQue=nullptr;

QtMySQLClass* QtMySQLClass::GetDataBase(const char* Host, const char* dbName, const char* User, const char* Password, unsigned Port)
{
	if(QsqlClassPtr==nullptr)
		QsqlClassPtr = new QtMySQLClass(Host, dbName, User, Password, Port);
	IsFirst = false;
	return QsqlClassPtr;
}

QtMySQLClass* QtMySQLClass::GetDataBase()
{
	if (!IsFirst)
		return QsqlClassPtr;
	else
		return nullptr;
}

bool QtMySQLClass::sqlExecute(QString state)//执行语句函数，后会更改，仅为暂时实现
{
	if (sqlQue == nullptr)
	{
		QMessageBox::information(this,u8"提醒",u8"sqlQue is nullptr!");
		return false;
	}
	else
	{
		if (sqlQue->exec(state))
			return true;
		else
			return false;
	}
}


QtMySQLClass::~QtMySQLClass()
{
	if (QsqlClassPtr != nullptr)
		delete QsqlClassPtr;
	if (qDB != nullptr)
		delete qDB;
}