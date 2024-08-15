#ifndef TITLE_ID_INTERFACE_H
#define TITLE_ID_INTERFACE_H

#include "rgsc_common.h"

#include <cstring>

namespace rgsc
{

// =====================================================================================================================
// TitleId Interface
// =====================================================================================================================

// This class is designed to be an extensible version of a plain-old-data structure.
class ITitleId : public IRgscUnknown
{
public:
	enum RosEnvironment
	{
		RLROS_ENV_UNKNOWN = -1,
		RLROS_ENV_RAGE,
		RLROS_ENV_DEV,
		RLROS_ENV_CERT,
		RLROS_ENV_PROD,
		RLROS_ENV_CERT_2,
		RLROS_ENV_CI_RAGE
	};

	enum Platform
	{
		PLATFORM_INVALID = 0,
		PLATFORM_PC,
		PLATFORM_STEAM,
		PLATFORM_ONLIVE,
		PLATFORM_NHN,
		PLATFORM_MAC_STEAM,
		PLATFORM_MAC_APP_STORE,
		PLATFORM_VIVEPORT,
		PLATFORM_OCULUS,
		PLATFORM_EPIC,
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};


#ifdef __cplusplus
extern "C" {
#endif

static const RGSC_IID IID_ITitleIdV1 = {0x4a71aca, 0xca82, 0x4ff4, {0x9a, 0xd1, 0xfa, 0x85, 0xa6, 0x9, 0x46, 0x54}};
static const RGSC_IID IID_ITitleIdV2 = {0x877dd30f, 0x5d57, 0x42a5, {0x9f, 0x58, 0x57, 0x54, 0x1a, 0xd6, 0x6c, 0x2a}};
static const RGSC_IID IID_ITitleIdV3 = {0x8f7949d6, 0x8284, 0x4290, {0x99, 0xa, 0xed, 0xad, 0x3c, 0xad, 0x13, 0xbf}};
static const RGSC_IID IID_ITitleIdV4 = {0x92700628, 0x6ad7, 0x4d66, {0xba, 0x75, 0x64, 0x71, 0xc4, 0xd0, 0x99, 0xd0}};
static const RGSC_IID IID_ITitleIdV5 = {0x4a7dc72, 0xc5af, 0x441c, {0xaf, 0xd1, 0x64, 0xd1, 0x58, 0x81, 0xa3, 0x79}};
static const RGSC_IID IID_ITitleIdV6 = {0xbe19a5ac, 0x48a3, 0x4372, {0x8f, 0x3b, 0x99, 0x17, 0x13, 0xd6, 0xd7, 0x35}};
static const RGSC_IID IID_ITitleIdV7 = { 0x5885c50b, 0x49a8, 0x4ec3, { 0x83, 0xfe, 0xe9, 0x9b, 0xf0, 0x2a, 0x79, 0x2e }};
static const RGSC_IID IID_ITitleIdV8 = { 0xba324c6c, 0x3699, 0x4dde, { 0x9c, 0xd8, 0xff, 0x3f, 0x9c, 0x88, 0xfa, 0x65 } };
static const RGSC_IID IID_ITitleIdV9 = {0x3b90579b, 0x4001, 0x4d4f,{0xb3, 0xd0, 0xd2, 0x45, 0xe7, 0x84, 0xa, 0xfc}};
static const RGSC_IID IID_ITitleIdV10 = { 0xcdd009ed, 0x2e37, 0x4678, { 0xa1, 0x4f, 0x75, 0x71, 0x25, 0xbc, 0x98, 0x4b} };

#ifdef __cplusplus
}
#endif

//! Version 1 of the title id interface.
class ITitleIdV1 : public ITitleId
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Returns the ROS title name for the current title.
	virtual const char* RGSC_CALL GetRosTitleName() const = 0;

	//! Returns the ROS environment for the current title.
	virtual RosEnvironment RGSC_CALL GetRosEnvironment() const = 0;

	//! Returns the ROS title version for the current title.
	virtual int RGSC_CALL GetRosTitleVersion() const = 0;

	//! Returns the ROS shared secret for the current title.
	virtual const char* RGSC_CALL GetRosSharedSecret() const = 0;

