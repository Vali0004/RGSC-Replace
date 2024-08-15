#ifndef RGSC_UI_INTERFACE_H
#define RGSC_UI_INTERFACE_H

#include "rgsc_common.h"

#include <cstring>
#include <stdlib.h>

namespace rgsc
{

class IActivation;
class IPatching;

// =====================================================================================================================
// IRgscPlatformMessageHandler
// =====================================================================================================================
class IRgscPlatformMessageHandler : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

class IRgscPlatformMessageHandlerV1 : public IRgscPlatformMessageHandler
{
public:

#if !__TOOL
	enum RgscPlatformMsg : unsigned
#else // !__TOOL
	enum RgscPlatformMsg // : unsigned
#endif // !__TOOL
	{
		RGSC_MSG_NULL = 0,
		RGSC_MSG_DEVICECHANGE,		// WM_DEVICECHANGE
		RGSC_MSG_MOUSEMOVE,			// WM_MOUSEMOVE
		RGSC_MSG_MOUSEWHEEL,		// WM_MOUSEWHEEL
		RGSC_MSG_LBUTTONDOWN,		// WM_LBUTTONDOWN
		RGSC_MSG_LBUTTONDBLCLK,		// WM_LBUTTONDBLCLK
		RGSC_MSG_LBUTTONUP,			// WM_LBUTTONUP
		RGSC_MSG_RBUTTONDOWN,		// WM_RBUTTONDOWN
		RGSC_MSG_RBUTTONUP,			// WM_RBUTTONUP
		RGSC_MSG_RBUTTONDBLCLK,		// WM_RBUTTONDBLCLK
		RGSC_MSG_MBUTTONDOWN,		// WM_MBUTTONDOWN
		RGSC_MSG_MBUTTONUP,			// WM_MBUTTONUP
		RGSC_MSG_MBUTTONDBLCLK,		// WM_MBUTTONDBLCLK
		RGSC_MSG_KEYUP,				// WM_KEYUP
		RGSC_MSG_KEYDOWN,			// WM_KEYDOWN
		RGSC_MSG_CHAR,				// WM_CHAR
		RGSC_MSG_SETCURSOR,			// WM_SETCURSOR
		RGSC_MSG_IME_SETCONTEXT,	// WM_IME_SETCONTEXT:
		RGSC_MSG_IME_STARTCOMPOSITION,	// WM_IME_STARTCOMPOSITION:
		RGSC_MSG_IME_COMPOSITION,	// WM_IME_COMPOSITION:
		RGSC_MSG_IME_ENDCOMPOSITION,// WM_IME_ENDCOMPOSITION:
		RGSC_MSG_IME_NOTIFY,		// WM_IME_NOTIFY:
		RGSC_MSG_IME_CHAR,			// WM_IME_CHAR:
		RGSC_MSG_TABLET_QUERYSYSTEMGESTURESTATUS, // WM_TABLET_QUERYSYSTEMGESTURESTATUS
		RGSC_MSG_MOUSEFIRST,		// WM_MOUSEFIRST (range start)
		RGSC_MSG_MOUSELAST,			// WM_MOUSELAST (range end)
		RGSC_MSG_NCCALCSIZE,		// WM_NCCALCSIZE
		RGSC_MSG_NCHITTEST,			// WM_NCHITTEST
	};

	enum ResponseBehaviour
	{
		FORWARD,
		RETURN_VALUE
	};

	//! Returns the response behaviour of the message handler.
	/**
	  \param bIsScuiVisible - The response behaviour can differ when the SCUI is on screen and visible
	*/
	virtual ResponseBehaviour RGSC_CALL GetResponseBehaviour(bool bIsScuiVisible) = 0;

	//! The value returned by the message handler when the response type is set
	//	to 'RETURN_VALUE'. Undefined behaviour when the response is of type 'FORWARD'
	/**
	  \param bIsScuiVisible - The response behaviour can differ when the SCUI is on screen and visible
	*/
	virtual s64 RGSC_CALL GetReturnValue(bool bIsScuiVisible) = 0;

	//! The specific RgscPlatformMsg (windows: WPARAM/msg) that this message handler applies to. For example, WM_KEYDOWN.
	//	To capture a range of messages, use GetStartMessageRange/GetEndMessageRange.
	virtual RgscPlatformMsg RGSC_CALL GetMessageToHandle() = 0;

	//! The starting value of a message range. For example, all windows mouse events
	// could be captured using a range of RGSC_MSG_MOUSEFIRST(WM_MOUSEFIRST) and RGSC_MSG_MOUSELAST(WM_MOUSELAST). 
	// In this example, RGSC_MSG_MOUSEFIRST would be returned for GetStartMessageRange();
	virtual RgscPlatformMsg RGSC_CALL GetStartMessageRange() = 0;

