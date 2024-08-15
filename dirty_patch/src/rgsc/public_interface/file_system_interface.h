#ifndef FILE_SYSTEM_INTERFACE_H
#define FILE_SYSTEM_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

class IFileSystem : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IFileSystemV1 = {0x46fa1b14, 0x631d, 0x4d93, {0xa6, 0xce, 0x89, 0xf7, 0x5d, 0x68, 0x6, 0x84}};
extern "C" static const RGSC_IID IID_IFileSystemV2 = {0xd0cc1a9a, 0x1eb4, 0x4053, {0xa7, 0x9a, 0xb1, 0x49, 0x50, 0x93, 0xe8, 0xfb}};
extern "C" static const RGSC_IID IID_IFileSystemV3 = {0xcd1812ad, 0x182b, 0x4253, {0xaa, 0xf3, 0xa5, 0x84, 0xf2, 0x2a, 0xe8, 0xe3}};
extern "C" static const RGSC_IID IID_IFileSystemV4 = {0x2cd99033, 0xd7e4, 0x4af7, {0xa2, 0xcf, 0x4d, 0x89, 0x4b, 0x1c, 0x42, 0x5e}};
extern "C" static const RGSC_IID IID_IFileSystemV5 = {0x4cf3f7d0, 0xeaf2, 0x49ac, {0x99, 0x79, 0xdb, 0xd8, 0x58, 0x88, 0x2f, 0xad}};

//! File System Interface
//! Defines the public interface that game clients use to access the platform's file system and directory structure.
class IFileSystemV1 : public IFileSystem
{
public:
	//! Gets the path to the directory that the game uses to store title-specific data.
	/**
	  This is data that the game creates and needs to be stored on disk.\n
	  Each title gets their own directory. For example: Documents/Rockstar Games/(game name).\n
	  The (game name) is passed as a parameter to the TitleId. See Rgsc::Init().\n
	  Note: this directory should not be used to store player-specific data. For that,
	  use GetTitleProfileDirectory();
	  \param
		  path - [out] the path to title-specific data.
	  \param
		  createDirectory - if set to true, the directory will be created.\n
							If the directory already exists, this parameter will be ignored.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL GetTitleDirectory(char (&path)[RGSC_MAX_PATH], bool createDirectory) const = 0;

	//! Gets the path to the directory that games use to store player-specific data.
	/**
	  For example: save games, players settings files, etc.\n
	  Each player gets their own directory under the title's unique directory.\n
	  For example: Documents/Rockstar Games/(game name)/Profiles/(profile id).\n
	  The (game name) is passed as a parameter to the TitleId. See Rgsc::Init().\n
	  \param
		  path - [out] the path to player-specific data.
	  \param
		  createDirectory - if set to true, the directory will be created.\n
							If the directory already exists, this parameter will be ignored.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL GetTitleProfileDirectory(char (&path)[RGSC_MAX_PATH], bool createDirectory) const = 0;
};

class IFileSystemV2 : public IFileSystemV1
{
public:
	//! Gets the directory name for the current profile. 
	/**
	  For example: save games, players settings files, etc.\n
	  Each player gets their own directory under the title's unique directory.\n
	  For example: Documents/Rockstar Games/(game name)/Profiles/(profile id).\n
	  This function returns just the profile id part of that path.\n
	  \param
		  path - [out] the path to player-specific data.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL GetProfileDirectoryId(char (&path)[RGSC_MAX_PATH]) const = 0;
};

class IFileSystemV3 : public IFileSystemV2
{
public:
	//! Gets the path to the directory that the Social Club uses to store its data.
	/**
	  For example: Documents/Rockstar Games/\n
	  \param
		  path - [out] the path of the root data directory.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	  \remark
	      This path was exposed to the calling process for the Korean Naver platform (NHN).
		  File paths sent to the file delegate will start with this path. The game then knows
		  which part of the absolute path to strip off in order to save data to the Naver cloud.
	*/
	virtual RGSC_HRESULT RGSC_CALL GetRootDataDirectory(char (&path)[RGSC_MAX_PATH]) const = 0;
};

class IFileSystemV4 : public IFileSystemV3
{
public:
	//! Gets the path to the directory that games use to store player-specific data.
	/**
	  For example: save games, players settings files, etc.\n
	  Each player gets their own directory under the title's unique directory.\n
	  For example: Documents/Rockstar Games/(game name)/Profiles/(profile id).\n
	  The (game name) is passed as the titleId param.\n
	  \param
		  path - [out] the path to player-specific data.
	  \param
		  titleDirectoryName - Game folder to use.
	  \param
		  createDirectory - if set to true, the directory will be created.\n
							If the directory already exists, this parameter will be ignored.
	  \return
		  RGSC_OK - success\n
		  Other values indicate the error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL GetProfileDirectoryForTitle(char (&path)[RGSC_MAX_PATH], const char* titleDirectoryName, bool bCreateDirectory) const = 0;
};

class IFileSystemV5 : public IFileSystemV4
{
public:

	//! Enables or Disables UTF8 file paths in the File System
	//	By default, this is enabled on x64 builds.
	//	On x86 builds, this feature is disabled for legacy purposes with L.A. Noire and Max Payne 3 (ANSI paths only).
	virtual void RGSC_CALL EnableUtf8FilePaths(const bool bEnabled) = 0;
};

typedef IFileSystemV5 IFileSystemLatestVersion;
#define IID_IFileSystemLatestVersion IID_IFileSystemV5

} // namespace rgsc

#endif // FILE_SYSTEM_INTERFACE_H
