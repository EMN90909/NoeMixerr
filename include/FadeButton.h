// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_FADE_BUTTON_H
#define NoeMixerr_GUI_FADE_BUTTON_H

#include <QAbstractButton>
#include <QColor>
#include <QElapsedTimer>


namespace noemixerr::gui
{


class FadeButton : public QAbstractButton
{
	Q_OBJECT
public:
	enum class State
	{
		Normal,
		Corrupted,
	};

	/**
	 * @brief Creates a fade button with the given color palette.
	 * 
	 * @param inactiveColor The default color for the widget
	 * @param normalColor The color to use on activation when in the Normal state
	 * @param corruptedColor The color to use on activation when in the Corrupted state
	 * @param mutedColor The color to use when the fade button is muted
	 * @param holdColor The color after the "play" fade is done but a note is still playing
	 */
	FadeButton(
		const QColor& inactiveColor,
		const QColor& normalColor,
		const QColor& corruptedColor,
		const QColor& mutedColor,
		const QColor& holdColor,
		QWidget* parent = nullptr);

	//! @brief Creates a fade button with the default application colors.
	FadeButton(QWidget* parent = nullptr);

	//! @brief Destroys the fade button.
	~FadeButton() override = default;

	//! @returns the current state of the fade button.
	auto state() const -> State;

	//! @returns true if the fade button is muted.
	auto muted() const -> bool;

	//! Set the state of the fade button to @a state.
	void setState(State state);

	//! Mute or unmute the fade button.
	void setMuted(bool mute);

public slots:
	void activate();
	void activateOnce();
	void noteEnd();

private:
	void paintEvent(QPaintEvent* pe) override;

	State m_state = State::Normal;

	QElapsedTimer m_stateTimer;
	QElapsedTimer m_releaseTimer;

	QColor m_inactiveColor;
	QColor m_normalColor;
	QColor m_corruptedColor;
	QColor m_mutedColor;
	QColor m_holdColor;

	int activeNotes;
	bool m_muted = false;

	QColor fadeToColor(QColor, QColor, QElapsedTimer, float);
	QColor activeColor() const;
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_FADE_BUTTON_H
