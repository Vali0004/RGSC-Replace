#ifndef CLOUDSAVE_INTERFACE_H
#define CLOUDSAVE_INTERFACE_H

#include "rgsc_common.h"
#include "tasks_interface.h"

namespace rgsc
{

// ===============================================================================================
// ICloudSaveConfiguration
// ===============================================================================================
class ICloudSaveTitleConfiguration : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveTitleConfiguration interface
class ICloudSaveTitleConfigurationV1 : public ICloudSaveTitleConfiguration
{
public:

	//!	Returns the title name for the configuration
	virtual const char* RGSC_CALL GetTitleName() = 0;

	//!	Returns the number of cloud save files in the title configuration
	virtual u32 RGSC_CALL GetNumCloudFiles() = 0;

	//!	Returns the file name of the configured file at a given index
	virtual const char* RGSC_CALL GetFileName(unsigned index) = 0;

	//!	Returns the directory that houses the per-profile/per-title save data
	virtual const char* RGSC_CALL GetSaveDirectory() = 0;

	//!	Returns the HARDWAREID that should be used when POSTING to the cloud (example: Machine Name)
	virtual const char* RGSC_CALL GetHardwareId() = 0;

};

//! Version 2 of the ICloudSaveTitleConfiguration interface
class ICloudSaveTitleConfigurationV2 : public ICloudSaveTitleConfigurationV1
{
public:
	//! Returns the numeric ROS title id for the configuration. Used for apps managing multiple titles.
	virtual const int RGSC_CALL GetTitleId() = 0;

	//! Returns the title access token for the configuration. Used for apps managing multiple titles.
	virtual const char* RGSC_CALL GetTitleAccessToken() = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveTitleConfigurationV1 = { 0x36040192, 0x1776, 0x4e6e, { 0x96, 0xce, 0x46, 0x9a, 0x75, 0x79, 0x72, 0x22 } };
extern "C" static const RGSC_IID IID_ICloudSaveTitleConfigurationV2 = { 0x8485dd6b, 0x9a41, 0x42e9, { 0xa6, 0xc8, 0xeb, 0xfa, 0x1, 0xc8, 0xa8, 0x3b } };

typedef ICloudSaveTitleConfigurationV2 ICloudSaveTitleConfigurationLatestVersion;
#define IID_ICloudSaveTitleConfigurationLatestVersion IID_ICloudSaveTitleConfigurationV2


// ===============================================================================================
// ICloudSaveHttpDebugInfo
// ===============================================================================================
class ICloudSaveHttpDebugInfo : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveHttpDebugInfo interface
class ICloudSaveHttpDebugInfoV1 : public ICloudSaveHttpDebugInfo
{
public:

	// PURPOSE
	//	Resets the debug object.
	virtual void RGSC_CALL Reset() = 0;

	// PURPOSE
	//	Gets or Sets the send state of the underlying http request.
	virtual int RGSC_CALL GetSendState() = 0;
	virtual void RGSC_CALL SetSendState(int sendState) = 0;

	// PURPOSE
	//	Gets or Sets the receive state of the underlying http request.
	virtual int RGSC_CALL GetRecvState() = 0;
	virtual void RGSC_CALL SetRecvState(int recvState) = 0;

	// PURPOSE
	//	Gets or Sets the number of inbound content bytes received.
	virtual unsigned RGSC_CALL GetInContentBytesRcvd() = 0;
	virtual void RGSC_CALL SetInContentBytesRcvd(int bytes) = 0;

	// PURPOSE
	//	Gets or Sets the number of outbound content bytes sent.
	virtual unsigned RGSC_CALL GetOutContentBytesSent() = 0;
	virtual void RGSC_CALL SetOutContentBytesSent(int bytes) = 0;

	// PURPOSE
	//	Gets or Sets if the http request was committed.
	virtual bool RGSC_CALL IsCommitted() = 0;
	virtual void RGSC_CALL SetCommitted(bool committed) = 0;

	// PURPOSE
	//	Gets or Sets the http status code (-1 if not received)
	virtual int RGSC_CALL GetHttpStatusCode() = 0;
	virtual void RGSC_CALL SetHttpStatusCode(int code) = 0;
};

//! Version 2 of the ICloudSaveHttpDebugInfo interface
class ICloudSaveHttpDebugInfoV2 : public ICloudSaveHttpDebugInfoV1
{
public:

	// PURPOSE
	//	Gets or sets the HTTP abort reason (0 if request was not aborted)
	virtual int RGSC_CALL GetAbortReason() = 0;
	virtual void RGSC_CALL SetAbortReason(int abortReason) = 0;

	// PURPOSE
	//	Gets or Sets if the HTTP request encountered an error allocating memory.
	virtual bool RGSC_CALL HadMemoryAllocationError() = 0;
	virtual void RGSC_CALL SetHadMemoryAllocationError(bool bHadMemoryError) = 0;

	// PURPOSE
	//	Gets or Sets the underlying TCP result state of the last HTTP request
	virtual int RGSC_CALL GetTcpResultState() = 0;
	virtual void RGSC_CALL SetTcpResultState(int resultState) = 0;

