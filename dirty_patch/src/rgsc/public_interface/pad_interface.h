#ifndef PAD_INTERFACE_H
#define PAD_INTERFACE_H

#include "rgsc_common.h"

#include <cstring>

namespace rgsc
{

class IGamepad : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

class IGamepadV1 : public IGamepad
{
public:

	enum PadButton
	{	
		// bitmask of values returned by GetButtons
		RGSC_L2=0x0001, 
		RGSC_R2=0x0002, 
		RGSC_L1=0x0004, 
		RGSC_R1=0x0008,
		RGSC_RUP=0x0010, 
		RGSC_RRIGHT=0x0020, 
		RGSC_RDOWN=0x0040, 
		RGSC_RLEFT=0x0080,
		RGSC_SELECT=0x0100, 
		RGSC_L3=0x0200, 
		RGSC_R3=0x0400, 
		RGSC_START=0x0800,
		RGSC_LUP=0x1000,
		RGSC_LRIGHT=0x2000, 
		RGSC_LDOWN=0x4000, 
		RGSC_LLEFT=0x8000
	};

	enum PadButtonIndex
	{	
		// log2(bitmask) of values returned by GetButtons
		RGSC_L2_INDEX, 
		RGSC_R2_INDEX, 
		RGSC_L1_INDEX, 
		RGSC_R1_INDEX,
		RGSC_RUP_INDEX, 
		RGSC_RRIGHT_INDEX, 
		RGSC_RDOWN_INDEX, 
		RGSC_RLEFT_INDEX,
		RGSC_SELECT_INDEX, 
		RGSC_L3_INDEX, 
		RGSC_R3_INDEX, 
		RGSC_START_INDEX,
		RGSC_LUP_INDEX, 
		RGSC_LRIGHT_INDEX, 
		RGSC_LDOWN_INDEX, 
		RGSC_LLEFT_INDEX,
		RGSC_NUMBUTTONS
	};

	// ===============================================================================================
	// inherited from IRgscUnknown
	// ===============================================================================================
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	// ===============================================================================================
	// IGamePadV1
	// ===============================================================================================
	virtual bool RGSC_CALL IsConnected() const  = 0;
	virtual int RGSC_CALL GetButtons() const = 0;
	virtual u32 RGSC_CALL GetChangedButtons() const = 0;
	virtual u32 RGSC_CALL GetPressedButtons() const = 0;
	virtual u32 RGSC_CALL GetReleasedButtons() const = 0;
	virtual u8 RGSC_CALL GetLeftX() const = 0;
	virtual u8 RGSC_CALL GetLeftY() const = 0;
	virtual u8 RGSC_CALL GetRightX() const = 0;
	virtual u8 RGSC_CALL GetRightY() const = 0;
	virtual float RGSC_CALL GetNormRightX() const = 0;
	virtual float RGSC_CALL GetNormRightY() const = 0;
	virtual float RGSC_CALL GetNormLeftX() const = 0;
	virtual float RGSC_CALL GetNormLeftY() const = 0;
};

extern "C" static const RGSC_IID IID_IGamepadV1 = { 0x69ca7614, 0xc799, 0x4e9d, { 0xbc, 0x97, 0x39, 0xda, 0xc5, 0xeb, 0x34, 0xab } };

class IGamepadV2 : public IGamepadV1
{
public:

	// ===============================================================================================
	// IGamePadV2
	// ===============================================================================================
	virtual void RGSC_CALL SetHasInput() = 0;
	virtual bool RGSC_CALL HasInput() const = 0;
	virtual void RGSC_CALL ClearHasInput() = 0;
};

extern "C" static const RGSC_IID IID_IGamepadV2 = { 0x14d450cd, 0xe9d7, 0x49ce, { 0xbe, 0x2c, 0x7c, 0x16, 0xc1, 0x9c, 0x1, 0x7e } };

class IGamepadV3: public IGamepadV2
{
public:

	// ===============================================================================================
	// IGamePadV3
	// ===============================================================================================

