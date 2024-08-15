#ifndef PLAYERS_INTERFACE_H
#define PLAYERS_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"

namespace rgsc
{

//! This class is designed to be an extensible version of a plain-old-data structure.
class IPlayer : public IRgscUnknown
{
public:
	static const u32 MAX_NICKNAME_CHARS = 51;

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_PlayerV1 = {0xc3898f63, 0x13af, 0x4983, {0x91, 0x65, 0x6b, 0xb2, 0xb9, 0x9b, 0x48, 0xd0}};

//! Version 1 of the player interface.
class IPlayerV1 : public IPlayer
{
public:
	enum Relationship
	{
		// Invalid relationship type.
		RELATIONSHIP_INVALID = 0x00,

		// They are neither friends, inviting, nor blocking each other.
		RELATIONSHIP_NONE = 0x01,

		// I am blocking them
		RELATIONSHIP_BLOCKED_BY_ME = 0x02,

		// They are blocking me
		RELATIONSHIP_BLOCKED_BY_THEM = 0x04,

		// Both sides are blocking the other
		RELATIONSHIP_BLOCKED_BY_BOTH = RELATIONSHIP_BLOCKED_BY_ME | RELATIONSHIP_BLOCKED_BY_THEM,

		// I am inviting them
		RELATIONSHIP_INVITED_BY_ME = 0x08,

		// They are inviting me
		RELATIONSHIP_INVITED_BY_THEM = 0x10,

		// We are friends
		RELATIONSHIP_FRIEND = 0x20,
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	/**
	  \return
		  Returns the player's RockstarId.
	*/
	virtual RockstarId RGSC_CALL GetRockstarId() const = 0;

	/**
	  \return
		  Returns the player's name.
	*/
	virtual const char* RGSC_CALL GetName() const = 0;

	/**
	  \return
		  Returns the player's relationship to the local player.
	*/
	virtual Relationship RGSC_CALL GetRelationship() const = 0;

	/**
	  \return
		  Returns whether the player is online.
		  Only valid if GetRelationship() returns RELATIONSHIP_FRIEND
	*/
	virtual bool RGSC_CALL IsOnline() const = 0;

	/**
	  \return
		  Returns whether the player is playing the same title.
		  Only valid if GetRelationship() returns RELATIONSHIP_FRIEND
	*/
	virtual bool RGSC_CALL IsPlayingSameTitle() const = 0;
};

extern "C" static const RGSC_IID IID_PlayerV2 = {0xe152d8de, 0x7d1, 0x4df9, {0xab, 0x62, 0x9b, 0xdf, 0x59, 0x80, 0x7, 0x29}};

//! Version 2 of the player interface.
class IPlayerV2 : public IPlayerV1
{
public:

	enum PlayerFlags
	{
		// Player is in a joinable multiplayer session.
		PLAYER_FLAG_IN_JOINABLE_SESSION = 0x01,
		PLAYER_FLAG_IN_JOINABLE_PARTY = 0x02,
	};

	/**
	  \return
		  Returns the player's flags (see PlayerFlags enum).
	*/
	virtual unsigned RGSC_CALL GetFlags() const = 0;
};

extern "C" static const RGSC_IID IID_PlayerV3 = {0x32059123, 0x7561, 0x46fd, {0x84, 0x8, 0x4b, 0xbb, 0x23, 0xe6, 0xeb, 0x90}};

//! Version 3 of the player interface.
class IPlayerV3 : public IPlayerV2
{
public:

	virtual const char* RGSC_CALL GetAvatarUrl() const = 0;
};


typedef IPlayerV3 IPlayerLatestVersion;
#define IID_IPlayerLatestVersion IID_PlayerV3

extern "C" static const RGSC_IID IID_IPlayerListV1 = {0xd1ae111a, 0x9f4e, 0x4fd4, {0xa4, 0x90, 0x27, 0x80, 0xd1, 0x72, 0xeb, 0xee}};

//! Encapsulates a list of players.
class IPlayerList : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the player list interface.
class IPlayerListV1 : public IPlayerList
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	virtual u32 RGSC_CALL GetNumPlayers() const = 0;
	virtual IPlayerLatestVersion* RGSC_CALL GetPlayer(const u32 index) = 0;
};

typedef IPlayerListV1 IPlayerListLatestVersion;
#define IID_IPlayerListLatestVersion IID_IPlayerListV1

//! Player Manager Interface
//! Defines the public interface that game clients use to access friend and related player information.
class IPlayerManager : public IRgscUnknown
{
public:
	static const u32 MAX_FRIENDS = 250;						// needs to match RL_FRIENDS_MAX_FRIENDS

	// these may be exposed in the future

// 	static const u32 MAX_PENDING_INVITES_SENT = 100;		// needs to match RL_FRIEND_MAX_PENDING_INVITES_SENT
// 	static const u32 MAX_PENDING_INVITES_RECEIVED = 100;	// needs to match RL_FRIEND_MAX_PENDING_INVITES_RECEIVED
// 	static const u32 MAX_BLOCKED_PLAYERS = 1000;			// needs to match RL_FRIENDS_MAX_BLOCKED_PLAYERS

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IPlayerManagerV1 = {0x308783b7, 0xbcde, 0x4a62, {0x8c, 0x21, 0xbc, 0xc2, 0x9e, 0x1a, 0x6a, 0x6a}};
extern "C" static const RGSC_IID IID_IPlayerManagerV2 = {0x4c6bc399, 0xa96c, 0x4b7e, {0xb1, 0x55, 0xe5, 0x98, 0x26, 0xa7, 0x6, 0x71 }};

//! Version 1 of the player manager interface.
class IPlayerManagerV1 : public IPlayerManager
{
public:
	enum PlayerListType
	{
		LIST_TYPE_INVALID = 0x00,
		LIST_TYPE_FRIENDS = 0x01,
		LIST_TYPE_FRIENDS_WITH_PRESENCE = 0x02,

