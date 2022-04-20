#ifndef BINARYRECORDING_H
#define BINARYRECORDING_H

#include <chrono>
#include <iomanip>
#include <memory>

#include "../../../Utils/Utils.h"
#include "../RecordEngine.h"
#include "SequentialBlockFile.h"
#include "NpyFile.h"

class BinaryRecording : public RecordEngine
{
public:

	/** Constructor */
	BinaryRecording();

	/** Destructor */
	~BinaryRecording();

	/** Returns the unique identifier of this RecordEngine */
	String getEngineId() const override;
    
    /** Launches the manager for this Record Engine, and instantiates any parameters */
    static RecordEngineManager* getEngineManager();

	/** Opens files at the start of recording */
	void openFiles(File rootFolder, int experimentNumber, int recordingNumber);

	/** Closes files at the end of recording */
	void closeFiles();

	/** Writes a block of continuous data */
	void writeContinuousData(int writeChannel, 
		int realChannel, 
		const float* dataBuffer, 
		const double* timestampBuffer, 
		int size);

	/** Writes an event to disk */
	void writeEvent(int eventIndex, const EventPacket& packet);

	/** Writes a spike to disk */
	void writeSpike(int electrodeIndex, const Spike* spike);

	/** Writes timestamp sync texts */
	void writeTimestampSyncText(uint64 streamId, int64 timestamp, float sampleRate, String text);

	/** Sets an engine parameter (in this case TTL word writing bool) */
	void setParameter(EngineParameter& parameter);

private:

    class EventRecording
    {
    public:

		std::unique_ptr<NpyFile> data;
		std::unique_ptr<NpyFile> samples;
		std::unique_ptr<NpyFile> channels;
        std::unique_ptr<NpyFile> extraFile;
        std::unique_ptr<NpyFile> timestamps;
    };

    std::unique_ptr<NpyFile> createEventMetadataFile(const MetadataEventObject* channel, String fileName, DynamicObject* jsonObject);
	void createChannelMetadata(const MetadataObject* channel, DynamicObject* jsonObject);
    void writeEventMetadata(const MetadataEvent* event, NpyFile* file);
    void increaseEventCounts(EventRecording* rec);

    bool m_saveTTLWords{ true };

	HeapBlock<float> m_scaledBuffer;
	HeapBlock<int16> m_intBuffer;
	HeapBlock<int64> m_sampleNumberBuffer;
	int m_bufferSize;
	int m_syncTimestampBufferSize;

	Array<unsigned int> m_channelIndexes;
	Array<unsigned int> m_fileIndexes;
    
    OwnedArray<SequentialBlockFile> m_continuousFiles;
	OwnedArray<EventRecording> m_eventFiles;
	OwnedArray<EventRecording> m_spikeFiles;

	static String jsonTypeValue(BaseType type);
	static String getProcessorString(const InfoObject* channelInfo);
	
	OwnedArray<NpyFile> m_dataTimestampFiles;
	OwnedArray<NpyFile> m_dataSyncTimestampFiles;
	std::unique_ptr<FileOutputStream> m_syncTextFile;

	Array<unsigned int> m_spikeFileIndexes;
    Array<uint16> m_spikeChannelIndexes;

	int m_recordingNum;
    int m_experimentNum;
	Array<int64> m_startSampleNum;

	const int samplesPerBlock{ 4096 };


};
#endif
