#include "StdAfx.h"
#include "ProcessComponent.h"
#include "InstallConfiguration.h"

ProcessComponent::ProcessComponent(component_type t)
	: Component(t)
{
	ZeroMemory(& m_process_info, sizeof(PROCESS_INFORMATION));
}

DWORD ProcessComponent::GetProcessExitCode() const
{
	DWORD l_ExitCode = 0xFFFFFF;
	if (m_process_info.hProcess != NULL)
	{
		CHECK_WIN32_BOOL(::GetExitCodeProcess(m_process_info.hProcess, & l_ExitCode),
			L"GetExitCodeProcess");
	}
    return l_ExitCode;
}

int ProcessComponent::GetExitCode() const 
{ 
	return GetProcessExitCode(); 
}

bool ProcessComponent::IsExecuting() const
{
	DWORD l_ExitCode;
	if (m_process_info.hProcess != NULL && GetExitCodeProcess(m_process_info.hProcess, &l_ExitCode))
	{
		return (l_ExitCode == STILL_ACTIVE);
	}
	else
    {
		return false;
    }
}

void ProcessComponent::Wait(DWORD /* tt */)
{
	CHECK_WIN32_BOOL(WAIT_OBJECT_0 == WaitForSingleObject(m_process_info.hProcess, INFINITE),
		L"WaitForSingleObject");
}
