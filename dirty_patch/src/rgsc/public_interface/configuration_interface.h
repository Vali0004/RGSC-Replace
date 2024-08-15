#ifndef CONFIGURATION_INTERFACE_H
#define CONFIGURATION_INTERFACE_H

#include "rgsc_common.h"
#include <cstring>

namespace rgsc
{

// =====================================================================================================================
// Configuration Interface
// =====================================================================================================================

// This class is designed to be an extensible version of a plain-old-data structure.
class IConfiguration : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IConfigurationV1	= {0x1056f2a4, 0x4180, 0x4185, {0x8a, 0x9f, 0xba, 0x6f, 0x1c, 0x2, 0xc9, 0x62}};
extern "C" static const RGSC_IID IID_IConfigurationV2	= {0x4d231e21, 0x496b, 0x4c17, {0x80, 0xa2, 0x83, 0x88, 0xb4, 0x88, 0x17, 0xae}};
extern "C" static const RGSC_IID IID_IConfigurationV3	= {0x710e48bb, 0x272, 0x43d4, {0xab, 0x6d, 0xaf, 0xab, 0x30, 0xde, 0x55, 0x29}};
extern "C" static const RGSC_IID IID_IConfigurationV4	= {0x515184f8, 0x4e86, 0x465c, {0x92, 0xef, 0x62, 0x63, 0x3d, 0xae, 0xee, 0x4f}};
extern "C" static const RGSC_IID IID_IConfigurationV5	= {0x813f07c7, 0x6198, 0x4d37, {0xb3, 0xb4, 0xd8, 0x98, 0x18, 0xcf, 0x5a, 0x53}};
extern "C" static const RGSC_IID IID_IConfigurationV6	= {0x2bf6cb6, 0x82e6, 0x4b28, {0x8c, 0xe4, 0x6b, 0x93, 0x44, 0xf, 0x1a, 0x47}};
extern "C" static const RGSC_IID IID_IConfigurationV7	= {0x11f927fa, 0x3b12, 0x4adf, {0xa3, 0xae, 0xa2, 0x33, 0x9b, 0xc7, 0xe, 0xc8}};
extern "C" static const RGSC_IID IID_IConfigurationV8	= {0x71281dc0, 0x7c49, 0x48d0, {0xbc, 0x4d, 0xf, 0x9e, 0xa3, 0xa6, 0xf3, 0x20}};
extern "C" static const RGSC_IID IID_IConfigurationV9	= {0x84972a90, 0x8a9b, 0x4614, {0xb8, 0xf5, 0x9a, 0xa3, 0xe0, 0x78, 0x43, 0xa}};
extern "C" static const RGSC_IID IID_IConfigurationV10	= {0xa5b3558a, 0x6a56, 0x4c3f, {0x9f, 0x10, 0xe1, 0x97, 0x25, 0x3d, 0x5c, 0xc3}};
extern "C" static const RGSC_IID IID_IConfigurationV11	= {0x2b91d62f, 0xc116, 0x40c6, { 0xbe, 0x10, 0x18, 0xc2, 0x1, 0xbc, 0xec, 0x1f}};

//! Version 1 of the configuration interface.
class IConfigurationV1 : public IConfiguration
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Returns the command line parameters.
	virtual int RGSC_CALL GetCommandLineParamCount() const = 0;
	virtual char** RGSC_CALL GetCommandLineParams() const = 0;
};

//! Concrete class that implements the IConfigurationV1 interface.
class ConfigurationV1 : public IConfigurationV1
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
			pUnknown = static_cast<IConfiguration*>(this);
		}
		else if(riid == IID_IConfigurationV1)
		{
			pUnknown = static_cast<IConfigurationV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	ConfigurationV1()
	{
		m_CommandLineParamCount = 0;
		m_CommandLineParams = NULL;
	}

	//! Returns the command line parameters.
	virtual char** RGSC_CALL GetCommandLineParams() const
	{
		return m_CommandLineParams;
	}

	virtual int RGSC_CALL GetCommandLineParamCount() const
	{
		return m_CommandLineParamCount;
	}

	virtual void RGSC_CALL SetCommandLineParams(int argc, char** argv)
	{
		m_CommandLineParamCount = argc;
		m_CommandLineParams = argv;
	}

protected:
	int m_CommandLineParamCount;
	char **m_CommandLineParams;
};

