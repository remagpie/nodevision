#include "imgcodecs.h"

#include <opencv2/opencv.hpp>
#include "core/Mat.h"

void imgcodecs::Init(Napi::Env env, Napi::Object exports) {
	exports.Set("imgcodecs_imread", Napi::Function::New(env, imgcodecs::imread));
}

Napi::Object imgcodecs::imread(const Napi::CallbackInfo& info) {
	Napi::String path = info[0].As<Napi::String>();
	cv::Mat mat = cv::imread(path);

	Napi::Object result = Mat::constructor.New({});
	Mat::Unwrap(result)->setMat(mat);

	return result;
}
