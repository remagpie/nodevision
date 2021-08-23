#pragma once

#include <napi.h>

namespace imgcodecs {
	void Init(Napi::Env env, Napi::Object exports);
	Napi::Object imread(const Napi::CallbackInfo& info);
	void imwrite(const Napi::CallbackInfo& info);
}