	// PURPOSE
	//	Gets or Sets the TCP error code of the last HTTP request (0 if no error)
	virtual int RGSC_CALL GetTcpError() = 0;
	virtual void RGSC_CALL SetTcpError(int error) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveHttpDebugInfoV1 = { 0x76f502a3, 0x1786, 0x4b3f, { 0xa5, 0x3b, 0xed, 0x2e, 0xa8, 0x1a, 0x2c, 0xdb } };
extern "C" static const RGSC_IID IID_ICloudSaveHttpDebugInfoV2 = { 0x5ced22a0, 0x3dbe, 0x417d, { 0xae, 0x3d, 0xdd, 0x50, 0x7f, 0x5f, 0x29, 0x90 } };

typedef ICloudSaveHttpDebugInfoV2 ICloudSaveHttpDebugInfoLatestVersion;
#define RGSC_IIDICloudSaveHttpDebugInfoLatestVersion IID_ICloudSaveHttpDebugInfoV2

// ===============================================================================================
// ICloudSaveFile
// ===============================================================================================
class ICloudSaveFile : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveFile interface
class ICloudSaveFileV1 : public ICloudSaveFile
{
public:

	//! Clears the save file, resetting it and de-allocating memory
	virtual void RGSC_CALL Clear() = 0;

	//! Get and set the file id
	virtual void RGSC_CALL SetFileId(u64 fileId) = 0;
	virtual u64 RGSC_CALL GetFileId() const = 0;

	//! Get and set the md5 hash
	virtual void RGSC_CALL SetMd5Hash(const char* md5Hash) = 0;
	virtual const char* RGSC_CALL GetMd5Hash() const = 0;

	//! Get and set the filename
	virtual void RGSC_CALL SetFileName(const char* fileName) = 0;
	virtual const char* RGSC_CALL GetFileName() const = 0;

	//! Get and set the file version
	virtual void RGSC_CALL SetFileVersion(u64 fileVersion) = 0;
	virtual u64 RGSC_CALL GetFileVersion() const = 0;

	//! Get and set the last modified date set by the client
	virtual void RGSC_CALL SetClientLastModifiedDate(u64 clientLastModifiedDate) = 0;
	virtual u64 RGSC_CALL GetClientLastModifiedDate() const = 0;

	//! Get and set the last modified date set by the server
	virtual void RGSC_CALL SetServerLastModifiedDate(u64 serverLastModifiedDate) = 0;
	virtual u64 RGSC_CALL GetServerLastModifiedDate() const = 0;

	//! Get and set the hardware id
	virtual void RGSC_CALL SetHardwareId(const char* hardwareId) = 0;
	virtual const char* RGSC_CALL GetHardwareId() const = 0;

	//! Get and set the last client ip address
	virtual void RGSC_CALL SetLastIpAddress(const char* ipAddressString) = 0;
	virtual const char* RGSC_CALL GetLastIpAddress() const = 0;

	//! Allocates a local copy of the input data
	virtual void RGSC_CALL CopyData(u8* data, unsigned dataLen) = 0;

	//! Get the data pointer and length
	virtual u8* RGSC_CALL GetData() const = 0;
	virtual u32 RGSC_CALL GetDataLength() const = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveFileV1 = { 0x643d3177, 0x3ab7, 0x4911, { 0x8b, 0x48, 0xa1, 0xf4, 0x90, 0xfc, 0x2, 0x11 } };

class ICloudSaveFileV2 : public ICloudSaveFileV1
{
public:

	enum ConflictState
	{
		CS_None, // Synced
		CS_FileMissing, // File is in the server manifest but not on disk. Must be downloaded.
		CS_ServerHasNewer, // Server has a newer version of the file than is on disk, but no local progress has been made. Must be downloaded.
		CS_ClientHasNewer, // The client's file has been modified more recently than the last write time of the server.
		CS_ClientHasNewerWithConflict, // The client has a different version than whats on the server, but has been updated since the last server side sync
		CS_FileDeleted, // File has been deleted from the local machine and must be deleted from the cloud.
		CS_FileDeletedWithConflict, // File has been marked for delete, and is missing locally, but the server has a newer version. Must be resolved.
		CS_ServerHasNewerWithConflict, // Server has a newer version of the file than is on disk, and local progress may have been made, so this must be resolved.
									// The only time we don't resolve conflict when the server has a newer version of the file is when we don't have any copy of the file
									// locally, but the separate 'FileMissing' state covers this.
	};

	// Per-File conflict resolution, similar to the ICloudSaveManager::ResolveType enum used in the
	//	POST/GET file operations. Each file should have their conflict resolution type set before
	//	requesting a manifest to have its conflicts resolved.
	enum ConflictResolutionType
	{
		CRT_None,
		CRT_AcceptRemote,
		CRT_AcceptLocal,
	};

	//!	Set or get the metadata that is associated with the save file.
	virtual const char* RGSC_CALL GetMetaData() = 0;
	virtual void RGSC_CALL SetMetaData(const char* metaData) = 0;

	//!	Set or get the conflict state of the file
	virtual ConflictState RGSC_CALL GetConflictState() = 0;
	virtual void RGSC_CALL SetConflictState(ConflictState state) = 0;