//! Version 2 of the configuration interface.
class IConfigurationV2 : public IConfigurationV1
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Returns the command line parameters.
	virtual int RGSC_CALL GetCommandLineParamCount() const = 0;
	virtual char** RGSC_CALL GetCommandLineParams() const = 0;

	virtual bool RGSC_CALL IsOfflineOnlyMode() const = 0;
	virtual bool RGSC_CALL IsPatchingEnabled() const = 0;
};

//! Version 3 of the configuration interface.
class IConfigurationV3 : public IConfigurationV2
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Returns the command line parameters.
	virtual int RGSC_CALL GetCommandLineParamCount() const = 0;
	virtual char** RGSC_CALL GetCommandLineParams() const = 0;

	virtual bool RGSC_CALL IsOfflineOnlyMode() const = 0;
	virtual bool RGSC_CALL IsPatchingEnabled() const = 0;
	virtual bool RGSC_CALL AreLocalProfilesEnabled() const = 0;
};

//! Version 4 of the configuration interface.
class IConfigurationV4
{
public:
	virtual bool RGSC_CALL HandleAutoSignIn() const = 0;
	virtual bool RGSC_CALL IsLauncher() const = 0;
};

//! Version 5 of the configuration interface.
class IConfigurationV5
{
public:
	virtual const char* RGSC_CALL GetAdditionalSessionAttr() const = 0;
	virtual const char* RGSC_CALL GetAdditionalJoinAttr() const = 0;
	virtual const char* RGSC_CALL GetMetaDataPath() const = 0;
};

//! Version 6 of the configuration interface.
class IConfigurationV6
{
public:

	enum GamepadSupport
	{
		// don't change or remove these values or you'll break existing games - we can add new ones.
		GAMEPADS_DISABLED = 0,	 // All gamepad input is ignored
		GAMEPADS_SUPPORTED = 1,  // Gamepad input is handled within the SDK (default)
		GAMEPADS_MARSHALLED = 2,  // Gamepad input is marshalled from the game client.
	};

	virtual GamepadSupport RGSC_CALL GetGamePadSupport() const = 0;
};

//! Version 7 of the configuration interface.
class IConfigurationV7
{
public:

	//! For applications that support multiple window handles, they can be passed via
	//  the configuration interface so that the Rgsc_Input windows message handlers can be aware.
	virtual WindowHandle* RGSC_CALL GetAdditionalWindowHandles() const = 0;
	virtual unsigned RGSC_CALL GetNumAdditionalWindowHandles() const = 0;
};

//! Version 8 of the configuration interface.
class IConfigurationV8
{
public:

	// Certain features like signin transfer files, presence, achievements, friends, etc were explicitly turned off
	// for older titles like LA Noire based on title id as their services could not support it. Then, when we added support for 
	// Launcher builds and added newer titles, this became more complicated as both a Launcher and a Game shared a title id, but
	// functioned as a completely different product. Finally, when new builds of older titles were released, they could be patched 
	// to support new functionality that other builds of the same title could not support. We expose the ability to enable or disable these
	// features using FeatureBehaviour. Older titles will not set feature behaviour, and will use the default values. However,
	// a new title could opt in to the feature to force it on or off.
	enum FeatureBehaviour
	{
		DEFAULT = -1,
		DISABLED = 0,
		ENABLED,
	};

	//! Allows to override the default handling of signin transfer files.
	//	   Disabled: LANoire, MaxPayne3, Launchers
	//     Enabled: GTAV+ Onwards
	virtual FeatureBehaviour RGSC_CALL GetSignIntransferBehaviour() const = 0;

	//! Allows to override the default handling of managing social club friends.
	//	   Disabled: Launchers, LANoire
	//	   Enabled: All other titles.
	virtual FeatureBehaviour RGSC_CALL GetFriendsBehaviour() const = 0;

	//! Allows to override the default handling of connecting to presence.
	//	   Disabled: LANoire, Titles Newer than GTAV
	//     Enabled: GTAV, MaxPayne3
	virtual FeatureBehaviour RGSC_CALL GetPresenceBehaviour() const = 0;

	//! Allows to override the default handling of achievement support.
	//	   Disabled: LANoire, Launchers
	//     Enabled: All other titles.
	virtual FeatureBehaviour RGSC_CALL GetAchievementBehaviour() const = 0;

	//! Allows to override the default handling of a change of internet connection state.
	//	   Disabled: LANoire, MaxPayne3, GTAV Launcher
	//     Enabled: GTAV Game, Non-GTAV Launchers, Newer Titles
	virtual FeatureBehaviour RGSC_CALL GetConnectionStateChangeBehaviour() const = 0;
};

