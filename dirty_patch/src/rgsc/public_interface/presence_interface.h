#ifndef PRESENCE_INTERFACE_H
#define PRESENCE_INTERFACE_H

#include "rgsc_common.h"
#if defined(PostMessage)
// windows headers conflict
#undef PostMessage
#endif

#include "tasks_interface.h"

#include <cstring>

namespace rgsc
{

// this needs to match RLSCPRESENCE_ATTR_NAME_MAX_SIZE
static const u32 RGSC_PRESENCE_ATTR_NAME_MAX_SIZE = 64;

// this needs to match RLSCPRESENCE_STRING_MAX_SIZE
static const u32 RGSC_PRESENCE_STRING_MAX_SIZE = 128;

//! Base interface class
class IPresenceAttribute : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};


#ifdef __cplusplus
extern "C" {
#endif

static const RGSC_IID IID_IPresenceAttributeV1 = {0x9b7e7354, 0xfed9, 0x42ca, {0xa0, 0xaf, 0xd0, 0xa3, 0x30, 0xa2, 0xa1, 0x62}};
static const RGSC_IID IID_IPresenceMessageV1 = {0xc3a48f00, 0x4873, 0x4a6d, {0x8c, 0xdd, 0x16, 0x56, 0x26, 0x42, 0x49, 0xbe}};
static const RGSC_IID IID_IPresenceMessageV2 = {0x37060b63, 0xe647, 0x4c2d, {0xb1, 0x5b, 0xf, 0x81, 0xe0, 0x32, 0xf9, 0x1}};
static const RGSC_IID IID_IPresenceManagerV1 = {0x8c6062e5, 0xd054, 0x478a, {0x9d, 0x66, 0x42, 0xe6, 0xf3, 0x6, 0x56, 0xb}};
static const RGSC_IID IID_IPresenceManagerV2 = {0xa2842ebb, 0x29de, 0x4389, {0xab, 0x37, 0x5d, 0xe1, 0x56, 0xb, 0x4e, 0x57}};
static const RGSC_IID IID_IPresenceManagerV3 = {0x4cca4554, 0xd0c1, 0x4f19, {0xb9, 0xe3, 0x8e, 0xd1, 0xac, 0x75, 0x5d, 0x49}};
static const RGSC_IID IID_IPresenceManagerV4 = {0xb1c0d9a8, 0x4e1e, 0x4ba0, {0x86, 0x40, 0x94, 0x94, 0xa6, 0x15, 0x49, 0x2}};
static const RGSC_IID IID_IPresenceManagerV5 = { 0xaddc682f, 0xab5e, 0x428a, { 0xa0, 0xa7, 0x6a, 0xd9, 0xfe, 0x66, 0x4a, 0x77 } };
static const RGSC_IID IID_IPresenceManagerV6 = { 0x8f5f574b, 0xa0, 0x40f7, { 0xa7, 0x7a, 0x15, 0xb2, 0x9f, 0x56, 0xae, 0x19 } };
static const RGSC_IID IID_IPresenceManagerV7 = { 0xa1b2d68f, 0xe486, 0x4e1b, { 0xb3, 0x26, 0x2b, 0x9a, 0xc3, 0x9f, 0xdd, 0x48 } };
static const RGSC_IID IID_IRgscPresenceDelegateV1 = { 0xbf1808e0, 0xb631, 0x4eec, { 0x8e, 0x99, 0xba, 0x4b, 0xb8, 0x9, 0xc6, 0x1b } };

#ifdef __cplusplus
}
#endif

//! Version 1 of the profile interface
class IPresenceAttributeV1 : public IPresenceAttribute
{
public:
	//! Presence attribute type
	enum Type
	{
		PRESTYPE_INVALID,	//!< Invalid type
		PRESTYPE_S64,		//!< Signed 64-bit
		PRESTYPE_DOUBLE,	//!< Double
		PRESTYPE_STRING,	//!< String
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;

	//! \param name null-terminated character string to use as the attribute name
	virtual void RGSC_CALL SetName(const char* name) = 0;

	//! \returns The attribute name
	virtual const char* RGSC_CALL GetName() const = 0;

	//! \returns The attribute #Type
	virtual Type RGSC_CALL GetType() const = 0;

	//! \param type #Type of attribute's value
	virtual void RGSC_CALL SetType(Type type) = 0;

