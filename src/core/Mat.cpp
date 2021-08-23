#include "Mat.h"

#include <vector>

Napi::FunctionReference Mat::constructor;

void Mat::Init(Napi::Env env, Napi::Object exports) {
	auto func = DefineClass(env, "Mat", {
		InstanceMethod<&Mat::release>("release"),
		InstanceMethod<&Mat::asBuffer>("asBuffer"),
		InstanceMethod<&Mat::asJpg>("asJpg"),
		InstanceMethod<&Mat::asPng>("asPng"),
		InstanceMethod<&Mat::width>("width"),
		InstanceMethod<&Mat::height>("height"),
	});

	Mat::constructor = Napi::Persistent(func);
	Mat::constructor.SuppressDestruct();

	exports.Set("Mat", func);
}

Mat::Mat(const Napi::CallbackInfo& info): Napi::ObjectWrap<Mat>(info) {
	this->alive = true;
}

Mat::~Mat() {
	if (this->alive) {
		this->mat.release();
	}
}

void Mat::setMat(cv::Mat mat) {
	if (this->alive) {
		this->mat.release();
	}
	this->mat = mat;
	this->alive = true;
}

void Mat::release(const Napi::CallbackInfo& info) {
	if (this->alive) {
		this->mat.release();
	}
	this->alive = false;
}

Napi::Value Mat::asBuffer(const Napi::CallbackInfo& info) {
	auto size = this->mat.rows * this->mat.cols * this->mat.elemSize();
	return Napi::Buffer<uchar>::Copy(info.Env(), this->mat.data, size);
}

Napi::Value Mat::asPng(const Napi::CallbackInfo& info) {
	auto result = std::vector<uchar>();
	cv::imencode(".png", this->mat, result);

	return Napi::Buffer<uchar>::Copy(info.Env(), result.data(), result.size());
}

Napi::Value Mat::asJpg(const Napi::CallbackInfo& info) {
	auto result = std::vector<uchar>();
	cv::imencode(".jpg", this->mat, result);

	return Napi::Buffer<uchar>::Copy(info.Env(), result.data(), result.size());
}

Napi::Value Mat::width(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.cols);
}

Napi::Value Mat::height(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.rows);
}
