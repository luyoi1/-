#pragma once

#include <QDialog>
#include<qmessagebox.h>
#include "ui_RegistInsertInfoDialog.h"
#include"LoginWindowUser.h"


class RegistInsertInfoDialog : public QDialog
{
	Q_OBJECT

public:
	RegistInsertInfoDialog(QWidget *parent = nullptr);
	void ClearText();
	void ConnectAfter(StudentInfo&);
	~RegistInsertInfoDialog();


private:
	Ui::RegistInsertInfoDialogClass ui;
public:
	QPushButton* ConfirmationPB;
	QPushButton* CancelPB;
};