	//! \param value The attribute value @{
	virtual bool RGSC_CALL SetValue(const s64 value) = 0;
	virtual bool RGSC_CALL SetValue(const double value) = 0;
	virtual bool RGSC_CALL SetValue(const char* value) = 0;	//! @}

	//! \param [out] value Pointer where the value will be stored @{
	virtual bool RGSC_CALL GetValue(s64* value) const = 0;
	virtual bool RGSC_CALL GetValue(double* value) const = 0;

	//! \param [out] value Pointer where the value will be stored
	//! \param sizeofValue Size of \p value buffer
	virtual bool RGSC_CALL GetValue(char* value, const unsigned sizeofValue) const = 0;	//! @}
};

//! Concrete class that implements the IPresenceAttributeV1 interface.
class PresenceAttributeV1 : public IPresenceAttributeV1
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
			pUnknown = static_cast<IPresenceAttribute*>(this);
		}
		else if(riid == IID_IPresenceAttributeV1)
		{
			pUnknown = static_cast<IPresenceAttributeV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	PresenceAttributeV1()
	{
		m_Type = PRESTYPE_INVALID;
		m_IntValue = 0;
		m_Name[0] = '\0';
	}

	virtual void RGSC_CALL SetName(const char* name)
	{
		strncpy_s(m_Name, sizeof(m_Name), name, sizeof(m_Name) - 1);
	}

	virtual const char* RGSC_CALL GetName() const
	{
		return m_Name;
	}

	virtual Type RGSC_CALL GetType() const
	{
		return m_Type;
	}

	virtual void RGSC_CALL SetType(Type type)
	{
		m_Type = type;
	}

	virtual bool RGSC_CALL SetValue(const s64 value)
	{
		m_IntValue = value;
		m_Type = PRESTYPE_S64;
		return true;
	}

	virtual bool RGSC_CALL SetValue(const double value)
	{
		m_DoubleValue = value;
		m_Type = PRESTYPE_DOUBLE;
		return true;
	}

	virtual bool RGSC_CALL SetValue(const char* value)
	{
		strncpy_s(m_StringValue, sizeof(m_StringValue), value, sizeof(m_StringValue) - 1);
		m_Type = PRESTYPE_STRING;
		return true;
	}

	virtual bool RGSC_CALL GetValue(s64* value) const
	{
		if(PRESTYPE_S64 == m_Type)
		{
			*value = m_IntValue;
			return true;
		}

		return false;
	}

	virtual bool RGSC_CALL GetValue(double* value) const
	{
		if(PRESTYPE_DOUBLE == m_Type)
		{
			*value = m_DoubleValue;
			return true;
		}

		return false;
	}

	virtual bool RGSC_CALL GetValue(char* value, const unsigned sizeofValue) const
	{
		if(PRESTYPE_STRING == m_Type)
		{
			strncpy_s(value, sizeofValue, m_StringValue, sizeofValue - 1);
			return true;
		}

		return false;
	}

protected:
	//Attribute name
	char m_Name[RGSC_PRESENCE_ATTR_NAME_MAX_SIZE];

	//Attribute value
	union
	{
		s64 m_IntValue;
		double m_DoubleValue;
		char m_StringValue[RGSC_PRESENCE_STRING_MAX_SIZE];
	};

	//Attribute type
	Type m_Type;
};

typedef PresenceAttributeV1 PresenceAttribute;
typedef IPresenceAttributeV1 IPresenceAttributeLatestVersion;
#define IID_IPresenceAttributeLatestVersion IID_IPresenceAttributeV1

//! Base interface class
class IPresenceMessage : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the profile interface
class IPresenceMessageV1 : public IPresenceMessage
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 2 of the profile interface
class IPresenceMessageV2 : public IPresenceMessageV1
{
public:

	//! Message source
	enum MessageSource
	{
		SENDER_UNKNOWN,
		SENDER_SERVER,
		SENDER_PLAYER,
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Concrete class that implements the IPresenceMessageV1 interface.
//! This version has a limit of #RGSC_PRESENCE_MAX_MESSAGE_SIZE chars in the message.
//! \deprecated This version exists for compatibility with older released titles. Use PresenceMessageV2.
class PresenceMessageV1 : public IPresenceMessageV1
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
			pUnknown = static_cast<IPresenceMessage*>(this);
		}
		else if(riid == IID_IPresenceMessageV1)
		{
			pUnknown = static_cast<IPresenceMessageV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	PresenceMessageV1()
	{
		m_PosixTimeStamp = 0;
		m_Contents[0] = '\0';
	}

	//! \param contents null-terminated contents
	virtual void RGSC_CALL SetContents(const char* contents)
	{
		strncpy_s(m_Contents, sizeof(m_Contents), contents, sizeof(m_Contents) - 1);
	}

	//! \returns The contents of the presence message
	virtual const char* RGSC_CALL GetContents() const
	{
		return m_Contents;
	}

	//! \returns The timestamp of the message
	virtual u64 RGSC_CALL GetTimestamp() const
	{
		return m_PosixTimeStamp;
	}

	//! \param timestamp The message timestamp
	virtual void RGSC_CALL SetTimestamp(u64 timestamp)
	{
		m_PosixTimeStamp = timestamp;
	}

protected:
	//! do not change this or you will break previously released games.
	//! PresenceMessageV2 (below) was created to handle the new
	//! 'unlimited size' presence messages.
	static const u32 RGSC_PRESENCE_MAX_MESSAGE_SIZE = 256;

	//Time at which message was created.
	//I.e. the time it was put in the queue on the presence server.
	u64 m_PosixTimeStamp;

	//Message contents.
	char m_Contents[RGSC_PRESENCE_MAX_MESSAGE_SIZE];
};

// error C4265: class has virtual functions, but destructor is not virtual
// the binary interface for virtual destructors isn't standardized, so don't make the destructor virtual
#pragma warning(push)
#pragma warning(disable: 4265)

//! Concrete class that implements the IPresenceMessageV1 interface.
//! This version supports messages of any length since Rage no longer has a max presence message size.
class PresenceMessageV2 : public IPresenceMessageV1
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
			pUnknown = static_cast<IPresenceMessage*>(this);
		}
		else if(riid == IID_IPresenceMessageV1)
		{
			pUnknown = static_cast<IPresenceMessageV1*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	PresenceMessageV2()
	{
		m_PosixTimeStamp = 0;
		m_Contents = NULL;
	}

	~PresenceMessageV2()
	{
		m_PosixTimeStamp = 0;
		FreeContents();
	}

	//! \copydoc PresenceMessageV1::SetContents
	virtual void RGSC_CALL SetContents(const char* contents)
	{
		FreeContents();
		unsigned bufSize = (unsigned)strlen(contents) + 1;
#if defined(rage_new)
		m_Contents = rage_new char[bufSize];
#else
		m_Contents = new char[bufSize];
#endif
		strncpy_s(m_Contents, bufSize, contents, bufSize - 1);
	}

	//! \copydoc PresenceMessageV1::GetContents
	virtual const char* RGSC_CALL GetContents() const
	{
		return m_Contents;
	}

	//! \copydoc PresenceMessageV1::GetTimestampe
	virtual u64 RGSC_CALL GetTimestamp() const
	{
		return m_PosixTimeStamp;
	}

	//! \copydoc PresenceMessageV1::SetTimestamp
	virtual void RGSC_CALL SetTimestamp(u64 timestamp)
	{
		m_PosixTimeStamp = timestamp;
	}

protected:
	virtual void RGSC_CALL FreeContents()
	{
		if(m_Contents)
		{
			delete m_Contents;
			m_Contents = NULL;
		}
	}

	//Time at which message was created.
	//I.e. the time it was put in the queue on the presence server.
	u64 m_PosixTimeStamp;

	//Message contents.
	char* m_Contents;
};