	//! The starting value of a message range. For example, all windows mouse events
	// could be captured using a range of RGSC_MSG_MOUSEFIRST(WM_MOUSEFIRST) and RGSC_MSG_MOUSELAST(WM_MOUSELAST). 
	// In this example, RGSC_MSG_MOUSELAST would be returned for GetEndMessageRange();
	virtual RgscPlatformMsg RGSC_CALL GetEndMessageRange() = 0;
};

extern "C" static const RGSC_IID IID_IRgscMessageHandlerV1 = { 0x7074e69b, 0xa2e2, 0x4b7f, { 0xa9, 0xda, 0xef, 0xe7, 0xe8, 0x5a, 0xcf, 0xbb } };

//! Interface to the RGSC Platform Message Handler
class RgscPlatformMessageHandler : public IRgscPlatformMessageHandlerV1
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
			pUnknown = static_cast<IRgscPlatformMessageHandler*>(this);
		}
		else if(riid == IID_IRgscMessageHandlerV1)
		{
			pUnknown = static_cast<IRgscPlatformMessageHandlerV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	RgscPlatformMessageHandler()
	{
		m_Behaviours[SCUI_VISIBLE] = FORWARD;
		m_Behaviours[SCUI_HIDDEN] = FORWARD;
		m_ReturnValues[SCUI_VISIBLE] = 0;
		m_ReturnValues[SCUI_HIDDEN] = 0;
		m_Message = RGSC_MSG_NULL;
		m_StartMessageRange = RGSC_MSG_NULL;
		m_EndMessageRange = RGSC_MSG_NULL;
	}

	RgscPlatformMessageHandler(ResponseBehaviour scuiVisibleBehaviour, ResponseBehaviour scuiHiddenBehaviour, RgscPlatformMsg message, s64 scuiVisibleReturnValue, s64 scuiHiddenReturnValue)
	{
		m_StartMessageRange = RGSC_MSG_NULL;
		m_EndMessageRange = RGSC_MSG_NULL;
		
		SetBehaviours(scuiVisibleBehaviour, scuiHiddenBehaviour);
		SetReturnValues(scuiVisibleReturnValue, scuiHiddenReturnValue);
		SetMessageToHandle(message);
	}

	RgscPlatformMessageHandler(ResponseBehaviour scuiVisibleBehaviour, ResponseBehaviour scuiHiddenBehaviour, RgscPlatformMsg start, RgscPlatformMsg end, s64 scuiVisibleReturnValue, s64 scuiHiddenReturnValue)
	{
		m_Message = RGSC_MSG_NULL;

		SetBehaviours(scuiVisibleBehaviour, scuiHiddenBehaviour);
		SetReturnValues(scuiVisibleReturnValue, scuiHiddenReturnValue);
		SetMessageRange(start, end);
	}

	virtual void SetBehaviours(ResponseBehaviour scuiVisibleBehaviour, ResponseBehaviour scuiHiddenBehaviour)
	{
		m_Behaviours[SCUI_VISIBLE] = scuiVisibleBehaviour;
		m_Behaviours[SCUI_HIDDEN] = scuiHiddenBehaviour;
	}

	virtual ResponseBehaviour RGSC_CALL GetResponseBehaviour(bool bIsScuiVisible)
	{
		return m_Behaviours[bIsScuiVisible ? SCUI_VISIBLE : SCUI_HIDDEN];
	}

	virtual void SetReturnValues(s64 scuiVisibleReturnValue, s64 scuiHiddenReturnValue)
	{
		m_ReturnValues[SCUI_VISIBLE] = scuiVisibleReturnValue;
		m_ReturnValues[SCUI_HIDDEN] = scuiHiddenReturnValue;
	}

	virtual s64 RGSC_CALL GetReturnValue(bool bIsScuiVisible)
	{
		return m_ReturnValues[bIsScuiVisible ? SCUI_VISIBLE : SCUI_HIDDEN];
	}

	virtual void SetMessageToHandle(RgscPlatformMsg message)
	{
		m_Message = message;
	}

	virtual RgscPlatformMsg RGSC_CALL GetMessageToHandle()
	{
		return m_Message;
	}

	virtual void RGSC_CALL SetMessageRange(RgscPlatformMsg start, RgscPlatformMsg end)
	{
		m_StartMessageRange = start;
		m_EndMessageRange = end;
	}

	virtual RgscPlatformMsg RGSC_CALL GetStartMessageRange()
	{
		return m_StartMessageRange;
	}

	virtual RgscPlatformMsg RGSC_CALL GetEndMessageRange()
	{
		return m_EndMessageRange;
	}

private:

	enum ScuiVisibilityIdx
	{
		SCUI_VISIBLE,
		SCUI_HIDDEN,
		SCUI_NUM
	};

	ResponseBehaviour m_Behaviours[SCUI_NUM];
	s64 m_ReturnValues[SCUI_NUM];

	// Message(s) to handle. Message and Range and mutually exclusive.
	RgscPlatformMsg m_Message;
	RgscPlatformMsg m_StartMessageRange;
	RgscPlatformMsg m_EndMessageRange;
};

