#pragma once

#include <sstream>

#include <napi.h>

template <typename T>
T expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) = delete;

template<>
Napi::Object expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) {
	if (info.Length() <= index || !info[index].IsObject()) {
		std::ostringstream message;
		message << index << "th argument is not an Object";
		Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();
	}

	return info[index].As<Napi::Object>();
}

template <typename T>
T expectField(Napi::Env env, Napi::Object& obj, const char* name, const char* key) = delete;

template<>
Napi::Number expectField(Napi::Env env, Napi::Object& obj, const char* name, const char* key) {
	auto value = obj.Get(key);

	if (!value.IsNumber()) {
		std::ostringstream message;
		message << name << "." << key << " is not a Number";
		Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();
	}

	return value.As<Napi::Number>();
}
