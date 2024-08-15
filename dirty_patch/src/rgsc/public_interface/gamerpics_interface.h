#ifndef GAMERPIC_INTERFACE_H
#define GAMERPIC_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"
#include "profiles_interface.h"

namespace rgsc
{
	// ===============================================================================================
	// IGamerPicManager
	// ===============================================================================================
	class IGamerPicManager : public IRgscUnknown
	{
	public:

		enum AvatarSize
		{
			SMALL = 0x01, // 32x32
			LARGE = 0x02, // 64x64
			XLARGE = 0x04, // 128x128
			ALL = SMALL | LARGE | XLARGE
		};

		virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	};

	//! GamerPic Interface
	//! Defines the public interface that clients use to download and read gamer pics.
	class IGamerPicManagerV1 : public IGamerPicManager
	{
	public:

		//! Returns the local path to the default gamer pic using the given avatar size.
		virtual bool RGSC_CALL GetDefaultGamerPicPath(char (&path)[RGSC_MAX_PATH], AvatarSize avatarSize) = 0;

		//! Download gamer pic from social club and cache it on disk. Multiple avatar sizes can be specified
		//	by constructing flags out of the AvatarSize enums.
		virtual bool RGSC_CALL DownloadGamerPic(const char* relativeAvatarUrl, int avatarSizeFlags, IAsyncStatus* status) = 0;

		//! Given a gamer pic name, returns the full local path to where the gamer pic is stored.
		//  Note that the gamer pic doesn't necessarily exist, this just returns the path to where it would get stored.
		virtual bool RGSC_CALL GetGamerPicPath(const char (&gamerPicName)[RGSC_MAX_AVATAR_URL_CHARS], AvatarSize avatarSize, char (&path)[RGSC_MAX_PATH]) const = 0;

		//! Returns the UTF8 encoded local path on disk for the gamerpic/avatar.
		//	NOTE: Returns an empty string if the gamerpic has not been cached on disk.
		virtual bool RGSC_CALL GetGamerPicUrl(const char (&gamerPicName)[RGSC_MAX_AVATAR_URL_CHARS], AvatarSize avatarSize, char (&url)[RGSC_MAX_PATH]) const = 0;
	};

	extern "C" static const RGSC_IID IID_IGamerPicManagerV1 = { 0x93241773, 0x8151, 0x4472, { 0x8b, 0xce, 0x94, 0x2c, 0xc9, 0x61, 0x4a, 0x85 } };
	typedef IGamerPicManagerV1 IGamerPicManagerLatestVersion;
	#define IID_IGamerPicManagerLatestVersion IID_IGamerPicManagerV1


} // namespace rgsc

#endif // GAMERPIC_INTERFACE_H

