#include "imgproc/filter.h"

#include <opencv2/opencv.hpp>
#include "expect.hpp"
#include "core/Mat.h"

void imgproc::filter::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("MORPH_RECT", Napi::Number::New(env, cv::MORPH_RECT));
	exports.Set("MORPH_CROSS", Napi::Number::New(env, cv::MORPH_CROSS));
	exports.Set("MORPH_ELLIPSE", Napi::Number::New(env, cv::MORPH_ELLIPSE));
	exports.Set("dilate", Napi::Function::New(env, imgproc::filter::dilate));
	exports.Set("erode", Napi::Function::New(env, imgproc::filter::erode));
}

Napi::Object imgproc::filter::dilate(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto mat = expectArg<core::Mat*>(env, info, 0);
	auto shape = expectArg<Napi::Number>(env, info, 1);
	auto width = expectArg<Napi::Number>(env, info, 2);
	auto height = expectArg<Napi::Number>(env, info, 3);

	auto kernel = cv::getStructuringElement(shape, cv::Size(width, height));
	auto output = cv::Mat();
	cv::dilate(mat->mat, output, kernel);

	return core::Mat::New(output);
}

Napi::Object imgproc::filter::erode(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto mat = expectArg<core::Mat*>(env, info, 0);
	auto shape = expectArg<Napi::Number>(env, info, 1);
	auto width = expectArg<Napi::Number>(env, info, 2);
	auto height = expectArg<Napi::Number>(env, info, 3);

	auto kernel = cv::getStructuringElement(shape, cv::Size(width, height));
	auto output = cv::Mat();
	cv::erode(mat->mat, output, kernel);

	return core::Mat::New(output);
}
