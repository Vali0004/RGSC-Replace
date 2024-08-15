#ifndef COMMERCE_INTERFACE_H
#define COMMERCE_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"

namespace rgsc
{

//! Commerce Manager Interface
//! Defines the public interface that game clients use to access commerce information.
class ICommerceManager : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_ICommerceManagerV1 = {0xf36c0d9c, 0xfd29, 0x4f44, {0xa1, 0x25, 0x6c, 0x70, 0xee, 0x6d, 0x70, 0x5}};
extern "C" static const RGSC_IID IID_ICommerceManagerV2 = {0xac578469, 0x84bf, 0x492a, {0x97, 0xc2, 0xcb, 0x40, 0x97, 0x8a, 0x95, 0x1e}};
extern "C" static const RGSC_IID IID_ICommerceManagerV3 = {0xf9b45ea8, 0xf69d, 0x4bb0, {0xaa, 0x36, 0x60, 0x54, 0xd3, 0xcf, 0xce, 0x72}};
extern "C" static const RGSC_IID IID_ICommerceManagerV4 = {0x85d695f4, 0xf5f2, 0x440b, {0xa9, 0xff, 0x44, 0x10, 0x2d, 0x39, 0xdb, 0x56}};
extern "C" static const RGSC_IID IID_ICommerceManagerV5 = {0xefd9fafa, 0xb309, 0x49d5, { 0xbd, 0xf9, 0x63, 0x8b, 0x2e, 0x4a, 0xf, 0x15}};

//! Version 1 of the commerce manager interface.
class ICommerceManagerV1 : public ICommerceManager
{
public:
	//! Shows the commerce UI
	/**
		\param url - the url to display. Pass NULL or "" to bring up a 'waiting...' panel.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowCommerceUi(const char* url) = 0;

	enum RedemptionAction
	{
		REDEMPTION_ENTERED_CODE = 1,
		REDEMPTION_USER_CANCELLED = 2,
		REDEMPTION_DOWNLOAD_CONTENT = 3,
	};

	//! The callback signature passed to ShowRedemptionCodeUi()
	/**
		\param redemptionCode - the redemption code that was entered by the user
		\param action - the action taken by the user (entered code, canceled, etc.)
	*/
	typedef void (*RedemptionCodeCallback)(const char* redemptionCode,
										   const RedemptionAction action);

	//! Shows the redemption code UI that allows the player to enter a redemption code.
	/**
		\param callback - the function that will receive the redemption code entered by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowRedemptionCodeUi(RedemptionCodeCallback callback) = 0;

	//! Gives the results of the previous code redemption.
	/**
		\param result - integer representing the result of the previous code redemption
		\param message - id of the message to display to the user
		\param callback - receives the action performed by the user (download, canceled, etc.).
	*/
	virtual RGSC_HRESULT RGSC_CALL RedemptionCodeResult(const int result, StringId message, RedemptionCodeCallback callback) = 0;

	//! Notifies the Social Club UI that a download has completed. The Social Club UI may display a toast for this event.
	/**
		\param name - the localized name of the downloaded item in utf-8 format, or NULL if no name is to be displayed.
		\param success - true if the download completed successfully, false if it failed.
	*/
	virtual void RGSC_CALL DownloadComplete(const char* name, bool success) = 0;
};

//! Version 2 of the commerce manager interface.
class ICommerceManagerV2 : public ICommerceManagerV1
{
public:
	using ICommerceManagerV1::RedemptionCodeResult;

	//! Gives the results of the previous code redemption.
	/**
		\param result - integer representing the result of the previous code redemption
		\param message - id of the message to display to the user
		\param contentName - the localized string representing the content name that was unlocked in utf-8 format. Can be NULL.
		\param callback - receives the action performed by the user (download, canceled, etc.).
	*/
	virtual RGSC_HRESULT RGSC_CALL RedemptionCodeResult(const int result, StringId message, const char* contentName, ICommerceManagerV1::RedemptionCodeCallback callback) = 0;
};

class ICommerceManagerV3 : public ICommerceManagerV2
{
#if RSG_CPU_X64
public:
	virtual void RGSC_CALL InitData() = 0;
	virtual void RGSC_CALL DestroyData() = 0;

	virtual bool RGSC_CALL StartDataFetch( const char* languageCode ) = 0;
	virtual const char* RGSC_CALL IsDataValidAsJson() = 0;
	virtual const char* RGSC_CALL IsInErrorStateAsJson() = 0;

