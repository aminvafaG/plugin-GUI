/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2016 Open Ephys

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

#ifndef __PARAMETER_H_62922AE5__
#define __PARAMETER_H_62922AE5__

#include <JuceHeader.h>
#include "../PluginManager/OpenEphysPlugin.h"

#include <stdio.h>

class ParameterEditor;
class BooleanParameterEditor;
class IntParameterEditor;

/**
    Class for holding user-definable processor parameters.

    Parameters can either hold boolean, categorical, continuous (float) values,
    or a list of selected channels.

    Using the Parameter class makes it easier to create a graphical interface for editing
    parameters, because each Parameter has a ParameterEditor that can be generated automatically.

    @see GenericProcessor, GenericEditor
*/


class PLUGIN_API Parameter //: private Value::Listener
{
public:
    //class Listener
   // {
   //// public:
    //    virtual ~Listener() {}

    //    virtual void parameterValueChanged(String parameterName) = 0;
    //};

    enum ParameterType
    {
        BOOLEAN_PARAM = 1,
        CATEGORICAL_PARAM,
        FLOAT_PARAM,
        INT_PARAM,
        SELECTED_CHANNELS_PARAM
    };

    /** Parameter constructor.*/
    Parameter(GenericProcessor* processor_,
        uint16 streamId_,
        ParameterType type_,
        const String& name_,
        const String& description_,
        var defaultValue_,
        bool deactivateDuringAcquisition_ = false) 
      : processor(processor_),
        streamId(streamId_),
        m_parameterType(type_),
        m_name(name_),
        m_description(description_),
        currentValue(defaultValue_),
        defaultValue(defaultValue_),
        m_deactivateDuringAcquisition(deactivateDuringAcquisition_)
    {

    }

    virtual Parameter::~Parameter() { }

    /** Returns the name of the parameter.*/
    String getName() const noexcept { return m_name; }

    /** Returns a description of the parameter.*/
    String getDescription() const noexcept { return m_description; }

    /** Returns the type of the parameter. */
    ParameterType getType() const noexcept { return m_parameterType; }

    /** Returns the streamId for this parameter*/
    uint16 getStreamId() { return streamId; }

    /** Sets the streamId for this parameter*/
    void setStreamId(uint16 streamId_) { streamId = streamId_;  }

    /** Determines whether the parameter's editor is accessible after acquisition starts*/
    bool shouldDeactivateDuringAcquisition() {
        return m_deactivateDuringAcquisition;
    }

    /** Sets the parameter value*/
    virtual void setValue(var newValue) = 0;

    /** Returns the parameter value*/
    var getValue() {
        return currentValue;
    }

    /** Returns a string describing this parameter's type*/
    String getParameterTypeString() const;

    /** Saves the parameter to an XML Element*/
    virtual void toXml(XmlElement*) = 0;

    /** Loads the parameter from an XML Element*/
    virtual void fromXml(XmlElement*) = 0;

protected:

    GenericProcessor* processor;
    uint16 streamId;

    var currentValue;
    var defaultValue;

private:

    ParameterType m_parameterType;
    String m_name;
    String m_description;

    bool m_deactivateDuringAcquisition;

   // ListenerList<Listener> m_listeners;
};


class PLUGIN_API BooleanParameter : public Parameter
{
public:
    /** Parameter constructor.*/
    BooleanParameter(GenericProcessor* processor,
        uint16 streamId,
        const String& name,
        const String& description,
        bool defaultValue,
        bool deactivateDuringAcquisition = false);

    /** Sets the parameter value*/
    virtual void setValue(var newValue);

    /** Gets the value as a boolean*/
    bool getBoolValue();

    /** Saves the parameter to an XML Element*/
    virtual void toXml(XmlElement*) override;

    /** Loads the parameter from an XML Element*/
    virtual void fromXml(XmlElement*) override;

    /** Creates an editor for this parameter*/
    static BooleanParameterEditor* createEditor(BooleanParameter* param);

};

class PLUGIN_API IntParameter : public Parameter
{
public:
    /** Parameter constructor.*/
    IntParameter(GenericProcessor* processor,
        uint16 streamId, 
        const String& name,
        const String& description,
        int defaultValue,
        int minValue = 0,
        int maxValue = 100,
        bool deactivateDuringAcquisition = false);

    /** Sets the current value*/
    virtual void setValue(var newValue) override;

    /** Gets the value as an integer*/
    int getIntValue();

    int getMinValue() { return minValue; }

    int getMaxValue() { return maxValue; }

    /** Saves the parameter to an XML Element*/
    virtual void toXml(XmlElement*) override;

    /** Loads the parameter from an XML Element*/
    virtual void fromXml(XmlElement*) override;

