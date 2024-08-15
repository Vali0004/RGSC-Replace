#ifndef RGSC_NETWORK_INTERFACE_H
#define RGSC_NETWORK_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

//! This class is designed to be an extensible version of a plain-old-data structure.
class INetworkInfo : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_INetworkInfoV1 = {0xccd81308, 0x8e72, 0x4eed, {0xa8, 0xb, 0x31, 0x14, 0x9b, 0x4, 0x94, 0x8b}};
extern "C" static const RGSC_IID IID_INetworkInfoV2 = {0x4357e574, 0xfc5c, 0x48fb, {0xa3, 0x17, 0x78, 0xce, 0xf9, 0x43, 0x10, 0x43}};

//! Version 1 of the network info interface
class INetworkInfoV1 : public INetworkInfo
{
public:

	enum NatDetectionState
	{
		NAT_NDS_UNATTEMPTED,
		NAT_NDS_IN_PROGRESS,
		NAT_NDS_SUCCEEDED,
		NAT_NDS_FAILED,
	};

	enum NatType
	{
		NET_NAT_UNKNOWN,
		NET_NAT_OPEN,
		NET_NAT_MODERATE,
		NET_NAT_STRICT,
	};

	enum UpNpState
	{
		NAT_UPNP_UNATTEMPTED,
		NAT_UPNP_IN_PROGRESS,
		NAT_UPNP_SUCCEEDED,
		NAT_UPNP_FAILED,
	};

	enum NatFilteringMode
	{
		NET_NAT_FM_UNKNOWN,
		NET_NAT_FM_OPEN, // endpoint independent or address restricted filtering
		NET_NAT_FM_PORT_AND_ADDRESS_RESTRICTED,
	};

	enum NatPortMappingMethod
	{
		NET_NAT_PMM_UNKNOWN,
		NET_NAT_PMM_ENDPOINT_INDEPENDENT,
		NET_NAT_PMM_ENDPOINT_DEPENDENT,
	};

	enum NatPortAllocationStrategy
	{
		NET_NAT_PAS_UNKNOWN,
		NET_NAT_PAS_PORT_PRESERVING,
		NET_NAT_PAS_PORT_CONTIGUOUS,
		NET_NAT_PAS_PORT_RANDOM,
	};

	enum UdpTimeoutState
	{
		NAT_UDP_TIMEOUT_UNATTEMPTED,
		NAT_UDP_TIMEOUT_IN_PROGRESS,
		NAT_UDP_TIMEOUT_SUCCEEDED,
		NAT_UDP_TIMEOUT_FAILED,
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	
	//! Gets the state of NAT detection
	virtual NatDetectionState RGSC_CALL GetNatDetectionState() const = 0;

	//! Determine whether to use a variable ping interval for the presence server.
	virtual bool GetAllowAdjustablePresencePingInterval() const = 0;

	//! Returns whether the local host is behind a NAT
	virtual bool RGSC_CALL GetNatDetected() const = 0;

	//! Gets the public address
	virtual const char* RGSC_CALL GetPublicAddress() const = 0;

	//! Gets the private address
	virtual const char* RGSC_CALL GetPrivateAddress() const = 0;

	//! Gets NAT Type
	virtual NatType RGSC_CALL GetNatType() const = 0;

	//! Gets the uPnP state
	virtual UpNpState RGSC_CALL GetuPnPState() const = 0;

	//! Gets the NAT filtering mode
	virtual NatFilteringMode RGSC_CALL GetNatFilteringMode() const = 0;

	//! Gets the NAT port mapping method
	virtual NatPortMappingMethod RGSC_CALL GetNatPortMappingMethod() const = 0;

	//! Gets the port increment for port-contiguous allocating NATs
	virtual int RGSC_CALL GetPortIncrement() const = 0;

	//! Gets the NAT port allocation strategy
	virtual NatPortAllocationStrategy RGSC_CALL GetNatPortAllocationStrategy() const = 0;

	//! Gets the UDP port binding timeout detection state
	virtual UdpTimeoutState RGSC_CALL GetUdpTimeoutState() const = 0;

