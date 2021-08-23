#include "imgcodecs.h"

#include <opencv2/opencv.hpp>
#include "core/Mat.h"

void imgcodecs::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("imread", Napi::Function::New(env, imgcodecs::imread));
	exports.Set("imwrite", Napi::Function::New(env, imgcodecs::imwrite));
}

Napi::Object imgcodecs::imread(const Napi::CallbackInfo& info) {
	auto path = info[0].As<Napi::String>();
	auto mat = cv::imread(path);

	auto result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(mat);

	return result;
}

void imgcodecs::imwrite(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	if (info.Length() != 2 || !info[0].IsString() || !info[1].IsObject()) {
		Napi::TypeError::New(env, "Mat expected").ThrowAsJavaScriptException();
	}

	auto path = info[0].As<Napi::String>();
	auto mat = Mat::Unwrap(info[1].As<Napi::Object>());
	cv::imwrite(path, mat->mat);
}