//! Concrete class that implements the IPresenceMessageV2 interface.
class PresenceMessageV3 : public IPresenceMessageV2
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
			pUnknown = static_cast<IPresenceMessage*>(this);
		}
		else if(riid == IID_IPresenceMessageV1)
		{
			pUnknown = static_cast<IPresenceMessageV1*>(this);
		}
		else if (riid == IID_IPresenceMessageV2)
		{
			pUnknown = static_cast<IPresenceMessageV2*>(this);
		}

		*ppvObject = pUnknown;
		if(pUnknown == NULL)
		{
			return RGSC_NOINTERFACE;
		}

		return RGSC_OK;
	}

	PresenceMessageV3()
	{
		m_PosixTimeStamp = 0;
		m_Contents = NULL;
		m_SenderGamerHandle = NULL;
		m_Source = IPresenceMessageV2::SENDER_UNKNOWN;
	}

	~PresenceMessageV3()
	{
		m_PosixTimeStamp = 0;
		FreeContents();
		FreeSenderGamerHandle();
		m_Source = IPresenceMessageV2::SENDER_UNKNOWN;
	}

	//! \copydoc PresenceMessageV1::SetContents
	virtual void RGSC_CALL SetContents(const char* contents)
	{
		FreeContents();
		unsigned bufSize = (unsigned)strlen(contents) + 1;
#if defined(rage_new)
		m_Contents = rage_new char[bufSize];
#else
		m_Contents = new char[bufSize];
#endif
		strncpy_s(m_Contents, bufSize, contents, bufSize - 1);
	}

	//! \copydoc PresenceMessageV1::GetContents
	virtual const char* RGSC_CALL GetContents() const
	{
		return m_Contents;
	}

	//! \copydoc PresenceMessageV1::GetTimestampe
	virtual u64 RGSC_CALL GetTimestamp() const
	{
		return m_PosixTimeStamp;
	}

	//! \copydoc PresenceMessageV1::SetTimestamp
	virtual void RGSC_CALL SetTimestamp(u64 timestamp)
	{
		m_PosixTimeStamp = timestamp;
	}

	//! \param gh null-terminated gamer handle
	virtual void RGSC_CALL SetSenderGamerHandle(const char* gh)
	{
		FreeSenderGamerHandle();
		unsigned bufSize = (unsigned)strlen(gh) + 1;
#if defined(rage_new)
		m_SenderGamerHandle = rage_new char[bufSize];
#else
		m_SenderGamerHandle = new char[bufSize];
#endif
		strncpy_s(m_SenderGamerHandle, bufSize, gh, bufSize - 1);
	}
	   
	//! \returns The gamer handle of the sender if the message is sent by a player
	virtual const char* RGSC_CALL GetSenderGamerHandle() const
	{
		return m_SenderGamerHandle;
	}

	//! \returns the message source if known
	virtual MessageSource RGSC_CALL GetSource() const
	{
		return m_Source;
	}

	//! sets the message source
	virtual void RGSC_CALL SetSource(MessageSource source)
	{
		m_Source = source;
	}
	
protected:
	virtual void RGSC_CALL FreeContents()
	{
		if(m_Contents)
		{
			delete m_Contents;
			m_Contents = NULL;
		}
	}

	virtual void RGSC_CALL FreeSenderGamerHandle()
	{
		if(m_SenderGamerHandle)
		{
			delete m_SenderGamerHandle;
			m_SenderGamerHandle = NULL;
		}
	}

	//Time at which message was created.
	//I.e. the time it was put in the queue on the presence server.
	u64 m_PosixTimeStamp;

	//Message contents.
	char* m_Contents;

	//Gamer handle of the sender if the message is sent by a player.
	char* m_SenderGamerHandle;

	//The source of the message.
	MessageSource m_Source;
};

#pragma warning(pop)

typedef IPresenceMessageV2 IPresenceMessageLatestVersion;
#define IID_IPresenceMessageLatestVersion IID_IPresenceMessageV2
typedef PresenceMessageV3 PresenceMessage;

//! Base interface class
class IRgscPresenceDelegate : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the IRgscPresenceDelegate interface
class IRgscPresenceDelegateV1 : public IRgscPresenceDelegate
{
public:
	//! @{
	//! \copydoc IPresenceManagerV1::SetIntAttribute
	virtual bool RGSC_CALL SetIntAttribute(const int localGamerIndex, const char* name, const s64 value) = 0;
	virtual bool RGSC_CALL SetDoubleAttribute(const int localGamerIndex, const char* name, const double value) = 0;
	virtual bool RGSC_CALL SetStringAttribute(const int localGamerIndex, const char* name, const char* value) = 0;	//! @}

	//! @{
	//! \copydoc IPresenceManagerV1::GetIntAttribute
	virtual bool RGSC_CALL GetIntAttribute(const int localGamerIndex, const char* name, s64* value) = 0;
	virtual bool RGSC_CALL GetDoubleAttribute(const int localGamerIndex, const char* name, double* value) = 0;
	//! \copydoc IPresenceManagerV1::GetStringAttribute
	virtual bool RGSC_CALL GetStringAttribute(const int localGamerIndex, const char* name, char* value, const unsigned sizeofValue) = 0;	//! @}

