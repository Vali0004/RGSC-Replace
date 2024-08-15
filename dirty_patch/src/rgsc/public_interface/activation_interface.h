#ifndef ACTIVATION_INTERFACE_H
#define ACTIVATION_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

class IActivation : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IActivationV1 = {0x4edfb05c, 0xf74, 0x4cab, {0x9b, 0x4a, 0x6, 0x77, 0xec, 0xad, 0xdc, 0xcd}};
extern "C" static const RGSC_IID IID_IActivationV2 = {0xd3542e14, 0x3cc7, 0x4211, {0x92, 0x3e, 0x7a, 0x60, 0xcc, 0x14, 0x11, 0xe8}};

//! Activation Interface
//! Defines the public interface that game clients use to access the activation system.
class IActivationV1 : public IActivation
{
public:
	enum ActivationAction
	{
		ACTIVATION_ERROR = 0,
		ACTIVATION_ACTIVATED_CONTENT = 1,
		ACTIVATION_DEACTIVATED_CONTENT = 2,
		ACTIVATION_USER_CANCELLED = 3,
		ACTIVATION_USER_QUIT = 4,
		ACTIVATION_LINK_STEAM_ACCOUNT = 5,
	};

	//! The callback signature passed to ShowCorruptLicenseUi()
	typedef void (*CorruptLicenseCallback)(void);

	//! Shows the corrupt license UI when the game's activations system determines the license is corrupted or missing.
	/**
	  \param callback - the function called when the user confirms the message.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowCorruptLicenseUi(StringId message, CorruptLicenseCallback callback) = 0;

	//! The callback signature passed to ShowActivationCodeUi()
	/**
		\param contentId - the id of the content being activated or deactivated
		\param activationCode - the activation code that was entered by the user
		\param action - the action taken by the user (activating, deactivating, cancelled)
	*/
	typedef void (*ActivationCodeCallback)(const int contentId,
										   const char* activationCode,
										   const ActivationAction action);

	//! Shows the activation code UI that allows the player to enter an activation code.
	/**
	  \param contentId - the id of the content for which the UI will be displayed
	  \param currentSerialNumber - the currently active serial number
	  \param isAlreadyActivated - whether the content is currently activated
	  \param callback - the function that will receive the activation code entered by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowActivationCodeUi(const int contentId,
													   const char* currentSerialNumber,
													   const bool isAlreadyActivated,
													   ActivationCodeCallback callback) = 0;

	//! Gives the results of the previous activation action.
	/**
	  \param contentId - the id of the content
	  \param result - integer representing the result of the previous activation action
	  \param message - id of the message to display to the user
	*/
	virtual RGSC_HRESULT RGSC_CALL ActivationCodeResult(const int contentId,
		const int result,
		StringId message) = 0;

	//! The callback signature passed to ShowLicenseRecoveryUi()
	/**
		\param contentId - the id of the content being activated.
		\param recoveryRequestCode - the same recover request code that was sent to ShowLicenseRecoveryUi().
		\param recoveryResponseCode - the response code entered by the user.
		\param action - the action taken by the user (error, activating, cancelled).
	*/
	typedef void (*LicenseRecoveryCallback)(const int contentId,
											const char* recoveryRequestCode,
											const char* recoveryResponseCode,
											const ActivationAction action);

	//! Shows the UI that allows the user to recover their broken/corrupt license.
	/**
	  \param contentId - the id of the content needing recovery.
	  \param recoveryRequestCode - the request code that will be displayed to the user.
	  \param callback - the function that will receive the response code entered by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowLicenseRecoveryUi(const int contentId, const char* recoveryRequestCode, LicenseRecoveryCallback callback) = 0;

	//! Gives the results of the previous attempt to recover a license.
	/**
	  \param contentId - the id of the content.
	  \param result - integer representing the result of the license recovery.
	  \param message - id of the message to display to the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL LicenseRecoveryResult(const int contentId, const int result, StringId message) = 0;

	//! The callback signature passed to ShowExpirationCodeUi()
	/**
		\param contentId - the id of the content being activated.
		\param activationCode - the activation code that was entered by the user.
		\param action - the action taken by the user (error, activating, cancelled).
	*/
	typedef void (*ExpirationCodeCallback)(const int contentId, const char* activationCode, const ActivationAction action);

	//! Shows the activation code UI that allows the user to extend the expiration on their license.
	/**
	  \param contentId - the id of the content for which the UI will be displayed.
	  \param currentSerialNumber - the currently active serial number.
	  \param callback - the function that will receive the activation code entered by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowExpirationCodeUi(const int contentId, const char* currentSerialNumber, ExpirationCodeCallback callback) = 0;

	//! Gives the results of the previous attempt to extend a license.
	/**
	  \param contentId - the id of the content.
	  \param result - integer representing the result of the license extension.
	  \param message - id of the message to display to the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ExpirationCodeResult(const int contentId, const int result, StringId message) = 0;
};

class IActivationV2 : public IActivationV1
{
public:
	//! The callback signature passed to ShowSteamLinkingUi()
	/**
		\param action - the action taken by the user (cancel, quit, link)
	*/
	typedef void (*SteamLinkingCallback)(const ActivationAction action);

	//! Shows the UI that allows users to link their Social Club account to their Steam account
	/**
	  \param callback - the function that will receive the action taken by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowSteamLinkingUi(SteamLinkingCallback callback) = 0;

	//! Gives the results of the Steam linking operation.
	/**
	  \param result - 0 = fail, 1 = success, others may be added in the future
	  \param message - id of the message to display to the user, or 0 to use the defaults.
	*/
	virtual RGSC_HRESULT RGSC_CALL SteamLinkingResult(const bool linkSucceeded, StringId message) = 0;
};

typedef IActivationV2 IActivationLatestVersion;
#define IID_IActivationLatestVersion IID_IActivationV2

} // namespace rgsc

#endif // ACTIVATION_INTERFACE_H
