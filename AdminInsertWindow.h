#pragma once

#include <QWidget>
#include<qpushbutton.h>
#include<qmessagebox.h>
#include<vector>
#include<qlineedit.h>
#include "ui_AdminInsertWindow.h"
#include"QtMySQLClass.h"
namespace luyoi1
{
	enum option {
		INSERT,
		UPDATE
	};
}

class AdminInsertWindow : public QWidget
{
	Q_OBJECT

public:
	AdminInsertWindow(luyoi1::option,QWidget *parent = nullptr);
	void AfterConfirmationWork();
	void ClearText();
	~AdminInsertWindow();

private:
	Ui::AdminInsertWindowClass ui;
	luyoi1::option Option;
	QtMySQLClass* pDB;
public:
	QPushButton* ConfirmationPB;
	QPushButton* CancelPB;
	QLineEdit* IDText;
};
