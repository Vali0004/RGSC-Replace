#ifndef TASKS_INTERFACE_H
#define TASKS_INTERFACE_H

#include "rgsc_common.h"

namespace rgsc
{

class IAsyncStatus : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_IAsyncStatusV1 = {0x456b72d5, 0x9734, 0x4034, {0x8e, 0x31, 0x88, 0xad, 0x45, 0xe2, 0x51, 0x85}};

//! Version 1 of the IAsyncStatus interface
class IAsyncStatusV1 : public IAsyncStatus
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
	virtual unsigned int RGSC_CALL AddRef(void) = 0;
	virtual unsigned int RGSC_CALL Release(void) = 0;

	typedef void (*OperationFinishedCallback)(IAsyncStatus* status, void* callbackData);
	virtual void RGSC_CALL SetOperationFinishedCallback(OperationFinishedCallback callback, void* callbackData) = 0;

	//! Returns a task-specific result code.
	/**
	  \return
		Returns a task-specific result code.
	*/
	virtual int RGSC_CALL GetResultCode() = 0;

	//! Cancels the task that this status object is monitoring.
	virtual void RGSC_CALL Cancel() = 0;

	//! Returns true if the task is in progress.
	/**
	  \return
		Returns true if the task is in progress.
	*/
	virtual bool RGSC_CALL Pending() = 0;

	//! Returns true if the task completed successfully.
	/**
	  \return
		Returns true if the task completed successfully.
	*/
	virtual bool RGSC_CALL Succeeded() = 0;

	//! Returns true if the task failed.
	/**
	  \return
		Returns true if the task failed.
	*/
	virtual bool RGSC_CALL Failed() = 0;

	//! Returns true if the task was canceled.
	/**
	  \return
		Returns true if the task was canceled.
	*/
	virtual bool RGSC_CALL Canceled() = 0;
};

typedef IAsyncStatusV1 IAsyncStatusLatestVersion;
#define IID_IAsyncStatusLatestVersion IID_IAsyncStatusV1

//! Task Manager Interface
//! Defines the public interface that game clients use to access the task manager.
class ITaskManager : public IRgscUnknown
{
public:
	virtual RGSC_HRESULT RGSC_CALL QueryInterface(RGSC_REFIID riid, void** ppvObject) = 0;
};

extern "C" static const RGSC_IID IID_ITaskManagerV1 = {0x92ef10eb, 0x8173, 0x47e0, {0xb8, 0x13, 0xe6, 0xbb, 0x6c, 0xf, 0x9a, 0x2c}};

//! Version 1 of the task manager interface.
class ITaskManagerV1 : public ITaskManager
{
public:
	//! Creates an object that can be used for polling the status of an asynchronous task.
	/**
	  \param status - the address of a pointer to an IAsyncStatus interface which will be populated on return.
	  \return
		RGSC_OK - success.\n
		RGSC_FAIL - if the status object could not be created.
	*/
	virtual RGSC_HRESULT RGSC_CALL CreateAsyncStatus(IAsyncStatus** status) = 0;
};

typedef ITaskManagerV1 ITaskManagerLatestVersion;
#define IID_ITaskManagerLatestVersion IID_ITaskManagerV1

} // namespace

#endif // TASKS_INTERFACE_H