// =====================================================================================================================
// RgscUiWindowConfiguration Interface
// =====================================================================================================================
class IRgscUiWindowConfiguration : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

class IRgscUiWindowConfigurationV1 : public IRgscUiWindowConfiguration
{
public:
	
	//! Returns the window coordinates: x, y, width, height
	virtual int RGSC_CALL GetX() = 0; 
	virtual int RGSC_CALL GetY() = 0;
	virtual int RGSC_CALL GetWidth() = 0;
	virtual int RGSC_CALL GetHeight() = 0;

	//! Returns the window handle that the window should be created in (i.e. immediate parent)
	virtual WindowHandle RGSC_CALL GetParent() = 0;
	
	//! Returns the root parent, which is the parent-most window in the chain (representing the outer window)
	virtual WindowHandle RGSC_CALL GetRootParent() = 0;

	//! Returns the caption height property for the window in pixels. This represents the height of the draggable (HTCAPTION) section of the window.
	virtual int RGSC_CALL GetCaptionHeight() = 0;

	//! Returns the non-client area border width. Input sent to the pixels within this width of the border are not considered within the client area.
	//	A window that maintains it native border would simply return zero.
	virtual int RGSC_CALL GetBorderWidth() = 0;

	//! A collection of WindowEdgeFlags that dictate which border edges should be resizable (i.e. return a non-HTCLIENT response when the mouse
	//	is within border width of the edge of the client rect.
	virtual int RGSC_CALL GetResizeEdgeFlags() = 0; 

	//! When resizing the lower right corner, the size grip size is used instead of the border width. This allows for rendering a size grip and is
	//	the most typical resize operation. The widht/height in pixels is returned here.
	virtual int RGSC_CALL GetSizeGripSize() = 0;
};

class IRgscUiWindowConfigurationV2 : public IRgscUiWindowConfigurationV1
{
public:

	//! Gets the minimum size of the window
	virtual int RGSC_CALL GetMinimumWidth() = 0;
	virtual int RGSC_CALL GetMinimumHeight() = 0;

	//! Gets the maximum size of the window
	virtual int RGSC_CALL GetMaximumWidth() = 0;
	virtual int RGSC_CALL GetMaximumHeight() = 0;

	//! Sets the default 'minimize on close' behaviour of the window. When true, essentially sets 
	//  the window's CanClose (RgscUi::SetWindowCanClose) property to false.
	virtual bool RGSC_CALL ShouldMinimizeOnClose() = 0;

	//! Gets the desired title for the window. Will also be used for the class name when registering the window.
	virtual const wchar_t* RGSC_CALL GetWindowTitle() = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiWindowConfigurationV1 = { 0x9e1ca185, 0xe4e5, 0x4c33, { 0x96, 0xe0, 0x25, 0x2f, 0x82, 0x87, 0xe6, 0xab } };
extern "C" static const RGSC_IID IID_IRgscUiWindowConfigurationV2 = { 0xa293ed37, 0x6319, 0x4381, { 0xb0, 0x20, 0x50, 0xca, 0x5d, 0x42, 0xdd, 0x1a } };

typedef IRgscUiWindowConfigurationV2 IRgscUiWindowConfigurationLatestVersion;
#define IID_IRgscUiWindowConfigurationLatestVersion IID_IRgscUiWindowConfigurationV2

//! Concrete implementation of IRgscUiWindowConfigurationV1
class RgscUiWindowConfiguration : public IRgscUiWindowConfigurationLatestVersion
{
public:

	RgscUiWindowConfiguration()
		: m_X(0)
		, m_Y(0)
		, m_Width(0)
		, m_Height(0)
		, m_MinWidth(0)
		, m_MinHeight(0)
		, m_MaxWidth(0)
		, m_MaxHeight(0)
		, m_Parent(0)
		, m_RootParent(0)
		, m_CaptionHeight(0)
		, m_BorderWidth(0)
		, m_ResizeEdgeFlags(0)
		, m_SizeGripSize(0)
		, m_ShouldMinimizeOnClose(false)
	{
		m_WindowTitle[0] = L'\0';
	}

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		IRgscUnknown *pUnknown = NULL;

		if(ppvObject == NULL)
		{
			return RGSC_INVALIDARG;
		}