	//! UTF8 encoded local path for the icon to display for the current button index.
	virtual const char* RGSC_CALL GetButtonIcon(PadButtonIndex buttonIndex) = 0;

	//! UTF8 encoded, localized string to display for the current button index.
	virtual const char* RGSC_CALL GetButtonText(PadButtonIndex buttonIndex) = 0;
};

extern "C" static const RGSC_IID IID_IGamepadV3 = { 0xc4394007, 0xa9b9, 0x445d, { 0xb3, 0x90, 0x9e, 0x7b, 0x92, 0xa, 0xde, 0xd0 } };

class IGamepadV4 : public IGamepadV3
{
public:

	// ===============================================================================================
	// IGamePadV4
	// ===============================================================================================

	//! Enum representing the type of controller, useful for displaying contextual iconography.
	virtual ControllerType RGSC_CALL GetType() = 0;

	//! UTF8 encoded name of the controller
	virtual const char* RGSC_CALL GetName() = 0;
};

extern "C" static const RGSC_IID IID_IGamepadV4 = { 0x1474d093, 0x63b8, 0x4d74, { 0x96, 0x9c, 0x70, 0xe6, 0xe2, 0x27, 0x50, 0x5a } };

class IGamepadV5 : public IGamepadV4
{
public:
	// ===============================================================================================
	// IGamePadV5
	// ===============================================================================================
	virtual bool RGSC_CALL IsPointingDevice() = 0;
	virtual bool RGSC_CALL HasPointerData() = 0;
	virtual int RGSC_CALL GetPointerX() = 0;
	virtual int RGSC_CALL GetPointerY() = 0;
};

extern "C" static const RGSC_IID IID_IGamepadV5 = { 0xde5ef66, 0x82e5, 0x4fc5, { 0x9e, 0xfd, 0xd, 0xc9, 0x54, 0x2c, 0x4a, 0xe3 } };

typedef IGamepadV5 IGamepadLatestVersion;
#define IID_IGamepadLatestVersion IID_IGamepadV5

class RgscGamepad : public IGamepadLatestVersion
{
public:
	// ===============================================================================================
	// inherited from IRgscUnknown
	// ===============================================================================================
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		IRgscUnknown *pUnknown = NULL;

		if(ppvObject == NULL)
		{
			return RGSC_INVALIDARG;
		}