    /** Creates an editor for this parameter*/
    static IntParameterEditor* createEditor(IntParameter* param);

private:
    int maxValue;
    int minValue;
};


    /** Returns the default value of a parameter (can be boolean, int, or float).*/
    //var getDefaultValue() const noexcept;

    /** Returns the value of a parameter for a given channel.*/
    //var getValue (int chan) const;

    /** Returns the value of a parameter for a given channel.*/
    //var operator[](int chan) const;

    /** Returns all the possible values that a parameter can take for Boolean and Discrete parameters;
        Returns the minimum and maximum value that a parameter can take for Continuous parameters.*/
    //const Array<var>& getPossibleValues() const;

    /** Returns the type of the parameter in string representation. */
    //String getParameterTypeString() const noexcept;

    /** Returns true if a parameter is boolean, false otherwise.*/
    //bool isBoolean() const noexcept;

    /** Returns true if a parameter is continuous, false otherwise.*/
    //bool isContinuous() const noexcept;

    /** Returns true if a parameter is discrete, false otherwise.*/
   //bool isDiscrete() const noexcept;

    /** Returns true if a parameter is numerical, false otherwise.*/
    //bool isNumerical() const noexcept;

    /** Returns true if a user set custom bounds for the possible parameter editor, false otherwise. */
    //bool hasCustomEditorBounds() const noexcept;

    /** Returns the recommended width value for the parameter editor if parameter has it. */
    //int getEditorRecommendedWidth() const noexcept;

    /** Returns the recommended height value for the parameter editor if parameter has it. */
    //int getEditorRecommendedHeight() const noexcept;

    /** Returns the desired bounds for editor if parameter has it. */
    //const juce::Rectangle<int>& getEditorDesiredBounds() const noexcept;

    /** Sets the name of a parameter. */
    //void setName (const String& newName);

    /** Sets the description of the parameter.*/
    //void setDescription (const String& desc);

    /** Sets the value of a parameter for a given channel.*/
    //void setValue (float val, int chan);

    /** Sets the value of a parameter for a given channel. Returns whether the value was actually set. */
    //bool setValue(const var& val, int chan);

    /** Gets the channels with values set for this parameter. */
    //int getNumChannels() const;

    /** Sets the possible values. It makes sense only for discrete parameters. */
   // void setPossibleValues (Array<var> possibleValues);

    /** Sets desired size for the parameter editor. */
   //void setEditorDesiredSize (int desiredWidth, int desiredHeight);

    /** Sets desired bounds for the parameter editor. */
    //void setEditorDesiredBounds (int x, int y, int width, int height);

    /** Sets desired bounds for the parameter editor. */
    //void setEditorDesiredBounds (const juce::Rectangle<int>& desiredBounds);

    /** Returns the appropriate parameter type from string. */
   // static ParameterType getParameterTypeFromString (const String& parameterTypeString);

    /** Creates value tree for given parameter. */
   // static ValueTree createValueTreeForParameter (Parameter* parameter);

    /** Creates parameter from a given value tree. */
    //static Parameter* createParameterFromValueTree (ValueTree parameterValueTree);

    /** Certain parameters should not be changed while data acquisition is active.
         This variable indicates whether or not these parameters can be edited.*/
   // bool shouldDeactivateDuringAcquisition;

    // Accessors for values
    // ========================================================================
   // Value& getValueObjectForID()                noexcept;
   // Value& getValueObjectForName()              noexcept;
   // Value& getValueObjectForDescription()       noexcept;
   // Value& getValueObjectForDefaultValue()      noexcept;
   // Value& getValueObjectForMinValue()          noexcept;
   // Value& getValueObjectForMaxValue()          noexcept;
   // Value& getValueObjectForPossibleValues()    noexcept;
   // Value& getValueObjectForDesiredX()          noexcept;
   // Value& getValueObjectForDesiredY()          noexcept;
   // Value& getValueObjectForDesiredWidth()      noexcept;
   // Value& getValueObjectForDesiredHeight()     noexcept;
    // ========================================================================

  //  void addListener    (Listener* listener);
   // void removeListener (Listener* listener);


//private:
  //  void registerValueListeners();

    //String m_name;
    //String m_description;

    //int m_parameterId;

   // bool m_hasCustomEditorBounds { false };

   // juce::Rectangle<int> m_editorBounds;

    //var m_defaultValue;
   // Array<var> m_values;
   // Array<var> m_possibleValues;

   // ParameterType m_parameterType;

    // Different values to be able to set any needed fields for parameters
    // without any effort when using property editors
    // ========================================================================
    /*Value m_nameValueObject;
    Value m_descriptionValueObject;
    Value m_parameterIdValueObject;
    Value m_defaultValueObject;
    Value m_minValueObject;
    Value m_maxValueObject;
    Value m_possibleValuesObject;
    Value m_desiredXValueObject;
    Value m_desiredYValueObject;
    Value m_desiredWidthValueObject;
    Value m_desiredHeightValueObject;*/
    // ========================================================================

   // ListenerList<Listener> m_listeners;
//};


//class ParameterFactory
//{
//public:
    /** Creates and returns the parameter of given type. */
  //  static Parameter* createEmptyParameter (Parameter::ParameterType parameterType, int parameterId);
//};


#endif  // __PARAMETER_H_62922AE5__
