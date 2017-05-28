#ifndef VEHICLE_OBSTRUCTIONS_H
#define VEHICLE_OBSTRUCTIONS_H

#include "Global.h"
#include "UDPSender.h"
#include "ThreadBase.h"
#include "LIDAR.h"

class VehicleObstructions : public ThreadBase
{
	public:
		// -----Singleton Code-----
		static VehicleObstructions* getInstance();
		static VehicleObstructions* getInstance(char* myIP);
		~VehicleObstructions();
		// ------------------------

		void ThreadMethod();
		void SetSample(LDATA LIDARDataFromLIDAR);
		void SetTach(unsigned int rpm, timeval* usTimestamp);
		bool CheckIfSendFlagIsSetAndReset();
		bool SetSendFlag();
		bool CheckIfSampleAvailFlagIsSetAndReset();
		bool SetSampleAvailFlag();
		bool CheckIfReconnectToLIDARFlagIsSetAndReset();
		bool SetReconnectToLIDARFlag();


	private:
		// -----Singleton Code-----
		VehicleObstructions();
		VehicleObstructions(char* myIP);
		static VehicleObstructions* vehicleObstructionsInstance;
		// ------------------------

		// Private Methods
		void CheckForObstructionInSample();
		void GetTach();
		void Decimation();
		void SampleMerge(int rawIndex, int binIndex);

		// Private Data
		struct TachSample
		{
			int rpm;
			long long usTimestamp;
		};

		char* instIP;
		int rawIndex;
		bool sendFlag;
		bool sampleAvailFlag;
		bool reconnectToLIDARFlag;
		int ActualNumSamples;
		int sampleWritePtr;
		LDATA* BinCircleBuffer;
		LDATA* RawBuffer;
		LDATA sampleBeingProcessed;
		UDPSender* vehObsSender;
		pthread_mutex_t LIDAR_DS_Mutex;
		pthread_mutex_t sendFlag_Mutex;
		pthread_mutex_t setSampleFlag_Mutex;
		pthread_mutex_t reconnectToLIDARFlag_Mutex;
};

#endif