#pragma once

#include <QDialog>
#include<qtextbrowser.h>
#include "ui_InformationDisplayWindow.h"

class InformationDisplayWindow : public QDialog
{
	Q_OBJECT

public:
	InformationDisplayWindow(QWidget *parent = nullptr);
	~InformationDisplayWindow();

private:
	Ui::InformationDisplayWindowClass ui;
public:
	QTextBrowser* Textl;
};
