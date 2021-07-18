#include <chrono>
#include <math.h>
#include <algorithm>
#include <memory>
#include <map>

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Utils/Utils.h"

class FloatTimestampBuffer
{
public:
    FloatTimestampBuffer(int size);
    ~FloatTimestampBuffer();

    void clear();

    int addToBuffer(float* data, int64* timestamps, int numItems, int chunkSize=1);
    int getNumSamples() const;
    int readAllFromBuffer(AudioSampleBuffer& data, uint64* timestamp, int maxSize, int dstStartChannel, int numChannels);
    void resize(int size);

private: 


    int64 lastTimestamp;
    AbstractFifo abstractFifo;
    AudioSampleBuffer buffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FloatTimestampBuffer);

};


class Stream
{
public:
    Stream(float expectedSampleRate);

    void reset();

    float expectedSampleRate;
    float actualSampleRate;

    int startSample;
    int lastSample;

    int syncChannel;

    bool isSynchronized;

    bool receivedEventInWindow;
    bool receivedPrimaryTimeInWindow;

    float primaryIntervalSec;

    int tempSampleNum;
    float tempPrimaryTime;

    float startSamplePrimaryTime = -1.0f;
    float lastSamplePrimaryTime = -1.0f;

    float sampleRateTolerance;

    void addEvent(int sampleNumber);

    void setPrimaryTime(float time);
    void openSyncWindow();
    void closeSyncWindow();
};

class RecordNode;

enum SyncStatus { 
    OFF,        //Synchronizer is not running
    SYNCING,    //Synchronizer is attempting to sync
    SYNCED      //Signal has been synchronized
};

class Synchronizer : public HighResolutionTimer
{
public:

    Synchronizer(RecordNode* parent);
    ~Synchronizer();
    
    void reset();

    void addDataStream(int streamId, float expectedSampleRate);
    void setPrimaryDataStream(int streamId);

    void setSyncBit(uint16 streamId, int bit);
    int getSyncBit(uint16 streamId);

    bool isSubprocessorSynced(int sourceID, int subProcIdx);
    SyncStatus getStatus(int sourceID, int subProcIdx);

    void addEvent(int sourceID, int subProcessorID, int ttlChannel, int sampleNumber);

    double convertTimestamp(int sourceID, int subProcID, int sampleNumber);

    std::map<int, std::map<int, Stream*>> streams;

    RecordNode* node;

    int primaryProcessorId = -1;
    int primaryStreamId = -1;

    bool isAvailable() { return primaryProcessorId > 0; };

private:

    int eventCount = 0;

    float syncWindowLengthMs;
    bool syncWindowIsOpen;

    void hiResTimerCallback();

    bool firstMasterSync;

    OwnedArray<Stream> streamArray;

    OwnedArray<FloatTimestampBuffer> ftsBuffer;

    void openSyncWindow();
};