		if(riid == IID_IRgscUnknown)
		{
			pUnknown = static_cast<IRgscUiWindowConfiguration*>(this);
		}
		else if(riid == IID_IRgscUiWindowConfigurationV1)
		{
			pUnknown = static_cast<IRgscUiWindowConfigurationV1*>(this);
		}
		else if(riid == IID_IRgscUiWindowConfigurationV2)
		{
			pUnknown = static_cast<IRgscUiWindowConfigurationV2*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	virtual int RGSC_CALL GetX()
	{
		return m_X;
	}

	virtual void RGSC_CALL SetX(int x)
	{
		m_X = x;
	}

	virtual int RGSC_CALL GetY()
	{
		return m_Y;
	}

	virtual void RGSC_CALL SetY(int y)
	{
		m_Y = y;
	}

	virtual int RGSC_CALL GetWidth()
	{
		return m_Width;
	}

	virtual void RGSC_CALL SetWidth(int width)
	{
		m_Width = width;
	}

	virtual int RGSC_CALL GetHeight()
	{
		return m_Height;
	}

	virtual void RGSC_CALL SetHeight(int height)
	{
		m_Height = height;
	}

	virtual WindowHandle RGSC_CALL GetParent()
	{
		return m_Parent;
	}

	virtual void RGSC_CALL SetParent(WindowHandle h)
	{
		m_Parent = h;
	}

	virtual WindowHandle RGSC_CALL GetRootParent()
	{
		return m_RootParent;
	}

	virtual void RGSC_CALL SetEffectiveParent(WindowHandle h)
	{
		m_RootParent = h;
	}

	virtual int RGSC_CALL GetCaptionHeight()
	{
		return m_CaptionHeight;
	}

	virtual void RGSC_CALL SetCaptionHeight(int height)
	{
		m_CaptionHeight = height;
	}

	virtual int RGSC_CALL GetBorderWidth()
	{
		return m_BorderWidth;
	}

	virtual void RGSC_CALL SetBorderWidth(int borderWidth)
	{
		m_BorderWidth = borderWidth;
	}

	virtual int RGSC_CALL GetResizeEdgeFlags()
	{
		return m_ResizeEdgeFlags;
	}

	virtual void RGSC_CALL SetResizeEdgeFlags(int resizeEdgeFlags)
	{
		m_ResizeEdgeFlags = resizeEdgeFlags;
	}

	virtual int RGSC_CALL GetSizeGripSize()
	{
		return m_SizeGripSize;
	}

	virtual void RGSC_CALL SetSizeGripSize(int sizeGripSize)
	{
		m_SizeGripSize = sizeGripSize;
	}

	virtual int RGSC_CALL GetMinimumWidth()
	{
		return m_MinWidth;
	}

	virtual void RGSC_CALL SetMinimumWidth(int width)
	{
		m_MinWidth = width;
	}

	virtual int RGSC_CALL GetMinimumHeight()
	{
		return m_MinHeight;
	}

	virtual void RGSC_CALL SetMinimumHeight(int height)
	{
		m_MinHeight = height;
	}

	virtual int RGSC_CALL GetMaximumWidth()
	{
		return m_MaxWidth;
	}

	virtual void RGSC_CALL SetMaximumWidth(int width)
	{
		m_MaxWidth = width;
	}

	virtual int RGSC_CALL GetMaximumHeight()
	{
		return m_MaxHeight;
	}

	virtual void RGSC_CALL SetMaximumHeight(int height)
	{
		m_MaxHeight = height;
	}

	virtual bool RGSC_CALL ShouldMinimizeOnClose()
	{
		return m_ShouldMinimizeOnClose;
	}

	virtual void RGSC_CALL SetShouldMinimizeOnClose(bool bMinimize)
	{
		m_ShouldMinimizeOnClose = bMinimize;
	}

	virtual const wchar_t* RGSC_CALL GetWindowTitle()
	{
		return m_WindowTitle;
	}

	virtual void RGSC_CALL SetWindowTitle(const wchar_t* windowTitle)
	{
		wcsncpy_s(m_WindowTitle, windowTitle, _countof(m_WindowTitle));
	}

private:

	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;
	int m_MinWidth;
	int m_MinHeight;
	int m_MaxWidth;
	int m_MaxHeight;
	WindowHandle m_Parent;
	WindowHandle m_RootParent;
	int m_CaptionHeight;
	int m_BorderWidth;
	int m_ResizeEdgeFlags;
	int m_SizeGripSize;
	bool m_ShouldMinimizeOnClose;
	wchar_t m_WindowTitle[256];
};

// =====================================================================================================================
// RgscUi Interface
// =====================================================================================================================
class IRgscUi : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV1 = {0x92662653, 0xba1c, 0x4b9b, {0x89, 0x68, 0x19, 0xd1, 0xec, 0x4e, 0x5, 0x50}};

//! Interface to the UI.
class IRgscUiV1 : public IRgscUi
{
public:
	//! Renders the user interface to the screen.
	/**
	  \remark
		  This should be called every frame, between BeginScene/EndScene calls, just before the call to Present.
	*/
	virtual void RGSC_CALL Render() = 0;

	//! Returns true if the UI is currently on screen, false otherwise.
	/**
	  \remark
		  This should be called every frame, between BeginScene/EndScene calls, just before the call to Present.
	*/
	virtual bool RGSC_CALL IsVisible() = 0;

	//! Returns true if the UI is currently in offline mode, false otherwise.
	/**
	  \remark
		  This should not be called unless IsReadyToAcceptCommands() returns true.
	*/
	virtual bool RGSC_CALL IsOfflineMode() = 0;