	//! \copydoc IPresenceManagerV2::Subscribe
	virtual bool RGSC_CALL Subscribe(const int localGamerIndex, const char** channels, const unsigned numChannels) = 0;

	//! \copydoc IPresenceManagerV2::Unsubscribe
	virtual bool RGSC_CALL Unsubscribe(const int localGamerIndex, const char** channels, const unsigned numChannels) = 0;

	//! \copydoc IPresenceManagerV2::UnsubscribeAll
	virtual bool RGSC_CALL UnsubscribeAll(const int localGamerIndex) = 0;

	//! \copydoc IPresenceManagerV2::Publish
	virtual bool RGSC_CALL Publish(const int localGamerIndex, const char** channels, const unsigned numChannels, const char* filterName, const char* paramNameValueCsv, const IPresenceMessage* message) = 0;
};

//! Base interface class
class IPresenceManager : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the \ref group_IPresenceManager interface.
class IPresenceManagerV1 : public IPresenceManager
{
public:
    //! Sets the local copy of the attribute. @{
    //! The new value will be synchronized with ROS a short time after.
    //!
    //! \param localGamerIndex Index of local gamer for whom to set attributes.
    //! \param name            Attribute name
    //! \param value           Attribute value
    //! 
    //! \returns
    //! True for success.  The method will succeed as long as the named
    //! attribute already exists, or it can be created without exceeding 
    //! RL_SCPRESENCE_MAX_ATTRIBUTES.
    virtual bool RGSC_CALL SetIntAttribute(const int localGamerIndex,
										   const char* name,
										   const s64 value) = 0;
    virtual bool RGSC_CALL SetDoubleAttribute(const int localGamerIndex,
											  const char* name,
											  const double value) = 0;
    virtual bool RGSC_CALL SetStringAttribute(const int localGamerIndex,
											  const char* name,
											  const char* value) = 0;	//! @}

    //! Retrieves the local copy of the attribute. @{
    //! 
    //! \param localGamerIndex Index of local gamer for whom to get attributes.
    //! \param name            Attribute name
    //! \param [out] value     Will be populated with the attribute value
    //! 
    //! \returns True for success, i.e. if the attribute exists.
    virtual bool RGSC_CALL GetIntAttribute(const int localGamerIndex,
										   const char* name,
										   s64* value) = 0;
    virtual bool RGSC_CALL GetDoubleAttribute(const int localGamerIndex,
											  const char* name,
											  double* value) = 0;
	//! \param sizeofValue Size of \p value.
	//! \copydoc GetIntAttribute
    virtual bool RGSC_CALL GetStringAttribute(const int localGamerIndex,
											  const char* name,
											  char* value,
											  const unsigned sizeofValue) = 0;	//! @}

    //! Retrieves attributes for the gamer identified by the gamer handle.
    //! 
    //!	\param rockstarId	Identifies the gamer for whom to retrieve attributes.
    //! \param attrs		Array of attributes to retrieve.  Each item in the array must have its Name member set.
    //! \param numAttrs		Number of attributes in the attrs array
    //! \param [out] status Optional. Can be polled for completion
    //!
    //! \note Upon completion attributes not retrieved will have their Type members set to INVALID.
    //! \note This is an asynchronous operation.  Don't deallocate \p attrs or \p status while the operation is pending.
    virtual bool RGSC_CALL GetAttributesForGamer(const RockstarId rockstarId,
												 IPresenceAttribute* attrs,
												 const unsigned numAttrs,
												 IAsyncStatus* status) = 0;

    //! Posts a message to the recipients' message queues.
    //! 
    //! \param localGamerindex	Index of local gamer making the call
    //! \param recipients		Message recipients
    //! \param numRecipients	Number of recipients
    //! \param message			The message
    //! \param ttlSeconds
	//! \param [out] status		Optional. Can be polled for completion
	//!
	//! \note This is an asynchronous operation.  Don't deallocate \p recipients, \p message, or \p status while the operation is pending.
    virtual bool RGSC_CALL PostMessage(const int localGamerindex,
									   const RockstarId* recipients,
									   const unsigned numRecipients,
									   IPresenceMessage* message,
									   const unsigned ttlSeconds,
									   IAsyncStatus* status) = 0;

