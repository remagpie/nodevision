#include <sstream>

#include "expect.hpp"

#define EXPECT_ARG_NAPI(type) \
	template<>\
	Napi::type expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) {\
		auto value = info[index];\
		if (!value.Is##type()) {\
			std::ostringstream message;\
			message << index << "th argument is not a(n) " #type;\
			Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();\
		}\
		return value.As<Napi::type>();\
	}

#define EXPECT_FIELD_NAPI(type) \
	template<>\
	Napi::type expectField(Napi::Env env, Napi::Object& obj, const char* name, const char* key) {\
		auto value = obj.Get(key);\
		if (!value.Is##type()) {\
			std::ostringstream message;\
			message << name << "." << key << " is not a(n) " #type;\
			Napi::TypeError::New(env, message.str()).ThrowAsJavaScriptException();\
		}\
		return value.As<Napi::type>();\
	}

EXPECT_ARG_NAPI(Number)
EXPECT_ARG_NAPI(String)
EXPECT_ARG_NAPI(Object)

EXPECT_FIELD_NAPI(Number)
