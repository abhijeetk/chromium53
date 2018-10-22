// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright 2016 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/ui/views/frame/webos_root_view.h"

#include "ui/base/dragdrop/drag_drop_types.h"
#include "ui/base/dragdrop/os_exchange_data.h"
#include "webos/ui/views/frame/webos_view.h"

// static
const char WebOSRootView::kViewClassName[] =
    "webos/ui/views/frame/WebOSRootView";

WebOSRootView::WebOSRootView(WebOSView* view,
                             views::Widget* widget)
    : views::internal::RootView(widget),
      view_(view) {
}

bool WebOSRootView::GetDropFormats(
    int* formats,
    std::set<ui::Clipboard::FormatType>* format_types) {
  NOTIMPLEMENTED();
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return false;
}

bool WebOSRootView::AreDropTypesRequired() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return true;
}

bool WebOSRootView::CanDrop(const ui::OSExchangeData& data) {
  NOTIMPLEMENTED();
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return false;
}

void WebOSRootView::OnDragEntered(const ui::DropTargetEvent& event) {
  NOTIMPLEMENTED();
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return;
}

int WebOSRootView::OnDragUpdated(const ui::DropTargetEvent& event) {
  NOTIMPLEMENTED();
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return ui::DragDropTypes::DRAG_NONE;
}

void WebOSRootView::OnDragExited() {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  NOTIMPLEMENTED();
}

int WebOSRootView::OnPerformDrop(const ui::DropTargetEvent& event) {
  NOTIMPLEMENTED();
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return ui::DragDropTypes::DRAG_NONE;
}

const char* WebOSRootView::GetClassName() const {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return kViewClassName;
}

bool WebOSRootView::OnMouseWheel(const ui::MouseWheelEvent& event) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return RootView::OnMouseWheel(event);
}

ui::EventDispatchDetails WebOSRootView::OnEventFromSource(ui::Event* event) {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return RootView::OnEventFromSource(event);
}
