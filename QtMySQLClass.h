#pragma once

#include<qsql.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qmessagebox.h>
#include<QString>
#include<qdebug.h>
#include<qwidget.h>


//单例模式实现数据库类
class QtMySQLClass:public QWidget
{
public:
	static QtMySQLClass* GetDataBase(const char*, const char*, const char*, const char*, unsigned);
	static QtMySQLClass* GetDataBase();
	bool sqlExecute(QString);
private:
	QtMySQLClass(const char*,const char*,const char*,const char*,unsigned);
	~QtMySQLClass();
	
	
	static QtMySQLClass* QsqlClassPtr;
	static bool IsFirst;
public:
	static QSqlDatabase* qDB;
	static QSqlQuery* sqlQue;
};

