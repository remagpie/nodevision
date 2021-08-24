#include "imgcodecs.h"

#include <opencv2/opencv.hpp>
#include "core/Mat.h"
#include "expect.hpp"

void imgcodecs::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("imread", Napi::Function::New(env, imgcodecs::imread));
	exports.Set("imwrite", Napi::Function::New(env, imgcodecs::imwrite));
}

Napi::Object imgcodecs::imread(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto path = expectArg<Napi::String>(env, info, 0);
	auto mat = cv::imread(path);

	return core::Mat::New(mat);
}

void imgcodecs::imwrite(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto path = expectArg<Napi::String>(env, info, 0);
	auto mat = expectArg<core::Mat*>(env, info, 1);

	cv::imwrite(path, mat->mat);
}
