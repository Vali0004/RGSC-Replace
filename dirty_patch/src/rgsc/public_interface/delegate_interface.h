#ifndef RGSC_DELEGATE_H
#define RGSC_DELEGATE_H

#include "rgsc_common.h"

namespace rgsc
{

class IRgscDelegate : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IRgscDelegateV1 = {0xfe7992d1, 0xf398, 0x45d6, {0xa5, 0x60, 0x60, 0x83, 0x2b, 0xbd, 0x5c, 0xb1}};
extern "C" static const RGSC_IID IID_IRgscDelegateV2 = {0x470244ff, 0x6440, 0x4e80, {0x8e, 0xc9, 0xbb, 0x60, 0xe5, 0xa0, 0x79, 0xfb}};
extern "C" static const RGSC_IID IID_IRgscDelegateV3 = {0xadf18730, 0x3149, 0x40f9, {0x86, 0xe1, 0xb4, 0xd5, 0xc2, 0x8, 0xbd, 0xa6}};

//! Rgsc will send unsolicited messages to the calling process via a delegate interface.
//! The calling process must implement a class that implements this interface.\n
class IRgscDelegateV1 : public IRgscDelegate
{
public:
	enum OutputSeverity
	{
		RGSC_OUTPUT_SEVERITY_ASSERT = 3,
		RGSC_OUTPUT_SEVERITY_ERROR = 2,
		RGSC_OUTPUT_SEVERITY_WARNING = 1,
		RGSC_OUTPUT_SEVERITY_INFO = 0,
	};

	//! Sends debug information to the calling process.
	virtual void RGSC_CALL Output(OutputSeverity severity, const char* msg) = 0;
	virtual bool RGSC_CALL GetStatsData(char** data) = 0;
	virtual void RGSC_CALL FreeStatsData(const char* data) = 0;
	virtual void RGSC_CALL SetTextBoxHasFocus(const bool hasFocus) = 0;
	virtual void RGSC_CALL UpdateSocialClubDll(const char* commandLine) = 0;
};

class IRgscDelegateV2 : public IRgscDelegateV1
{
public:
	virtual void RGSC_CALL SetTextBoxHasFocusV2(const bool hasFocus, const char* prompt, const char* text, const bool isPassword, const unsigned int maxNumChars) = 0;
};

class IRgscDelegateV3 : public IRgscDelegateV2
{
public:
	virtual void RGSC_CALL HandleNotification(const NotificationType id, const void* param) = 0;
};

typedef IRgscDelegateV3 IRgscDelegateLatestVersion;

} // namespace rgsc

#endif // RGSC_DELEGATE_H