//! Version 9 of the configuration interface.
class IConfigurationV9
{
public:

	//! Returns the path to the offline SCUI File on disk, overriding SCUI.pak that is normally loaded
	//	from the SDK install directory (i.e. Program Files/Social Club)
	virtual const char* RGSC_CALL GetOfflineScuiPakPath() const = 0;

	//! Allows for a title to enable/disable initializing the metadata system, which normally requires a metadata.dat file.
	//	This option is enabled (true) by default. Disabling it will also disable achievements which rely on metadata.
	virtual bool RGSC_CALL IsMetadataEnabled() const = 0;

};

//! Version 10 of the configuration interface.
class IConfigurationV10
{
public:

	//! Returns the services to be used for Auth (Legacy, WCF, etc)
	virtual RgscAuthServices RGSC_CALL GetAuthServices() const = 0;
	
	//! Allows for a title to disable the UI, even in release builds. This is effectively the same as specifying -scnoui. 
	// A title will need to log in via autologin, signintransfer, or on debug builds with -scemail and -scpassword.
	virtual bool RGSC_CALL IsUiEnabled() const = 0;
};

//! Version 11 of the configuration interface
class IConfigurationV11
{
public:

	enum RosFilterBehaviour
	{
		FILTER_DISABLED,				// ROS HTTP requests use no filter and no encryption
		FILTER_ENABLED,					// ROS HTTP requests are filtered by use no security flags.
		FILTER_ENABLED_WITH_SECURITY	// ROS HTTP requests are filtered and use the default security flags.
	};

	//! Returns if ROS services should use HTTPS by default
	virtual bool RGSC_CALL UseHttpsForRosServices() const = 0;

	//! Returns the filtering type used by ROS services.
	virtual RosFilterBehaviour RGSC_CALL GetRosFilterBehaviour() const = 0;

	//! Returns the SCUI url to use when loading the online site.
	//	If empty, the default SCUI web site will be loaded.
	//	Passing -scuiurl=URL has the same effect.
	virtual const char* RGSC_CALL GetOnlineUrl() const = 0;
};

typedef IConfigurationV11 IConfigurationLatestVersion;
#define IID_IConfigurationLatestVersion IID_IConfigurationV11

//! Concrete class that implements the IConfigurationV2 interface.
class ConfigurationV2 : public IConfigurationV2
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
			pUnknown = static_cast<IConfiguration*>(this);
		}
		else if(riid == IID_IConfigurationV1)
		{
			pUnknown = static_cast<IConfigurationV1*>(this);
		}
		else if(riid == IID_IConfigurationV2)
		{
			pUnknown = static_cast<IConfigurationV2*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	ConfigurationV2()
	{
		m_CommandLineParamCount = 0;
		m_CommandLineParams = NULL;
		m_OfflineOnlyMode = false;
		m_EnablePatching = false;
	}

	//! Returns the command line parameters.
	virtual char** RGSC_CALL GetCommandLineParams() const
	{
		return m_CommandLineParams;
	}

	virtual int RGSC_CALL GetCommandLineParamCount() const
	{
		return m_CommandLineParamCount;
	}

	virtual void RGSC_CALL SetCommandLineParams(int argc, char** argv)
	{
		m_CommandLineParamCount = argc;
		m_CommandLineParams = argv;
	}

	virtual bool RGSC_CALL IsOfflineOnlyMode() const
	{
		return m_OfflineOnlyMode;
	}

	virtual void RGSC_CALL SetOfflineOnlyMode(bool offlineOnlyMode)
	{
		m_OfflineOnlyMode = offlineOnlyMode;
	}

	virtual bool RGSC_CALL IsPatchingEnabled() const
	{
		return m_EnablePatching;
	}

	virtual void RGSC_CALL SetPatchingEnabled(bool enablePatching)
	{
		m_EnablePatching = enablePatching;
	}

protected:
	int m_CommandLineParamCount;
	char **m_CommandLineParams;
	bool m_OfflineOnlyMode;
	bool m_EnablePatching;
};

