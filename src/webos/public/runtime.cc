// Copyright (c) 2016 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/public/runtime.h"

#include "webos/public/runtime_delegates.h"

namespace webos {

Runtime* Runtime::GetInstance() {
  return base::Singleton<Runtime>::get();
}

Runtime::Runtime()
    : luna_service_delegate_(NULL),
      cookie_store_util_delegate_(NULL),
      platform_delegate_(NULL),
      is_mrcu_paired_(false),
      is_network_connected_(true),
      is_foreground_app_enyo_(false),
      is_main_getter_created_(false) {
          fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
      }

Runtime::~Runtime() {}

void Runtime::InitializeLunaService(
    LunaServiceDelegate* luna_service_delegate) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  luna_service_delegate_ = luna_service_delegate;
}

void Runtime::InitializeCookieStoreUtil(
    CookieStoreUtilDelegate* cookie_store_util_delegate) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  cookie_store_util_delegate_ = cookie_store_util_delegate;
}

LSHandle* Runtime::GetLSHandle() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (luna_service_delegate_)
    return luna_service_delegate_->GetLSHandle();
  return NULL;
}

void Runtime::FlushStoreCookie(PowerOffState power_off_state,
                               std::string timestamp) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (cookie_store_util_delegate_)
    cookie_store_util_delegate_->FlushStoreCookie(power_off_state, timestamp);
}

void Runtime::OnCursorVisibilityChanged(bool visible) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (platform_delegate_)
    platform_delegate_->OnCursorVisibilityChanged(visible);
}

void Runtime::SetNetworkConnected(bool is_connected) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (is_network_connected_ == is_connected)
    return;

  is_network_connected_ = is_connected;

  if (platform_delegate_)
    platform_delegate_->OnNetworkStateChanged(is_connected);
}

void Runtime::SetLocale(std::string locale) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (current_locale_ == locale)
    return;

  current_locale_ = locale;

  if (platform_delegate_)
    platform_delegate_->OnLocaleInfoChanged(locale);
}

}  // namespace webos
