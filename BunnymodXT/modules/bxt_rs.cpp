#include "../stdafx.hpp"

#include "../sptlib-wrapper.hpp"
#include <SPTLib/MemUtils.hpp>
#include "../simulation_ipc.hpp"
#include "bxt_rs.hpp"

void bxt_rs::Hook(const std::wstring& moduleName, void* moduleHandle, void* moduleBase, size_t moduleLength, bool needToIntercept)
{
	Clear(); // Just in case.

	m_Handle = moduleHandle;
	m_Base = moduleBase;
	m_Length = moduleLength;
	m_Name = moduleName;
	m_Intercepted = needToIntercept;

	ORIG_bxt_rs_on_tas_playback_frame = reinterpret_cast<_bxt_rs_on_tas_playback_frame>(MemUtils::GetSymbolAddress(m_Handle, "bxt_rs_on_tas_playback_frame"));
	if (ORIG_bxt_rs_on_tas_playback_frame) {
		EngineDevMsg("[bxt_rs] Found bxt_rs_on_tas_playback_frame at %p.\n", ORIG_bxt_rs_on_tas_playback_frame);
	} else {
		EngineDevWarning("[bxt_rs] Could not find bxt_rs_on_tas_playback_frame.\n");
	}
}

void bxt_rs::Unhook()
{
	Clear();
}

void bxt_rs::Clear()
{
	IHookableNameFilter::Clear();
	ORIG_bxt_rs_on_tas_playback_frame = nullptr;
}

bool bxt_rs::Found() const
{
	return ORIG_bxt_rs_on_tas_playback_frame != nullptr;
}

void bxt_rs::on_tas_playback_frame() const
{
	if (ORIG_bxt_rs_on_tas_playback_frame != nullptr)
		ORIG_bxt_rs_on_tas_playback_frame();
}
