/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef __AUDIOMONITOREDITOR_H__
#define __AUDIOMONITOREDITOR_H__

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../Editors/GenericEditor.h"
#include "../Editors/PopupChannelSelector.h"
#include "../Parameter/ParameterEditor.h"
#include "../../Source/UI/Utils/LinearButtonGroupManager.h"
#include "../../Source/UI/LookAndFeel/MaterialButtonLookAndFeel.h"
#include "AudioMonitor.h"

class AudioMonitor;

/**
  Toggles audio output on and off.

  @see AudioMonitor, AudioMonitorEditor

*/
class MonitorMuteButton : public ParameterEditor,
    public Button::Listener
{
public:
    MonitorMuteButton(Parameter* param);
    ~MonitorMuteButton() { }

    void buttonClicked(Button* label);

    virtual void updateView() override;

    virtual void resized();

private:
    ScopedPointer<ImageButton> muteButton;
};


/**
  Toggles Left / Right / Both audio output

  @see AudioMonitor, AudioMonitorEditor

*/
class AudioOutputSelector : public ParameterEditor,
    public Button::Listener
{
public:
    AudioOutputSelector(Parameter* param);
    ~AudioOutputSelector() { }

    void buttonClicked(Button* label);

    virtual void updateView() override;

    virtual void resized();

private:
    std::unique_ptr<LinearButtonGroupManager> outputChannelButtonManager;
    TextButton* leftButton;
    TextButton* rightButton;
    TextButton* bothButton;

    std::shared_ptr<MaterialButtonLookAndFeel> m_materialButtonLookAndFeel;

};

/**

  User interface for the "AudioMonitor" node.

*/

class AudioMonitorEditor : public GenericEditor
{
public:
    /** Constructor */
    AudioMonitorEditor (GenericProcessor* parentNode);
    
    /** Destructor */
    virtual ~AudioMonitorEditor() { }

private:

    AudioMonitor* audioMonitor;
    
    std::unique_ptr<juce::ComboBox> spikeChan; // to replace with ParameterEditor

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioMonitorEditor);
};



#endif  // __AUDIOMONITOREDITOR_H__