	//! Gets the UDP port binding timeout in seconds
	virtual unsigned RGSC_CALL GetUdpTimeoutSec() const = 0;
};

//! Version 2 of the network info interface
class INetworkInfoV2
{
public:
	/*
	SCUI Rules
	If PCP State is:
	-  "0" Don't show the PCP information at all.
	-  "1" Show "NAT-PMP / PCP: Detecting..."
	-  "2" Show "NAT-PMP / PCP: Enabled"
	-  "3" Show "NAT-PMP / PCP: Disabled"
	-  "4" Show "NAT-PMP: Enabled"
	-  "5" Show "PCP (Port Control Protocol): Enabled"
	*/
	enum PcpState
	{
		NAT_PCP_UNATTEMPTED,
		NAT_PCP_IN_PROGRESS,
		NAT_PCP_SUCCEEDED,
		NAT_PCP_FAILED,
		NAT_PCP_METHOD_PMP,
		NAT_PCP_METHOD_PCP,
	};

	//! Gets the PCP state
	virtual PcpState RGSC_CALL GetPcpState() const = 0;
};

//! Concrete class that implements the INetworkInfoV1 interface.
class NetworkInfoV1 : public INetworkInfoV1
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
			pUnknown = static_cast<INetworkInfo*>(this);
		}
		else if(riid == IID_INetworkInfoV1)
		{
			pUnknown = static_cast<INetworkInfoV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	NetworkInfoV1()
	{
		m_NatDetectionState = INetworkInfoV1::NAT_NDS_UNATTEMPTED;
		m_NatDetected = false;

		memset(m_PublicAddress, 0, sizeof(m_PublicAddress));
		memset(m_PrivateAddress, 0, sizeof(m_PrivateAddress));

		m_AllowAdjustablePresencePingInterval = false;
		m_NatType = INetworkInfoV1::NET_NAT_UNKNOWN;
		m_UpNpState = INetworkInfoV1::NAT_UPNP_UNATTEMPTED;
		m_NatFilteringMode = INetworkInfoV1::NET_NAT_FM_UNKNOWN;

		m_NatPortMappingMethod = INetworkInfoV1::NET_NAT_PMM_UNKNOWN;
		m_PortIncrement = 0;

		m_NatPortAllocationStrategy = INetworkInfoV1::NET_NAT_PAS_UNKNOWN;

		m_UdpTimeoutState = INetworkInfoV1::NAT_UDP_TIMEOUT_UNATTEMPTED;
		m_UdpTimeoutSec = 0;
	}

	virtual NatDetectionState RGSC_CALL GetNatDetectionState() const
	{
		return m_NatDetectionState;
	}

	virtual void RGSC_CALL SetNatDetectionState(NatDetectionState state)
	{
		m_NatDetectionState = state;
	}

	virtual bool RGSC_CALL GetNatDetected() const
	{
		return m_NatDetected;
	}

	virtual void RGSC_CALL SetNatDetected(bool natDetected)
	{
		m_NatDetected = natDetected;
	}

	virtual const char* RGSC_CALL GetPublicAddress() const
	{
		return m_PublicAddress;
	}

	virtual void RGSC_CALL SetPublicAddress(const char* publicAddress)
	{
		strncpy_s(m_PublicAddress, sizeof(m_PublicAddress), publicAddress, sizeof(m_PublicAddress) - 1);
	}

	virtual const char* RGSC_CALL GetPrivateAddress() const
	{
		return m_PrivateAddress;
	}

	virtual void RGSC_CALL SetPrivateAddress(const char* privateAddress)
	{
		strncpy_s(m_PrivateAddress, sizeof(m_PrivateAddress), privateAddress, sizeof(m_PrivateAddress) - 1);
	}
	
	virtual NatType RGSC_CALL GetNatType() const
	{
		return m_NatType;
	}

	virtual void RGSC_CALL SetNatType(NatType natType)
	{
		m_NatType = natType;
	}
	
	virtual NatFilteringMode RGSC_CALL GetNatFilteringMode() const
	{
		return m_NatFilteringMode;
	}

	virtual void RGSC_CALL SetNatFilteringMode(NatFilteringMode filteringMode)
	{
		m_NatFilteringMode = filteringMode;
	}

	virtual NatPortMappingMethod RGSC_CALL GetNatPortMappingMethod() const
	{
		return m_NatPortMappingMethod;
	}

	virtual void RGSC_CALL SetNatPortMappingMethod(NatPortMappingMethod portMappingMethod)
	{
		m_NatPortMappingMethod = portMappingMethod;
	}

	virtual int RGSC_CALL GetPortIncrement() const
	{
		return m_PortIncrement;
	}

	virtual void RGSC_CALL SetPortIncrement(int portIncrement)
	{
		m_PortIncrement = portIncrement;
	}

	virtual NatPortAllocationStrategy RGSC_CALL GetNatPortAllocationStrategy() const
	{
		return m_NatPortAllocationStrategy;
	}

	virtual void RGSC_CALL SetNatPortAllocationStrategy(NatPortAllocationStrategy portAllocationStrategy)
	{
		m_NatPortAllocationStrategy = portAllocationStrategy;
	}

	virtual UpNpState RGSC_CALL GetuPnPState() const
	{
		return m_UpNpState;
	}

	virtual void RGSC_CALL SetuPnPState(UpNpState state)
	{
		m_UpNpState = state;
	}

	virtual UdpTimeoutState RGSC_CALL GetUdpTimeoutState() const
	{
		return m_UdpTimeoutState;
	}

	virtual void RGSC_CALL SetUdpTimeoutState(UdpTimeoutState state)
	{
		m_UdpTimeoutState = state;
	}

	virtual unsigned RGSC_CALL GetUdpTimeoutSec() const
	{
		return m_UdpTimeoutSec;
	}

	virtual void RGSC_CALL SetUdpTimeoutSec(unsigned timeoutSec)
	{
		m_UdpTimeoutSec = timeoutSec;
	}

	virtual bool GetAllowAdjustablePresencePingInterval() const
	{
		return m_AllowAdjustablePresencePingInterval;
	}

	virtual void SetAllowAdjustablePingInterval(bool allowAdjustablePingInterval)
	{
		m_AllowAdjustablePresencePingInterval = allowAdjustablePingInterval;
	}

protected:
	NatDetectionState m_NatDetectionState;
	bool m_NatDetected;
	// enough space for IPv6, colon, and port
	char m_PublicAddress[64];
	char m_PrivateAddress[64];
	NatType m_NatType;
	NatFilteringMode m_NatFilteringMode;
	NatPortMappingMethod m_NatPortMappingMethod;
	int m_PortIncrement;
	NatPortAllocationStrategy m_NatPortAllocationStrategy;
	UpNpState m_UpNpState;
	UdpTimeoutState m_UdpTimeoutState;
	unsigned m_UdpTimeoutSec;
	bool m_AllowAdjustablePresencePingInterval;
};

