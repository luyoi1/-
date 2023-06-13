#pragma once

#include <QDialog>
#include "ui_RegistInsertAdminInfoDialog.h"
#include"LoginWindow.h"


class RegistInsertAdminInfoDialog : public QDialog
{
	Q_OBJECT

public:
	RegistInsertAdminInfoDialog(QWidget *parent = nullptr);
	void ClearText();
	void ConnectAfter(AdminInfo&);
	~RegistInsertAdminInfoDialog();

private:
	Ui::RegistInsertAdminInfoDialogClass ui;
public:
	QPushButton* ConfirmationPB;
	QPushButton* CancelPB;
};
