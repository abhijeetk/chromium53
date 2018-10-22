// Copyright 2017 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/window_group_configuration.h"

namespace webos {

WindowGroupConfiguration::WindowGroupConfiguration(const std::string& name)
    : name_(name), is_anonymous_(false) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);}

WindowGroupConfiguration::~WindowGroupConfiguration() {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);}

void WindowGroupConfiguration::SetIsAnonymous(bool is_anonymous) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  is_anonymous_ = is_anonymous;
}

bool WindowGroupConfiguration::GetIsAnonymous() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return is_anonymous_;
}

std::string WindowGroupConfiguration::GetName() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return name_;
}

void WindowGroupConfiguration::AddLayer(
    const WindowGroupLayerConfiguration& layer_config) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  layers_.push_back(layer_config);
}

const std::vector<WindowGroupLayerConfiguration>&
WindowGroupConfiguration::GetLayers() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return layers_;
}

}  // namespace webos