		// these may be exposed in the future
// 		LIST_TYPE_INVITES_SENT = 0x02,
// 		LIST_TYPE_INVITES_RECEIVED = 0x04,
// 		LIST_TYPE_BLOCKED_PLAYERS = 0x08,
	};

	//! Creates an enumerator that can be used to read lists of players and their relationships with the signed-in player.
	/**
	  \param riid - the RGSC_IID of the player list. For example: IID_IPlayerListLatestVersion
	  \param rockstarId - the id of the player whose friends/lists are to be enumerated
	  \param firstPlayerIndex - the index of the first player to be read.
	  \param maxPlayersToRead - the maximum number of players to read, starting at firstPlayerIndex.
	  \param numBytesRequired - [out] Pointer to the size, in bytes, of the buffer needed to contain
								  the enumeration results.
	  \param handle - [out] Pointer to the handle to the created enumerator
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not online.
	*/
	virtual RGSC_HRESULT RGSC_CALL CreatePlayerEnumerator(RGSC_REFIID riid,
														 const RockstarId rockstarId,
														 const PlayerListType playerListType,
														 const u32 firstPlayerIndex,
														 const u32 maxPlayersToRead,
														 u32* numBytesRequired,
														 void** handle) = 0;

	//! Creates an enumerator that can be used to read player data.
	/**
	  \param handle - the handle returned by CreatePlayerEnumerator()
	  \param buffer - Pointer to a buffer that will store the items found during the enumeration
					  operation. This buffer must be allocated by the function caller
	  \param bufferSize - the number of bytes available in buffer. This must be >= than the
						  value of numBytesRequired returned by CreatePlayerEnumerator().
	  \param players - pointer to a player list interface with the same RGSC_IID as was
					   passed to CreatePlayerEnumerator().
	  \return
		RGSC_OK - success.\n
		ERROR_NOT_LOGGED_ON - if the local player is not online.
	*/
	virtual RGSC_HRESULT RGSC_CALL EnumeratePlayers(void* handle,
												   void* buffer,
												   const u32 bufferSize,
												   IPlayerList** players,
												   IAsyncStatus* status) = 0;

	//Returns true if the specified player is on the local player's friend list
	virtual bool RGSC_CALL IsFriend(const RockstarId rockstarId) = 0;

	//Shows the friend request UI (this allows you to add a friend through the SC UI instead of directly via SendInvite())
	virtual RGSC_HRESULT RGSC_CALL ShowFriendRequestUi(const RockstarId rockstarId) = 0;

	//Shows a player's profile UI
	virtual RGSC_HRESULT RGSC_CALL ShowPlayerProfileUi(const RockstarId rockstarId) = 0;

 	//Sends a friend request
 	virtual RGSC_HRESULT RGSC_CALL SendInvite(const RockstarId rockstarId, IAsyncStatus* status) = 0;

	// these may be exposed in the future

	/*
	//Cancels a sent invite
	virtual RGSC_HRESULT RGSC_CALL CancelInvite(const RockstarId rockstarId, IAsyncStatus* status) = 0;

	//Declines a received invite
	virtual RGSC_HRESULT RGSC_CALL DeclineInvite(const RockstarId rockstarId, IAsyncStatus* status) = 0;

	//Accepts a received invite
	virtual RGSC_HRESULT RGSC_CALL AcceptInvite(const RockstarId rockstarId, IAsyncStatus* status) = 0;

 	//Removes a friend from the local gamer's friend list and removes the local gamer from the remote gamer's friend list
 	virtual RGSC_HRESULT RGSC_CALL DeleteFriend(const RockstarId rockstarId, IAsyncStatus* status) = 0;

	//Adds a remote player to the local player's block list
	virtual RGSC_HRESULT RGSC_CALL BlockPlayer(const RockstarId rockstarId, IAsyncStatus* status) = 0;

	//Removes a player from the local player's block list
	virtual RGSC_HRESULT RGSC_CALL UnblockPlayer(const RockstarId rockstarId, IAsyncStatus* status) = 0;
	*/

	//Returns true if the specified player is on the local player's block list
	virtual bool RGSC_CALL IsBlocked(const RockstarId rockstarId) = 0;
};

//! Version 2 of the player manager interface.
class IPlayerManagerV2 : public IPlayerManagerV1
{
public:
	// Expose rlFriendsManager functionality
	virtual unsigned RGSC_CALL GetTotalNumFriends() = 0;
	virtual bool RGSC_CALL RequestFriendSync() = 0;
	virtual bool RGSC_CALL IsSyncingFriends() = 0;

	//Shows the Friends Search UI 
	virtual RGSC_HRESULT RGSC_CALL ShowFriendSearchUi() = 0;
};

typedef IPlayerManagerV2 IPlayerManagerLatestVersion;
#define IID_IPlayerManagerLatestVersion IID_IPlayerManagerV2

} // namespace rgsc

#endif // PLAYERS_INTERFACE_H
