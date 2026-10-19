// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Ryan Roden-Corrent <ryan/at/rcorre.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_RENDER_MANAGER_H
#define NoeMixerr_RENDER_MANAGER_H

#include <memory>

#include "ProjectRenderer.h"
#include "OutputSettings.h"


namespace noemixerr
{


class RenderManager : public QObject
{
	Q_OBJECT
public:
	RenderManager(const OutputSettings& outputSettings, ProjectRenderer::ExportFileFormat fmt, QString outputPath);

	~RenderManager() override;

	/// Export all unmuted tracks into a single file
	void renderProject();

	/// Export all unmuted tracks into individual file
	void renderTracks();

	void abortProcessing();

signals:
	void progressChanged( int );
	void finished();

private slots:
	void renderNextTrack();
	void updateConsoleProgress();

private:
	QString pathForTrack( const Track *track, int num );
	void restoreMutedState();

	void render( QString outputPath );

	const OutputSettings m_outputSettings;
	ProjectRenderer::ExportFileFormat m_format;
	QString m_outputPath;

	std::unique_ptr<ProjectRenderer> m_activeRenderer;

	std::vector<Track*> m_tracksToRender;
	std::vector<Track*> m_unmuted;
} ;


} // namespace noemixerr

#endif // NoeMixerr_RENDER_MANAGER_H
