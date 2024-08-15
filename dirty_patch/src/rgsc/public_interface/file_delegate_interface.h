#ifndef RGSC_FILE_DELEGATE_H
#define RGSC_FILE_DELEGATE_H

#include "rgsc_common.h"

namespace rgsc
{

class IFileDelegate : public IRgscUnknown
{
public:
	typedef void *FileHandle;
	static const int invalidHandle = -1;
	struct FileFindData {
		char m_Name[RGSC_MAX_PATH];	// Name of the file
		u64 m_Size;			// Size of the file
		u64 m_LastWriteTime;// Last time the file was written
		u32 m_Attributes;	// Bitfield using the FILE_ATTRIBUTE_... values
	};

	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IFileDelegateV1 = {0xd895fb45, 0x7191, 0x4c1f, {0x8e, 0x91, 0xc0, 0x4e, 0xaa, 0x9f, 0xba, 0xef}};

//! Rgsc will call certain file I/O functions via this delegate interface.
//! Note: this is a special-purpose feature to support Korean internet cafes
//! that need to store profile data via their cloud system.
class IFileDelegateV1 : public IFileDelegate
{
public:
	// PURPOSE:	Attempt to open a file on this device
	// PARAMS:	filename - Name of file to open (including device id)
	//			readOnly - True if file will be read-only, else false.
	// RETURNS:	Non-negative handle value on success, negative value on error.
	// NOTES:	If a file is read-only, we attempt to open in a sharing-friendly
	//			manner.  If this function returns a value file handle, you
	//			must eventually call Close on this device with that handle or
	//			else you would suffer a resource leak.
	virtual FileHandle RGSC_CALL Open(const char *filename, bool readOnly)const = 0;

	// PURPOSE:	Attempt to create a file on this device
	// PARAMS:	filename - Name of file to open (including device id)
	//			readOnly - True if file will be read-only, else false.
	// RETURNS:	Non-negative handle value on success, negative value on error.
	//	NOTES:	If this function returns a value file handle, you
	//			must eventually call Close on this device with that handle or
	//			else you would suffer a resource leak.
	virtual FileHandle RGSC_CALL Create(const char *filename)const = 0;

	// PURPOSE:	Read binary data from file
	// PARAMS:	handle - Handle for file (must have been opened or created with
	//				the same device)
	//			outBuffer - Destination to receive data that is read
	//			bufferSize - Maximum amount of data to read
	// RETURNS:	Non-negative integer on success representing number of bytes
	//			of data read (zero typically means end-of-file).  Negative integer
	//			indicates an error.
	// NOTES:	No translation of any kind is done on the data.
	virtual int RGSC_CALL Read(FileHandle handle, void *outBuffer, int bufferSize)const = 0;

	// PURPOSE:	Write binary data to file
	// PARAMS:	handle - Handle for file (must have been opened or created with
	//				the same device)
	//			buffer - Source buffer for data to write
	//			bufferSize - Maximum amount of data to read
	// RETURNS:	Non-negative integer on success representing number of bytes
	//			of data written (zero typically means media full).  Negative integer
	//			indicates an error.
	// NOTES:	No translation of any kind is done on the data.
	virtual int RGSC_CALL Write(FileHandle handle, const void *buffer, int bufferSize)const = 0;

	// PURPOSE:	Close a file
	// PARAMS:	handle - Handle of file to close (must have been opened or created
	// 				with the same device).
	// NOTES:	You must eventually Close any handle successfully returned by an Open
	//			or Create call or else you will have a resource leak.
	// RETURNS:	zero if the call succeeded, non-zero if it failed
	virtual int RGSC_CALL Close(FileHandle handle)const = 0;

	// PURPOSE:	Delete a file from device
	// PARAMS:	filename - Name of file to delete
	// RETURNS:	True on success (file deleted), or false on failure (file not found,
	//			marked read-only, etc)
	virtual bool RGSC_CALL Delete(const char *filename)const = 0;

	// PURPOSE:	Iterate over all files in a directory
	// PARAMS:	directoryName - Name of the directory to search (no wildcard necessary
	//				or supported; do filtering yourself in higher-level code).
	//			outData - Info for first matching file (if return value was not -1)
	// RETURNS:	A "find handle" that is used to identify this search so that more
	//			that one can be in progress at a time, or -1 if we were unable to
	//			find any matches.  Must eventually call FindFileEnd on this handle
	//			if it did not return -1.
	// NOTES:	Some platforms will return "." and ".." and some will not, so make
	//			sure you handle them properly.
	virtual FileHandle RGSC_CALL FindFileBegin(const char *directoryName, FileFindData &outData)const = 0;

	// PURPOSE:	Continue a search begun with FindFileBegin
	// PARAMS:	handle - Find handle returned by FindFileBegin
	//			outData - Info for next match file (if return value was not false)
	// RETURNS:	True on success (outData is valid), or false if there were no more matches
	virtual bool RGSC_CALL FindFileNext(FileHandle handle, FileFindData &outData)const = 0;

	// PURPOSE:	Close a search begun with FindFileBegin
	// PARAMS:	handle - Find handle to close
	// RETURNS: Zero if the call succeeded, non-zero otherwise.
	virtual int RGSC_CALL FindFileEnd(FileHandle handle)const = 0;

	// PURPOSE:	Make a directory on device
	// PARAMS:	pathname - Name of directory to create
	// RETURNS:	True on success, or false on failure (directory already existed, etc)
	virtual bool RGSC_CALL MakeDirectory(const char *pathname)const = 0;

	// PURPOSE: Remove a directory and optionally all of its contents from a device
	// PARAMS: pathname - Name of the directory to remove
	//			deleteContents - auto delete everything inside the directory as well
	// RETURNS: True on success, false on failure (invalid path, deleteContents is false 
	//			but directory isn't empty, etc.)
	virtual bool RGSC_CALL DeleteDirectory(const char *pathname, bool deleteContents, bool ignoreReadOnly)const = 0;
};

typedef IFileDelegateV1 IFileDelegateLatestVersion;

} // namespace rgsc

#endif // RGSC_FILE_DELEGATE_H
