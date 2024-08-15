#ifndef TELEMETRY_INTERFACE_H
#define TELEMETRY_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

// ===============================================================================================
// ITelemetryPolicy
// ===============================================================================================
class ITelemetryPolicy : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ITelemetryPolicy interface
class ITelemetryPolicyV1 : public ITelemetryPolicy
{
public:
	enum RgscTelemetryLogLevel
	{
		RGSC_LOGLEVEL_VERYHIGH_PRIORITY,
		RGSC_LOGLEVEL_HIGH_PRIORITY,
		RGSC_LOGLEVEL_MEDIUM_PRIORITY,
		RGSC_LOGLEVEL_LOW_PRIORITY,
		RGSC_LOGLEVEL_VERYLOW_PRIORITY,

		//Debug log levels
		RGSC_LOGLEVEL_DEBUG1,
		RGSC_LOGLEVEL_DEBUG2,
		RGSC_LOGLEVEL_DEBUG3,
		RGSC_LOGLEVEL_DEBUG4,
		RGSC_LOGLEVEL_DEBUG5,
		RGSC_LOGLEVEL_DEBUG_NEVER
	};

	virtual void RGSC_CALL SetSubmissionIntervalSeconds(unsigned intervalSeconds) = 0;
	virtual unsigned RGSC_CALL GetSubmissionIntervalSeconds() = 0;

	virtual void RGSC_CALL SetSubmissionTimeoutSeconds(unsigned timeoutSeconds) = 0;
	virtual unsigned RGSC_CALL GetSubmissionTimeoutSeconds() = 0;

	virtual void RGSC_CALL SetLogLevel(RgscTelemetryLogLevel logLevel) = 0;
	virtual RgscTelemetryLogLevel RGSC_CALL GetLogLevel() = 0;
};

extern "C" static const RGSC_IID IID_ITelemetryPolicyV1 = { 0x3b8a0d1c, 0xf5a0, 0x4132, { 0xa9, 0x21, 0xcf, 0xa0, 0x6b, 0x7, 0x6a, 0xea}};
typedef ITelemetryPolicyV1 ITelemetryPolicyLatestVersion;
#define IID_ITelemetryPolicyLatestVersion IID_ITelemetryPolicyV1

// ===============================================================================================
// rlPcTelemetryPolicy
// ===============================================================================================
class rlPcTelemetryPolicy : public ITelemetryPolicyLatestVersion
{
public:
	rlPcTelemetryPolicy()
	{
		m_SubmissionIntervalSeconds = 0;
		m_SubmissionTimeoutSeconds = 0;
		m_ChannelLogLevel = RGSC_LOGLEVEL_DEBUG_NEVER;
	}

	// ===============================================================================================
	// inherited from IRgscUnknown
	// ===============================================================================================
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		IRgscUnknown *pUnknown = NULL;

		if(ppvObject == NULL)
		{
			return RGSC_INVALIDARG;
		}

		if(riid == IID_IRgscUnknown)
		{
			pUnknown = static_cast<ITelemetryPolicy*>(this);
		}
		else if(riid == IID_ITelemetryPolicyV1)
		{
			pUnknown = static_cast<ITelemetryPolicyV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	// ===============================================================================================
	// inherited from ITelemetryPolicyV1
	// ===============================================================================================
	void RGSC_CALL SetSubmissionIntervalSeconds(unsigned intervalSeconds) { m_SubmissionIntervalSeconds = intervalSeconds; } 
	unsigned RGSC_CALL GetSubmissionIntervalSeconds() { return m_SubmissionIntervalSeconds; } 
	void RGSC_CALL SetSubmissionTimeoutSeconds(unsigned timeoutSeconds) { m_SubmissionTimeoutSeconds = timeoutSeconds; }
	unsigned RGSC_CALL GetSubmissionTimeoutSeconds() { return m_SubmissionTimeoutSeconds; }
	void RGSC_CALL SetLogLevel(RgscTelemetryLogLevel logLevel) { m_ChannelLogLevel = logLevel; }
	RgscTelemetryLogLevel RGSC_CALL GetLogLevel() { return m_ChannelLogLevel; }

private:
	unsigned m_SubmissionIntervalSeconds;
	unsigned m_SubmissionTimeoutSeconds;
	RgscTelemetryLogLevel m_ChannelLogLevel;
};

// ===============================================================================================
// ITelemetry
// ===============================================================================================
class ITelemetry : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Telemetry Interface
//! Defines the public interface that clients use to read and write to telemetry
class ITelemetryV1 : public ITelemetry
{
public:
	virtual RGSC_HRESULT RGSC_CALL SetPolicies(ITelemetryPolicy* policies) = 0;
	virtual bool RGSC_CALL Write(const char* metricName, const char* metric) = 0;
	virtual bool RGSC_CALL Flush(bool bFlushImmediate) = 0;
	virtual bool RGSC_CALL HasAnyMetrics() = 0;
	virtual bool RGSC_CALL IsFlushInProgress() = 0;
	virtual u32 RGSC_CALL GetAvailableMemory() = 0;
	virtual bool RGSC_CALL HasMemoryForMetric() = 0;
	virtual bool RGSC_CALL IsAcceptingWrites() = 0;
};

class ITelemetryV2 : public ITelemetryV1
{
public:
	typedef const char* (*GameHeaderInfoCallback)();
	virtual void RGSC_CALL SetGameHeaderInfoCallback(GameHeaderInfoCallback cb) = 0;
};

class ITelemetryV3 : public ITelemetryV2
{
public:
	using ITelemetryV1::Write;
	virtual bool RGSC_CALL Write(const char* metricName, const char* metricBlob, const int logChannel, const int logLevel) = 0;
};


class ITelemetryV4 : public ITelemetryV3
{
public:
	virtual void RGSC_CALL CancelFlushes() = 0;
};

extern "C" static const RGSC_IID IID_ITelemetryV1 = {0x8baf448e, 0x7047, 0x4ee2, {0x9c, 0x20, 0x20, 0x54, 0x1f, 0x42, 0xd4, 0xa4}};
extern "C" static const RGSC_IID IID_ITelemetryV2 = {0x414522ca, 0x1718, 0x447e, {0x9e, 0x97, 0xe3, 0xb7, 0x9b, 0x91, 0xc6, 0xb7}};
extern "C" static const RGSC_IID IID_ITelemetryV3 = { 0xcd0e6ca2, 0xba48, 0x4eef, { 0x80, 0x3a, 0x76, 0xbd, 0x15, 0x61, 0x9c, 0x6d } };
extern "C" static const RGSC_IID IID_ITelemetryV4 = { 0x5b534fbd, 0x4d97, 0x467e, { 0xa7, 0x73, 0xc6, 0xb5, 0xb9, 0xe8, 0x25, 0x86 } };

typedef ITelemetryV4 ITelemetryLatestVersion;
#define IID_ITelemetryLatestVersion IID_ITelemetryV4

} // namespace rgsc

#endif // TELEMETRY_INTERFACE_H