	//! Runs a predefined query on the presence database and returns the results.
	//! 
	//! Results are JSON representations of presence records. 
	//!
	//! \param queryName			Name of predefined query
	//! \param paramNameValueCsv	Query parameters in CSV format. Parameter names alternate with values. Names must be prefixed with '@', as in \@playerid.
	//! \param offset				Offset into results at which to begin returning results.
	//! \param count				Number of results to return.
	//! \param recordsBuf			Buffer to hold records returned
	//! \param sizeofRecordsBuf		Size of \p recordsBuf.
	//! \param records				Array of char pointers that will be populated with records returned from the query.
	//!									It must be large enough to contain \p count results.
	//!									Each string in the array points to a section of the \p resultsBuf memory buffer.
	//! \param numRecordsRetrieved	Upon completion will contain the number of records actually retrieved.
	//! \param numRecords			Upon completion will contain the number of records parsed.
	//!									If \p recordsBuf is too small, \p numRecords will be less than \p numRecordsRetrieved.
	//! \param status				Optional. Can be polled for completion
	//!
	//! \note Records are limited to RLSC_PRESENCE_QUERY_MAX_RECORD_SIZE bytes each.
	//! \note Each record is returned as a null terminated string. The \p recordsBuf parameter should be large enough to hold <tt>(count * RLSC_PRESENCE_QUERY_MAX_RECORD_SIZE) chars.</tt>
	//! \note This is an asynchronous operation.  Do not deallocate \p recordBuf, \p records, \p numRecords, or \p status while the operation is pending.
	virtual bool RGSC_CALL Query(const char* queryName,
								 const char* paramNameValueCsv,
								 const int offset,
								 const int count,
								 char* recordsBuf,
								 const unsigned sizeofRecordsBuf,
								 char** records,
                                 unsigned* numRecordsRetrieved,
								 unsigned* numRecords,
								 IAsyncStatus* status) = 0;

	//! Runs a predefined query on the presence database and returns the number of records that match the query.
	//! 
	//! \param queryName			Name of predefined query
	//! \param paramNameValueCsv	Query parameters in CSV format. Parameter names alternate with values. Names must be prefixed with '@', as in \@playerid.
	//! \param [out] count			Upon completion will contain the number of records that match the query.
	//! \param [out] status			Optional. Can be polled for completion
	//!
	//! \note This is an asynchronous operation.  Don't deallocate \p queryName, \p paramNameValueCsv, \p count or \p status while the operation is pending.
	virtual bool RGSC_CALL QueryCount(const char* queryName,
									  const char* paramNameValueCsv,
									  unsigned* count,
									  IAsyncStatus* status) = 0;

	//! Set a rich presence
	//! 
	//! \param presenceId	Selects the rich presence template
	//! \param attrs		Array of \ref group_IPresenceAttribute
	//! \param numAttrs		Size of \p attrs array
	//! \param [out] status	Optional. Can be polled for completion
	//! 
	//! \note This is an asynchronous operation.  Don't deallocate \p attrs or \p status while the operation is pending.
    virtual bool RGSC_CALL SetRichPresence(const int presenceId,
										   IPresenceAttribute* attrs,
										   const unsigned numAttrs,
										   IAsyncStatus* status) = 0;

	//! \param allowInvites Allow/disallow invites to a game
	virtual bool RGSC_CALL AllowGameInvites(bool allowInvites) = 0;

	//! \param sessionInfo The session info for the game
	virtual bool RGSC_CALL SetGameSessionInfo(const char* sessionInfo) = 0;

	//! \param allowInvites Allow/disallow party invites
	virtual bool RGSC_CALL AllowPartyInvites(bool allowInvites) = 0;

	//! \param sessionInfo The session info for a party
	virtual bool RGSC_CALL SetPartySessionInfo(const char* sessionInfo) = 0;
};

//! Version 2 of the \ref group_IPresenceManager interface
class IPresenceManagerV2 : public IPresenceManagerV1
{
public:

	//! Subscribe/unsubscribe to one or more message channels. @{
	//!
	//! \param localGamerIndex	Index of local gamer making the call.
	//! \param channels			List of channels to (un)subscribe to.
	//! \param numChannels		Number of channels in the list.
	//!
	//! \note This is an asynchronous operation. Don't deallocate \p channels while the operation is pending.
    virtual bool RGSC_CALL Subscribe(const int localGamerIndex,
									 const char** channels,
									 const unsigned numChannels) = 0;

