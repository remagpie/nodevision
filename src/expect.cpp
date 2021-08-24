#include <sstream>

#include "expect.hpp"

template<>
Napi::String expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) {
	if (info.Length() <= index || !info[index].IsString()) {
		std::ostringstream message;
		message << index << "th argument is not a String";
		Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();
	}

	return info[index].As<Napi::String>();
}

template<>
Napi::Object expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) {
	if (info.Length() <= index || !info[index].IsObject()) {
		std::ostringstream message;
		message << index << "th argument is not an Object";
		Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();
	}

	return info[index].As<Napi::Object>();
}

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
