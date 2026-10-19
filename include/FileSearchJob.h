// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 saker <sakertooth@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_FILE_SEARCH_JOB_H
#define NoeMixerr_GUI_FILE_SEARCH_JOB_H

#include <QDir>
#include <QObject>
#include <QString>
#include <future>

namespace noemixerr::gui {
//! The `FileSearchJob` class allows for searching for files on the filesystem.
//! Searching occurs on a background thread, and results are emitted as a Qt slot back to the user.
class FileSearchJob : public QObject
{
	Q_OBJECT
public:
	//! Represents a search task to be carried out by the search job.
	struct Task
	{
		QString filter;					 //! The filter to be tokenized.
		QStringList paths;				 //! The list of paths to search recursively through.
		QStringList extensions;			 //! The list of allowed extensions.
		QFlags<QDir::Filter> dirFilters; //! The directory filter flag.
	};

	//! Create a search job with the given @p parent (if any).
	FileSearchJob(QObject* parent = nullptr);

	//! Stop processing and destroys the object.
	~FileSearchJob();

	FileSearchJob(const FileSearchJob&) = delete;
	FileSearchJob(FileSearchJob&&) = delete;
	FileSearchJob& operator=(const FileSearchJob&) = delete;
	FileSearchJob& operator=(FileSearchJob&&) = delete;

	//! Commit to searching with the given @p task.
	//! Cancels any previous search.
	//! Callers can connect to the provided signals to interact with the search and its progress.
	void search(Task task);

signals:
	//! Emitted when the search job has found a matching path.
	void foundMatch(const QString& path);

	//! Emitted when the search job has started searching.
	void started();

	//! Emitted when the search job has finished searching.
	void finished();

private:
	void runSearch(Task task);
	std::future<void> m_task;
	std::atomic_flag m_stop = ATOMIC_FLAG_INIT;
};
} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_FILE_SEARCH_JOB_H