		if(riid == IID_IRgscUnknown)
		{
			pUnknown = static_cast<IGamepad*>(this);
		}
		else if(riid == IID_IGamepadV1)
		{
			pUnknown = static_cast<IGamepadV1*>(this);
		}
		else if(riid == IID_IGamepadV2)
		{
			pUnknown = static_cast<IGamepadV2*>(this);
		}
		else if(riid == IID_IGamepadV3)
		{
			pUnknown = static_cast<IGamepadV3*>(this);
		}
		else if(riid == IID_IGamepadV4)
		{
			pUnknown = static_cast<IGamepadV4*>(this);
		}
		else if(riid == IID_IGamepadV5)
		{
			pUnknown = static_cast<IGamepadV5*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	// ===============================================================================================
	// inherited from IGamePadV1
	// ===============================================================================================
	virtual bool RGSC_CALL IsConnected() const
	{
		return m_IsConnected;
	}

	virtual int RGSC_CALL GetButtons() const
	{
		return m_Buttons;
	}

	virtual u32 RGSC_CALL GetChangedButtons() const
	{ 
		return m_LastButtons ^ GetButtons(); 
	}

	virtual u32 RGSC_CALL GetPressedButtons() const
	{ 
		return GetChangedButtons() & GetButtons(); 
	}

	virtual u32 RGSC_CALL GetReleasedButtons() const
	{ 
		return GetChangedButtons() & m_LastButtons; 
	}

	virtual u8 RGSC_CALL GetLeftX() const
	{
		return m_Axis[0];
	}

	virtual u8 RGSC_CALL GetLeftY() const
	{
		return m_Axis[1];
	}

	virtual u8 RGSC_CALL GetRightX() const
	{
		return m_Axis[2];
	}

	virtual u8 RGSC_CALL GetRightY() const
	{
		return m_Axis[3];
	}

	// RETURNS: Normalized value of right analog stick X, as per ioPad::Norm
	virtual float RGSC_CALL GetNormRightX() const
	{
		return Norm(GetRightX());
	}

	// RETURNS: Normalized value of right analog stick Y, as per ioPad::Norm (-1 is up, +1 is down)
	virtual float RGSC_CALL GetNormRightY() const
	{
		return Norm(GetRightY());
	}

	// RETURNS: Normalized value of left  analog stick X, as per ioPad::Norm
	virtual float RGSC_CALL GetNormLeftX() const
	{
		return Norm(GetLeftX());
	}

	// RETURNS: Normalized value of left analog stick Y, as per ioPad::Norm (-1 is up, +1 is down)
	virtual float RGSC_CALL GetNormLeftY() const
	{
		return Norm(GetLeftY());
	}

	// ===============================================================================================
	// IGamePadV2
	// ===============================================================================================
	virtual void RGSC_CALL SetHasInput()
	{
		m_bInputProduced = true;
	}

	virtual bool RGSC_CALL HasInput() const
	{
		return m_bInputProduced;
	}

	virtual void RGSC_CALL ClearHasInput()
	{
		if (m_bInputProduced)
		{
			// reset buttons only
			m_LastButtons = m_Buttons;
			m_Buttons = 0;
			memset(m_AnalogButtons, 0, sizeof(m_AnalogButtons));
		}

		m_bInputProduced = false;
	}

	// ===============================================================================================
	// IGamePadV3
	// ===============================================================================================
	const char* RGSC_CALL GetButtonIcon(PadButtonIndex buttonIndex)
	{
		if (buttonIndex < RGSC_NUMBUTTONS)
		{
			return m_ButtonPath[buttonIndex];
		}

		return "";
	}

	void RGSC_CALL SetButtonIcon(PadButtonIndex buttonIndex, const char* buttonPathUtf8)
	{
		if (buttonIndex < RGSC_NUMBUTTONS && buttonPathUtf8)
		{
			strcpy_s(m_ButtonPath[buttonIndex], sizeof(m_ButtonPath[buttonIndex]), buttonPathUtf8);
		}
	}

	const char* RGSC_CALL GetButtonText(PadButtonIndex buttonIndex)
	{
		if (buttonIndex < RGSC_NUMBUTTONS)
		{
			return m_ButtonText[buttonIndex];
		}

		return "";
	}

	void RGSC_CALL SetButtonText(PadButtonIndex buttonIndex, const char* locButtonTextUtf8)
	{
		if (buttonIndex < RGSC_NUMBUTTONS && locButtonTextUtf8)
		{
			strcpy_s(m_ButtonText[buttonIndex], sizeof(m_ButtonText[buttonIndex]), locButtonTextUtf8);
		}
	}

	// ===============================================================================================
	// IGamePadV4
	// ===============================================================================================
	ControllerType RGSC_CALL GetType()
	{
		return m_Type;
	}

	void RGSC_CALL SetType(ControllerType t)
	{
		m_Type = t;
	}

	const char* RGSC_CALL GetName()
	{
		return m_Name;
	}

	void RGSC_CALL SetName(const char* name)
	{
		strcpy_s(m_Name, sizeof(m_Name), name);
	}

	// ===============================================================================================
	// IGamePadV5
	// ===============================================================================================
	bool RGSC_CALL IsPointingDevice()
	{
		return m_bIsPointingDevice;
	}

	void RGSC_CALL SetIsPointingDevice(bool bIsPointingDevice)
	{
		m_bIsPointingDevice = bIsPointingDevice;
	}

	bool RGSC_CALL HasPointerData()
	{
		return m_bHasPointerData;
	}

	void RGSC_CALL SetHasPointerData(bool bHasPointerData)
	{
		m_bHasPointerData = bHasPointerData;
	}

	int RGSC_CALL GetPointerX()
	{
		return m_PointerX;
	}

	int RGSC_CALL GetPointerY()
	{
		return m_PointerY;
	}

	void RGSC_CALL SetPointer(int x, int y)
	{
		m_PointerX = x;
		m_PointerY = y;
	}

	// ===============================================================================================
	// accessible anywhere in the dll
	// ===============================================================================================

public:

	static const int RGSC_MAX_AXIS = 4;
	static const int RGSC_MAX_BUTTON_TEXT_BUF_SIZE = 64;
	static const u8 RGSC_AXIS_ZERO_VALUE = 127;

	RgscGamepad()
	{
		m_PadIndex = -1;
		m_Buttons = 0;
		m_LastButtons = 0;
		memset(m_Axis, 0, sizeof(m_Axis));
		memset(m_AnalogButtons, 0, sizeof(m_AnalogButtons));
		m_IsConnected = false;
		m_bInputProduced = false;
		m_Type = RGSC_CT_UNKNOWN;
		memset(m_Name, 0, sizeof(m_Name));
		m_bIsPointingDevice = false;
		m_bHasPointerData = false;
		m_PointerX = 0;
		m_PointerY = 0;

		for (int i = 0; i < RGSC_NUMBUTTONS; i++)
		{
			m_ButtonPath[i][0] = '\0';
			m_ButtonText[i][0] = '\0';
		}
	}

	// PURPOSE: Forces digital button state to specified value
	// PARAMS:	b - New button bitmask
	virtual void RGSC_CALL SetButtons(u32 b)
	{
		m_Buttons = b;
	}

	virtual void RGSC_CALL SetAxisNorm (int axis, float normVal)
	{
		if (axis >= 0 && axis < RGSC_MAX_AXIS)
		{
			m_Axis[axis] = (u8)(normVal * 127.5f);
		}
	}

	virtual void RGSC_CALL SetAxis( int axis, u8 value )
	{
		if (axis >= 0 && axis < RGSC_MAX_AXIS)
		{
			m_Axis[axis] = value;
		}
	}

	// RETURNS: Normalized version of value
	// PARAMS:	value - Value to normalize (presumably an analog axis)
	// NOTES:	Will give you a range between -1.0 and 1.0.
	static float RGSC_CALL Norm(u8 value)
	{ 
		float n = ((float)value - 127.5f) * (1.0f / 127.0f);
		if (n < -1.0f)
		{
			return -1.0f;
		}
		else if (n > 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return n;
		}
	}

	virtual u8 RGSC_CALL GetAnalogButton(IGamepadLatestVersion::PadButtonIndex b) const
	{
		return m_AnalogButtons[b];
	}

	virtual float RGSC_CALL GetNormAnalogButton(IGamepadLatestVersion::PadButtonIndex b) const
	{
		return m_AnalogButtons[b] / 255.0f;
	}

	// RETURNS: True if the pad is connected and usable.
	virtual void RGSC_CALL SetIsConnected(bool bConnected)
	{ 
		m_IsConnected = bConnected; 
	}

	// PURPOSE
	//	Returns the index of the pad
	virtual int RGSC_CALL GetPadIndex() const 
	{
		return m_PadIndex;
	}

	virtual void RGSC_CALL SetPadIndex(int index)
	{
		m_PadIndex = index;
	}

	// PURPOSE: All Update functions call this first to copy previous button
	// state and re-center analog inputs.  This should be called exactly once
	// per update so that higher-level code will never miss a press or release
	// event even on communication error or disconnect.
	virtual void RGSC_CALL ClearInputs()
	{
		m_LastButtons = m_Buttons;
		m_Buttons = 0;
		m_Axis[0] = m_Axis[1] = m_Axis[2] = m_Axis[3] = RGSC_AXIS_ZERO_VALUE;

		for (int i=0; i < RGSC_NUMBUTTONS; i++)
		{
			m_AnalogButtons[i] = 0;
		}
	}

protected:
	int m_PadIndex;
	u32 m_Buttons;
	u32 m_LastButtons;
	u8 m_Axis[RGSC_MAX_AXIS];
	unsigned char m_AnalogButtons[RGSC_NUMBUTTONS];
	bool m_IsConnected;
	bool m_bInputProduced;
	char m_ButtonPath[RGSC_NUMBUTTONS][RGSC_MAX_PATH];
	char m_ButtonText[RGSC_NUMBUTTONS][RGSC_MAX_BUTTON_TEXT_BUF_SIZE];
	char m_Name[256];
	bool m_bIsPointingDevice, m_bHasPointerData;
	int m_PointerX, m_PointerY;
	ControllerType m_Type;
};


class IGamepadManager : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

class IGamepadManagerV1 : public IGamepadManager
{
public:

	enum InputMode
	{
		INPUTMODE_INVALID = -1,
		INPUTMODE_D3D = 0,
		INPUTMODE_XINPUT,
		INPUTMODE_MARSHALLED,
		INPUTMODE_MAX
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	virtual RGSC_HRESULT RGSC_CALL SetMarshalledGamepads(IGamepad** gamePads, unsigned numGamePads) = 0;
	virtual void RGSC_CALL ClearMarshalledGamepads() = 0;
};

class IGamepadManagerV2 : public IGamepadManagerV1
{
public:

	//! When the configuration of a gamepad has changed (i.e. the icon path or help text for a IGamePadV3 has been updated),
	//	call NotifyGamepadsChanged() notify the gamepad manager. This will queue an update to the SCUI to update any
	//	help text that may appear on screen.
	virtual void RGSC_CALL NotifyGamepadsChanged() = 0;
};

class IGamepadManagerV3 : public IGamepadManagerV2
{
public:

	//! Sets if gamepad input is allowed while the window does not have focus.
	//	Note: Mouse movement will still be constrained to the window.
	virtual void RGSC_CALL SetBackgroundInputEnabled(bool bEnabled) = 0;
};

class IGamepadManagerV4 : public IGamepadManagerV3
{
public:

	//! Sets if gamepad input should simulate keyboard events.
	//	Note: Enabled by default.
	virtual void RGSC_CALL SetSimulateKeyboardEventsEnabled(bool bEnabled) = 0;

