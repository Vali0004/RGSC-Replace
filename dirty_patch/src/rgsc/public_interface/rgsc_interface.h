#ifndef RGSC_INTERFACE_H
#define RGSC_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

class IConfiguration;
class ITitleId;
class IRgscDelegate;
class IAchievementManager;
class IPlayerManager;
class IPresenceManager;
class ICommerceManager;
class IProfileManager;
class IFileSystem;
class IFileDelegate;
class ITaskManager;
class IRgscUi;
class ITelemetry;
class IGamepadManager;
class INetwork;
class ICloudSaveManager;
class IGamerPicManager;

class IRgsc : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

static const RGSC_IID IID_IRgscV1 = {0x672b22e1, 0xf777, 0x4957, {0xa3, 0xa4, 0x6c, 0xa0, 0xcd, 0xf6, 0x4b, 0x90}};
static const RGSC_IID IID_IRgscV2 = {0x14c231fc, 0xeb34, 0x4a64, {0xb5, 0x32, 0xa, 0xfb, 0xa9, 0xf, 0xf2, 0xf4}};
static const RGSC_IID IID_IRgscV3 = {0x366f0f01, 0xc0c9, 0x47d4, {0xbe, 0x39, 0xf9, 0x63, 0x57, 0xb4, 0x19, 0x69}};
static const RGSC_IID IID_IRgscV4 = {0x726c2aca, 0x58e2, 0x4f46, {0xa3, 0x60, 0xdd, 0xf5, 0x60, 0x69, 0x5c, 0x65}};
static const RGSC_IID IID_IRgscV5 = {0xc17f6cff, 0x23dc, 0x4b4d, {0x96, 0x6e, 0x9a, 0x3c, 0xb, 0xf1, 0x67, 0xec}};
static const RGSC_IID IID_IRgscV6 = {0xac23727, 0xe98c, 0x456d, {0x8c, 0xb6, 0xa2, 0x43, 0x43, 0xb8, 0x7c, 0xf7}};
static const RGSC_IID IID_IRgscV7 = {0x97f7a667, 0x70f7, 0x4249, { 0x85, 0x9c, 0xdb, 0x4d, 0x97, 0x71, 0x98, 0x5b}};
static const RGSC_IID IID_IRgscV8 = {0x40807ac1, 0x836b, 0x4461, {0x8d, 0xf3, 0xc7, 0x86, 0x7e, 0xe0, 0x7e, 0x9a}};
static const RGSC_IID IID_IRgscV9 = {0x123846d6, 0x26ae, 0x4cbf,{0xaf, 0x9e, 0x33, 0x2a, 0x48, 0x61, 0x75, 0xd1}};
static const RGSC_IID IID_IRgscV10 = {0x44805574, 0xc36c, 0x423b,{0xb2, 0xb7, 0x2, 0xd5, 0xe5, 0x62, 0x91, 0xdf}};

#ifdef __cplusplus
}
#endif

//! Main interface to the RGSC platform.
//! \example rlpc.cpp
//! \example rlpc.h
class IRgscV1 : public IRgsc
{
public:
	//! Initializes the systems that make up the RGSC platform.
	/**
	  \param
		  titleId - id of the current title
	  \param
		  language - used for localizing text displayed by the built-in user interface
	  \param
		  dlgt - delegate object that receives unsolicited messages from the platform.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL Init(ITitleId* titleId, RgscLanguage language, IRgscDelegate* dlgt) = 0;

	//! Shuts down the RGSC platform and frees resources.
	virtual void RGSC_CALL Shutdown() = 0;

	//! Performs processing required by the platform.\n
	//! This should be called every frame.
	virtual void RGSC_CALL Update() = 0;

	//! Returns the interface to the achievement manager.
	virtual IAchievementManager* RGSC_CALL GetAchievementManager() = 0;

	//! Returns the interface to the profile manager.
	virtual IProfileManager* RGSC_CALL GetProfileManager() = 0;

	//! Returns the interface to the file system manager.
	virtual IFileSystem* RGSC_CALL GetFileSystem() = 0;

	//! Returns the interface to the UI manager.
	virtual IRgscUi* RGSC_CALL GetUiInterface() = 0;
};

class IRgscV2 : public IRgscV1
{
public:
	using IRgscV1::Init;

	//! Initializes the systems that make up the RGSC platform.
	/**
	  \param
		  configuration - configuration options
	  \param
		  titleId - id of the current title
	  \param
		  language - used for localizing text displayed by the built-in user interface
	  \param
		  dlgt - delegate object that receives unsolicited messages from the platform.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL Init(IConfiguration* config, ITitleId* titleId, RgscLanguage language, IRgscDelegate* dlgt) = 0;

	//! Returns the interface to the friend manager.
	virtual IPlayerManager* RGSC_CALL GetPlayerManager() = 0;

	//! Returns the interface to the task manager.
	virtual ITaskManager* RGSC_CALL GetTaskManager() = 0;

	//! Returns the interface to the presence manager.
	virtual IPresenceManager* RGSC_CALL GetPresenceManager() = 0;

	//! Returns the interface to the commerce manager.
	virtual ICommerceManager* RGSC_CALL GetCommerceManager() = 0;
};

class IRgscV3 : public IRgscV2
{
public:

	//! Sets the delegate for file operations.
	/**
	  \remark
	  This has a special purpose to support Korean internet cafes where
	  profile data needs to be uploaded to their cloud system.
	*/
	virtual void RGSC_CALL SetFileDelegate(IFileDelegate* dlgt) = 0;
};

