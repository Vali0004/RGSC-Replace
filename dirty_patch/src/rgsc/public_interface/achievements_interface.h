#ifndef ACHIEVEMENT_MANAGER_INTERFACE_H
#define ACHIEVEMENT_MANAGER_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"

#include <time.h>

namespace rgsc
{

typedef u32 AchievementId;
class ITitleId;

//! This class is designed to be an extensible version of a plain-old-data structure.
class IAchievement : public IRgscUnknown
{
public:
	static const u32 MAX_LABEL_LEN = 32 * 2;
	static const u32 MAX_DESC_LEN = 100 * 2;
	static const u32 MAX_UNACHIEVED_LEN = 100 * 2;

	enum AchievementType
	{
		//From xbox.h
		ACHIEVEMENT_TYPE_INVALID = 0,
		ACHIEVEMENT_TYPE_COMPLETION = 1,
		ACHIEVEMENT_TYPE_LEVELING = 2,
		ACHIEVEMENT_TYPE_UNLOCK = 3,
		ACHIEVEMENT_TYPE_EVENT = 4,
		ACHIEVEMENT_TYPE_TOURNAMENT = 5,
		ACHIEVEMENT_TYPE_CHECKPOINT = 6,
		ACHIEVEMENT_TYPE_OTHER = 7,
	};

	//! Indicates what data is required when enumerating achievements.
	//! \sa CreateAchievementEnumerator()
	enum DetailFlags
	{
		ACHIEVEMENT_DETAILS_STRINGS = 1,							//!< retrieves the string metadata for each achievement
		ACHIEVEMENT_DETAILS_IMAGE = 2,								//!< retrieves the image metadata
		ACHIEVEMENT_DETAILS_IS_AWARDED = 4,							//!< retrieves player-specific awarded flag
		ACHIEVEMENT_DETAILS_TIMESTAMP = 8,							//!< retrieves player-specific awarded timestamp

		ACHIEVEMENT_DETAILS_ALL = ACHIEVEMENT_DETAILS_STRINGS |		//!< retrieves all data
								  ACHIEVEMENT_DETAILS_IMAGE | 
								  ACHIEVEMENT_DETAILS_IS_AWARDED |
								  ACHIEVEMENT_DETAILS_TIMESTAMP,
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_AchievementV1 = {0x5ae619c9, 0x90a9, 0x4a0a, {0xb8, 0x4, 0x80, 0x22, 0x60, 0xd2, 0xc, 0x42}};

//! Version 1 of the achievement interface.
class IAchievementV1 : public IAchievement
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	/**
	  \return
		  Returns the achievement id.
	*/
	virtual AchievementId RGSC_CALL GetId() const = 0;

	/**
	  \return
		  Returns number of points this achievement is worth.
	*/
	virtual u32 RGSC_CALL GetPoints() const = 0;

	/**
	  \return
		  Returns the type of the achievement.
	*/
	virtual AchievementType RGSC_CALL GetType() const = 0;

	/**
	  \return
		  Returns whether to display the achievement before it is earned.
	*/
	virtual bool RGSC_CALL ShowUnachieved() const = 0;

	/**
	  \return
		  Returns the label (name) of the achievement.
	*/
	virtual const char* RGSC_CALL GetLabel() const = 0;

	/**
	  \return
		  Returns the achievement description.
	*/
	virtual const char* RGSC_CALL GetDescription() const = 0;

	/**
	  \return
		  Returns the unachieved string of the achievement.
	*/
	virtual const char* RGSC_CALL GetUnachievedString() const = 0;

	/**
	  \return
		  Returns true if the achievement has been achieved.
	*/
	virtual bool RGSC_CALL IsAchieved() const = 0;

	/**
	  \return
		  If the achievement has been awarded, returns the time at which it was awarded, else zero.
	*/
 	virtual time_t RGSC_CALL GetAchievedTime() const = 0;
};

extern "C" static const RGSC_IID IID_AchievementV2 = { 0x129cce6f, 0xef04, 0x4288, { 0xbb, 0xdb, 0x50, 0xd, 0x66, 0x74, 0xba, 0xd9 } };

//! Version 2 of the achievement interface.
class IAchievementV2 : public IAchievementV1
{
	/**
	\return
		Returns the current progress of the achievement
	*/
	virtual s64 RGSC_CALL GetProgress() const = 0;
};

typedef IAchievementV2 IAchievementLatestVersion;
#define IID_IAchievementLatestVersion IID_AchievementV2

extern "C" static const RGSC_IID IID_IAchievementListV1 = {0xb834f61f, 0x1062, 0x4209, {0x81, 0x58, 0xa1, 0xf2, 0x13, 0xb1, 0xea, 0x58}};

//! Encapsulates a list of achievements.
class IAchievementList : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the achievement list interface.
class IAchievementListV1 : public IAchievementList
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	virtual u32 GetNumAchievements() const = 0;
	virtual IAchievementLatestVersion* GetAchievement(const u32 index) = 0;
};

typedef IAchievementListV1 IAchievementListLatestVersion;
#define IID_IAchievementListLatestVersion IID_IAchievementListV1

//! Achievement Manager Interface
//! Defines the public interface that game clients use to access achievement information.
//!	\example enumerating_achievements.cpp
class IAchievementManager : public IRgscUnknown
{
public:
	static const u32 MAX_NUM_ACHIEVEMENTS = 256;

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IAchievementManagerV1 = {0x3b7524e1, 0xe3a9, 0x4e80, {0xa2, 0x3e, 0xf2, 0xa7, 0xc7, 0xb3, 0xe8, 0xd6}};

//! Version 1 of the achievement manager interface.
class IAchievementManagerV1 : public IAchievementManager
{
public:
	//! Creates an enumerator that can be used to read achievement data.
	/**
	  \param riid - the RGSC_IID of the achievement list. For example: IID_IAchievementListLatestVersion
	  \param titleId - the id of the title whose achievements are to be enumerated
	  \param profileId - the id of the player whose achievements are to be enumerated
	  \param detailFlags - indicates which data is required to be enumerated. This will impact the
					   amount of memory and time it takes to enumerate the achievements.
	  \param firstAchievementId - the id of the first achievement to be read. Must be > 0.
	  \param maxAchievementsToRead - the maximum number of achievements to read, starting at
								 firstAchievementId. Must be < 256.
	  \param numBytesRequired - [out] Pointer to the size, in bytes, of the buffer needed to contain
								  the enumeration results.
	  \param handle - [out] Pointer to the handle to the created enumerator
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not signed in.
	*/
	virtual RGSC_HRESULT RGSC_CALL CreateAchievementEnumerator(RGSC_REFIID riid,
														  const ITitleId* titleId,
														  const RockstarId profileId,
														  const IAchievement::DetailFlags detailFlags,
														  const AchievementId firstAchievementId,
														  const u32 maxAchievementsToRead,
														  u32* numBytesRequired,
														  void** handle) = 0;