	virtual const char* RGSC_CALL GetDataAsJson() = 0;
	virtual const char* RGSC_CALL GetItemDataAsJson( const char *parameterJson ) = 0;
	virtual const char* RGSC_CALL RequestUrlForCheckout( const char *parameterJson ) = 0;

	virtual const char* RGSC_CALL GetUserAgeAppropriateData() = 0;

	virtual RGSC_HRESULT RGSC_CALL ShowCommerceStore(const char* product, const char* category) = 0;

	//New voucher flow. Goes [RequestVoucherContent]->[WAIT FOR RESPONSE]->[SendVoucherRequestResultToJs Calls RGSC_JS_VOUCHER_REQUEST_RESULT]->{SCUI presents content and requests confirmation.}
	//							{If user confirms}->[RequestVoucherConsumption]->[WAIT FOR RESPONSE]->[SendVoucherRequestResultToJs calls RGSC_JS_VOUCHER_REQUEST_RESULT]->{SCUI presents confirmation or fail}
	virtual const char* RGSC_CALL RequestVoucherContent( const char* parameterJson ) = 0;
	virtual const char* RGSC_CALL RequestVoucherConsumption( const char* parameterJson ) = 0;

	typedef bool (*IsContainedPackageInstalledCallback)( const char* containedPackageName );
	virtual const char* RGSC_CALL IsProductInstalled( const char* parameterJson ) = 0;
	virtual RGSC_HRESULT RGSC_CALL SetContainedPackageInstalledCallback(IsContainedPackageInstalledCallback) = 0;

	//Function used to access steam microtransactions
	virtual const char* RGSC_CALL StartSteamPurchase( const char* /*parameterJson*/ ) = 0;

	//These functions are here for durables. Consumables should use StartSteamPurchase()
	typedef void (*SteamStoreOpenCallback)( u32 steamAppId );
	virtual RGSC_HRESULT RGSC_CALL SetSteamStoreOpenCallback(SteamStoreOpenCallback newCallback) = 0; 
	virtual bool RGSC_CALL ShowSteamStore() = 0;

	virtual bool RGSC_CALL GetContentPathUrl(const char* path, char* outputBuffer, unsigned int outputBufferLength, IAsyncStatus* status) = 0;
#endif
};


class ICommerceManagerV4 : public ICommerceManagerV3
{
#if RSG_CPU_X64
public:
	virtual bool RGSC_CALL RequestEntitlementData( const char* machineHash, const char* language ) = 0;
	virtual bool RGSC_CALL IsEntitlementDataValid() = 0;
	virtual bool RGSC_CALL IsEntitlementDataInErrorState() = 0;
	virtual const char* RGSC_CALL GetEntitlementDataAsJson() = 0;

	virtual bool RGSC_CALL GetEntitlementDownloadUrl(const char* entitlementCode, char* outputBuffer, unsigned int outputBufferLength,IAsyncStatus* status) = 0;

	//These functions grant access to the secure entitlements data block. The request will start the download of the block.
	//Once IsEntitlementBlockValid returns true you can check for the availability of an entitlement by passing its ID into 
	//DoesEntitlementBlockGrantEntitlement.
	virtual bool RGSC_CALL RequestEntitlementBlock( const char* machineHash, const char* locale, char* outputBuffer, unsigned int outputBufferSize, int* outputVersion, unsigned int* outputDataSize,IAsyncStatus* status ) = 0;
	virtual bool RGSC_CALL DoesEntitlementBlockGrantEntitlement( const RockstarId rockstarId, const char* machineHash, const char* entitlementId, void* dataBuffer, unsigned int dataBufferSize ) = 0;


	//! Allocates a block of memory for saving an entitlement blob
	/**
		\param size - the size of the entitlement blob to allocate in bytes
	*/
	virtual u8* RGSC_CALL AllocateOfflineEntitlementBlob(unsigned size) = 0;

	//! Saves offline entitlement to disk in the social club profiles folder
	/**
		\param entitlementBuf - the entitlement blob to save
		\param entitlementBufLen - the length of the entitlement blob
	*/
	virtual bool RGSC_CALL SaveOfflineEntitlement(u8* entitlementBuf, unsigned entitlementBufLen, u8* machineHash) = 0;