	//!	Set or get if a file is dirty. A file is set to dirty when the cloud save manager calls 'RegisterForUpload'.
	/**
		This dirty flag is only cleared after a successful post.
	*/
	virtual bool RGSC_CALL IsDirty() = 0;
	virtual void RGSC_CALL SetIsDirty(bool bDirty) = 0;

	//!	Get or set the resolve type. This resolution type should be set by the client after conflicts have been identified.
	virtual ConflictResolutionType RGSC_CALL GetResolveType() = 0;
	virtual void RGSC_CALL SetResolveType(ConflictResolutionType resolveType) = 0;

	//! Free the data associated with a save file
	virtual void RGSC_CALL FreeSaveData() = 0;

	//!	Gets or sets if a file should be copied (i.e. from .cloudsave). This is set during the GetUpdatedFiles task and used in the CopyUpdatedFiles task. 
	/**
		This act ensures that lingering ".cloudsave" files won't overwrite your data. This value does not persist through multiple launches.
	*/
	virtual void RGSC_CALL SetShouldCopyFile(bool bShouldCopy) = 0;
	virtual bool RGSC_CALL ShouldCopyFile() = 0;

	//! Get and set the file version that the server expects to be written next
	virtual void RGSC_CALL SetNextExpectedVersion(u64 fileVersion) = 0;
	virtual u64 RGSC_CALL GetNextExpectedVersion() const = 0;

	//! Get and set the metadata from the server
	virtual void RGSC_CALL SetServerMetadata(const char* metadata) = 0;
	virtual const char* RGSC_CALL GetServerMetadata() const = 0;

	//! Get and set the file size on the local disk
	virtual void RGSC_CALL SetClientFileSize(u64 fileSize) = 0;
	virtual u64 RGSC_CALL GetClientFileSize() const = 0;

	//! Get and set the file size on the server
	virtual void RGSC_CALL SetServerFileSize(u64 fileSize) = 0;
	virtual u64 RGSC_CALL GetServerFileSize() const = 0;

	//! Get and set the latest file version from the server. 
	/** This is set during the identify conflicts task,
	*	and used to validate the results of an upload. It is not cached to disk.
	*/
	virtual void RGSC_CALL SetLatestServerVersion(u64 fileVersion) = 0;
	virtual u64 RGSC_CALL GetLatestServerVersion() const = 0;

	//! Get and set if the file has been marked for deletion.
	virtual void RGSC_CALL SetMarkedForDeletion(bool bMarkedForDeletion) = 0;
	virtual bool RGSC_CALL IsMarkedForDeletion() const = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveFileV2 = { 0xe6fb4c3b, 0xfa13, 0x4f6b, { 0x82, 0xf4, 0xd8, 0xe2, 0xee, 0x2c, 0xf1, 0x9 } };

class ICloudSaveFileV3 : public ICloudSaveFileV2
{
public:

	//! Returns TRUE if backups for the cloud file have been identified.
	virtual bool RGSC_CALL HasSearchedBackups() = 0;
	virtual void RGSC_CALL SetHasSearchedBackups(bool bSearched) = 0;

	//! Returns the backup slot data for the save file. The backup slots use bit flags to determine if
	//	a backup exists for the given slot. While we only use 3 slots by default, this allows us bump this
	//	value up to 64 save slots without issue.
	virtual s64 RGSC_CALL GetBackupSlots() = 0;
	virtual void RGSC_CALL SetBackupSlots(s64 numBackups) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveFileV3 = { 0xa438fef8, 0xac20, 0x4d4b, { 0x8b, 0x61, 0x90, 0x83, 0xbe, 0xf7, 0x90, 0x41 } };

typedef ICloudSaveFileV3 ICloudSaveFileLatestVersion;
#define IID_ICloudSaveFileLatestVersion IID_ICloudSaveFileV3



// ===============================================================================================
// ICloudSaveOperationProgress
// ===============================================================================================
class ICloudSaveOperationProgress : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveOperationProgress interface
class ICloudSaveOperationProgressV1 : public ICloudSaveOperationProgress
{
public:

	//! Clears and resets the interface
	virtual void RGSC_CALL Reset() = 0;

	//! Returns true if the operation progress has been initialized.
	virtual void RGSC_CALL SetIsActive(bool bActive) = 0;
	virtual bool RGSC_CALL IsActive() = 0;

	//! Sets or gets the number of steps (i.e. files to be uploaded) as part of the operation.
	virtual void RGSC_CALL SetStepCount(u32 stepCount) = 0;
	virtual u32 RGSC_CALL GetStepCount() = 0;

	//! Sets or gets how many steps have been completed (i.e. # of uploaded files) as part of the operation
	virtual void RGSC_CALL SetCompletedCount(u32 completedCount) = 0;
	virtual u32 RGSC_CALL GetCompletedCount() = 0;
};

class ICloudSaveOperationProgressV2 : public ICloudSaveOperationProgressV1
{
public:

	//! Gets and sets the length of the total operation.
	virtual u64 RGSC_CALL GetTotalLength() = 0;
	virtual void RGSC_CALL SetTotalLength(u64 length) = 0;

