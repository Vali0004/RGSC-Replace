#ifndef PROFILE_MANAGER_INTERFACE_H
#define PROFILE_MANAGER_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"

#include <cstring>

namespace rgsc
{

// includes null terminator - this needs to match RLSC_MAX_NICKNAME_CHARS
static const u32 RGSC_MAX_NAME_CHARS = 51;

// includes null terminator - this needs to match RLROS_MAX_TICKET_SIZE
static const u32 RGSC_ROS_MAX_TICKET_LEN = 512;

// this needs to match UniqueKey::SIZE_OF_KEY_IN_BYTES
static const u32 RGSC_PROFILE_UNIQUE_KEY_LEN = 256 >> 3;

// this needs to match RLSC_MAX_EMAIL_CHARS
static const u32 RGSC_MAX_EMAIL_CHARS = 101;

// This is the legacy password length (used on mp3, lan and gtav)
// This value cannot change as it will impact legacy structures
static const u32 RGSC_MAX_PASSWORD_LEGACY_CHARS = 31;

// this needs to match RLSC_MAX_PASSWORD_CHARS
static const u32 RGSC_MAX_PASSWORD512_CHARS = 513;

// this needs to at least RLSC_MAX_SCAUTHTOKEN_CHARS
static const u32 RGSC_MAX_AUTHTOKEN_CHARS = 512;

// this needs to at least RLSC_MAX_AVATAR_URL_CHARS
static const u32 RGSC_MAX_AVATAR_URL_CHARS = 128;

// this needs to be at least RLSC_MAX_DEVICETOKEN_CHARS
static const u32 RGSC_MAX_MACHINETOKEN_CHARS = 129;

//! This class is designed to be an extensible version of a plain-old-data structure.
class IProfile : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IProfileV1 = {0x5c0c8f48, 0x7f01, 0x4680, {0x99, 0xa1, 0x5f, 0x8d, 0x52, 0xc1, 0x62, 0xb8}};

//! Version 1 of the profile interface
class IProfileV1 : public IProfile
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Sets the signed-in player's profile id
	virtual void RGSC_CALL SetProfileId(RockstarId profileId) = 0;

	//! Sets the signed-in player's nickname
	virtual void RGSC_CALL SetNickname(const char* nickname) = 0;

	//! Sets the signed-in player's unique key that can be used to tie save data to the profile
	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN]) = 0;

	//! Sets whether the signed-in player is using a purely offline profile.
	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile) = 0;

	//! Sets the ROS ticket
	virtual void RGSC_CALL SetRosTicket(const char* ticket) = 0;
};

//! Concrete class that implements the IProfileV1 interface.
class ProfileV1 : public IProfileV1
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
			pUnknown = static_cast<IProfile*>(this);
		}
		else if(riid == IID_IProfileV1)
		{
			pUnknown = static_cast<IProfileV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	virtual RockstarId RGSC_CALL GetProfileId() const
	{
		return m_ProfileId;
	}

	virtual void RGSC_CALL SetProfileId(RockstarId profileId)
	{
		m_ProfileId = profileId;
	}

	virtual const char* RGSC_CALL GetNickname() const
	{
		return m_Nickname;
	}

	virtual void RGSC_CALL SetNickname(const char* nickname)
	{
		strncpy_s(m_Nickname, sizeof(m_Nickname), nickname, sizeof(m_Nickname) - 1);
	}

	virtual const u8* RGSC_CALL GetProfileUniqueKey() const
	{
		return m_UniqueKey;
	}

	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN])
	{
		memcpy(m_UniqueKey, key, sizeof(key));
	}

	virtual bool RGSC_CALL IsOfflineProfile() const
	{
		return m_IsOfflineProfile;
	}

	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile)
	{
		m_IsOfflineProfile = isOfflineProfile;
	}

	virtual const char* RGSC_CALL GetRosTicket() const
	{
		return m_RosTicket;
	}

	virtual void RGSC_CALL SetRosTicket(const char* ticket)
	{
		strncpy_s(m_RosTicket, sizeof(m_RosTicket), ticket, sizeof(m_RosTicket) - 1);
	}

protected:
	RockstarId m_ProfileId;
	char m_Nickname[RGSC_MAX_NAME_CHARS];
	u8 m_UniqueKey[RGSC_PROFILE_UNIQUE_KEY_LEN];
	bool m_IsOfflineProfile;
	char m_RosTicket[RGSC_ROS_MAX_TICKET_LEN];
};

extern "C" static const RGSC_IID IID_IProfileV2 = {0x43412d5, 0xaedd, 0x486b, {0xbc, 0xde, 0x71, 0xfd, 0xfb, 0x83, 0x2, 0x1f}};

