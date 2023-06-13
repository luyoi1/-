#include "RegistInsertAdminInfoDialog.h"

RegistInsertAdminInfoDialog::RegistInsertAdminInfoDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->ConfirmationPB = ui.ConfirmationPB;
	this->CancelPB = ui.CancelPB;
}

void RegistInsertAdminInfoDialog::ConnectAfter(AdminInfo& Admin)
{
	Admin.Name = ui.NameText->text();
	Admin.Department = ui.ProfessionText->text();
	Admin.age = ui.AgeText->text().toInt();
}

void RegistInsertAdminInfoDialog::ClearText()
{
	ui.NameText->clear();
	ui.ProfessionText->clear();
	ui.AgeText->clear();
}

RegistInsertAdminInfoDialog::~RegistInsertAdminInfoDialog()
{}
