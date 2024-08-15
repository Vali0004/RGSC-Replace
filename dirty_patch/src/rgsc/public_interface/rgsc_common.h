#ifndef RGSC_COMMON_H
#define RGSC_COMMON_H

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT
#endif
#endif /* NO_STRICT */

namespace rgsc
{

#define RGSC_SDK_VERSION (1242)

// Application User Model IDs (AppUserModelIDs) are used extensively by the taskbar in Windows 7 and later systems 
// to associate processes, files, and windows with a particular application. An application can call:
// SetCurrentProcessExplicitAppUserModelID(RGSC_AUMID); to group taskbar icons together.
// > Format - 128 chars - no spaces: CompanyName.ProductName.SubProduct.VersionInformation
//	 SubProduct and VersionInformation are optional.
#define RGSC_AUMID L"RockstarGames.SocialClub.UI.Final"
#define RGSC_AUMID_DEBUG L"RockstarGames.SocialClub.UI.Debug"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned __int64 u64;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed __int64 s64;
typedef char* Utf8String;
typedef int StringId;

#if RSG_CPU_X86
typedef unsigned int RGSC_WPARAM;
typedef long RGSC_LPARAM;
typedef long RGSC_LRESULT;
#else
typedef unsigned __int64 RGSC_WPARAM;
typedef __int64 RGSC_LPARAM;
typedef __int64 RGSC_LRESULT;
#endif

typedef struct _RGSC_RGSC_IID {
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[ 8 ];
} RGSC_IID;

typedef const RGSC_IID& RGSC_REFIID;

inline bool operator==(RGSC_REFIID src1, RGSC_REFIID src2)
{
	return ((src1.Data1 == src2.Data1) &&
		(src1.Data2 == src2.Data2) &&
		(src1.Data3 == src2.Data3) &&
		(*(__int64*)src1.Data4 == *(__int64*)src2.Data4)) ? true : false;
}

typedef long RGSC_HRESULT;

typedef s64 RockstarId;

typedef u64 RgscTitleId;
static const RgscTitleId InvalidRgscTitleId = 0;

#define DECLARE_WINDOWHANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_WINDOWHANDLE(HWnd);
typedef HWnd WindowHandle;

#define RGSC_CALL __stdcall

// same as MAX_PATH as defined in the windows header files
static const u32 RGSC_MAX_PATH = 260;

// same as RL_MAX_URL_BUF_LENGTH
static const u32 RGSC_MAX_URL_BUF_SIZE = 2048;

// steam
static const u32 RGSC_STEAM_TICKET_BUF_SIZE = 1024;
static const u32 RGSC_STEAM_TICKET_ENCODED_BUF_SIZE = (RGSC_STEAM_TICKET_BUF_SIZE * 2) + 1; // 2x for hex encoding + null term
static const u32 RGSC_STEAM_MAX_PERSONA_LENGTH = 32;
static const u32 RGSC_STEAM_MAX_PERSONA_BUF_SIZE = (4 * RGSC_STEAM_MAX_PERSONA_LENGTH) + 1; //4x for utf8 + null term

// additional session presence attributes
static const u32 RGSC_ADDITIONAL_SESSION_ATTR_BUF_SIZE = 64;

// telemetry
static const u32 RGSC_TELEMETRY_MAX_NAME_BUF_SIZE = 32;
static const u32 RGSC_TELEMETRY_MAX_BUF_SIZE = 256;

// input
static const u32 RGSC_MAX_PADS = 4;

extern "C" static const RGSC_IID IID_IRgscUnknown = {0x298e73ac, 0x3a30, 0x47a5, {0xb4, 0x50, 0xb9, 0x9a, 0x24, 0xbc, 0xc4, 0x27}};

//! COM-like queryable interface used as the root object for most of the platform's classes.
class IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Language to display in the Social Club UI
enum RgscLanguage
{
	// More languages can be added but do not change the values of existing enums. 
	RGSC_LANGUAGE_INVALID				= 0,
	RGSC_LANGUAGE_ENGLISH				= 1,
	RGSC_LANGUAGE_SPANISH				= 2,
	RGSC_LANGUAGE_FRENCH				= 3,
	RGSC_LANGUAGE_GERMAN				= 4,
	RGSC_LANGUAGE_ITALIAN				= 5,
	RGSC_LANGUAGE_JAPANESE				= 6,
	RGSC_LANGUAGE_RUSSIAN				= 7,
	RGSC_LANGUAGE_PORTUGUESE			= 8,
	RGSC_LANGUAGE_POLISH				= 9,
	RGSC_LANGUAGE_KOREAN				= 10,
	RGSC_LANGUAGE_CHINESE_TRADITIONAL	= 11, // formerly named: RGSC_LANGUAGE_CHINESE
	RGSC_LANGUAGE_MEXICAN				= 12,
	RGSC_LANGUAGE_CHINESE_SIMPLIFIED	= 13,