//! Version 2 of the profile interface
class IProfileV2 : public IProfileV1
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Sets the signed-in player's profile id
	virtual void RGSC_CALL SetProfileId(RockstarId profileId) = 0;

	//! Sets the signed-in player's nickname
	virtual void RGSC_CALL SetNickname(const char* nickname) = 0;

	//! Sets the signed-in player's unique key that can be used to tie save data to the profile
	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN]) = 0;

	//! Sets whether the signed-in player is using a purely offline profile.
	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile) = 0;

	//! Sets the ROS ticket
	virtual void RGSC_CALL SetRosTicket(const char* ticket) = 0;

	//! Sets the Social Club e-mail
	virtual void RGSC_CALL SetSocialClubEmail(const char* email) = 0;

	//! Sets the Social Club password
	virtual void RGSC_CALL SetSocialClubPassword(const char* password) = 0;
};

//! Concrete class that implements the IProfileV2 interface.
class ProfileV2 : public IProfileV2
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
			pUnknown = static_cast<IProfile*>(this);
		}
		else if(riid == IID_IProfileV1)
		{
			pUnknown = static_cast<IProfileV1*>(this);
		}
		else if(riid == IID_IProfileV2)
		{
			pUnknown = static_cast<IProfileV2*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	virtual RockstarId RGSC_CALL GetProfileId() const
	{
		return m_ProfileId;
	}

	virtual void RGSC_CALL SetProfileId(RockstarId profileId)
	{
		m_ProfileId = profileId;
	}

	virtual const char* RGSC_CALL GetNickname() const
	{
		return m_Nickname;
	}

	virtual void RGSC_CALL SetNickname(const char* nickname)
	{
		strncpy_s(m_Nickname, sizeof(m_Nickname), nickname, sizeof(m_Nickname) - 1);
	}

	virtual const u8* RGSC_CALL GetProfileUniqueKey() const
	{
		return m_UniqueKey;
	}

	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN])
	{
		memcpy(m_UniqueKey, key, sizeof(key));
	}

	virtual bool RGSC_CALL IsOfflineProfile() const
	{
		return m_IsOfflineProfile;
	}

	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile)
	{
		m_IsOfflineProfile = isOfflineProfile;
	}

	virtual const char* RGSC_CALL GetRosTicket() const
	{
		return m_RosTicket;
	}

	virtual void RGSC_CALL SetRosTicket(const char* ticket)
	{
		strncpy_s(m_RosTicket, sizeof(m_RosTicket), ticket, sizeof(m_RosTicket) - 1);
	}

	virtual const char* RGSC_CALL GetSocialClubEmail() const
	{
		return m_SocialClubEmail;
	}

	virtual void RGSC_CALL SetSocialClubEmail(const char* email)
	{
		strncpy_s(m_SocialClubEmail, sizeof(m_SocialClubEmail), email, sizeof(m_SocialClubEmail) - 1);
	}

	virtual const char* RGSC_CALL GetSocialClubPassword() const
	{
		return m_SocialClubPassword;
	}

	virtual void RGSC_CALL SetSocialClubPassword(const char* password)
	{
		strncpy_s(m_SocialClubPassword, sizeof(m_SocialClubPassword), password, sizeof(m_SocialClubPassword) - 1);
	}

protected:
	RockstarId m_ProfileId;
	char m_Nickname[RGSC_MAX_NAME_CHARS];
	u8 m_UniqueKey[RGSC_PROFILE_UNIQUE_KEY_LEN];
	bool m_IsOfflineProfile;
	char m_RosTicket[RGSC_ROS_MAX_TICKET_LEN];
	char m_SocialClubEmail[RGSC_MAX_EMAIL_CHARS];
	char m_SocialClubPassword[RGSC_MAX_PASSWORD_LEGACY_CHARS];
};

extern "C" static const RGSC_IID IID_IProfileV3 = { 0xce15b3d4, 0xe4cf, 0x43e2, { 0x81, 0x58, 0x65, 0x30, 0xc, 0x95, 0xe1, 0x65 } };

