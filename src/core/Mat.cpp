#include "Mat.h"

Napi::FunctionReference Mat::constructor;

void Mat::Init(Napi::Env env, Napi::Object exports) {
	Napi::Function func = DefineClass(env, "Mat", {
		InstanceMethod<&Mat::release>("release"),
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

Napi::Value Mat::width(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.cols);
}

Napi::Value Mat::height(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.rows);
}