//! Concrete class that implements the IConfigurationV3 interface.
class ConfigurationV3 : public IConfigurationV3
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
			pUnknown = static_cast<IConfiguration*>(this);
		}
		else if(riid == IID_IConfigurationV1)
		{
			pUnknown = static_cast<IConfigurationV1*>(this);
		}
		else if(riid == IID_IConfigurationV2)
		{
			pUnknown = static_cast<IConfigurationV2*>(this);
		}
		else if(riid == IID_IConfigurationV3)
		{
			pUnknown = static_cast<IConfigurationV3*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	ConfigurationV3()
	{
		// do not change these defaults or you'll break existing games
		m_CommandLineParamCount = 0;
		m_CommandLineParams = NULL;
		m_OfflineOnlyMode = false;
		m_EnablePatching = false;
		m_EnableLocalProfiles = true;
	}

	//! Returns the command line parameters.
	virtual char** RGSC_CALL GetCommandLineParams() const
	{
		return m_CommandLineParams;
	}

	virtual int RGSC_CALL GetCommandLineParamCount() const
	{
		return m_CommandLineParamCount;
	}

	virtual void RGSC_CALL SetCommandLineParams(int argc, char** argv)
	{
		m_CommandLineParamCount = argc;
		m_CommandLineParams = argv;
	}

	virtual bool RGSC_CALL IsOfflineOnlyMode() const
	{
		return m_OfflineOnlyMode;
	}

	virtual void RGSC_CALL SetOfflineOnlyMode(bool offlineOnlyMode)
	{
		m_OfflineOnlyMode = offlineOnlyMode;
	}

	virtual bool RGSC_CALL IsPatchingEnabled() const
	{
		return m_EnablePatching;
	}

	virtual void RGSC_CALL SetPatchingEnabled(bool enablePatching)
	{
		m_EnablePatching = enablePatching;
	}

	virtual bool RGSC_CALL AreLocalProfilesEnabled() const
	{
		return m_EnableLocalProfiles;
	}

	virtual void RGSC_CALL SetLocalProfilesEnabled(bool enableLocalProfiles)
	{
		m_EnableLocalProfiles = enableLocalProfiles;
	}

protected:
	int m_CommandLineParamCount;
	char **m_CommandLineParams;
	bool m_OfflineOnlyMode;
	bool m_EnablePatching;
	bool m_EnableLocalProfiles;
};

//! Concrete class that implements the IConfigurationV4 interface.
class ConfigurationV4 : public IConfigurationV4, public ConfigurationV3
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV3::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV4)
		{
			*ppvObject = static_cast<IConfigurationV4*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV4()
	{
		// do not change these defaults or you'll break existing games
		m_HandleAutoSignIn = false;
		m_IsLauncher = false;
	}

	virtual bool RGSC_CALL IsLauncher() const
	{
		return m_IsLauncher;
	}

	virtual void RGSC_CALL SetIsLauncher(bool isLauncher)
	{
		m_IsLauncher = isLauncher;
	}

	virtual bool RGSC_CALL HandleAutoSignIn() const
	{
		return m_HandleAutoSignIn;
	}

	virtual void RGSC_CALL SetHandleAutoSignIn(bool handleAutoSignIn)
	{
		m_HandleAutoSignIn = handleAutoSignIn;
	}

protected:
	bool m_HandleAutoSignIn;
	bool m_IsLauncher;
};

//! Concrete class that implements the IConfigurationV5 interface.
class ConfigurationV5 : public IConfigurationV5, public ConfigurationV4
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV4::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV5)
		{
			*ppvObject = static_cast<IConfigurationV5*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV5()
	{
		// do not change these defaults or you'll break existing games
		memset(m_AdditionalSessionAttr, 0, sizeof(m_AdditionalSessionAttr));
		memset(m_AdditionalJoinAttr, 0, sizeof(m_AdditionalJoinAttr));
		memset(m_MetaDataPath, 0, sizeof(m_MetaDataPath));
	}

	virtual const char* RGSC_CALL GetAdditionalSessionAttr() const
	{
		return m_AdditionalSessionAttr;
	}

	virtual void RGSC_CALL SetAdditionalSessionAttr(const char* additionalSessionAttr)
	{
		strcpy_s(m_AdditionalSessionAttr, sizeof(m_AdditionalSessionAttr), additionalSessionAttr);
	}

	virtual const char* RGSC_CALL GetAdditionalJoinAttr() const
	{
		return m_AdditionalJoinAttr;
	}

	virtual void RGSC_CALL SetAdditionalJoinAttr(const char* additionalJoinAttr)
	{
		strcpy_s(m_AdditionalJoinAttr, sizeof(m_AdditionalJoinAttr), additionalJoinAttr);
	}

	virtual const char* RGSC_CALL GetMetaDataPath() const
	{
		return m_MetaDataPath;
	}

	virtual void RGSC_CALL SetMetadataPath(const char* path)
	{
		strcpy_s(m_MetaDataPath, sizeof(m_MetaDataPath), path);
	}

protected:
	char m_AdditionalSessionAttr[rgsc::RGSC_ADDITIONAL_SESSION_ATTR_BUF_SIZE];
	char m_AdditionalJoinAttr[rgsc::RGSC_ADDITIONAL_SESSION_ATTR_BUF_SIZE];
	char m_MetaDataPath[RGSC_MAX_PATH];
};

