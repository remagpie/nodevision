#pragma once

#include <napi.h>

namespace imgproc {
	namespace misc {
		void Init(Napi::Env env, Napi::Object exports);
		Napi::Object threshold(const Napi::CallbackInfo& info);
	}
}