//! Version 3 of the profile interface
class IProfileV3 : public IProfileV2
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! Sets the signed-in player's profile id
	virtual void RGSC_CALL SetProfileId(RockstarId profileId) = 0;

	//! Sets the signed-in player's nickname
	virtual void RGSC_CALL SetNickname(const char* nickname) = 0;

	//! Sets the signed-in player's unique key that can be used to tie save data to the profile
	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN]) = 0;

	//! Sets whether the signed-in player is using a purely offline profile.
	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile) = 0;

	//! Sets the ROS ticket
	virtual void RGSC_CALL SetRosTicket(const char* ticket) = 0;

	//! Sets the Social Club e-mail
	virtual void RGSC_CALL SetSocialClubEmail(const char* email) = 0;

	//! Sets the Social Club password
	virtual void RGSC_CALL SetSocialClubPassword(const char* password) = 0;

	//! Sets the Social Club Auth Token
	virtual void RGSC_CALL SetSocialClubAuthToken(const char* scAuthToken) = 0;
};

//! Concrete class that implements the IProfileV3 interface.
class ProfileV3 : public IProfileV3
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
			pUnknown = static_cast<IProfile*>(this);
		}
		else if(riid == IID_IProfileV1)
		{
			pUnknown = static_cast<IProfileV1*>(this);
		}
		else if(riid == IID_IProfileV2)
		{
			pUnknown = static_cast<IProfileV2*>(this);
		}
		else if(riid == IID_IProfileV3)
		{
			pUnknown = static_cast<IProfileV3*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	ProfileV3()
	{
		m_ProfileId = 0;
		memset(m_Nickname, 0, sizeof(m_Nickname));
		memset(m_UniqueKey, 0, sizeof(m_UniqueKey));
		memset(m_RosTicket, 0, sizeof(m_RosTicket));
		memset(m_SocialClubEmail, 0, sizeof(m_SocialClubEmail));
		memset(m_SocialClubPassword, 0, sizeof(m_SocialClubPassword));
		memset(m_SocialClubAuthToken, 0, sizeof(m_SocialClubAuthToken));
		m_IsOfflineProfile = false;
	}

	virtual RockstarId RGSC_CALL GetProfileId() const
	{
		return m_ProfileId;
	}

	virtual void RGSC_CALL SetProfileId(RockstarId profileId)
	{
		m_ProfileId = profileId;
	}

	virtual const char* RGSC_CALL GetNickname() const
	{
		return m_Nickname;
	}

	virtual void RGSC_CALL SetNickname(const char* nickname)
	{
		strncpy_s(m_Nickname, sizeof(m_Nickname), nickname, sizeof(m_Nickname) - 1);
	}

	virtual const u8* RGSC_CALL GetProfileUniqueKey() const
	{
		return m_UniqueKey;
	}

	virtual void RGSC_CALL SetProfileUniqueKey(const u8 (&key)[RGSC_PROFILE_UNIQUE_KEY_LEN])
	{
		memcpy(m_UniqueKey, key, sizeof(key));
	}

	virtual bool RGSC_CALL IsOfflineProfile() const
	{
		return m_IsOfflineProfile;
	}

	virtual void RGSC_CALL SetIsOfflineProfile(bool isOfflineProfile)
	{
		m_IsOfflineProfile = isOfflineProfile;
	}

	virtual const char* RGSC_CALL GetRosTicket() const
	{
		return m_RosTicket;
	}

	virtual void RGSC_CALL SetRosTicket(const char* ticket)
	{
		strncpy_s(m_RosTicket, sizeof(m_RosTicket), ticket, sizeof(m_RosTicket) - 1);
	}

	virtual const char* RGSC_CALL GetSocialClubEmail() const
	{
		return m_SocialClubEmail;
	}

	virtual void RGSC_CALL SetSocialClubEmail(const char* email)
	{
		strncpy_s(m_SocialClubEmail, sizeof(m_SocialClubEmail), email, sizeof(m_SocialClubEmail) - 1);
	}

	virtual const char* RGSC_CALL GetSocialClubPassword() const
	{
		return m_SocialClubPassword;
	}

	virtual void RGSC_CALL SetSocialClubPassword(const char* password)
	{
		strncpy_s(m_SocialClubPassword, sizeof(m_SocialClubPassword), password, sizeof(m_SocialClubPassword) - 1);
	}

	virtual const char* RGSC_CALL GetSocialClubAuthToken() const
	{
		return m_SocialClubAuthToken;
	}

	virtual void RGSC_CALL SetSocialClubAuthToken(const char* scAuthToken)
	{
		strncpy_s(m_SocialClubAuthToken, sizeof(m_SocialClubAuthToken), scAuthToken, sizeof(m_SocialClubAuthToken) - 1);
	}

protected:
	RockstarId m_ProfileId;
	char m_Nickname[RGSC_MAX_NAME_CHARS];
	u8 m_UniqueKey[RGSC_PROFILE_UNIQUE_KEY_LEN];
	bool m_IsOfflineProfile;
	char m_RosTicket[RGSC_ROS_MAX_TICKET_LEN];
	char m_SocialClubEmail[RGSC_MAX_EMAIL_CHARS];
	char m_SocialClubPassword[RGSC_MAX_PASSWORD_LEGACY_CHARS];
	char m_SocialClubAuthToken[RGSC_MAX_AUTHTOKEN_CHARS];
};

