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


#include <stdio.h>

#include "PulsePalOutput.h"


PulsePalOutput::PulsePalOutput()
    : GenericProcessor("Pulse Pal")
{

    pulsePal.initialize();

    pulsePal.updateDisplay("GUI Connected","Click for menu");

    for (int i = 0; i < 4; i++)
    {
        channelTtlTrigger.add(-1);
    }

}

PulsePalOutput::~PulsePalOutput()
{

    pulsePal.updateDisplay("PULSE PAL v0.3","Click for menu");
}

AudioProcessorEditor* PulsePalOutput::createEditor()
{
    editor = new PulsePalOutputEditor(this, &pulsePal, true);
    return editor;
}

void PulsePalOutput::handleEvent(int eventType, MidiMessage& event, int sampleNum)
{
    if (eventType == TTL)
    {
      //  std::cout << "Received an event!" << std::endl;

        const uint8* dataptr = event.getRawData();

        // int eventNodeId = *(dataptr+1);
        int eventId = *(dataptr+2);
        int eventChannel = *(dataptr+3);

        for (int i = 0; i < channelTtlTrigger.size(); i++)
        {
            if (eventChannel == channelTtlTrigger[i])
            {
                pulsePal.triggerChannel(i+1);
            }
        }

    }

}

void PulsePalOutput::setParameter(int parameterIndex, float newValue)
{
    std::cout << "Changing channel " << parameterIndex << " to " << newValue << std::endl;

    channelTtlTrigger.set(parameterIndex-1, (int) newValue);

}

void PulsePalOutput::process(AudioSampleBuffer& buffer,
                         MidiBuffer& events,
                         int& nSamples)
{

    checkForEvents(events);

}