	//! Creates an enumerator that can be used to read achievement data.
	/**
	  \param handle - the handle returned by CreateAchievementEnumerator()
	  \param buffer - Pointer to a buffer that will store the items found during the enumeration
					  operation. This buffer must be allocated by the function caller
	  \param bufferSize - the number of bytes available in buffer. This must be >= than the
						  value of numBytesRequired returned by CreateAchievementEnumerator().
	  \param achievements - pointer to an achievement list interface with the same RGSC_IID as was
							passed to CreateAchievementEnumerator().
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not signed in.
	*/
	virtual RGSC_HRESULT RGSC_CALL EnumerateAchievements(void* handle,
													void* buffer,
													const u32 bufferSize,
													IAchievementList** achievements) = 0;

	//! Awards an achievement to the currently signed-in player.
	/**
	  \param achievementId - the id of the achievement to be awarded.
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not signed in.\n
		Other values indicate the type of error that occurred.
	  \remark - this function blocks the calling thread until the operation is complete.
				The function should be called from a worker thread.
	*/
    virtual RGSC_HRESULT RGSC_CALL WriteAchievement(const AchievementId achievementId) = 0;

#if defined(__DEV) && __DEV
	//! Deletes all achievements awarded to the currently signed-in player.
	//! Only available in debug builds for testing purposes.
	virtual RGSC_HRESULT RGSC_CALL DeleteAllAchievements() = 0;
#endif
};

extern "C" static const RGSC_IID IID_IAchievementManagerV2 = {0xa43c3cea, 0x9968, 0x4caa, {0xb8, 0x9d, 0x32, 0x87, 0x1e, 0xb, 0xd5, 0x47}};

//! Version 2 of the achievement manager interface.
class IAchievementManagerV2 : public IAchievementManagerV1
{
public:
	using IAchievementManagerV1::EnumerateAchievements;

	//! Creates an enumerator that can be used to read achievement data.
	/**
	  \param handle - the handle returned by CreateAchievementEnumerator()
	  \param buffer - Pointer to a buffer that will store the items found during the enumeration
					  operation. This buffer must be allocated by the function caller
	  \param bufferSize - the number of bytes available in buffer. This must be >= than the
						  value of numBytesRequired returned by CreateAchievementEnumerator().
	  \param achievements - pointer to an achievement list interface with the same RGSC_IID as was
							passed to CreateAchievementEnumerator().
	  \param status - can be polled to determine the status of the asynchronous operation
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not signed in.
	*/
	virtual RGSC_HRESULT RGSC_CALL EnumerateAchievements(void* handle,
													void* buffer,
													const u32 bufferSize,
													IAchievementList** achievements,
													IAsyncStatus* status) = 0;
};

extern "C" static const RGSC_IID IID_IAchievementManagerV3 = { 0x4ff0075d, 0x1064, 0x4827, { 0xa1, 0xd2, 0xba, 0x53, 0xd0, 0xce, 0x8b, 0x56 } };

//! Version 3 of the achievement manager interface.
class IAchievementManagerV3 : public IAchievementManagerV2
{
public:

	//! Sets a progress value to the given achievement id
	/**
	  \param achievementId - the id of the achievement to be updated.
	  \param progress - the progress value to be written
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not signed in.\n
		Other values indicate the type of error that occurred.
	*/
	virtual RGSC_HRESULT RGSC_CALL SetAchievementProgress(const AchievementId achievementId, const s64 progress) = 0;
};

typedef IAchievementManagerV3 IAchievementManagerLatestVersion;
#define IID_IAchievementManagerLatestVersion IID_IAchievementManagerV3

} // namespace rgsc

#endif // ACHIEVEMENT_MANAGER_INTERFACE_H
