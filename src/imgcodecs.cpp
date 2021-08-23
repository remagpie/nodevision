#include "imgcodecs.h"

#include <opencv2/opencv.hpp>
#include "core/Mat.h"

void imgcodecs::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("imgcodecs_imread", Napi::Function::New(env, imgcodecs::imread));
	exports.Set("imgcodecs_imwrite", Napi::Function::New(env, imgcodecs::imwrite));
}

Napi::Object imgcodecs::imread(const Napi::CallbackInfo& info) {
	Napi::String path = info[0].As<Napi::String>();
	cv::Mat mat = cv::imread(path);

	Napi::Object result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(mat);

	return result;
}

void imgcodecs::imwrite(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if (info.Length() != 2 || !info[0].IsString() || !info[1].IsObject()) {
		Napi::TypeError::New(env, "Mat expected").ThrowAsJavaScriptException();
	}

	Napi::String path = info[0].As<Napi::String>();
	Mat* mat = Mat::Unwrap(info[1].As<Napi::Object>());
	cv::imwrite(path, mat->mat);
}
