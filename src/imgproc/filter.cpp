#include "imgproc/filter.h"

#include <opencv2/opencv.hpp>
#include "expect.hpp"
#include "core/Mat.h"

void imgproc::filter::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("dilate", Napi::Function::New(env, imgproc::filter::dilate));
	exports.Set("erode", Napi::Function::New(env, imgproc::filter::erode));
}

Napi::Object imgproc::filter::dilate(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto mat = Mat::Unwrap(expectArg<Napi::Object>(env, info, 0));
	auto props = expectArg<Napi::Object>(env, info, 1);

	auto shape = expectField<Napi::Number>(env, props, "props", "shape");
	auto width = expectField<Napi::Number>(env, props, "props", "width");
	auto height = expectField<Napi::Number>(env, props, "props", "height");

	auto kernel = cv::getStructuringElement(shape, cv::Size(width, height));
	auto output = cv::Mat();
	cv::dilate(mat->mat, output, kernel);

	auto result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(output);
	return result;
}

Napi::Object imgproc::filter::erode(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto mat = Mat::Unwrap(expectArg<Napi::Object>(env, info, 0));
	auto props = expectArg<Napi::Object>(env, info, 1);

	auto shape = expectField<Napi::Number>(env, props, "props", "shape");
	auto width = expectField<Napi::Number>(env, props, "props", "width");
	auto height = expectField<Napi::Number>(env, props, "props", "height");

	auto kernel = cv::getStructuringElement(shape, cv::Size(width, height));
	auto output = cv::Mat();
	cv::erode(mat->mat, output, kernel);

	auto result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(output);
	return result;
}