	//! Sets the D3D device and parameters.
	/**
	  \param d3d - Pointer to either a new IDirect3DDevice9, IDirect3DDevice9Ex, ID3D10Device, or ID3D11Device interface.
	  \param params - Pointer to a structure that contains the presentation parameters that the title used when it\n
					  created the current Direct3D device. The pD3DPP parameter must contain a valid HWND type. 
					  If the title renders using an IDirect3DDevice9 device, pD3DPP must receive a D3DPRESENT_PARAMETERS pointer.\n
					  If the title renders using an ID3D10Device device, pD3DPP must receive a DXGI_SWAP_CHAIN_DESC pointer. 
	*/
	virtual RGSC_HRESULT RGSC_CALL OnCreateDevice(void* d3d, void* params) = 0;

	//! Frees resources when the device is lost.
	/**
	  \remark - D3D10 does not suffer device loss or reset issues. D3D10 applications must still use OnLostDevice() in
				order to ensure the UI cleans up properly and prepares for the subsequent call to OnResetDevice().
	*/
	virtual RGSC_HRESULT RGSC_CALL OnLostDevice() = 0;

	//! Resets the D3D device and parameters.
	/**
	  \param params - Pointer to a structure that contains the presentation parameters that the title used when it\n
					  created the current Direct3D device. The pD3DPP parameter must contain a valid HWND type. 
					  If the title renders using an IDirect3DDevice9 device, pD3DPP must receive a D3DPRESENT_PARAMETERS pointer.\n
					  If the title renders using an ID3D10Device device, pD3DPP must receive a DXGI_SWAP_CHAIN_DESC pointer. 
	  \remark - D3D10 does not suffer device loss or reset issues. D3D10 applications must still use OnResetDevice() in
				order to ensure the UI renders properly and responds to mouse clicks properly when either the resolution,
				back buffer or window size changes.
	*/
	virtual RGSC_HRESULT RGSC_CALL OnResetDevice(void* params) = 0;

	//! Indicates whether the UI is loaded and accepting commands.\n
	//! The title should not call any of the functions below this function before checking that this value is true.
	virtual bool RGSC_CALL IsReadyToAcceptCommands() = 0;

	//! Sets whether the user can manually show the Social Club UI via the hotkey.
	/**
	  \param enable - By default, the hotkey is enabled. Titles can set this to false to prevent the user from opening
					  the Social Club UI via the hotkey. However, the UI can still be opened programatically regardless.
	*/
	virtual void RGSC_CALL EnableHotkey(bool enable) = 0;

	//! Programatically opens the UI as if the player had manually activated it.
	virtual RGSC_HRESULT RGSC_CALL ShowUi() = 0;

	//! Shows the SignIn UI allowing the player to sign in.
	virtual RGSC_HRESULT RGSC_CALL ShowSignInUi() = 0;

	//! deprecated - Use PlayerManager()->ShowPlayerProfileUi() instead
	/**
		Do not remove or you'll break compatibility with existing games.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowGamerProfileUi(unsigned int profileId) = 0;

	//! Returns the activation system interface.
	virtual IActivation* RGSC_CALL GetActivationSystem() = 0;

	//! Returns the patching system interface.
	virtual IPatching* RGSC_CALL GetPatchingSystem() = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV2 = {0xdc57a5b9, 0x58f4, 0x40c3, {0xb0, 0xc2, 0xa0, 0x67, 0xfa, 0xc, 0x5c, 0x2f}};

//! Interface to the UI.
class IRgscUiV2 : public IRgscUiV1
{
public:
	//! Sets the position and size of the Social Club UI.
	/**
	  \param top - the top coordinate of the UI
	  \param left - the left coordinate of the UI
	  \param bottom - the bottom coordinate of the UI
	  \param right - the right coordinate of the UI
	  \remark
  		  - The coordinates are in pixels relative to the frame buffer, which can be a different
		  size than the client area of the window in which the game is running.
		  - The origin is at the top-left of the framebuffer (0, 0) = top-left corner.
		  - This function is optional, but must be called before OnCreateDevice() or
		  OnResetDevice() in order to take effect.
		  - If this function is not called, the Social Club UI will be rendered over the 
		  full area of the render buffer.
		  - The purpose of this function is to support multiple monitor setups. The game
		  determines which part of the render buffer belongs to the monitor on which 
		  to render the Social Club UI and passes that information to this function.
	*/
	virtual RGSC_HRESULT RGSC_CALL SetRenderRect(unsigned int top, unsigned int left, unsigned int bottom, unsigned int right) = 0;

	//! Programatically closes the UI.
	virtual RGSC_HRESULT RGSC_CALL CloseUi() = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV3 = {0x7dd873af, 0xdcea, 0x481f, {0x87, 0xd, 0x3c, 0xc8, 0x65, 0x8, 0x11, 0x21}};

//! Interface to the UI.
class IRgscUiV3 : public IRgscUiV2
{
public:
	enum AccountLinkingResult
	{
		ACCOUNT_LINK_SUCCESS = 0,
		ACCOUNT_LINK_FAIL = 1,
		ACCOUNT_LINK_USER_CANCELLED = 2,
		ACCOUNT_LINK_USER_QUIT = 3,
	};

