// Copyright 2016-2017 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/webapp_window_base.h"

#include "ui/platform_window/webos/window_group_configuration.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host.h"
#include "webos/webapp_window.h"
#include "webos/window_group_configuration.h"

namespace webos {

////////////////////////////////////////////////////////////////////////////////
// WebAppWindowBase, public:

WebAppWindowBase::WebAppWindowBase()
    : pending_surface_id_(0) {
        fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
    }

WebAppWindowBase::~WebAppWindowBase() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetDelegate(NULL);
}

void WebAppWindowBase::InitWindow(int width, int height) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_ =
    std::unique_ptr<WebAppWindow>(new WebAppWindow(gfx::Rect(width, height), pending_surface_id_));
  webapp_window_->SetDelegate(this);
}

void WebAppWindowBase::Show() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->Show();
}

void WebAppWindowBase::Hide() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->Hide();
}

#if defined(OS_WEBOS)
unsigned WebAppWindowBase::GetWindowHandle() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return 0;

  return webapp_window_->host()->GetWindowHandle();
}
#endif

#if defined(OS_WEBOS)
void WebAppWindowBase::SetCustomCursor(CustomCursorType type,
                                       const std::string& path,
                                       int hotspot_x,
                                       int hotspot_y) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return;

  webapp_window_->host()->SetCustomCursor(type, path, hotspot_x, hotspot_y);
}
#endif

int WebAppWindowBase::DisplayWidth() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return webapp_window_->DisplayWidth();
}

int WebAppWindowBase::DisplayHeight() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return webapp_window_->DisplayHeight();
}

void WebAppWindowBase::AttachWebContents(void* web_contents) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->AttachWebContents((content::WebContents*)web_contents);
}

void WebAppWindowBase::DetachWebContents() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->DetachWebContents();
}

void WebAppWindowBase::RecreatedWebContents() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return;

#if defined(OS_WEBOS)
  webapp_window_->host()->ResetCompositor();
#endif
}

NativeWindowState WebAppWindowBase::GetWindowHostState() const {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return webapp_window_->GetWindowHostState();
}

NativeWindowState WebAppWindowBase::GetWindowHostStateAboutToChange() const {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return webapp_window_->GetWindowHostStateAboutToChange();
}

void WebAppWindowBase::SetWindowHostState(NativeWindowState state) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetWindowHostState(state);
}

void WebAppWindowBase::SetKeyMask(WebOSKeyMask key_mask, bool value) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetKeyMask(key_mask, value);
}

void WebAppWindowBase::SetWindowProperty(const std::string& name,
                                         const std::string& value) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetWindowProperty(name, value);
}

void WebAppWindowBase::SetWindowSurfaceId(int surface_id) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (webapp_window_)
    webapp_window_->SetWindowSurfaceId(surface_id);
  else
    pending_surface_id_ = surface_id;
}

void WebAppWindowBase::SetOpacity(float opacity) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetOpacity(opacity);
}

void WebAppWindowBase::Resize(int width, int height) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->Resize(width, height);
}

void WebAppWindowBase::SetUseVirtualKeyboard(bool enable) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->SetUseVirtualKeyboard(enable);
}

void WebAppWindowBase::CreateWindowGroup(
    const WindowGroupConfiguration& config) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  ui::WindowGroupConfiguration ui_config;

  ui_config.name = config.GetName();
  ui_config.is_anonymous = config.GetIsAnonymous();

  for (auto& it : config.GetLayers()) {
    ui::WindowGroupLayerConfiguration layer_config;
    layer_config.name = it.GetName();
    layer_config.z_order = it.GetZOrder();
    ui_config.layers.push_back(layer_config);
  }
  webapp_window_->CreateGroup(ui_config);
}

void WebAppWindowBase::AttachToWindowGroup(const std::string& group,
                                           const std::string& layer) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->AttachToGroup(group, layer);
}

void WebAppWindowBase::FocusWindowGroupOwner() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->FocusGroupOwner();
}

void WebAppWindowBase::FocusWindowGroupLayer() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->FocusGroupLayer();
}

void WebAppWindowBase::DetachWindowGroup() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  webapp_window_->DetachGroup();
}

#if defined(OS_WEBOS)
void WebAppWindowBase::XInputActivate(const std::string& type) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return;

  webapp_window_->host()->WebOSXInputActivate(type);
}

void WebAppWindowBase::XInputDeactivate() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return;

  webapp_window_->host()->WebOSXInputDeactivate();
}

void WebAppWindowBase::XInputInvokeAction(uint32_t keysym,
                                          SpecialKeySymbolType symbol_type,
                                          XInputEventType event_type) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!webapp_window_->host())
    return;

  ui::WebOSXInputSpecialKeySymbolType ui_symbol_type;
  switch (symbol_type) {
    case QT_KEY_SYMBOL:
      ui_symbol_type = ui::WEBOS_XINPUT_QT_KEY_SYMBOL;
      break;
    case NATIVE_KEY_SYMBOL:
      ui_symbol_type = ui::WEBOS_XINPUT_NATIVE_KEY_SYMBOL;
      break;
  };

  ui::WebOSXInputEventType ui_event_type;
  switch (event_type) {
    case XINPUT_PRESS_AND_RELEASE:
      ui_event_type = ui::WEBOS_XINPUT_PRESS_AND_RELEASE;
      break;
    case XINPUT_PRESS:
      ui_event_type = ui::WEBOS_XINPUT_PRESS;
      break;
    case XINPUT_RELEASE:
      ui_event_type = ui::WEBOS_XINPUT_RELEASE;
      break;
  };

  webapp_window_->host()->WebOSXInputInvokeAction(keysym, ui_symbol_type,
                                                  ui_event_type);
}
#endif

}  // namespace webos