	RGSC_LANGUAGE_NUM_LANGUAGES
};

//! Modifiers to associate with keyboard events.
enum RgscKeyModifier
{
	RGSC_SHIFT_MOD      = 1 << 0,
	RGSC_CONTROL_MOD    = 1 << 1,
	RGSC_ALT_MOD        = 1 << 2,
};

//! Modifiers to associate with mouse events.
enum RgscMouseModifier
{
	RGSC_MOUSE_MOD_NONE		= 1 << 0,
	RGSC_MOUSE_MOD_NO_MAP	= 1 << 1, // Do not map the mouse position to client coordinates
};

//! Return Codes meant to mirror error/success codes from winerror.h
enum RgscReturnCodes
{
	RGSC_INVALIDARG		= 0x80070057L,	// Matches E_INVALIDARG
	RGSC_NOINTERFACE	= 0x80004002L,	// Matches E_NOINTERFACE
	RGSC_FAIL			= 0x80004005L,	// Matches E_FAIL
	RGSC_OK = 0L,						// Matches S_OK
};

//! Services to use when authenticating with Social Club
enum RgscAuthServices
{
	RGSC_AUTH_ASMX			= 0, // Original ASP service(default)
	RGSC_AUTH_LEGACY_SVC	= 1, // WCF service that uses same protocol as ASP service (POST form request, XML response)
	RGSC_AUTH_SVC			= 2, // WCF service that uses JSON for both request and response.
};

//! Method used to interact with Social Club UI
enum InputMethod
{
	RGSC_IM_KEYBOARDMOUSE = 0,
	RGSC_IM_CONTROLLER = 1
};

//! Type of input controller used with RgscGamePad
enum ControllerType
{
	RGSC_CT_UNKNOWN = 0,	// Unknown controller type
	RGSC_CT_DINPUT,			// Generic/unknown direct input controller
	RGSC_CT_XINPUT,			// Generic/unknown xinput controller
	RGSC_CT_XBOX360,		// Xbox 360 controller
	RGSC_CT_XBOXONE,		// Xbox One controller
	RGSC_CT_PS3,			// PlayStation 3 controller
	RGSC_CT_PS4,			// PlayStation 4 controller
	RGSC_CT_OCULUS,			// Oculus controller
	RGSC_CT_OPENVR,			// OpenVR controller
};

//! Type of cursor to display on screen.
//  Designed to match CEF's cef_cursor_type_t
enum RgscCursorType
{
	RGSC_CURSOR_TYPE_INVALID = -1,
	RGSC_CURSOR_POINTER = 0,
	RGSC_CURSOR_CROSS,
	RGSC_CURSOR_HAND,
	RGSC_CURSOR_IBEAM,
	RGSC_CURSOR_WAIT,
	RGSC_CURSOR_HELP,
	RGSC_CURSOR_EASTRESIZE,
	RGSC_CURSOR_NORTHRESIZE,
	RGSC_CURSOR_NORTHEASTRESIZE,
	RGSC_CURSOR_NORTHWESTRESIZE,
	RGSC_CURSOR_SOUTHRESIZE,
	RGSC_CURSOR_SOUTHEASTRESIZE,
	RGSC_CURSOR_SOUTHWESTRESIZE,
	RGSC_CURSOR_WESTRESIZE,
	RGSC_CURSOR_NORTHSOUTHRESIZE,
	RGSC_CURSOR_EASTWESTRESIZE,
	RGSC_CURSOR_NORTHEASTSOUTHWESTRESIZE,
	RGSC_CURSOR_NORTHWESTSOUTHEASTRESIZE,
	RGSC_CURSOR_COLUMNRESIZE,
	RGSC_CURSOR_ROWRESIZE,
	RGSC_CURSOR_MIDDLEPANNING,
	RGSC_CURSOR_EASTPANNING,
	RGSC_CURSOR_NORTHPANNING,
	RGSC_CURSOR_NORTHEASTPANNING,
	RGSC_CURSOR_NORTHWESTPANNING,
	RGSC_CURSOR_SOUTHPANNING,
	RGSC_CURSOR_SOUTHEASTPANNING,
	RGSC_CURSOR_SOUTHWESTPANNING,
	RGSC_CURSOR_WESTPANNING,
	RGSC_CURSOR_MOVE,
	RGSC_CURSOR_VERTICALTEXT,
	RGSC_CURSOR_CELL,
	RGSC_CURSOR_CONTEXTMENU,
	RGSC_CURSOR_ALIAS,
	RGSC_CURSOR_PROGRESS,
	RGSC_CURSOR_NODROP,
	RGSC_CURSOR_COPY,
	RGSC_CURSOR_NONE,
	RGSC_CURSOR_NOTALLOWED,
	RGSC_CURSOR_ZOOMIN,
	RGSC_CURSOR_ZOOMOUT,
	RGSC_CURSOR_GRAB,
	RGSC_CURSOR_GRABBING,
	RGSC_CURSOR_CUSTOM,
};

//! Error codes returned during SDK initialization.
enum FatalErrorCodes
{
	// do not remove or renumber these. Only add new error codes to the end.
	FATAL_ERROR_INIT_RAGE = 1001,
	FATAL_ERROR_INIT_FILE_SYSTEM = 1002,
	FATAL_ERROR_INIT_JSON = 1004,
	FATAL_ERROR_INIT_METADATA = 1005,
	FATAL_ERROR_INIT_ACHIEVEMENT_MANAGER = 1006,
	FATAL_ERROR_INIT_PLAYER_MANAGER = 1007,
	FATAL_ERROR_INIT_GAMERPIC_MANAGER = 1008,
	FATAL_ERROR_INIT_PROFILE_MANAGER = 1009,
	FATAL_ERROR_INIT_PRESENCE_MANAGER = 1010,
	FATAL_ERROR_INIT_COMMERCE_MANAGER = 1011,
	FATAL_ERROR_INIT_TASK_MANAGER = 1012,
	FATAL_ERROR_INIT_UI = 1014,
	FATAL_ERROR_INIT_SUBPROCESS_NOT_FOUND = 1015,
	FATAL_ERROR_INIT_SUBPROCESS_WRONG_VERSION = 1016,
	FATAL_ERROR_TELEMETRY_MANAGER = 1017,
	FATAL_ERROR_STEAM_MANAGER = 1018,
	FATAL_ERROR_NETWORK_INTERFACE = 1019,
	FATAL_ERROR_CLOUD_INTERFACE = 1020,
	FATAL_ERROR_INIT_LOGIN = 1021,
	FATAL_ERROR_MULTI_FACTOR_AUTH = 1022
};

//! Notifications returned to the client via delegate callbacks.
enum NotificationType
{
	// don't change or remove these values or you'll break existing games.
	// we can add new ones.
	NOTIFY_SOCIAL_CLUB_EVENT = 1,
	NOTIFY_SIGN_IN_STATE_CHANGED = 2,	// param is a pointer to a u32 bitflag, combination of SignInState flags
	NOTIFY_ROS_TICKET_CHANGED = 3,		// param is a pointer to the ticket xml response as a string.
	NOTIFY_FRIEND_STATUS_CHANGED = 4,
	NOTIFY_GAME_INVITE_ACCEPTED = 5,	// Triggers when a player accepts a game invite.
										// param is a pointer to an IPresenceMessage.
										// The data will be out of scope after the notification has been sent to the game.