	enum AccountLinkPlatform
	{
		ACCOUNT_PLATFORM_FACEBOOK = 1,
		ACCOUNT_PLATFORM_GOOGLE = 2,
		ACCOUNT_PLATFORM_TWITCHTV = 3,
	};

	//! Allows the calling process to send messages to the SCUI.
	/**
	  \param jsonMessage - json object to send to javascript
	*/
	virtual RGSC_HRESULT RGSC_CALL SendMessageToScui(const char* jsonMessage) = 0;

	//! The callback signature passed to ShowAccountLinkingUi()
	/**
		\param result - the result of the account linking operation
	*/
	typedef void (*AccountLinkingCallback)(const AccountLinkingResult result);

	//! Shows the UI that allows users to link their Social Club account to another platform.
	/**
	  \param callback - the function that will receive the action taken by the user.
	*/
	virtual RGSC_HRESULT RGSC_CALL ShowAccountLinkingUi(const AccountLinkPlatform platform, AccountLinkingCallback callback) = 0;

	//! Sends virtual text input from the game client to the SCUI
	/**
	  \param text - the text entered by the virtual keyboard
	*/
	virtual void RGSC_CALL SendVirtualKeyboardResult(const wchar_t* text) = 0;

	//! Disables the user's ability to close the SCUI
	/**
	  \param enable - By default, the ability to close the UI is enabled. Titles can set this to false to prevent the user 
					  from closing the Social Club UI. However, the UI can still be closed programatically regardless.
	*/
	virtual void RGSC_CALL EnableClosingUi(bool enable) = 0;

	//! Requests the SCUI to show its on-screen virtual keyboard
	/**
	  \param text - the text to pre-populate in the keyboard
	*/
	virtual void RGSC_CALL ShowVirtualKeyboard(const char* initialText, bool bIsPassword, int maxNumChars) = 0;

	//! Returns the input mode that the SCUI is using
	virtual InputMethod RGSC_CALL GetInputMethod() = 0;

	//! Tells the SCUI to stop handling external URLs and instead forward them to the game
	/**
	  \param enable - if true, the SCUI will stop handling external URLs and will instead forward them to the game
	*/
	virtual void RGSC_CALL ForwardExternalUrls(bool enable) = 0;

	//! Returns TRUE if the SCUI has failed to load both the online and offline website.
	//	The title should indicate to the user the catastrophic failure and shut down.
	virtual bool RGSC_CALL IsInFailState() = 0;

	//! Programmatically requests the SCUI to unload the current site and reload it in offline or online mode
	//	Returns true if the request is successfully received
	virtual bool RGSC_CALL ReloadUi(bool bOfflineOnly) = 0;

	//! Sets the scale factor of the UI (eg. 2.0 would render the UI at double it's normal size, etc.)
	/**
	  \remark
		  - This function is optional, but must be called before OnCreateDevice() or
		  OnResetDevice() in order to take effect.
		  - If this function is not called, the Social Club UI will scale automatically based on window resolution.
		  - If this function is called, it will disable the automatic scale factor and apply the specified scale.
	*/
	virtual void RGSC_CALL SetUiScale(float scale) = 0;
};

//! Interface to the UI.
class IRgscUiV4 : public IRgscUiV3
{
public:
	//! Returns TRUE if the SCUI hotkey is enabled.
	virtual bool RGSC_CALL IsHotkeyEnabled() = 0;

	//! Returns TRUE if closing of the SCUI is enabled
	virtual bool RGSC_CALL IsClosingEnabled() = 0;

	//! Returns TRUE if the SCUI is reloading
	virtual bool RGSC_CALL IsReloadingUi() = 0;

	//! Returns TRUE if the SCUI is reloading and the user was signed in prior to the reload.
	virtual bool RGSC_CALL IsReloadingUiSignedIn() = 0;

	//! returns TRUE if the SCUI is reloading and the user was online prior to the reload.
	virtual bool RGSC_CALL IsReloadingUiOnline() = 0;

	//! Sets the Message Handlers for the RGSC UI Input class
	virtual bool RGSC_CALL SetMessageHandlers(IRgscPlatformMessageHandler** handlers, const unsigned numHandlers) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV4 = { 0x971ebf9b, 0x8bed, 0x458b, { 0x83, 0x2c, 0x66, 0x8f, 0x2, 0xf5, 0x47, 0x2d } };

//! Interface to the UI.
class IRgscUiV5 : public IRgscUiV4
{
public:
	//! Returns TRUE if the SCUI is overriding the mouse cursor.
	/**
	  \remark
		The conditions include:
			- Current window mouse cursor is the standard pointer.
			- Input is enabled.
			- The cursor is within bounds of the window.
	*/
	virtual bool RGSC_CALL IsOverridingCursor() = 0;

