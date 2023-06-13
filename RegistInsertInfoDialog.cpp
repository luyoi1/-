#include "RegistInsertInfoDialog.h"

RegistInsertInfoDialog::RegistInsertInfoDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->ConfirmationPB = ui.ConfirmationPB;
	this->CancelPB = ui.CancelPB;
}

void RegistInsertInfoDialog::ConnectAfter(StudentInfo& User)
{
	User.Name = ui.NameText->text();
	User.Profession = ui.ProfessionText->text();
	User.age = ui.AgeText->text().toInt();
	User.ClassID = ui.ClassIDText->text().toInt();
}

void RegistInsertInfoDialog::ClearText()
{
	ui.NameText->clear();
	ui.ProfessionText->clear();
	ui.AgeText->clear();
	ui.ClassIDText->clear();
}

RegistInsertInfoDialog::~RegistInsertInfoDialog()
{}
