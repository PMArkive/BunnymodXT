#pragma once

#include "../sptlib-wrapper.hpp"
#include <SPTLib/IHookableNameFilter.hpp>

class bxt_rs : public IHookableNameFilter
{
public:
	static bxt_rs& GetInstance()
	{
		static bxt_rs instance;
		return instance;
	}

	virtual void Hook(const std::wstring& moduleName, void* moduleHandle, void* moduleBase, size_t moduleLength, bool needToIntercept);
	virtual void Unhook();
	virtual void Clear();

	bool Found() const;
	void on_tas_playback_frame() const;

private:
	bxt_rs() : IHookableNameFilter({ L"bxt_rs.dll", L"libbxt_rs.so" }) {};
	bxt_rs(const bxt_rs&);
	void operator=(const bxt_rs&);

protected:
	typedef void(__cdecl *_bxt_rs_on_tas_playback_frame) ();
	_bxt_rs_on_tas_playback_frame ORIG_bxt_rs_on_tas_playback_frame;
};