    virtual bool RGSC_CALL Unsubscribe(const int localGamerIndex,
									   const char** channels,
									   const unsigned numChannels) = 0;	//! @}

	//! Unsubscribe from all subscribed message channels
	//! \param localGamerIndex	Index of local gamer making the call
    virtual bool RGSC_CALL UnsubscribeAll(const int localGamerIndex) = 0;

	//! Publish a message to one or more message channels.
	//!
	//! \param localGamerIndex		Index of local gamer making the call.
	//! \param channels				Optional. List of channels to publish to.
	//! \param numChannels			Number of channels in the list.
	//! \param filterName			Optional. Name of filter that can be used to perform additional filtering on message recipients.
	//! \param paramNameValueCsv	Filter parameters in CSV format. Parameter names alternate with values. Names must be prefixed with '@', as in \@playerid.
	//! \param message				The message.
	//!
	//! \note This is an asynchronous operation. Don't deallocate \p channels, \p filterName, or \p paramNameValueCsv while the operation is pending.
    virtual bool RGSC_CALL Publish(const int localGamerIndex,
								   const char** channels,
								   const unsigned numChannels,
								   const char* filterName,
								   const char* paramNameValueCsv,
								   const IPresenceMessage* message) = 0;
};

//! Version 3 of the \ref group_IPresenceManager interface
class IPresenceManagerV3 : public IPresenceManagerV2
{
public:
	//! \param sessionInfo The additional info to broadcast
	virtual bool RGSC_CALL SetAdditionalSessionInfo(const char* sessionInfo) = 0;

	//! \param allowInvites	Enable/disable additional invites
	virtual bool RGSC_CALL AllowAdditionalSessionGameInvites(bool allowInvites) = 0;
};

//! Version 4 of the \ref group_IPresenceManager interface
class IPresenceManagerV4 : public IPresenceManagerV3
{
public:

	//! Result from a game invite
	enum GameInviteConsumeReason
	{
		ACCEPTED = 0,
		REJECTED = 1,
		INVALID = 2,
		FAILED = 3
	};

	//! Notify RGSC that an invite was consumed
	//!
	//! \param inviterId	The id of the inviter
	//! \param sessionInfo	Any information about the session
	//! \param reason		The reason the invite was consumed
	virtual bool RGSC_CALL NotifyGameInviteConsumed(RockstarId inviterId, const char* sessionInfo, IPresenceManagerV4::GameInviteConsumeReason reason) = 0;
};

//! Version 5 of the \ref group_IPresenceManager interface
class IPresenceManagerV5 : public IPresenceManagerV4
{
public:	

	//! For titles managing their own connection to presence, they can invoke this interface to 
	//  forward a presence message to the SDK. If the SDK consumes the message, this will return true.
	virtual bool RGSC_CALL NotifySocialClubEvent(IPresenceMessage* message) = 0;
};

//! Version 6 of the \ref group_IPresenceManager interface
class IPresenceManagerV6 : public IPresenceManagerV5
{
public:	

	//! Method for sending Presence messages
	enum PresenceSendMethod
	{
		PRESENCE_SERVER,
		PEER_TO_PEER
	};

	//! Callback function signature
	typedef bool (*HandlePresenceMessageCallback)( PresenceSendMethod sendType, RockstarId* rockstarIds, unsigned numRockstarIds, IPresenceMessage* message, int ttlSeconds);

	//! For titles managing their own connection to presence, they can set this callback and the SDK
	//  will forward presence messages to this function first. The client should return 'true' if the game has consumed this message.
	//  If this handler is not set, or it returns 'false', the default presence message posting will occur.
	virtual bool RGSC_CALL SetPresenceMessageHandler(HandlePresenceMessageCallback cb) = 0;
};

//! Version 7 of the \ref group_IPresenceManager interface
class IPresenceManagerV7 : public IPresenceManagerV6
{
public:

	//! For titles managing their own connection to presence, they must provide a delegate for 
	//  the SDK to write presence attributes, add/remove subscriptions, etc.
	virtual bool RGSC_CALL SetDelegate(IRgscPresenceDelegate* delegate) = 0;
};

typedef IPresenceManagerV7 IPresenceManagerLatestVersion;
#define IID_IPresenceManagerLatestVersion IID_IPresenceManagerV7

} // namespace

#endif // PRESENCE_INTERFACE_H
