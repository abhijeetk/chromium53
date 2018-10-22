// Copyright 2016 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/browser/webos_browser_context.h"

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/resource_context.h"
#include "content/public/browser/storage_partition.h"
#include "content/public/common/content_switches.h"
#include "content/shell/browser/shell_permission_manager.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_context_getter.h"
#include "webos/browser/webos_browser_context_adapter.h"
#include "webos/browser/webos_browser_switches.h"
#include "webos/browser/webos_url_request_context_getter.h"

namespace webos {

class WebOSBrowserContext::WebOSResourceContext :
    public content::ResourceContext {
 public :
  WebOSResourceContext(WebOSBrowserContext* context) : context_(context) {}
  virtual ~WebOSResourceContext() {}

  // ResourceContext implementation
  net::HostResolver* GetHostResolver() override {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
    return GetRequestContext()->host_resolver();
  }

  net::URLRequestContext* GetRequestContext() override {
    fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
    return context_->GetRequestContext()->GetURLRequestContext();
  }

 private:
  WebOSBrowserContext* context_;

  DISALLOW_COPY_AND_ASSIGN(WebOSResourceContext);
};

WebOSBrowserContext::WebOSBrowserContext(WebOSBrowserContextAdapter* adapter)
    : adapter_(adapter) { fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__); }

WebOSBrowserContext::~WebOSBrowserContext() {
}

net::URLRequestContextGetter* WebOSBrowserContext::GetRequestContext() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return url_request_getter_.get();
}

std::unique_ptr<content::ZoomLevelDelegate>
    WebOSBrowserContext::CreateZoomLevelDelegate(
    const base::FilePath& partition_path) {
      fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return std::unique_ptr<content::ZoomLevelDelegate>();
}

base::FilePath WebOSBrowserContext::GetPath() const {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  base::CommandLine* cmd_line = base::CommandLine::ForCurrentProcess();
  if (cmd_line->HasSwitch(kUserDataDir)) {
    base::FilePath path = cmd_line->GetSwitchValuePath(kUserDataDir);
    return path.Append(adapter_->GetStorageName());
  }

  return base::FilePath();
}

content::ResourceContext* WebOSBrowserContext::GetResourceContext() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!resource_context_)
    resource_context_.reset(new WebOSResourceContext(this));
  return resource_context_.get();
}

content::PermissionManager* WebOSBrowserContext::GetPermissionManager() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return nullptr;
}

content::BackgroundSyncController* WebOSBrowserContext::GetBackgroundSyncController() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return nullptr;
}

// Creates the main net::URLRequestContextGetter. It's called only once.
net::URLRequestContextGetter* WebOSBrowserContext::CreateRequestContext(
    content::ProtocolHandlerMap* protocol_handlers,
    content::URLRequestInterceptorScopedVector request_interceptors) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (!url_request_getter_)
    url_request_getter_ = new WebOSRequestContextGetter(
        this, protocol_handlers, std::move(request_interceptors),
        std::move(extra_websocket_headers_), proxy_rules_);
  return url_request_getter_.get();
}

// Creates the net::URLRequestContextGetter for a StoragePartition. It's
// called only once per partition_path.
net::URLRequestContextGetter* WebOSBrowserContext::CreateRequestContextForStoragePartition(
    const base::FilePath& partition_path,
    bool in_memory,
    content::ProtocolHandlerMap* protocol_handlers,
    content::URLRequestInterceptorScopedVector request_interceptors) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return nullptr;
}

// Creates the main net::URLRequestContextGetter for media resources. It's
// called only once.
net::URLRequestContextGetter* WebOSBrowserContext::CreateMediaRequestContext() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return url_request_getter_.get();
}

// Creates the media net::URLRequestContextGetter for a StoragePartition. It's
// called only once per partition_path.
net::URLRequestContextGetter*
    WebOSBrowserContext::CreateMediaRequestContextForStoragePartition(
        const base::FilePath& partition_path,
        bool in_memory) {
      fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return nullptr;
}

void WebOSBrowserContext::SetProxyRules(const std::string& proxy_rules) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  proxy_rules_ = proxy_rules;
}

void WebOSBrowserContext::AppendExtraWebSocketHeader(const std::string& key,
                                                     const std::string& value) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  extra_websocket_headers_.insert(std::make_pair(key, value));

  content::BrowserThread::PostTask(
      content::BrowserThread::IO, FROM_HERE,
      base::Bind(
          &WebOSBrowserContext::UpdateRequestContextGetterExtraWebSocketHeader,
          base::Unretained(this), key, value));
}

void WebOSBrowserContext::UpdateRequestContextGetterExtraWebSocketHeader(
    const std::string& key,
    const std::string& value) {
  if (url_request_getter_) {
      fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
    url_request_getter_->AppendExtraWebSocketHeader(key, value);
  }
}

void WebOSBrowserContext::FlushCookieStore() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  content::BrowserThread::PostTask(
      content::BrowserThread::IO, FROM_HERE,
      base::Bind(&WebOSBrowserContext::FlushCookieStoreOnIOThread,
                 base::Unretained(this)));
}

void WebOSBrowserContext::FlushCookieStoreOnIOThread() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  DCHECK_CURRENTLY_ON(content::BrowserThread::IO);
  net::CookieStore* cookie_store =
      GetResourceContext()->GetRequestContext()->cookie_store();
  if (cookie_store)
    cookie_store->FlushStore(base::Closure());
}

} // namespace webos
