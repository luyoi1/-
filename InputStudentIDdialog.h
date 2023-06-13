#pragma once

#include <QDialog>
#include<qpushbutton.h>
#include<qlineedit.h>
#include "ui_InputStudentIDdialog.h"
#include"InformationDisplayWindow.h"
#include"QtMySQLClass.h"
#include"AdminInsertWindow.h"

namespace luyoi
{
	enum option{
		SELECT,
		DELETE,
		UPDATE
		
	};
}


class InputStudentIDdialog : public QDialog
{
	Q_OBJECT

public:
	InputStudentIDdialog(luyoi::option Option_,QWidget *parent = nullptr);
	QString GetStudentID();
	void AfterConfirmationWork();
	void OneConnect();
	~InputStudentIDdialog();


private:
	Ui::InputStudentIDdialogClass ui;
	QString ID;
	QtMySQLClass* pDB;
	luyoi::option Option;
	InformationDisplayWindow* InfoWin;
	std::shared_ptr<AdminInsertWindow> AdmWin;
	
public:
	QPushButton* ConfirmationPB;
	QPushButton* CancelPB;
	QLineEdit* InputIDEdit;
};
