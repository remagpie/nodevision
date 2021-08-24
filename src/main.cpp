#include <napi.h>
#include "core/Mat.h"
#include "imgcodecs.h"
#include "imgproc/filter.h"
#include "imgproc/misc.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	core::Mat::Init(env, exports);
	imgcodecs::Init(env, exports);
	imgproc::filter::Init(env, exports);
	imgproc::misc::Init(env, exports);
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