class IRgscV4 : public IRgscV3
{
public:
	//! Sets the updated steam auth ticket
	/**
	  \remark
	  Updates the steam auth ticket and length within the cached titleid
	*/
	virtual void RGSC_CALL SetSteamAuthTicket(const char* steamAuthTicket) = 0;
};

class IRgscV5 : public IRgscV4
{
public:
	//! Returns the interface to the Telemetry Manager
	virtual ITelemetry* RGSC_CALL GetTelemetry() = 0;

	//! Event fired by a client (i.e. launcher) when a games crash is detected, allowing for post-crash actions like unadvertising matchmaking.
	/**
		\remark
		The actionToTake param represents bit fields of shutdown actions. See OnGameCrashActionFlags
	*/
	virtual RGSC_HRESULT RGSC_CALL OnGameCrashed(u64 actionToTake) = 0;

	//! Returns TRUE if the RGSC instance is ready to shutdown (i.e. no pending critical tasks, telemetry flushes, etc)
	virtual bool RGSC_CALL IsReadyToShutdown() = 0;
};

class IRgscV6 : public IRgscV5
{
public:
	//! Returns the interface to the Gamepads container.
	virtual IGamepadManager* RGSC_CALL GetGamepadMgr() = 0;

	//! Returns the network interface.
	virtual INetwork* RGSC_CALL GetNetworkInterface() = 0;
};

class IRgscV7 : public IRgscV6
{
public:
	//! Returns the interface to the Cloud Save manager
	virtual ICloudSaveManager* RGSC_CALL GetCloudSaveManager() = 0;

	//! Returns the interface to the Gamer Pic manager
	virtual IGamerPicManager* RGSC_CALL GetGamerPicManager() = 0;
};

class IRgscV8 : public IRgscV7
{
public:
	//! Updates the Steam persona, overriding the value from ITitleId.
	virtual void RGSC_CALL SetSteamPersona(const char* steamPersona) = 0;

	//! Updates the Steam user id, overriding the value from ITitleId.
	virtual void RGSC_CALL SetSteamId(u64 steamId) = 0;

	//! Updates the Steam application id, overriding the value from ITitleId.
	virtual void RGSC_CALL SetSteamAppId(u32 steamAppId) = 0;
};

class IRgscV9 : public IRgscV8
{
public:
	//! Notifies the SDK that a title is now active.
	virtual void RGSC_CALL SetTitleActive(const RgscTitleId titleId, bool isActive) = 0;
};

class IRgscV10 : public IRgscV9
{
public:
	//! Sets the Epic player name, overriding the value from ITitleId
	virtual void RGSC_CALL SetEpicPlayerName(const char* name) = 0;

	//! Sets the Epic account id, overriding the value from ITitleId
	virtual void RGSC_CALL SetEpicAccountId(const char* accountId) = 0;

	//! Sets the Epic access token, overriding the value from ITitleId
	virtual void RGSC_CALL SetEpicAccessToken(const char* epicAccessToken) = 0;

	//! Sets the Epic product id, overriding the value from ITitleId
	virtual void RGSC_CALL SetEpicProductId(const char* productId) = 0;

	//! Sets the Epic sandbox id, overriding the value from ITitleId
	virtual void RGSC_CALL SetEpicSandboxId(const char* sandboxId) = 0;
};

typedef IRgscV10 IRgscLatestVersion;
#define IID_IRgscLatestVersion IID_IRgscV10

// this is the one and only exported function (see rgsc.def)
extern "C" IRgsc* GetRgscInterface();

} // namespace rgsc

#endif // RGSC_INTERFACE_H