//! Concrete class that implements the IConfigurationV6 interface.
class ConfigurationV6 : public IConfigurationV6, public ConfigurationV5
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV5::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV6)
		{
			*ppvObject = static_cast<IConfigurationV6*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV6()
	{
		// By default, gamepads are implicitly supported in the SDK
		m_GamepadSupport = GAMEPADS_SUPPORTED;
	}

	virtual GamepadSupport RGSC_CALL GetGamePadSupport() const
	{
		return m_GamepadSupport;
	}

	virtual void RGSC_CALL SetGamepadSupport(GamepadSupport gamePadSupport)
	{
		m_GamepadSupport = gamePadSupport;
	}

protected:
	GamepadSupport m_GamepadSupport;
};

//! Concrete class that implements the IConfigurationV7 interface.
class ConfigurationV7 : public IConfigurationV7, public ConfigurationV6
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV6::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV7)
		{
			*ppvObject = static_cast<IConfigurationV7*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV7()
	{
		m_AdditionalWindowHandles = NULL;
		m_NumAdditionalWindowHandles = 0;
	}

	virtual WindowHandle* RGSC_CALL GetAdditionalWindowHandles() const
	{
		return m_AdditionalWindowHandles;
	}

	virtual unsigned RGSC_CALL GetNumAdditionalWindowHandles() const
	{
		return m_NumAdditionalWindowHandles;
	}

	virtual void RGSC_CALL SetAdditionalWindowHandles(WindowHandle* additionalWindows, const unsigned int numAdditionalWindows)
	{
		m_AdditionalWindowHandles = additionalWindows;
		m_NumAdditionalWindowHandles = numAdditionalWindows;
	}

protected:
	WindowHandle* m_AdditionalWindowHandles;
	unsigned int m_NumAdditionalWindowHandles;
};

//! Concrete class that implements the IConfigurationV8 interface.
class ConfigurationV8 : public IConfigurationV8, public ConfigurationV7
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV7::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV8)
		{
			*ppvObject = static_cast<IConfigurationV8*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV8()
	{
		// Changing these risks breaking older titles.
		m_SignInTransferBehaviour = IConfigurationV8::DEFAULT;
		m_FriendsBehaviour = IConfigurationV8::DEFAULT;
		m_PresenceBehaviour = IConfigurationV8::DEFAULT;
		m_AchievementBehaviour = IConfigurationV8::DEFAULT;
		m_ConnectionChangeBehaviour = IConfigurationV8::DEFAULT;
	}

	virtual FeatureBehaviour RGSC_CALL GetSignIntransferBehaviour() const
	{
		return m_SignInTransferBehaviour;
	}

	virtual void RGSC_CALL SetSignInTransferBehaviour(FeatureBehaviour behaviour)
	{
		m_SignInTransferBehaviour = behaviour;
	}

	virtual FeatureBehaviour RGSC_CALL GetFriendsBehaviour() const
	{
		return m_FriendsBehaviour;
	}

	virtual void RGSC_CALL SetFriendsBehaviour(FeatureBehaviour behaviour)
	{
		m_FriendsBehaviour = behaviour;
	}

	virtual FeatureBehaviour RGSC_CALL GetPresenceBehaviour() const
	{
		return m_PresenceBehaviour;
	}

	virtual void RGSC_CALL SetPresenceBehaviour(FeatureBehaviour behaviour)
	{
		m_PresenceBehaviour = behaviour;
	}

	virtual FeatureBehaviour RGSC_CALL GetAchievementBehaviour() const
	{
		return m_AchievementBehaviour;
	}

	virtual void RGSC_CALL SetAchievementBehaviour(FeatureBehaviour behaviour)
	{
		m_AchievementBehaviour = behaviour;
	}

	virtual FeatureBehaviour RGSC_CALL GetConnectionStateChangeBehaviour() const
	{
		return m_ConnectionChangeBehaviour;
	}

	virtual void RGSC_CALL SetConnectionStateChangeBehaviour(FeatureBehaviour behaviour)
	{
		m_ConnectionChangeBehaviour = behaviour;
	}

protected:
	
	FeatureBehaviour m_SignInTransferBehaviour;
	FeatureBehaviour m_FriendsBehaviour;
	FeatureBehaviour m_PresenceBehaviour;
	FeatureBehaviour m_AchievementBehaviour;
	FeatureBehaviour m_ConnectionChangeBehaviour;
};

