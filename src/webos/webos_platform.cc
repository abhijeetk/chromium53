// Copyright 2016 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos_platform.h"

#include "net/base/webos/network_change_notifier_factory_webos.h"
#include "net/base/webos/network_change_notifier_webos.h"
#include "ozone/wayland/display.h"
#include "ozone/wayland/window.h"
#include "webos/app/webos_content_main_delegate.h"
#include "webos/common/webos_locales_mapping.h"
#include "webos/public/runtime.h"

#if defined(OS_WEBOS)
#include "ozone/wayland/shell/webos_shell_surface.h"
#endif

namespace webos {

WebOSPlatform* WebOSPlatform::webos_platform_ = new WebOSPlatform;

WebOSPlatform* WebOSPlatform::GetInstance() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return webos_platform_;
}

WebOSPlatform::WebOSPlatform() : input_pointer_(NULL) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  Runtime::GetInstance()->InitializePlatformDelegate(this);
}

WebOSPlatform::~WebOSPlatform() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
}

void WebOSPlatform::OnCursorVisibilityChanged(bool visible) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (input_pointer_)
    input_pointer_->OnCursorVisibilityChanged(visible);
}

void WebOSPlatform::OnNetworkStateChanged(bool is_connected) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
#if defined(OS_WEBOS)
  webos::NetworkChangeNotifierWebos* network_change_notifier =
      NetworkChangeNotifierFactoryWebos::GetInstance();
  if (network_change_notifier)
    network_change_notifier->OnNetworkStateChanged(is_connected);
#endif
}

void WebOSPlatform::OnLocaleInfoChanged(std::string language) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  std::string locale = webos::MapWebOsToChromeLocales(language);
  GetWebOSContentBrowserClient()->SetApplicationLocale(locale);
}

void WebOSPlatform::SetInputPointer(InputPointer* input_pointer) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  input_pointer_ = input_pointer;
}

InputPointer* WebOSPlatform::GetInputPointer() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return input_pointer_;
}

void WebOSPlatform::SetInputRegion(unsigned handle,
                                   std::vector<gfx::Rect>region) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
#if defined(OS_WEBOS)
  ozonewayland::WaylandDisplay* display = ozonewayland::WaylandDisplay::GetInstance();
  ozonewayland::WaylandWindow* window = display->GetWindow(handle);

  ozonewayland::WebosShellSurface* shellSurface =
      static_cast<ozonewayland::WebosShellSurface*>(window->ShellSurface());
  shellSurface->SetInputRegion(region);
#endif
}

void WebOSPlatform::SetKeyMask(unsigned handle, webos::WebOSKeyMask keyMask) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
#if defined(OS_WEBOS)
  ozonewayland::WaylandDisplay* display = ozonewayland::WaylandDisplay::GetInstance();
  ozonewayland::WaylandWindow* window = display->GetWindow(handle);

  ozonewayland::WebosShellSurface* shellSurface =
      static_cast<ozonewayland::WebosShellSurface*>(window->ShellSurface());
  shellSurface->SetKeyMask(keyMask);
#endif
}

} //namespace ozonewayland
