#include "imgproc/misc.h"

#include <opencv2/opencv.hpp>
#include "expect.hpp"
#include "core/Mat.h"

void imgproc::misc::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("threshold", Napi::Function::New(env, imgproc::misc::threshold));
}

Napi::Object imgproc::misc::threshold(const Napi::CallbackInfo& info) {
	auto env = info.Env();

	auto mat = Mat::Unwrap(expectArg<Napi::Object>(env, info, 0));
	auto thresh = expectArg<Napi::Number>(env, info, 1);
	auto max = expectArg<Napi::Number>(env, info, 2);

	auto output = cv::Mat();
	cv::threshold(mat->mat, output, thresh, max, cv::THRESH_BINARY);

	auto result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(output);
	return result;
}
