#ifndef PATCHING_INTERFACE_H
#define PATCHING_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

class IPatching : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IPatchingV1 = {0x43d787f0, 0x966e, 0x4911, {0xb7, 0xdb, 0xe4, 0xea, 0xc7, 0x8b, 0x4c, 0x61}};

//! Patching Interface
//! Defines the public interface that game clients use to access the patching system.
class IPatchingV1 : public IPatching
{
public:
	// Important: don't change the values of these enums. Javascript hardcodes the value and they must match.
	enum DialogType
	{
		DT_OK = 1,
		DT_OKCANCEL = 2,
		DT_YESNO = 3,
		DT_YESNOCANCEL = 4,
	};

	enum DialogButton
	{
		DB_OK = 1,		//!< The OK button was selected.
		DB_CANCEL = 2,	//!< The Cancel button was selected.
		DB_YES = 6,		//!< The Yes button was selected.
		DB_NO = 7,		//!< The No button was selected.
	};

	typedef void (*AnimationCallback)(const int state, void* userdata);
	typedef void (*ShowOptionsCallback)(const unsigned char* install, const unsigned char* hide, const unsigned int numOptions, void* userdata);
	typedef void (*ShowDialogCallback)(const DialogButton response, void* userdata);
	typedef void (*SetProgressCallback)(const int state, void* userdata);
	
	virtual bool RGSC_CALL CanPerformTitleUpdate() = 0;
	virtual RGSC_HRESULT RGSC_CALL InitPatchingUi(AnimationCallback callback, void* callbackData) = 0;
	virtual RGSC_HRESULT RGSC_CALL ShowMessage(StringId messageId, const Utf8String utf8String, const bool modal, const bool animateSpinner) = 0;
	virtual RGSC_HRESULT RGSC_CALL SetProgress(StringId messageId, const Utf8String utf8String, const unsigned int progress, SetProgressCallback callback, void* callbackData) = 0;
	virtual RGSC_HRESULT RGSC_CALL ShowOptions(const Utf8String message, const Utf8String* options, const bool* optional, const bool* hidden, const unsigned int numOptions, ShowOptionsCallback callback, void* callbackData) = 0;
	virtual RGSC_HRESULT RGSC_CALL ShowDialog(StringId messageId, const Utf8String utf8String, DialogType type, const bool modal, ShowDialogCallback callback, void* callbackData) = 0;
	virtual RGSC_HRESULT RGSC_CALL ClosePatchingUi(bool showFinalMessage) = 0;
};

typedef IPatchingV1 IPatchingLatestVersion;
#define IID_IPatchingLatestVersion IID_IPatchingV1

} // namespace rgsc

#endif // PATCHING_INTERFACE_H
