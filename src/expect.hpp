#pragma once

#include <sstream>

#include <napi.h>

#include "core/Mat.h"

template <typename T>
T expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index) = delete;

template<>
Napi::Number expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index);

template<>
Napi::String expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index);

template<>
Napi::Object expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index);

template<>
Mat* expectArg(Napi::Env env, const Napi::CallbackInfo& info, size_t index);

template <typename T>
T expectField(Napi::Env env, Napi::Object& obj, const char* name, const char* key) = delete;

template<>
Napi::Number expectField(Napi::Env env, Napi::Object& obj, const char* name, const char* key);