//! Concrete class that implements the INetworkInfoV2 interface.
class NetworkInfoV2 : public INetworkInfoV2, public NetworkInfoV1
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject)
	{
		if(riid == IID_INetworkInfoV2)
		{
			*ppvObject = static_cast<INetworkInfoV2*>(this);
			return RGSC_OK;
		}

		return NetworkInfoV1::QueryInterface(riid, ppvObject);
	}

	NetworkInfoV2()
	{
		m_PcpState = INetworkInfoV2::NAT_PCP_UNATTEMPTED;
	}

	virtual PcpState RGSC_CALL GetPcpState() const
	{
		return m_PcpState;
	}

	virtual void RGSC_CALL SetPcpState(PcpState state)
	{
		m_PcpState = state;
	}

protected:
	PcpState m_PcpState;
};

typedef INetworkInfoV2 INetworkInfoLatestVersion;
#define IID_INetworkInfoLatestVersion IID_INetworkInfoV2
typedef NetworkInfoV2 NetworkInfo;

class INetwork : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_INetworkV1 = {0xb1ec2ca1, 0x7145, 0x470c, {0xa1, 0xa2, 0x4d, 0x65, 0x5a, 0x49, 0xbf, 0xba}};

//! Defines the public interface that game clients use to set/get network information/services.
class INetworkV1 : public INetwork
{
public:
	//! Informs the DLL about network information
	virtual void RGSC_CALL SetNetworkInfo(INetworkInfo* info) = 0;

	//! If set to true, the network information UI will display a warning about the NAT type with info on how to resolve.
	virtual void RGSC_CALL SetShowNatTypeWarning(bool showNatTypeWarning) = 0;
};

typedef INetworkV1 INetworkLatestVersion;
#define IID_INetworkLatestVersion IID_INetworkV1

} // namespace rgsc

#endif // RGSC_NETWORK_INTERFACE_H
