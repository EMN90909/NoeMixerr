// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Controls.h"

#include <QLabel>
#include <QString>
#include <QVBoxLayout>

#include "ComboBox.h"
#include "LcdSpinBox.h"
#include "LedCheckBox.h"
#include "Knob.h"


namespace noemixerr::gui
{


void KnobControl::setText(const QString& text)
{
	m_knob->setLabel(text);
}

QWidget *KnobControl::topWidget() { return m_knob; }

void KnobControl::setModel(AutomatableModel *model)
{
	m_knob->setModel(model->dynamicCast<FloatModel>(true));
}

FloatModel *KnobControl::model() { return m_knob->model(); }

AutomatableModelView* KnobControl::modelView() { return m_knob; }

KnobControl::KnobControl(const QString& text, QWidget *parent) :
	m_knob(new Knob(KnobType::Bright26, text, parent)) {}


void ComboControl::setText(const QString &text) { m_label->setText(text); }

void ComboControl::setModel(AutomatableModel *model)
{
	m_combo->setModel(model->dynamicCast<ComboBoxModel>(true));
}

ComboBoxModel *ComboControl::model() { return m_combo->model(); }

AutomatableModelView* ComboControl::modelView() { return m_combo; }

ComboControl::ComboControl(QWidget *parent) :
	m_widget(new QWidget(parent)),
	m_combo(new ComboBox(nullptr)),
	m_label(new QLabel(m_widget))
{
	m_combo->setFixedSize(64, ComboBox::DEFAULT_HEIGHT);
	auto vbox = new QVBoxLayout(m_widget);
	vbox->addWidget(m_combo);
	vbox->addWidget(m_label);
	m_combo->repaint();
}



void CheckControl::setText(const QString &text) { m_label->setText(text); }

QWidget *CheckControl::topWidget() { return m_widget; }

void CheckControl::setModel(AutomatableModel *model)
{
	m_checkBox->setModel(model->dynamicCast<BoolModel>(true));
}

BoolModel *CheckControl::model() { return m_checkBox->model(); }

AutomatableModelView* CheckControl::modelView() { return m_checkBox; }

CheckControl::CheckControl(QWidget *parent) :
	m_widget(new QWidget(parent)),
	m_checkBox(new LedCheckBox(nullptr, QString(), LedCheckBox::LedColor::Green)),
	m_label(new QLabel(m_widget))
{
	auto vbox = new QVBoxLayout(m_widget);
	vbox->addWidget(m_checkBox);
	vbox->addWidget(m_label);
}




void LcdControl::setText(const QString &text) { m_lcd->setLabel(text); }

QWidget *LcdControl::topWidget() { return m_lcd; }

void LcdControl::setModel(AutomatableModel *model)
{
	m_lcd->setModel(model->dynamicCast<IntModel>(true));
}

IntModel *LcdControl::model() { return m_lcd->model(); }

AutomatableModelView* LcdControl::modelView() { return m_lcd; }

LcdControl::LcdControl(int numDigits, QWidget *parent) :
	m_lcd(new LcdSpinBox(numDigits, parent))
{
}


} // namespace noemixerr::gui