	//! Returns a filesystem-friendly ASCII name for the title.
	/**
		This name will be used as the name of the title's save data directory,
		i.e. Documents/Rockstar Games\(game name). The name must not
		contain characters that are invalid	to the OS's file system.\n
		Examples of invalid characters: \, /, *, ?, <, >, |, "
	*/
	virtual const char* RGSC_CALL GetTitleDirectoryName() const = 0;
};

//! Version 2 of the title id interface.
class ITitleIdV2 : public ITitleIdV1
{
public:
	//! Returns the platform the title is running on.
	virtual Platform RGSC_CALL GetPlatform() const = 0;

	//! Returns the root path where Social Club and Title data is stored on OnLive builds.
	/**
		The default root directory is the user's Documents directory. On OnLive platforms,
		they require a different root which the title can specify here.
		If the function returns NULL, or the platform is not PLATFORM_ONLIVE, the default root directory is used.
		Note: this function only has affect when the platform is set to PLATFORM_ONLIVE.
	*/
	virtual const char* RGSC_CALL GetRootDataDirectory() const = 0;
};

//! Version 3 of the title id interface.
class ITitleIdV3 : public ITitleIdV2
{
public:
	//! Returns the ROS title secrets for the current title.
	virtual const char* RGSC_CALL GetRosTitleSecrets() const = 0;

	//! Returns the SC (Social Club) version.
	virtual int RGSC_CALL GetScVersion() const = 0;
};

//! Version 4 of the title id interface.
class ITitleIdV4 : public ITitleIdV3
{
public:
	//! Returns the base64 encoded Steam Auth Token (only valid on Steam platform).
	virtual const char* RGSC_CALL GetSteamAuthTicket() const = 0;

	//! Returns the Steam App Id (only valid on Steam platform).
	virtual u32 RGSC_CALL GetSteamAppId() const = 0;
};

//! Version 5 of the title id interface.
class ITitleIdV5 : public ITitleIdV4
{
public:
	//! Returns the Mac App Store receipt (only valid on MacAppStore platform).
	/**
		Note: the data contained in receipt must be valid until you call IRgsc::Init
	*/
	virtual void RGSC_CALL GetMacAppStoreReceipt(u8** receipt, int* len) const = 0;
};

//! Version 6 of the title id interface.
class ITitleIdV6 : public ITitleIdV5
{
public:
	//! Returns the SteamId for the user currently signed into Steam (only valid on Steam platform).
	virtual u64 RGSC_CALL GetSteamId() const = 0;

	//! Returns the public RSA key which is used in the internal rlRosTitleId.
	virtual void RGSC_CALL GetPublicRsaKey(const u8** publicRsaKey, unsigned* len) const = 0;
};

//! Version 7 of the title id interface.
class ITitleIdV7 : public ITitleIdV6
{
public:
	//! Returns the Steam Persona (Community Name) for the user currently signed into Steam (only valid on Steam platform).
	virtual const char* RGSC_CALL GetSteamPersona() const = 0;
};

//! Version 8 of the title id interface
class ITitleIdV8
{
public:
	//! Returns the hostname prefix that should be used for HTTP requests.
	//	i.e. intead of ros.rockstargames.com, use {title}-ros.rockstargames.com
	virtual const char* RGSC_CALL GetHostnamePrefix() const = 0;
};

//! Version 9 of the title id interface
class ITitleIdV9
{
public:
	//! Gets the Epic player name
	virtual const char* RGSC_CALL GetEpicPlayerName() const = 0;

	//! Gets the Epic account id
	virtual const char* RGSC_CALL GetEpicAccountId() const = 0;

	//! Gets the Epic access token
	virtual const char* RGSC_CALL GetEpicAccessToken() const = 0;

	//! Gets the Epic product id
	virtual const char* RGSC_CALL GetEpicProductId() const = 0;

	//! Gets the Epic sandbox id
	virtual const char* RGSC_CALL GetEpicSandboxId() const = 0;
};

//! Version 10 of the title id interface
class ITitleIdV10
{
public:
	//! Enables the usage of the staging version of GetRosEnvironment.
	//	Can also be enabled using -netUseStagingEnv
	virtual bool RGSC_CALL UseStagingEnvironment() const = 0;
};

typedef ITitleIdV9 ITitleIdLatestVersion;
#define IID_ITitleIdLatestVersion IID_ITitleIdV9

//! Concrete class that implements the ITitleIdV7 interface.
class TitleIdV7 : public ITitleIdV7
{
public:

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		IRgscUnknown *pUnknown = NULL;

		if(ppvObject == NULL)
		{
			return RGSC_INVALIDARG;
		}