	//! Sets if gamepad input should simulate mouse events.
	//	Note: Enabled by default.
	virtual void RGSC_CALL SetSimulateMouseEventsEnabled(bool bEnabled) = 0;

	//! Sets if gamepad input should be forwarded to the SCUI
	//	Note: Disabled by default
	virtual void RGSC_CALL SetSendPadInputToBrowserEnabled(bool bEnabled) = 0;
};

extern "C" static const RGSC_IID IID_IGamepadManagerV1 = { 0xe4db8d5f, 0x7450, 0x40d3, { 0x95, 0xf0, 0xdc, 0x24, 0x55, 0x51, 0x4, 0x36 } };
extern "C" static const RGSC_IID IID_IGamepadManagerV2 = { 0x9c5f019, 0x6c47, 0x46a8, { 0x9b, 0x9f, 0x0, 0x47, 0x23, 0xbf, 0xc5, 0x9d } };
extern "C" static const RGSC_IID IID_IGamepadManagerV3 = { 0x58b572ef, 0x1a4, 0x42ef, { 0x86, 0xac, 0x98, 0xad, 0x79, 0x3e, 0x2d, 0x50 } };
extern "C" static const RGSC_IID IID_IGamepadManagerV4 = { 0xeccca878, 0x5b29, 0x4f6d, { 0xa4, 0x68, 0x1c, 0x5d, 0x34, 0x67, 0xeb, 0x2e } };

typedef IGamepadManagerV4 IGamepadManagerLatestVersion;
#define IID_IGamepadManagerLatestVersion IID_IGamepadManagerV4

} // namespace rgsc

#endif // PAD_INTERFACE_H