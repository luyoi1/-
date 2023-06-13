#include "InformationDisplayWindow.h"

InformationDisplayWindow::InformationDisplayWindow(QWidget *parent)
	: QDialog(parent),Textl(nullptr)
{
	ui.setupUi(this);
	this->Textl = ui.QueryResultText;
}

InformationDisplayWindow::~InformationDisplayWindow()
{}