	//! Gets and sets the overall progress
	virtual u64 RGSC_CALL GetTotalProgress() = 0;
	virtual void RGSC_CALL SetTotalProgress(u64 progress) = 0;

	//! Gets and sets the length of the current step.
	virtual u64 RGSC_CALL GetStepLength() = 0;
	virtual void RGSC_CALL SetStepLength(u64 length) = 0;

	//! Gets and sets the step progress
	virtual u64 RGSC_CALL GetStepProgress() = 0;
	virtual void RGSC_CALL SetStepProgress(u64 progress) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveOperationProgressV1 = { 0x69c0ebc8, 0x8fb7, 0x4d05, { 0x8e, 0xae, 0xa4, 0xed, 0xed, 0xe2, 0xce, 0x22 } };
extern "C" static const RGSC_IID IID_ICloudSaveOperationProgressV2 = { 0x4629de2b, 0xadf4, 0x4510, { 0x81, 0x85, 0x1c, 0x7d, 0x29, 0x4f, 0x35, 0x88 } };

typedef ICloudSaveOperationProgressV2 ICloudSaveOperationProgressLatestVersion;
#define IID_ICloudOperationProgressLatestVersion IID_ICloudSaveOperationProgressV2

// ===============================================================================================
// ICloudSaveManifest
// ===============================================================================================
class ICloudSaveManifest : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveManifest interface
class ICloudSaveManifestV1 : public ICloudSaveManifest
{
public:

	//! Adds an empty file to the manifest, and returns a reference to it. Returns NULL if the operation fails.
	virtual ICloudSaveFile* RGSC_CALL AddFile() = 0;

	//! Clears the manifest, freeing all memory associated with its cloud files
	virtual void RGSC_CALL Clear() = 0;

	//! Returns the number of files owned by the manifest
	virtual u32 RGSC_CALL GetNumFiles() const = 0;

	//! Returns the cloud file at the given index, or NULL if the index is out of range
	virtual ICloudSaveFile* RGSC_CALL GetFile(unsigned index) = 0;

	//! Gets or sets the number of bytes used
	virtual u64 RGSC_CALL GetBytesUsed() const = 0;
	virtual void RGSC_CALL SetBytesUsed(u64 bytesUsed) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManifestV1 = { 0xe057a27c, 0x788, 0x40a4, { 0xa1, 0x2a, 0xb9, 0x0, 0xf0, 0xa0, 0x86, 0x72 } };

//! Version 2 of the ICloudSaveManifest interface
class ICloudSaveManifestV2 : public ICloudSaveManifestV1
{
public:

	enum CloudSavesEnabledState
	{
		INVALID = -1,
		UNKNOWN = 0,
		ENABLE_CLOUD_SAVES = 1,
		DISABLE_CLOUD_SAVES = 2
	};

	//!	Returns the configuration for the title
	virtual ICloudSaveTitleConfiguration* RGSC_CALL GetConfiguration() = 0;

	//!	Returns the title name for the manifest (derived from the underlying configuration)
	virtual const char* RGSC_CALL GetTitleName() = 0;

	//!	Export functionality
	virtual bool RGSC_CALL Export(void* buf, const unsigned sizeofBuf, unsigned* size = 0) = 0;

	//!	Import functionality
	virtual bool RGSC_CALL Import(const void* buf, const unsigned sizeofBuf, unsigned* size = 0) = 0;

	//!	Returns the maximum buf size required for exporting the manifest.
	virtual unsigned RGSC_CALL GetMaxExportBufSize() = 0;

	//!	Gets or Sets the cloud save state.
	/**	
		This will return an uninitialized 'INVALID' unless 'LoadLocalManifest' is called first.
	*/
	virtual CloudSavesEnabledState RGSC_CALL GetCloudSaveEnabled() = 0;
	virtual void RGSC_CALL SetCloudSavesEnabled(CloudSavesEnabledState state) = 0;

	//!	Registers a file within the manifest for upload. Fails if the filename is invalid.
	/**	
		This is normally only used internally in the CloudManager.
	*/
	virtual bool RGSC_CALL RegisterForUpload(const char* fileName, const char* metadata) = 0;

	//!	Returns the number of files with conflicts. 
	virtual int RGSC_CALL GetNumUnresolvedConflicts() = 0;

	//!	Returns the number of dirty files
	virtual int RGSC_CALL GetNumDirtyFiles() = 0;

	//!		Loads the local manifest from disk. 
	/**	
		Potentially blocking operation (reads from disk) so should be called immediately after sign in
		to identify the CloudSavesEnabledState, and immediately before a Metadata/CloudSavesEnabledState write. 
		The manifest's contents (files, etc) will be routinely cleared/loaded during the identify conflicts, get, post and merge tasks,
		so this is the only way to get latest data from disk.
	*/
	virtual bool RGSC_CALL Load() = 0;