	//! Sets margins in the SCUI window to ignore for mouse events. For example, if 8,8,8,8 is set, the mouse will not be considered
	//	in the window if it is within 8 pixels of the border on any side.
	virtual void RGSC_CALL SetWindowMargins(int top, int left, int bottom, int right) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV5 = { 0xa65191e8, 0x2684, 0x41ce, { 0x8c, 0x27, 0x3b, 0xb3, 0x1f, 0xb6, 0x84, 0x9c } };

//! Interface to the UI.
class IRgscUiV6 : public IRgscUiV5
{
public:
	
	//! Sets the UI into a modal interface.
	virtual void RGSC_CALL SetIsModal(bool isModal) = 0;

	//! Returns true if the UI is in a modal interface
	virtual bool RGSC_CALL IsModal() = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV6 = { 0x877b51d6, 0xc566, 0x4efd, { 0xa8, 0x66, 0x25, 0xc9, 0x45, 0xe4, 0x62, 0x7e } };

//! Interface to the UI.
class IRgscUiV7 : public IRgscUiV6
{
public:

	//! Creates a SCUI window as a child of another window using the given configuration.
	virtual RGSC_HRESULT RGSC_CALL CreateInWindow(IRgscUiWindowConfiguration* config) = 0;

	//! Updates the window to the given dimensions. Should be called after a move or resize operation for CreateInWindow,
	//	or to request a move/resize operation for Popup/Borderless windows.
	/**
		\remark
			- Should only be used for windows created via CreateInWindow, CreatePopupWindow or CreateBorderlessWindow. 
			  Resizing a device-based window (i.e. OnCreateDevice) should trigger a device lost and reset call (OnLostDevice->OnResetDevice). 
			  For most cases, x,y would remain zero and only width, height should be specified.
			  For BorderlessWindow mode, x and y would refer to the desired coordinates of the window.
	*/
	virtual void RGSC_CALL SetWindowDimensions(int x, int y, int width, int height) = 0;

	//! Adds a rect that should be excluded from the draggable caption region.
	/**
		\remark
			- The reference point is a combination of WindowEdgeFlags that the x,y coordinates are relative to. By default, the position
			  is relative to the top left corner (as is the default on windows). However, you could specify WE_WOP | WE_RIGHT and the rect
			  would be relative to the upper right corner. These points are fixed and must be re-applied after a resize if the location is
			  percentage based instead of a fixed offset.
	*/
	virtual void RGSC_CALL AddCaptionExclusion(int x, int y, int width, int height, int referencePoint = WE_TOP | WE_LEFT) = 0;
	
	//! Clears the caption exclusion rectangles.
	virtual void RGSC_CALL ClearCaptionExclusion() = 0;

	//! Requests the browser window to close
	virtual void RGSC_CALL DestroyWindow() = 0;

	//! Returns true if the browser window has processed the destroy message and is closing.
	virtual bool RGSC_CALL IsWindowDestroyed() = 0;

	//! Attempts to set or clear focus on the browser window
	virtual void RGSC_CALL SetWindowFocus(bool bEnabled) = 0;

	//! Informs the SCUI to begin shutdown operations. 
	/** IsReadyToShutdown from the IRgscV5 interface will return true when the SCUI is ready to shutdown.
		\param
		  timeOutMs - Indicates to the SCUI how long the shutdown operation will be allowed to run before terminating.
	*/
	virtual void RGSC_CALL BeginShutdown(int timeOutMs) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV7 = { 0x906ce6cb, 0x4120, 0x4c51, { 0xb9, 0xd5, 0xf7, 0xcc, 0xc5, 0x55, 0xa7, 0xa7 } };

//! Interface to the UI.
class IRgscUiV8 : public IRgscUiV7
{
public:
	//! Hibernates the UI, unloading the subprocess to reduce the memory footprint.
	virtual void RGSC_CALL Hibernate() = 0;

	//! Returns true if the SCUI is hibernating.
	virtual bool RGSC_CALL IsHibernating() = 0;

	//! Restore the UI after a hibernation.
	virtual void RGSC_CALL WakeUp() = 0;

	//! Get the handle to the browser.
	virtual WindowHandle RGSC_CALL GetBrowserHandle() = 0; 

	//! Get the handle to the parent window (borderless mode only)
	virtual WindowHandle RGSC_CALL GetWindowHandle() = 0;

	//! Creates a popup SCUI window using the given configuration.
	virtual RGSC_HRESULT RGSC_CALL CreatePopupWindow(IRgscUiWindowConfiguration* config) = 0;

	//! Creates a bordless SCUI window using the given configuration.
	virtual RGSC_HRESULT RGSC_CALL CreateBorderlessWindow(IRgscUiWindowConfiguration* config) = 0;

	//! Sets if the window can be closed through a system close message.
	//	 Currently only valid for Borderless Windows.
	virtual void RGSC_CALL SetWindowCanClose(bool bCanClose) = 0;

