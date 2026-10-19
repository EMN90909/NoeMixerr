// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MODEL_H
#define NoeMixerr_MODEL_H

#include <QString>
#include <QObject>

#include "noemixerr_export.h"

namespace noemixerr
{

class NOEMIXERR_EXPORT Model : public QObject
{
	Q_OBJECT
public:
	Model(Model* parent, QString displayName = QString(),
		  bool defaultConstructed = false);

	~Model() override = default;

	bool isDefaultConstructed() const;

	Model* parentModel() const;

	virtual QString displayName() const;

	virtual void setDisplayName(const QString& displayName);

	virtual QString fullDisplayName() const;


private:
	QString m_displayName;
	bool m_defaultConstructed;


signals:
	// emitted if actual data of the model (e.g. values) have changed
	void dataChanged();

	// emitted in case new data was not set as it's been equal to old data
	void dataUnchanged();

	// emitted if properties of the model (e.g. ranges) have changed
	void propertiesChanged();

} ;


} // namespace noemixerr

#endif // NoeMixerr_MODEL_H