//! Concrete class that implements the IConfigurationV9 interface.
class ConfigurationV9 : public IConfigurationV9, public ConfigurationV8
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV8::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV9)
		{
			*ppvObject = static_cast<IConfigurationV9*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV9()
	{
		memset(m_ScuiPakPath, 0, sizeof(m_ScuiPakPath));
		m_bIsMetadataEnabled = true;
	}

	virtual const char* RGSC_CALL GetOfflineScuiPakPath() const
	{
		return m_ScuiPakPath;
	}

	virtual void RGSC_CALL SetOfflineScuiPakPath(const char* path)
	{
		strcpy_s(m_ScuiPakPath, sizeof(m_ScuiPakPath), path);
	}

	virtual bool RGSC_CALL IsMetadataEnabled() const
	{
		return m_bIsMetadataEnabled;
	}

	virtual void RGSC_CALL SetIsMetadataEnabled(bool bEnabled)
	{
		m_bIsMetadataEnabled = bEnabled;
	}

protected:

	char m_ScuiPakPath[RGSC_MAX_PATH];
	bool m_bIsMetadataEnabled;
};

//! Concrete class that implements the IConfigurationV10 interface.
class ConfigurationV10 : public IConfigurationV10, public ConfigurationV9
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV9::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV10)
		{
			*ppvObject = static_cast<IConfigurationV10*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV10()
	{
		// Default to legacy services and a full UI experience.
		m_AuthServices = RGSC_AUTH_ASMX;
		m_bIsUiEnabled = true;
	}

	virtual RgscAuthServices RGSC_CALL GetAuthServices() const
	{
		return m_AuthServices;
	}

	virtual void RGSC_CALL SetAuthServices(RgscAuthServices authServices)
	{
		m_AuthServices = authServices;
	}

	virtual bool RGSC_CALL IsUiEnabled() const
	{
		return m_bIsUiEnabled;
	}

	virtual void RGSC_CALL SetIsUiEnabled(bool bEnabled)
	{
		m_bIsUiEnabled = bEnabled;
	}

protected:

	RgscAuthServices m_AuthServices;
	bool m_bIsUiEnabled;
};

//! Concrete class that implements the IConfigurationV11 interface.
class ConfigurationV11 : public IConfigurationV11, public ConfigurationV10
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		RGSC_HRESULT hr = ConfigurationV10::QueryInterface(riid, ppvObject);

		if(hr == RGSC_NOINTERFACE && riid == IID_IConfigurationV11)
		{
			*ppvObject = static_cast<IConfigurationV11*>(this);
			return RGSC_OK;
		}

		return hr;
	}

	ConfigurationV11()
		: ConfigurationV10()
	{
		// Default to legacy behaviour - no HTTPS for ros services
		m_bRosUseHttps = false;

		// Default to legacy behaviour - filtered+security
		m_RosFilter = IConfigurationV11::FILTER_ENABLED_WITH_SECURITY;

		// When scui url is empty - the default will be used.
		m_OnlineUrl[0] = '\0';
	}

	virtual bool RGSC_CALL UseHttpsForRosServices() const
	{
		return m_bRosUseHttps;
	}

	virtual void RGSC_CALL SetUseHttpsForRosServices(bool bRosUseHttps)
	{
		m_bRosUseHttps = bRosUseHttps;
	}

	virtual RosFilterBehaviour RGSC_CALL GetRosFilterBehaviour() const
	{
		return m_RosFilter;
	}

	virtual void RGSC_CALL SetRosFilterBehaviour(RosFilterBehaviour rosEncryption)
	{
		m_RosFilter = rosEncryption;
	}

	virtual const char* RGSC_CALL GetOnlineUrl() const
	{
		return m_OnlineUrl;
	}

	virtual void RGSC_CALL SetOnlineUrl(const char* scuiUrl)
	{
		strcpy_s(m_OnlineUrl, sizeof(m_OnlineUrl), scuiUrl);
	}

protected:

	bool m_bRosUseHttps;
	RosFilterBehaviour m_RosFilter;
	char m_OnlineUrl[RGSC_MAX_URL_BUF_SIZE];
};

typedef ConfigurationV11 Configuration;

} // namespace

#endif // CONFIGURATION_INTERFACE_H