	//! Loads offline entitlement from disk into the static blob in rlRosEntitlement
	virtual bool RGSC_CALL LoadOfflineEntitlement(u8* machineHash) = 0;

	//! Returns TRUE if the rlRosEntitlement has an offline entitlement blob loaded
	virtual bool RGSC_CALL HasOfflineEntitlement() = 0;

	//! Retrieves the offline entitlement blob
	virtual u8* RGSC_CALL GetOfflineEntitlement() = 0;

	//! Retrieves the length of the offline entitlement blob
	virtual unsigned RGSC_CALL GetOfflineEntitlementLength() = 0;

	//! Clears the offline entitlement blob
	virtual bool RGSC_CALL ClearOfflineEntitlement() = 0;

	//! Returns TRUE if the entitlement blob is being saved or loaded
	virtual bool RGSC_CALL IsEntitlementIOInProgress() = 0;


	//! The callback signature passed to SetPurchaseFlowTelemetryCallback()
	/**
		\param telemtry - json-formatted data to pass to the SCUI when the Store UI is opened.
		\param bufSize - the size of the telemetry buffer.
	*/
	typedef void (*PurchaseFlowTelemetryCallback)(char* telemtry, const unsigned bufSize);

	//! This sets the PurchaseFlowTelemetryCallback.
	/**
		\param callback - the function that will supply the purchase flow telemetry data.
		\remark
		  If non-NULL, the callback will be called every time the Store UI is opened.
		  The data returned from the callback will be sent to the SCUI.
		  This is used to obtain Purchase Flow Telemetry from the game so we can gather analytics
		  data about when and why people choose to purchase items in the Store.
	*/
	virtual void RGSC_CALL SetPurchaseFlowTelemetryCallback(PurchaseFlowTelemetryCallback callback) = 0;

	//! Returns TRUE is previous call to StartSteamPurchase has failed
    virtual bool RGSC_CALL DidLastSteamPurchaseFail() = 0;
#endif
};

class ICommerceManagerV5 : public ICommerceManagerV4
{
#if RSG_CPU_X86
public:
	/*
	** The following functionality is an integration from the Max Payne 3 build of RAGE and likely should only be called by that title. By moving the code
		from MP3's RAGE into our local instance, we can apply code protections to the Social Club SDK (and potentially expose to other back catalog games).
		However, since these APIs are not part of the new Entitlements V2 interface introduced with GTAV and share similar names, they have been explicitly
		prefixed with "EntitlementV1_" to differentiate their usage.
	*/
	virtual void RGSC_CALL EntitlementV1_RefreshData(bool bForceBackendSync) = 0;
	virtual bool RGSC_CALL EntitlementV1_IsCheckingForEntitlement() = 0;
	virtual bool RGSC_CALL EntitlementV1_IsEntitlementUpToDate() = 0;
	virtual bool RGSC_CALL EntitlementV1_RegisterPurchaseBySN(int entitlementProjectId, char* serialNumber, bool* isActivated, char* skuName, 
															  unsigned skuNameBufLen, char* friendlyName, unsigned friendlyLength, IAsyncStatus* status) = 0;
	virtual bool RGSC_CALL EntitlementV1_RegisterPurchaseAndActivationBySN(int entitlementProjectId, char* serialNumber, IAsyncStatus* status) = 0;
	virtual bool RGSC_CALL EntitlementV1_GetValidateContentPlayerAge(const char* contentName, IAsyncStatus* status) = 0;
	virtual bool RGSC_CALL EntitlementV1_IsEntitledToContent(const char* skuName) = 0;
	virtual bool RGSC_CALL EntitlementV1_GetActivationState(const char* skuName, bool* bIsOwned, char (&serialKey)[256], bool* bIsActivated) = 0;
	virtual bool RGSC_CALL EntitlementV1_GetContentNameBySku(const char * skuName, char * contentName, unsigned int contentNameLen) = 0;
	virtual bool RGSC_CALL EntitlementV1_GetSkuDownloadURL(const char* skuName, char* downloadUrl, unsigned int downloadUrlBufLen, IAsyncStatus* status) = 0;

#endif // RSG_CPU_X86
};

typedef ICommerceManagerV5 ICommerceManagerLatestVersion;
#define IID_ICommerceManagerLatestVersion IID_ICommerceManagerV5

} // namespace

#endif // COMMERCE_INTERFACE_H