	//! Sets the WindowHandle of the modal blocker (Calls SetIsModal() internally based on if the handle is valid)
	//	 Currently only valid for Borderless Windows.
	virtual void RGSC_CALL SetWindowModalBlocker(WindowHandle handle) = 0;

	//! For BorderlessWindows, the browser and the parent window both belong to the subprocess. Thus,
	//	the window cannot be subclassed to intercept keyboard events. In this situation, keyboard events
	//  will be forwarded back to the UI. Set a callback here to also receive them. For Child, Popup and 
	//	off-screen rendering, this callback will not be used and the main parent window should be subclassed instead.
	/**
		\remark
			iMsg, wParam and lParam take the form of windows WM_KEYDOWN, WM_KEYUP, WM_CHAR events,
			where iMsg will represent the event (i.e. WM_CHAR), and wParam will represent the windows virtual keycode
			or character code of the key and lParam will represent the native key code for platform compatibility.
			scKeyModifiers includes RgscKeyModifier bitflags.
	*/
	typedef void (*BrowserKeyEventCallback)( s64 iMsg, s64 wParam, s64 lParam, int scKeyModifiers );
	virtual RGSC_HRESULT RGSC_CALL SetBrowserKeyEventCallback(BrowserKeyEventCallback) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV8 = { 0x9c0a4057, 0x8789, 0x44fb, { 0x98, 0x33, 0xe8, 0x61, 0x77, 0xb, 0xc2, 0xbc } };

//! Interface to the UI.
class IRgscUiV9 : public IRgscUiV8
{
public:

	// PURPOSE
	//	Sends a custom windows message to the browser window. Returns RGSC_OK on successful completion.
	/**
		\remark
			Should only be used for windows created via CreateInWindow, CreatePopupWindow or CreateBorderlessWindow. The browser
			window will also response to windows ::PostMessage and ::SendMessage commands, so this should only be needed for
			non-windows platforms.
		\param wParam - Usage defined on a per-message basis. See definition of 'CustomWindowMessages'
		\param lParam - Usage defined on a per-message basis. See definition of 'CustomWindowMessages'
	*/
	virtual RGSC_HRESULT RGSC_CALL SendMessageToBrowser(CustomWindowMessages msg, RGSC_WPARAM wParam, RGSC_LPARAM lParam) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV9 = { 0x45df046d, 0x58b5, 0x4ff2, { 0xba, 0x93, 0x9b, 0x2d, 0x53, 0x1c, 0x89, 0x3 } };

//! Interface to the UI.
class IRgscUiV10 : public IRgscUiV9
{
public:

	//! Set the device context used to render the SCUI.
	/**
	  \remark
		  Should be used only when a D3D11 device is passed to CreateDevice.
	  \param d3dDeviceContext - Should be of type ID3D11DeviceContext*
	*/
	virtual void RGSC_CALL SetDeviceContext(void* d3dDeviceContext) = 0;

	//! Disables the UI forwarding of windows mouse and keyboard events to the chrome subprocess
	/**
		\remark
			Mouse and keyboard event forwarding is enabled by default when a device is created using CreateDevice.
			Mouse and keyboard event forwarding are disabled by default when a device is created using CreateInWindow, CreatePopupWindow or CreateBorderlessWindow.
	*/
	virtual void RGSC_CALL SetKeyboardEventForwarding(bool bEnabled) = 0;
	virtual void RGSC_CALL SetMouseEventForwarding(bool bEnabled) = 0;

	//! Enables/Disables the virtual cursor
	//	Should be paired with a pointing device from IGamepadManager
	virtual void RGSC_CALL SetVirtualCursor(bool bEnabled) = 0;

	//! Sets the RGBA color to use with modal dialogs
	virtual void RGSC_CALL SetModalBackgroundColor(u8 red, u8 green, u8 blue, u8 alpha) = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV10 = { 0x2f3238c7, 0x96f3, 0x4b8e, { 0xb4, 0xd4, 0x32, 0x3e, 0xcd, 0x17, 0x23, 0x74 } };

//! Interface to the UI.
class IRgscUiV11 : public IRgscUiV10
{
public:

	//! Returns true if the Javascript link between SCUI and SDK is ready.
	//	This should only be necessary for apps that have their own communication APIs with SCUI.
	//  Other titles should simply use IsReadyToAcceptCommands which will wait for all UI initialization to complete, including autosignin.
	virtual bool RGSC_CALL IsJavascriptReadyToAcceptCommands() = 0;
};

extern "C" static const RGSC_IID IID_IRgscUiV11 = { 0x2040c652, 0xabbf, 0x4659, { 0xad, 0xcc, 0x2a, 0xd7, 0x11, 0x29, 0x2d, 0x89 } };

typedef IRgscUiV11 IRgscUiLatestVersion;
#define IID_IRgscUiLatestVersion IID_IRgscUiV11

} // namespace rgsc

#endif //RGSC_UI_INTERFACE_H
