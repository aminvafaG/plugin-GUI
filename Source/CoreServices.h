/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2014 Open Ephys

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

#ifndef CORESERVICES_H_INCLUDED
#define CORESERVICES_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Processors/PluginManager/OpenEphysPlugin.h"

class GenericEditor;
class GenericProcessor;
class SpikeChannel;
class Spike;

namespace CoreServices
{
/** Issues a signal chain update; this should be called whenver a plugin's
* are changed in a way that would affect downstream plugins.
* 
* For example, if a plugin adds a new EventChannel, updateSignalChain() must
* be called in order for downstream plugins to register this change.
*/
PLUGIN_API void updateSignalChain(GenericEditor* source);

/** Returns true if the GUI is acquiring data */
PLUGIN_API bool getAcquisitionStatus();

/** Activates or deactivates data acquisition */
PLUGIN_API void setAcquisitionStatus(bool enable);

/** Returns true is the GUI is recording */
PLUGIN_API bool getRecordingStatus();

/** Activates or deactivates recording for all Record Nodes */
PLUGIN_API void setRecordingStatus(bool enable);

/** Sends a status message that appears in the GUI's MessageCenter.
* These messages are meant to notify the user about a status change,
* and they are not recorded.
* To send a message that's written to disk (while acquisition + recording are active),
* use GenericProcessor::broadcastMessage()
*/
PLUGIN_API void sendStatusMessage(const String& text);

/** Sends a status message that appears in the GUI's MessageCenter.
* These messages are meant to notify the user about a status change,
* and they are not recorded.
* To send a message that's written to disk (while acquisition + recording are active),
* use GenericProcessor::broadcastMessage()
*/
PLUGIN_API void sendStatusMessage(const char* text);

/** Highlights a plugin's editor in the EditorViewport, without updating the signal chain.
* It will also make the editor visible if it's not currently seen by the user.*/
PLUGIN_API void highlightEditor(GenericEditor* ed);

/** Returns the latest "global" timestamp, which can be used to assign
* timestamps to events not associated with a data stream, such as MessageCenter
* events. The user can select whether the global timestamp comes from
* particular Source processor, or from software.*/
PLUGIN_API juce::int64 getGlobalTimestamp();

/** Gets the sample rate of the global timestamp clock.*/
PLUGIN_API float getGlobalSampleRate();

/** Gets the name of the data stream (or software clock) that generates global timestamps. */
PLUGIN_API String getGlobalTimestampSource();

/** Gets the software timestamp (milliseconds since midnight Jan 1st 1970 UTC)*/
PLUGIN_API juce::int64 getSoftwareTimestamp();

/** Gets the ticker frequency of the software timestamp clock (1000 Hz)*/
PLUGIN_API float getSoftwareSampleRate();

/** Sets new default recording directory. This will only affect new Record Nodes */
PLUGIN_API void setDefaultRecordingDirectory(String dir);

/** Returns the default recording directory.*/
PLUGIN_API File getDefaultRecordingDirectory();

/** Creates new directory the next time recording is started.
* This will apply to all Record Nodes*/
PLUGIN_API void createNewRecordingDirectory();

/** Set the text to be prepended to the name of newly created recording directories. */
PLUGIN_API void setRecordDirectoryPrependText(String text);

/** Set the text to be appended to the name of newly reated recording directories. */
PLUGIN_API void setRecordingDirectoryAppendText(String text);

/** Get array of available record engines */
PLUGIN_API std::vector<RecordEngineManager*> getAvailableRecordEngines();

/** Gets the ID of the default Record Engine*/
PLUGIN_API String getDefaultRecordEngineId();

/** Returns the index of the default record engine in the RecordEngineManager vector.*/
PLUGIN_API int getDefaultRecordEngineIdx();

/** Sets a specific RecordEngine to be used based on its id. 
* Returns true if there is an engine with the specified ID and it's possible to
* change the current engine or false otherwise. */
PLUGIN_API bool setDefaultRecordEngine(String id);

namespace RecordNode
{
/** Sets the recording directory for a specific Record Node, based on its numeric ID.
* If applyToAll=true, the nodeId is ignored, and the setting is applied to all Record Nodes
* in the signal chain. */
PLUGIN_API void setRecordingDirectory(String dir, int nodeId, bool applyToAll=false);

/** Returns the recording directory for a specific Record Node */
PLUGIN_API File getRecordingDirectory(int nodeId);

/** Returns the free space available (in kB) for a Record Node's directory */
PLUGIN_API float getFreeSpaceAvailable(int nodeId);

/** Instructs a specific Record Node to creates new directory the next time recording is started.*/
PLUGIN_API void createNewRecordingDirectory(int nodeId);

/** Sets the RecordEngine for a specific Record Nodes.
* If applyToAll=true, the nodeId is ignored, and the setting is applied to all Record Nodes
* in the signal chain. */
PLUGIN_API void setRecordEngine(String id, int nodeId, bool applyToAll = false);

/** Returns the recording number for a specific Record Node (number of times recording 
* was stopped and re-started).*/
PLUGIN_API int getRecordingNumber(int nodeId);

/** Returns the experiment number for a specific Record Node (number of times acquisition
* was stopped and re-started).*/
PLUGIN_API int getExperimentNumber(int nodeId);

/** Toggles recording for a specific Record Node.*/
PLUGIN_API void setRecordingStatus(int nodeId, bool status);

/** Gets the recording status for a specific Record Node.*/
PLUGIN_API bool getRecordingStatus(int nodeId);

};

/** Returns data for an application resource (stored in BinaryData object) */
//PLUGIN_API const char* getApplicationResource(const char* name, int& size);
    
/** Gets the default directory for user-initiated file saving/loading */
PLUGIN_API File getDefaultUserSaveDirectory();

/** Gets the save directory for GUI-related file saving/loading */
PLUGIN_API File getSavedStateDirectory();

/** Gets the GUI version */
PLUGIN_API String getGUIVersion();

};




#endif  // CORESERVICES_H_INCLUDED