	//!		Saves the local manifest to disk. 
	/**	Potentially blocking operation (writes to disk), so should only be called immediately after a user
		enables/disables the CloudSaveEnabledState or registers a file for upload. The manifest's contents (files, etc) will be routinely cleared/loaded during the
		identify conflicts, get, post, and merge tasks, so 'LoadLocalManifest' should be called immediately before making the change and saving
		to ensure the latest data is used.
			i.e.
		RegisterFileForUpload -> Load(), SetMetadata(...), Save()
		Writing the CloudSavesEnabledState -> Load(), SetCloudSavesEnabled(...), Save()
	*/
	virtual bool RGSC_CALL Save() = 0;

	//!	Deletes a file from the manifest
	virtual bool RGSC_CALL RemoveFile(unsigned index) = 0;

	//!	Unregisters a file.
	/**	
		This is normally only used internally in the CloudManager.
	*/
	virtual bool RGSC_CALL UnregisterFile(const char* fileName) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManifestV2 = { 0xd579f3c1, 0x24b3, 0x4607, { 0x88, 0x20, 0x76, 0xc7, 0x28, 0xae, 0x91, 0xf1 } };

//! Version 3 of the ICloudSaveManifest interface
class ICloudSaveManifestV3 : public ICloudSaveManifestV2
{
public:

	//! Retrieves a progress object for any async operation attached to this manifest
	virtual ICloudSaveOperationProgress* RGSC_CALL GetProgressTracker() = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManifestV3 = { 0x7d938d1, 0x5381, 0x4330, { 0x93, 0xb9, 0xab, 0x34, 0xa0, 0x10, 0xa2, 0x93 } };

class ICloudSaveManifestV4 : public ICloudSaveManifestV3
{
public:

	//! Returns an http debug info object that will contain data after a failed request.
	virtual ICloudSaveHttpDebugInfo* RGSC_CALL GetHttpDebugInfo() = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManifestV4 = { 0xc6c88f28, 0x7930, 0x44c9, { 0x88, 0x7b, 0x56, 0xfa, 0x7d, 0xcc, 0x6e, 0x44 } };

typedef ICloudSaveManifestV4 ICloudSaveManifestLatestVersion;
#define IID_ICloudSaveManifestLatestVersion IID_ICloudSaveManifestV4

// ===============================================================================================
// ICloudSaveBackupInfo
// ===============================================================================================
class ICloudSaveBackupInfo : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Version 1 of the ICloudSaveBackupInfo interface
class ICloudSaveBackupInfoV1 : public ICloudSaveBackupInfo
{
public:

	//! Clears the save file, resetting it to its uninitialized state.
	virtual void RGSC_CALL Clear() = 0;

	//! Get and set the md5 hash
	virtual void RGSC_CALL SetMd5Hash(const char* md5Hash) = 0;
	virtual const char* RGSC_CALL GetMd5Hash() const = 0;

	//!	Set or get the metadata that is associated with the save file.
	virtual const char* RGSC_CALL GetMetaData() = 0;
	virtual void RGSC_CALL SetMetaData(const char* metaData) = 0;

	//! Get and set the filename
	virtual void RGSC_CALL SetFileName(const char* fileName) = 0;
	virtual const char* RGSC_CALL GetFileName() const = 0;

	//! Get and set the last modified date set by the client
	virtual void RGSC_CALL SetClientLastModifiedDate(u64 clientLastModifiedDate) = 0;
	virtual u64 RGSC_CALL GetClientLastModifiedDate() const = 0;

	//! Get and set the hardware id
	virtual void RGSC_CALL SetHardwareId(const char* hardwareId) = 0;
	virtual const char* RGSC_CALL GetHardwareId() const = 0;

	//!	Export functionality
	virtual bool RGSC_CALL Export(void* buf, const unsigned sizeofBuf, unsigned* size) = 0;

	//!	Import functionality
	virtual bool RGSC_CALL Import(const void* buf, const unsigned sizeofBuf, unsigned* size) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveBackupInfoV1 = { 0x69c0ebc8, 0x8fb7, 0x4d05, { 0x8e, 0xae, 0xa4, 0xed, 0xed, 0xe2, 0xce, 0x22 } };
typedef ICloudSaveBackupInfoV1 ICloudSaveBackupInfoLatestVersion;
#define IID_ICloudSaveBackupInfoV1 IID_ICloudSaveBackupInfoV1

// ===============================================================================================
// ICloudSaveManager
// ===============================================================================================
// ===============================================================================================
// Cloud Syncing Managed by Application (CloudSaveManagerV1)
//	1.	Set the maximum size of a cloud file using SetMaximumFileSize
//	2.	Create cloud saves manifest using CreateManifest, and pass it into GetCloudSaveManifest
//	3.	For each cloud save file that needs to be downloaded, call GetFile
//	4.  For each cloud save file that needs to be uploaded, call PostFile
//
// Cloud Save Syncing Managed by SDK (CloudSaveManagerV2)
//	1.	Set the maximum size of a cloud file using SetMaximumFileSize
//	2.	Create a cloud save configuration and pass it to the SDK using RegisterTitle. This will return
//		a manifest for each title. This manifest shoudl be used in all following tasks.
//	3.	Request a list of conflicts using IdentifyConflicts. The configuration file will be compared
//		against the server side manifest (downloaded as part of this task). The resolve state
//		of every file in the configuration will be cleared.
//	4.	a) For each conflict (file with a conflict state), determine the desired resolve type. Write back
//			the resolve type to the configuration's save files using SetResolveType.
//		b) At this point, the configuration should either have zero conflicts, or a resolve type for each conflict.
//	5.	Upload files from the configuration that are identified as 'ClientHasNewer' using PostUpdatedFiles. 
//		This means that the client has a file newer than whats on the server that needs to be uploaded. It should
//		be called before the game is run (usually will do nothing) and again after the game (usually will upload files).
//	6.  Download new files using 'GetUpdatedFiles' 
//	7.  If successful, copy all updated files to their desired location using 'CopyUpdatedFiles'
//	8.	Launch the game.
//	9.	After the game terminates, run IdentifyConflicts and PostUpdatedFiles again. Only files that
//		are marked as 'ClientHasNewer' or 'ClientHasNewerWithConflict' (with AcceptLocal resolve type) will be automatically updated. 
//		If somehow a conflict has occurred during gameplay, it will be handled on the next boot.
// ================================================================================================

class ICloudSaveManager : public IRgscUnknown
{
public:

	static const unsigned HARDWARE_ID_MAX_LEN = 64;
	static const unsigned HARDWARE_ID_MAX_BUF_SIZE = HARDWARE_ID_MAX_LEN + 1;
	static const unsigned MAX_CLOUD_SAVE_SLOTS = 64;

	// matches rlCloudSave eCloudSaveResolveType
	enum ResolveType
	{
		None,
		// Indicates that there's a conflict. The user's local save file is newer than the server, but the user has chosen 
		// to retrieve the file that's remote anyway. Used in the GetFile Operation
		AcceptRemote,
		// The user's local save file is older / different from what's on the server. But the user chooses to overwrite the server 
		// with his local save anyway. Used in the PostFile Operation.
		AcceptLocal,
	};

public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

//! Cloud Saves Interface
//! Defines the public interface that clients use to read and write to the single player cloud
class ICloudSaveManagerV1 : public ICloudSaveManager
{
public:

	//! Sets the maximum file size of an upload
	virtual void RGSC_CALL SetMaximumFileSize(u64 maximumFileSize) = 0;

	//! Creates an empty manifest object, which can be passed into 'GetCloudSaveManifest'.
	/**	
		Specify the max number of save slots for the manifest. This function should only be
		used in conjunction with 'GetCloudSaveManifest' when the application manages its own save data.
	*/
	virtual ICloudSaveManifest* RGSC_CALL CreateManifest(u32 numSlots) = 0;