	NOTIFY_JOINED_VIA_PRESENCE = 6,		// Triggers when a player joins a game via presence.
										// param is a pointer to an IPresenceMessage.
										// The data will be out of scope after the notification has been sent to the game.

	NOTIFY_FATAL_ERROR = 7,				// param is an int representing the error code. See FatalErrorCodes. Make sure to handle other codes that don't exist yet (later DLLs can have additional codes).
	NOTIFY_UI_EVENT = 8,				// param is a json string that contains details of the event. Example: {"EventId": 23, "Data" : {"ButtonId" : 4}}. See RGSC_RAISE_UI_EVENT().
	NOTIFY_EXTERNAL_BROWSER_URL = 9,	// param is a url to be launched externally by the game client
	NOTIFY_REFRESH_STEAM_AUTH_TICKET = 10, // triggers when the SCUI requires a new steam ticket,
	NOTIFY_ENTITLEMENT_EVENT = 11,		// param is a json string including the product ID and action. Example: { "ProductId": "TEST-GTAV-SHARK-MULTI", "Action" : "Download" }
	NOTIFY_CLOUD_SAVE_ENABLED_UPDATED = 12,	// the param is the ros title name of the cloud save manifest that has been updated.
	NOTIFY_BROWSER_CREATED = 13,		// param is a 'WindowHandle' representing the browser that has been created.
};

//! Flags to indicate the type of signin event that has occurred.
enum SignInStateFlags
{        
	STATE_SIGNED_IN = 0x0001,      //Gamer signed in locally        
	STATE_SIGNED_OUT = 0x0002,     //Gamer signed out locally        
	STATE_SIGNED_ONLINE = 0x0004,  //Gamer went online        
	STATE_SIGNED_OFFLINE = 0x0008, //Gamer went offline
	STATE_KICKED_BY_DUPLICATE_SIGN_IN = 0x0010, //The same account was signed in somewhere else
	STATE_SIGNED_CONNECTION_LOST = 0x0020, //A connection we depended on was lost
};

//! Flags to indicate which actions to take when a game crashes. Used by game launchers.
enum OnGameCrashActionFlags
{
	OGC_UNADVERTISE_ALL_MATCHES		= 0x0001,	// Unadvertise the user from all social club matchmaking sessions
	OGC_PRESENCE_SIGNOUT			= 0x0002,	// Sign out from social club presence
};

//! Filter window events to only interact with certain edges of the window.
enum WindowEdgeFlags
{
	WE_NONE		   = 0, // 0
	WE_LEFT        = 0x001,	// Action should apply to the left window edge
	WE_RIGHT       = 0x002, // Action should apply to the right window edge
	WE_TOP         = 0x004, // Action should apply to the top window edge
	WE_BOTTOM	   = 0x008, // Action should apply to the bottom window edge

