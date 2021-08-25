#include "imgcodecs.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include "core/Mat.h"
#include "expect.hpp"

void imgcodecs::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("imdecode", Napi::Function::New(env, imgcodecs::imdecode));
	exports.Set("imencode", Napi::Function::New(env, imgcodecs::imencode));
	exports.Set("imread", Napi::Function::New(env, imgcodecs::imread));
	exports.Set("imwrite", Napi::Function::New(env, imgcodecs::imwrite));
}

Napi::Object imgcodecs::imdecode(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto buffer = expectArg<Napi::Buffer<uchar>>(env, info, 0);

	auto vec = std::vector<uchar>(buffer.Data(), buffer.Data() + buffer.Length());
	auto mat = cv::imdecode(vec, cv::IMREAD_ANYCOLOR);

	return core::Mat::New(mat);
}

Napi::Object imgcodecs::imencode(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto ext = expectArg<Napi::String>(env, info, 0);
	auto mat = expectArg<core::Mat*>(env, info, 1);

	auto vec = std::vector<uchar>();
	cv::imencode(ext, mat->mat, vec);

	return Napi::Buffer<uchar>::Copy(info.Env(), vec.data(), vec.size());
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