	//! Downloads the cloud save manifest from SCS, and fills it out into the 'manifest' object.
	/**	
		This should be used when an application wants to manage its cloud syncing directly, through the 
		use of the GetFile/PostFile functions. 
	*/
	virtual bool RGSC_CALL GetCloudSaveManifest(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//! With a specified save file, resolve type and hardware id, downloads the file data.
	virtual bool RGSC_CALL GetFile(ICloudSaveFile* saveFile, ResolveType resolveType, const char* hardwareId, IAsyncStatus* status) = 0;

	//! With a specified save file (containing new data) and resolve type, write the file to the cloud.
	virtual bool RGSC_CALL PostFile(ICloudSaveFile* saveFile, ResolveType resolveType, IAsyncStatus* status) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManagerV1 = { 0xf5c49bdb, 0x83d, 0x4a1f, { 0xac, 0x62, 0x86, 0xb6, 0x94, 0xde, 0xeb, 0x4f } };

//! Cloud Saves Interface
//! Defines the public interface that clients use to read and write to the single player cloud
class ICloudSaveManagerV2 : public ICloudSaveManagerV1
{
public:

	enum IdentifyConflictsErrors
	{
		ICE_ERROR_LOAD_LOCAL_MANIFEST_FAILED = 1000, // The local manifest could not be retrieved, and neither could a new manifest be generated.
		ICE_ERROR_LOAD_SERVER_MANIFEST_FAILED, // The cloud save manifest from the server could not be retrieved.
		ICE_ERROR_MANIFEST_RESOLVE_FAILED,	// The local and server manifests were both retrieved successfully, but fatally errored trying to merge and identify conflicts.
		ICE_ERROR_WRITE_LOCAL_MANIFEST_FAILED, // The local and server manifests retrieved successfully, merged and identified conflicts, but failed to write the manifest back to disk.
		ICE_ERROR_SETUP_SERVER_MANIFEST_TASK_FAILED, // Could not even setup the task that downloads the manifest.
	};

	enum PostUpdatedFilesErrors
	{
		PUFE_ERROR_SETUP_FILE = 2000, // Preparing to set up a file for post failed. This would indicate a bad IRgscCloudSaveFile, i.e. missing data. Check for asserts.
		PUFE_ERROR_POSTING_FILE,	// Posting the file to the cloud failed.
		PUFE_ERROR_WRITE_LOCAL_MANIFEST_FAILED, // The local manifest could not be written back to disk after posting files.
	};

	enum GetUpdatedFilesErrors
	{
		GUFE_ERROR_SETUP_FILE = 3000, // Preparing to set up a file for retrieval failed. This would indicate a bad IRgscCloudSaveFile, i.e. missing data. Check for asserts.
		GUFE_ERROR_GETTING_FILE, // Retrieving the file from the cloud failed.
		GUFE_ERROR_GETTING_FILE_INVALID_SIZE, // The size of the file did not match the manifest.
		GUFE_ERROR_GETTING_FILE_LOAD,	// Error opening a handle to the file on disk
		GUFE_ERROR_GETTING_FILE_MD5_HASH, // The md5 hash of the file did not match the manifest.
		GUFE_ERROR_GETTING_FILE_DISK_WRITE, // Writing the file to disk failed
		GUFE_ERROR_WRITE_LOCAL_MANIFEST_FAILED, // The local manifest could not be written back to disk after retrieving files.
	};

	enum CopyUpdatedFilesErrors
	{
		CUFE_ERROR_VALIDATING_MD5_HASHES = 4000, // The md5 hash of the file could not be validated.
		CUFE_ERROR_FILE_MISSING, // Files were missing from the folder
		CUFE_ERROR_FILE_COPY_FAILED, // The files failed to copy overtop of the original savedata
		CUFE_ERROR_WRITE_LOCAL_MANIFEST_FAILED, // The local manifest could not be written back to disk after copying files.
	};

	// PURPOSE
	//!	Allocates and initializes a cloud save manifest with the title configuration. 
	/**	This should be called once for each title the application supports.
		If the configuration's 'GetSaveDirectory' function correctly handles sign in state, this should only be called on initialization. If it does
		not support sign in/sign out, it the titles should be registered/unregistered as the user signs out.
	*/
	virtual ICloudSaveManifest* RGSC_CALL RegisterTitle(ICloudSaveTitleConfiguration* configuration) = 0;

	//! Destroys a cloud save manifest, unregistering it from the system. 
	/**	
		Should be called on termination, or on sign out if the manifest/configuration
		does not handle sign out internally. The manifest passed into this function can no longer be referenced.
	*/
	virtual void RGSC_CALL UnregisterTitle(ICloudSaveManifest* manifest) = 0;

	// PURPOSE
	//!	Using the cloud save configuration passed to Init, identify a list of conflicts. 
	/**	
		This task will load the local manifest from disk (if it exists), download the user's manifest from the server and compare against the file list in the configuration.
	*/
	virtual bool RGSC_CALL IdentifyConflicts(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//!	From the manifest, upload any files with the conflict state 'ClientHasNewer' or ('ClientHasNewerWithConflict' and 'AcceptLocal' resolution)
	virtual bool RGSC_CALL PostUpdatedFiles(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//!	From the manifest, download any files with a conflict state 'Missing', 'ServerHasNewer' or ('ServerHasNewerWithConflict' and 'AcceptRemote' resolution)
	virtual bool RGSC_CALL GetUpdatedFiles(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//!	From the manifest, copy any downloaded files into place.
	virtual bool RGSC_CALL CopyUpdatedFiles(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//!	Marks the save file as dirty, and updates the local manifest. This file cannot be overwritten by GetUpdatedFiles without first uploading the file to the cloud, or resolving a conflict.
	virtual bool RGSC_CALL RegisterFileForUpload(ICloudSaveManifest* manifest, const char* fileName, const char* metaData) = 0;

	//!	Marks the save file as marked for deletion, and updates the local manifest. After 'DeleteUpdatedFiles' has been run, this file will no longer be stored on the cloud.
	virtual bool RGSC_CALL UnregisterFile(ICloudSaveManifest* manifest, const char* fileName) = 0;

	enum DeleteUpdatedFilesErrors
	{
		ERROR_SETUP_FILE = 5000, // Preparing to set up a file for delete failed. This would indicate a bad IRgscCloudSaveFile, i.e. missing data. Check for asserts.
		ERROR_DELETING_FILE,	// Deleting a file from the cloud failed.
		ERROR_WRITE_LOCAL_MANIFEST_FAILED, // The local manifest could not be written back to disk after deleting files.
	};

	//! From the manifest, inform the cloud to delete any files with a conflict state 'FileDeleted' or ('FileDeletedWithConflict' and 'AcceptLocal').
	/**
	*	Any file with 'ClientHasNewerWithConflict' and 'AcceptRemote' that does not exist on the server will be removed from disk and from the manifest
	*/
	virtual bool RGSC_CALL DeleteUpdatedfiles(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManagerV2 = { 0x962f0f4b, 0xf450, 0x432f, { 0x85, 0x4a, 0x17, 0xe1, 0xf, 0x6c, 0xeb, 0xd9 } };

//! Cloud Saves Interface
//! Defines the public interface that clients use to read and write to the single player cloud
class ICloudSaveManagerV3 : public ICloudSaveManagerV2
{
public:
	
	static const int RGSC_MAX_COHORTS_CLOUD_FILE_LENGTH = 63;
	static const int RGSC_MAX_COHORTS_CLOUD_FILE_BUF_SIZE = RGSC_MAX_COHORTS_CLOUD_FILE_LENGTH + 1;
	static const int RGSC_CLOUDSAVE_DEFAULT_NUM_BACKUP_FILES = 2;

	//! Queries the Social Club services to determine if the user has access to the beta for cloud saves
	/**
		\param cohortsFilePath - The local cloud file used to signify beta access.
		\param bOutResult - If the currently logged in user has beta access, a TRUE value will be written to this bool.
	*/
	virtual bool RGSC_CALL HasBetaAccessAsync(const char* cohortsFilePath, bool* bOutResult, IAsyncStatus* status) = 0;

	//! Writes a telemetry event for conflict resolution
	virtual bool RGSC_CALL WriteConflictTelemetry(ICloudSaveManifest* manifest) = 0;

	enum BackupConflictedFilesErrors
	{
		BCFE_ERROR_SETUP_FILE = 4000, // Preparing to set up a file for retrieval failed. This would indicate a bad IRgscCloudSaveFile, i.e. missing data. Check for asserts.
		BCFE_ERROR_GETTING_FILE, // Retrieving the file from the cloud failed.
		BCFE_ERROR_GETTING_FILE_INVALID_SIZE, // The size of the file did not match the manifest.
		BCFE_ERROR_GETTING_FILE_LOAD,	// Error opening a handle to the file on disk
		BCFE_ERROR_GETTING_FILE_MD5_HASH, // The md5 hash of the file did not match the manifest.
		BCFE_ERROR_GETTING_FILE_DISK_WRITE, // Writing the file to disk failed
		BCFE_ERROR_FILE_COPY_FAILED, // The files failed to copy overtop of the older backups savedata
		BCFE_ERROR_BACKUP_INFO_FAILED, // Creating backup information (metadata) for the backup file failed.
	};

	//! Creates a backup of conflicted files. Conflicts must be resolved with AcceptLocal or AcceptRemove. Files that are 'AcceptLocal' will
	//	have the server version downloaded, and stored on disk as the most recent backup. Files that are 'AcceptRemote' will have the local version
	//	saved as a backup.
	virtual bool RGSC_CALL BackupConflictedFiles(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//! Searches the manifest for backups of local files. Should be called after IdentifyConflicts has completed,
	//	so the manifest is in a initialized and identified state. 
	virtual bool RGSC_CALL SearchForBackups(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;

	//!	Gets or sets the number of backup slots to save for each file. Defaults to RGSC_CLOUDSAVE_DEFAULT_NUM_BACKUP_FILES (3).
	virtual int RGSC_CALL GetNumBackupSlots() = 0;
	virtual void RGSC_CALL SetNumBackupSlots(int numSlots) = 0;

	//! Creates or Frees a backup info 
	virtual ICloudSaveBackupInfo* RGSC_CALL AllocateBackupInfo() = 0;
	virtual void RGSC_CALL FreeBackupInfo(ICloudSaveBackupInfo* info) = 0;

	//! From the given manifest, file index and backup slot, fill out the ICloudSaveBackup information.
	virtual RGSC_HRESULT RGSC_CALL GetBackupInfo(ICloudSaveManifest* manifest, const int fileIndex, const int backupIndex, ICloudSaveBackupInfo* out_info) = 0;

	//! Restores a backup from the given file index in the manifest
	virtual bool RGSC_CALL RestoreBackup(ICloudSaveManifest* manifest, const int fileIndex, const int backupIndex, IAsyncStatus* status) = 0;

	enum GetConflictMetadataErrors
	{
		GCME_ERROR_SETUP_FILE = 3000, // Preparing to set up a file for retrieval failed. This would indicate a bad IRgscCloudSaveFile, i.e. missing data. Check for asserts.
		GCME_ERROR_GETTING_METADATA,	// Metadata retrieval failed from the server. (And not for a missing reason -- missing metadata returns empty JSON {})
	};

	//! Downloads the metadata for all conflicted files
	virtual bool RGSC_CALL GetConflictMetadata(ICloudSaveManifest* manifest, IAsyncStatus* status) = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManagerV3 = { 0xc94d25a8, 0x58dd, 0x4935, { 0xb8, 0x7a, 0x24, 0x3d, 0xc7, 0xbc, 0xe0, 0xc6 } };

class ICloudSaveManagerV4 : public ICloudSaveManagerV3
{
public:

	//! Creates or shuts down the cloud save worker thread. Normally, the cloud save tasks are updated 
	//	in the IRgsc interface's main update function. By creating a worker thread for cloud saves, they
	//	can run independently of the main thread. All cloud save APIs in ICloudSaveManager interface
	//	are thread safe.
	virtual void RGSC_CALL CreateWorkerThread() = 0;
	virtual void RGSC_CALL ShutdownWorkerThread() = 0;
};

extern "C" static const RGSC_IID IID_ICloudSaveManagerV4 = { 0xe434fc07, 0x677b, 0x4eb7, { 0x9e, 0x40, 0xa7, 0x13, 0x5c, 0x43, 0x8f, 0x5b } };

typedef ICloudSaveManagerV4 ICloudSaveManagerLatestVersion;
#define IID_ICloudSaveManagerLatestVersion IID_ICloudSaveManagerV4

} // namespace rgsc

#endif // CLOUDSAVE_INTERFACE_H