	WE_ALL = WE_LEFT | WE_RIGHT | WE_TOP | WE_BOTTOM
};

// These are the window messages that can be handled from the borderless window wrapper.
// On windows, you can send a message directly to that borderless window handle (WindowHandle),
// using PostMessage or SendMessage as this enum mirrors custom windows messages (beginning with WM_USER
// and ending with WM_APP). The WPARAM and LPARAM parameters must be defined for each message. 
// For non-windows platforms, the RgscUi interface can also be used to relay the message. 
enum CustomWindowMessages
{
	// Start with WM_USER
	MSG_FIRST = 0x0400, // WM_USER	

	//////////////////////////////////////////
	// All Custom Messages to be defined here.
	//////////////////////////////////////////
	
	// Request the borderless window to bring another window to the foreground.
	//  In order to avoid race conditions with window activation and focus when a client
	//  wishes to bring a window to the front, defer the operation to the borderless window.
	// PARAMS:
	//  WPARAM - WindowHandle of the window to bring to front.
	//  LPARAM - unused
	MSG_BRING_WINDOW_TO_FRONT,
	
	// End with WM_APP
	MSG_LAST = 0x8000, // WM_APP
};

//! For applications that leverage Social Club, we want to maintain a consistent list of fatal exit 
//  codes that the application can return in order to display error messages in the game launcher.
//  The only standard exit codes in Windows are EXIT_SUCCESS = 0 (and somewhat EXIT_FAILURE=1), so we have leeway in creating our own.
//  We want to avoid using system error codes which fall within the range 0-16000 (https://msdn.microsoft.com/library/ms681381(v=vs.85)
//  We also want to avoid known COM exception codes, i.e. 0x8000000 - 0x8000FFF
enum CustomExitCodes
{
	// DO NOT INSERT CODES INTO THIS LIST
	// Codes must be appended - inserting a code into this list will break existing titles.
	RGSC_EXIT_SUCCESS			= 0,		// EXIT_SUCCESS from Windows
	RGSC_EXIT_FAILURE			= 1,		// EXIT_FAILURE from Windows
	RGSC_EXIT_SC_INIT			= 622000,	// App could not initialize the Social Club SDK
	RGSC_EXIT_STEAM_RESTART		= 622001,	// App is restarting to launch from Steam
	RGSC_EXIT_STEAM_API_INIT	= 622002,	// App could not initialize the Steam API
	RGSC_EXIT_NO_HMD_MODE		= 622003,	// App did not specify which type of HMD device to use.
	RGSC_EXIT_NO_HMD_INSTALL	= 622004,	// App did not appear to have an HMD device installed.
	RGSC_EXIT_NO_HMD_DEVICE		= 622005,	// App did not appear to have an HMD device plugged in and available.
	RGSC_EXIT_OCULUS_API_INIT	= 622006,	// App could not initialize the Oculus Platform API
	RGSC_EXIT_OCULUS_ENTITLEMENT_FAIL = 622007,	// User not entitled to play on Oculus Store
};

//! Represents the state of a window: maximized, minimized or normal. 
//  The default uninitialized state will be 'unknown' until a windows message is posted
//  that updates the state.
enum WindowState
{
	WS_UNKNOWN,		// The state of the window is unknown.
	WS_NORMAL,		// The state of the window is neither maximized or minimized.
	WS_MINIMIZED,	// The state of the window is minimized.
	WS_MAXIMIZED	// The state of the window is maximized.
};

// these string functions are used to make copies of variable-length 
// strings passed between the calling process and the SC DLL.
template< typename T >
int
RgscStringLength(const T *s)
{
	if(s)
	{
		const T* e = s;

		for(; '\0' != *e; ++e)
		{
		}

		return int(e - s);
	}
	else
	{
		return 0;
	}
}

template< typename T >
T*
RgscStringDuplicate(const T* str)
{
	if(!str)
		return 0;
	int siz = (int)RgscStringLength(str) + 1;
	return (T*)memcpy(rage_new T[siz], str, sizeof(T) * siz);
}

template< typename T >
inline
void
RgscStringFree(T* str)
{
	delete[](T*) str;
}

} // namespace rgsc

#endif // RGSC_COMMON_H