typedef IProfileV3 IProfileLatestVersion;
#define IID_IProfileLatestVersion IID_IProfileV3

typedef ProfileV3 Profile;

//! Profile Manager Interface
//! Defines the public interface that game clients use to access profile information.
//!	\example profile_manager.cpp
class IProfileManager : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IProfileManagerV1 = {0xc925c862, 0xd355, 0x4b9a, {0x82, 0x57, 0x64, 0x9c, 0x30, 0x3f, 0xaa, 0x3f}};
extern "C" static const RGSC_IID IID_IProfileManagerV2 = {0x61a90b24, 0x4bdb, 0x4d0e, {0x9c, 0x41, 0x7f, 0x55, 0x79, 0x11, 0xb2, 0x22}};
extern "C" static const RGSC_IID IID_IProfileManagerV3 = {0x72b5802d, 0xbc97, 0x4c88, { 0xbe, 0xb3, 0x7c, 0xbd, 0x6d, 0xc, 0xa8, 0x14 } };

//! Version 1 of the profile manager interface.
class IProfileManagerV1 : public IProfileManager
{
public:
	//! Queries the signed-in state of the user.
	/**
	  \return
		true if the user is signed in to the local platform, false otherwise.
	  \remark
		This function does not indicate whether a user is signed-in online.
		To obtain that info, call IsOnline.
	*/
	virtual bool RGSC_CALL IsSignedIn() = 0;

	//! Queries the online state of the user.
	/**
	  \return
		true if the user is signed-in online, false otherwise.
	  \remark
		if a user is signed-in online, they are also implicitly signed-in locally.
	*/
	virtual bool RGSC_CALL IsOnline() = 0;

	//! Retrieves information about the signed-in user.
	/**
	  \param
		 profile - on return, this gets populated with the information about the signed-in user.
	  \return
		  ERROR_SUCCESS if the function succeeds.\n
		  ERROR_BAD_ARGUMENTS if profile is NULL.\n
		  ERROR_NO_SUCH_USER if no user is signed-in.\n
	*/
	virtual RGSC_HRESULT RGSC_CALL GetSignInInfo(IProfile* profile) = 0;

	//! Signs in the profile that is set to automatically sign in, or returns an error if no auto-sign-in profile exists.
	/**
	  \return
	  RGSC_OK - success\n
	  ERROR_NO_SUCH_USER - no profile is set to automatically sign in.\n
	  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL AttemptAutoSignIn() = 0;
};

//! Version 2 of the profile manager interface
class IProfileManagerV2 : public IProfileManagerV1
{
public:
	//! Queries the signing in state of the user.
	/**
	  \return
		true if the profile signin is in progress
	*/
	virtual bool RGSC_CALL IsSigningIn() const = 0;

	//! Creates a signin transfer profile manually.
	virtual bool RGSC_CALL CreateSigninTransferProfile() = 0;

	//! Event fired when the game receives a ticket invalidation due to duplicate signin
	virtual void RGSC_CALL OnDuplicateSignInMessageReceived(const int localGamerIndex) = 0;

	//! Event fired in the launcher when the the game has received an updated ticket
	virtual void RGSC_CALL OnLauncherReceivedUpdatedSocialClubTicket(RockstarId id, const char* base64credentials) = 0;

	//! Event fired in the launcher when the the game has signed out
	virtual void RGSC_CALL OnLauncherReceivedSignOutEvent() = 0;

	//! Event fired in the launcher when the the game has signed in
	virtual void RGSC_CALL OnLauncherReceivedSignInEvent(RockstarId id) = 0;
};

//! Version 3 of the profile manager interface
class IProfileManagerV3 : public IProfileManagerV2
{
public:

	//! Asynchronously exchanges a LauncherServices ticket for a title specific game ticket,
	//	saving it in the signin transfer profile.
	//	NOTE:
	//   Should only be called by clients that access Launcher services prior to launching a title.
	virtual bool RGSC_CALL CreateTitleSpecificTransferProfile(int rosTitleId, IAsyncStatus* status) = 0;

};
 
typedef IProfileManagerV3 IProfileManagerLatestVersion;
#define IID_IProfileManagerLatestVersion IID_IProfileManagerV3

} // namespace

#endif // PROFILE_MANAGER_INTERFACE_H