		if(riid == IID_IRgscUnknown)
		{
			pUnknown = static_cast<ITitleId*>(this);
		}
		else if(riid == IID_ITitleIdV1)
		{
			pUnknown = static_cast<ITitleIdV1*>(this);
		}
		else if(riid == IID_ITitleIdV2)
		{
			pUnknown = static_cast<ITitleIdV2*>(this);
		}
		else if(riid == IID_ITitleIdV3)
		{
			pUnknown = static_cast<ITitleIdV3*>(this);
		}
		else if(riid == IID_ITitleIdV4)
		{
			pUnknown = static_cast<ITitleIdV4*>(this);
		}
		else if(riid == IID_ITitleIdV5)
		{
			pUnknown = static_cast<ITitleIdV5*>(this);
		}
		else if(riid == IID_ITitleIdV6)
		{
			pUnknown = static_cast<ITitleIdV6*>(this);
		}
		else if(riid == IID_ITitleIdV7)
		{
			pUnknown = static_cast<ITitleIdV7*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	TitleIdV7()
	{
		m_RosEnvironment = RLROS_ENV_UNKNOWN;
		m_RosTitleVersion = 0;
		m_ScVersion = 0;
		m_Platform = PLATFORM_INVALID;
		memset(m_RosTitleName, 0, sizeof(m_RosTitleName));
		memset(m_RosTitleSecrets, 0, sizeof(m_RosTitleSecrets));
		memset(m_PublicRsaKey, 0, sizeof(m_PublicRsaKey));
		memset(m_TitleDirectoryName, 0, sizeof(m_TitleDirectoryName));
		memset(m_RootDataDirectory, 0, sizeof(m_RootDataDirectory));
		memset(m_SteamAuthTicket, 0, sizeof(m_SteamAuthTicket));
		memset(m_SteamPersonaName, 0, sizeof(m_SteamPersonaName));
		m_PublicRsaKeyLength = 0;
		m_SteamAppId = 0;
		m_SteamId = 0;
		m_MacAppStoreReceipt = NULL;
		m_MacAppStoreReceiptLength = 0;
	}

	virtual const char* RGSC_CALL GetRosTitleName() const
	{
		return m_RosTitleName;
	}

	virtual void RGSC_CALL SetRosTitleName(const char* rosTitleName)
	{
		strncpy_s(m_RosTitleName, sizeof(m_RosTitleName), rosTitleName, sizeof(m_RosTitleName) - 1);
	}

	virtual RosEnvironment RGSC_CALL GetRosEnvironment() const
	{
		return m_RosEnvironment;
	}

	virtual void RGSC_CALL SetRosEnvironment(RosEnvironment rosEnvironment)
	{
		m_RosEnvironment = rosEnvironment;
	}

	virtual int RGSC_CALL GetRosTitleVersion() const
	{
		return m_RosTitleVersion;
	}

	virtual void RGSC_CALL SetRosTitleVersion(int rosTitleVersion)
	{
		m_RosTitleVersion = rosTitleVersion;
	}

	virtual int RGSC_CALL GetScVersion() const
	{
		return m_ScVersion;
	}

	virtual void RGSC_CALL SetScVersion(int scVersion)
	{
		m_ScVersion = scVersion;
	}

	virtual const char* RGSC_CALL GetTitleDirectoryName() const
	{
		return m_TitleDirectoryName;
	}

	virtual void RGSC_CALL SetTitleDirectoryName(const char* titleDirectoryName)
	{
		strncpy_s(m_TitleDirectoryName, sizeof(m_TitleDirectoryName), titleDirectoryName, sizeof(m_TitleDirectoryName) - 1);
	}

	virtual const char* RGSC_CALL GetRosSharedSecret() const
	{
		// no longer used
		return NULL;
	}

	virtual Platform RGSC_CALL GetPlatform() const
	{
		return m_Platform;
	}

	virtual void RGSC_CALL SetPlatform(Platform platform)
	{
		m_Platform = platform;
	}

	virtual const char* RGSC_CALL GetRootDataDirectory() const
	{
		return m_RootDataDirectory;
	}

	virtual void RGSC_CALL SetRootDataDirectory(const char* rootDataDirectory)
	{
		strncpy_s(m_RootDataDirectory, sizeof(m_RootDataDirectory), rootDataDirectory, sizeof(m_RootDataDirectory) - 1);
	}

	virtual const char* RGSC_CALL GetRosTitleSecrets() const
	{
		return m_RosTitleSecrets;
	}

	virtual void RGSC_CALL SetRosTitleSecrets(const char* rosTitleSecrets)
	{
		strncpy_s(m_RosTitleSecrets, sizeof(m_RosTitleSecrets), rosTitleSecrets, sizeof(m_RosTitleSecrets) - 1);
	}

	virtual const char* RGSC_CALL GetSteamAuthTicket() const
	{
		return m_SteamAuthTicket;
	}

	virtual void RGSC_CALL SetSteamAuthTicket(const char* steamAuthTicket)
	{
		strncpy_s(m_SteamAuthTicket, sizeof(m_SteamAuthTicket), steamAuthTicket, sizeof(m_SteamAuthTicket) - 1);
	}

	virtual void RGSC_CALL GetMacAppStoreReceipt(u8** receipt, int* len) const
	{
		*receipt = m_MacAppStoreReceipt;
		*len = m_MacAppStoreReceiptLength;
	}

	virtual void RGSC_CALL SetMacAppStoreReceipt(u8* receipt, int len)
	{
		m_MacAppStoreReceipt = receipt;
		m_MacAppStoreReceiptLength = len;
	}

	virtual u32 RGSC_CALL GetSteamAppId() const
	{
		return m_SteamAppId;
	}

	virtual void RGSC_CALL SetSteamAppId(u32 steamAppId)
	{
		m_SteamAppId = steamAppId;
	}

	virtual u64 RGSC_CALL GetSteamId() const
	{
		return m_SteamId;
	}

	virtual void RGSC_CALL SetSteamId(u64 steamId)
	{
		m_SteamId = steamId;
	}

	virtual void RGSC_CALL GetPublicRsaKey(const u8** publicRsaKey, unsigned* len) const
	{
		if(m_PublicRsaKeyLength == 0)
		{
			*publicRsaKey = NULL;
		}
		else
		{
			*publicRsaKey = m_PublicRsaKey;
		}
		*len = m_PublicRsaKeyLength;
	}

	virtual void RGSC_CALL SetPublicRsaKey(const u8* publicRsaKey, unsigned len)
	{
		if((len > 0 && len <= sizeof(m_PublicRsaKey)) && (publicRsaKey != NULL))
		{
			memcpy(m_PublicRsaKey, publicRsaKey, len);
			m_PublicRsaKeyLength = len;
		}
		else
		{
			m_PublicRsaKeyLength = 0;
		}
	}

	//! Returns the Steam Persona (Community Name) for the user currently signed into Steam (only valid on Steam platform).
	virtual const char* RGSC_CALL GetSteamPersona() const
	{
		return m_SteamPersonaName;
	}

	virtual void RGSC_CALL SetSteamPersona(const char* steamPersona)
	{
		strncpy_s(m_SteamPersonaName, sizeof(m_SteamPersonaName), steamPersona, sizeof(m_SteamPersonaName) - 1);
	}

protected:
	char m_RosTitleName[32];
	RosEnvironment m_RosEnvironment;
	int m_RosTitleVersion;
	int m_ScVersion;
	char m_RosTitleSecrets[128];
	u8 m_PublicRsaKey[256];
	unsigned m_PublicRsaKeyLength;
	char m_TitleDirectoryName[64];
	Platform m_Platform;
	char m_RootDataDirectory[RGSC_MAX_PATH];
	char m_SteamAuthTicket[RGSC_STEAM_TICKET_ENCODED_BUF_SIZE];
	u32 m_SteamAppId;
	u64 m_SteamId;
	u8* m_MacAppStoreReceipt;
	int m_MacAppStoreReceiptLength;
	char m_SteamPersonaName[RGSC_STEAM_MAX_PERSONA_BUF_SIZE];
};

class TitleIdV8 : public ITitleIdV8, public TitleIdV7
{
public:

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = TitleIdV7::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_ITitleIdV8)
		{
			*ppvObject = static_cast<ITitleIdV8*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	TitleIdV8() 
		: TitleIdV7()
	{
		m_HostNamePrefix[0] = '\0';
	}

	virtual const char* RGSC_CALL GetHostnamePrefix() const
	{
		return m_HostNamePrefix;
	}

	virtual void SetHostnamePrefix(const char* hostnamePrefix)
	{
		strcpy_s(m_HostNamePrefix, sizeof(m_HostNamePrefix), hostnamePrefix);
	}

private:

	char m_HostNamePrefix[64];

};

class TitleIdV9 : public ITitleIdV9, public TitleIdV8
{
public:

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = TitleIdV8::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_ITitleIdV9)
		{
			*ppvObject = static_cast<ITitleIdV9*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	TitleIdV9() 
		: TitleIdV8()
		, m_EpicPlayerName(nullptr)
		, m_EpicAccountId(nullptr)
		, m_EpicAccessToken(nullptr)
		, m_EpicProductId(nullptr)
		, m_EpicSandboxId(nullptr)
	{

	}

	virtual ~TitleIdV9()
	{
		if(m_EpicPlayerName)
		{
			RgscStringFree(m_EpicPlayerName);
			m_EpicPlayerName = nullptr;
		}

		if(m_EpicAccountId)
		{
			RgscStringFree(m_EpicAccountId);
			m_EpicAccountId = nullptr;
		}

		if(m_EpicAccessToken)
		{
			RgscStringFree(m_EpicAccessToken);
			m_EpicAccessToken = nullptr;
		}

		if (m_EpicProductId)
		{
			RgscStringFree(m_EpicProductId);
			m_EpicProductId = nullptr;
		}

		if (m_EpicSandboxId)
		{
			RgscStringFree(m_EpicSandboxId);
			m_EpicSandboxId = nullptr;
		}
	}

	virtual const char* RGSC_CALL GetEpicPlayerName() const
	{
		return m_EpicPlayerName ? m_EpicPlayerName : "";
	}

	virtual void RGSC_CALL SetEpicPlayerName(const char* name)
	{
		if(m_EpicPlayerName)
		{
			RgscStringFree(m_EpicPlayerName);
		}

		m_EpicPlayerName = RgscStringDuplicate(name);
	}

	virtual const char* RGSC_CALL GetEpicAccountId() const
	{
		return m_EpicAccountId ? m_EpicAccountId : "";
	}

	virtual void RGSC_CALL SetEpicAccountId(const char* accountId)
	{
		if(m_EpicAccountId)
		{
			RgscStringFree(m_EpicAccountId);
		}

		m_EpicAccountId = RgscStringDuplicate(accountId);
	}

	virtual const char* RGSC_CALL GetEpicAccessToken() const
	{
		return m_EpicAccessToken ? m_EpicAccessToken : "";
	}

	virtual void RGSC_CALL SetEpicAccessToken(const char* epicAccessToken)
	{
		if(m_EpicAccessToken)
		{
			RgscStringFree(m_EpicAccessToken);
		}

		m_EpicAccessToken = RgscStringDuplicate(epicAccessToken);
	}

	virtual const char* RGSC_CALL GetEpicProductId() const
	{
		return m_EpicProductId ? m_EpicProductId : "";
	}

	virtual void RGSC_CALL SetEpicProductId(const char* epicProductId)
	{
		if (m_EpicProductId)
		{
			RgscStringFree(m_EpicProductId);
		}

		m_EpicProductId = RgscStringDuplicate(epicProductId);
	}

	virtual const char* RGSC_CALL GetEpicSandboxId() const
	{
		return m_EpicSandboxId ? m_EpicSandboxId : "";
	}

	virtual void RGSC_CALL SetEpicSandboxId(const char* sandboxId)
	{
		if (m_EpicSandboxId)
		{
			RgscStringFree(m_EpicSandboxId);
		}

		m_EpicSandboxId = RgscStringDuplicate(sandboxId);
	}
	
private:
	char* m_EpicPlayerName;
	char* m_EpicAccountId;
	char* m_EpicAccessToken;
	char* m_EpicProductId;
	char* m_EpicSandboxId;
};

class TitleIdV10 : public ITitleIdV10, public TitleIdV9
{
public:

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = TitleIdV9::QueryInterface(riid, ppvObject);

		if (hr == RGSC_NOINTERFACE && riid == IID_ITitleIdV10)
		{
			*ppvObject = static_cast<ITitleIdV10*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	TitleIdV10()
		: TitleIdV9()
		, m_UseStagingEnv(false)
	{
	}

	void SetUseStagingEnvironment(bool useStaging)
	{
		m_UseStagingEnv = useStaging;
	}

	virtual bool RGSC_CALL UseStagingEnvironment() const
	{
		return m_UseStagingEnv;
	}

private:
	bool m_UseStagingEnv;
};

typedef TitleIdV10 TitleId;

} // namespace

#endif // TITLE_ID_INTERFACE_H
