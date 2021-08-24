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

	auto result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(mat);

	return result;
}

void imgcodecs::imwrite(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto path = expectArg<Napi::String>(env, info, 0);
	auto mat = expectArg<Mat*>(env, info, 1);

	cv::imwrite(path, mat->mat);
}
