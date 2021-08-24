#pragma once

#include <napi.h>

namespace imgproc {
	namespace filter {
		void Init(Napi::Env env, Napi::Object exports);
		Napi::Object dilate(const Napi::CallbackInfo& info);
		Napi::Object erode(const Napi::CallbackInfo& info);
	}
}
