// Copyright 2016 LG Electronics, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webos/webview_base.h"

#include "base/memory/memory_pressure_listener.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_contents.h"
#include "third_party/WebKit/public/platform/WebPageVisibilityState.h"
#include "webos/common/webos_event.h"
#include "webos/webview.h"

namespace webos {

void WebViewBase::SetFileAccessBlocked(bool blocked) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  WebView::SetFileAccessBlocked(blocked);
}

WebViewBase::WebViewBase(int width, int height)
    : m_webview(new WebView(width, height)) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);}

WebViewBase::~WebViewBase() {
  delete m_webview;
}

WebViewProfile* WebViewBase::GetProfile() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return m_webview->GetProfile();
}

void WebViewBase::SetProfile(WebViewProfile* profile) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetProfile(profile);
}

void WebViewBase::Initialize(const std::string& app_id,
                             const std::string& app_path,
                             const std::string& trust_level,
                             const std::string& v8_snapshot_path,
                             const std::string& v8_extra_flags,
                             bool use_native_scroll) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  SetAppPath(app_path);
  SetTrustLevel(trust_level);

  m_webview->Initialize(this, v8_snapshot_path, v8_extra_flags,
                        use_native_scroll);

  if (GetWebContents()) {
    //The arcitecture of using WebContentsImpl is not good way and is not what we want to do
    //Need to change it
    content::RenderViewHost *rvh = GetWebContents()->GetRenderViewHost();
    if (!rvh->IsRenderViewLive()) {
      content::FrameReplicationState state; // FIXME(jb) how can I get this?
      static_cast<content::WebContentsImpl*>(
          GetWebContents())->
              CreateRenderViewForRenderManager(rvh,
                                               MSG_ROUTING_NONE,
                                               MSG_ROUTING_NONE,
                                               state);
    }
  }

  SetAppId(app_id);
}

content::WebContents* WebViewBase::GetWebContents() {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return m_webview->GetWebContents();
}

void WebViewBase::AddUserStyleSheet(const std::string& sheet)
{fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->AddUserStyleSheet(sheet);
}

std::string WebViewBase::DefaultUserAgent() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return m_webview->DefaultUserAgent();
}

std::string WebViewBase::UserAgent() const {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  return m_webview->UserAgent();
}

void WebViewBase::LoadUrl(const std::string& url) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->LoadUrl(GURL(url));
}

void WebViewBase::StopLoading() {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->StopLoading();
}

void WebViewBase::LoadExtension(const std::string& name) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->LoadExtension(name);
}

void WebViewBase::ClearExtensions() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->ClearExtensions();
}

void WebViewBase::EnableInspectablePage() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);GetWebContents()->EnableInspectable();
}

void WebViewBase::SetInspectable(bool enable) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetInspectable(enable);
}

void WebViewBase::AddAvailablePluginDir(const std::string& directory) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);GetWebContents()->AddAvailablePluginDir(directory.c_str());
}

void WebViewBase::AddCustomPluginDir(const std::string& directory) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->AddCustomPluginDir(directory);
}

void WebViewBase::SetUserAgent(const std::string& useragent) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);GetWebContents()->SetUserAgentOverride(useragent);
}

void WebViewBase::SetBackgroundColor(int r, int g, int b, int alpha) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetBackgroundColor(r, g, b, alpha);
}

void WebViewBase::SetAllowFakeBoldText(bool allowFakeBoldText) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetAllowFakeBoldText(allowFakeBoldText);
}

void WebViewBase::SetShouldSuppressDialogs(bool suppress) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetShouldSuppressDialogs(suppress);
}

void WebViewBase::SetAppId(const std::string& appId) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetAppId(appId);
}

void WebViewBase::SetAcceptLanguages(const std::string& languages) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetAcceptLanguages(languages);
}

void WebViewBase::SetUseLaunchOptimization(bool enabled) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetUseLaunchOptimization(enabled);
}

void WebViewBase::SetUseEnyoOptimization(bool enabled) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetUseEnyoOptimization(enabled);
}

void WebViewBase::SetUseAccessibility(bool enabled) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (enabled)
    GetWebContents()->EnableCompleteAccessibilityMode();
}

void WebViewBase::SetBlockWriteDiskcache(bool blocked) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetBlockWriteDiskcache(blocked);
}

void WebViewBase::SetTransparentBackground(bool enable) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetTransparentBackground(enable);
}

void WebViewBase::SetBoardType(const std::string& boardType) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetBoardType(boardType);
}

void WebViewBase::SetMediaCodecCapability(const std::string& capability) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetMediaCodecCapability(capability);
}

void WebViewBase::SetSupportDolbyHDRContents(bool support) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetSupportDolbyHDRContents(support);
}

void WebViewBase::SetViewportSize(int width, int height) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetViewportSize(width, height);
}

void WebViewBase::NotifyMemoryPressure(MemoryPressureLevel level) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  base::MemoryPressureListener::MemoryPressureLevel pressure_level =
      base::MemoryPressureListener::MEMORY_PRESSURE_LEVEL_NONE;
  if (level == MemoryPressureLevel::MEMORY_PRESSURE_LOW) {
    pressure_level =
        base::MemoryPressureListener::MEMORY_PRESSURE_LEVEL_MODERATE;
  } else if (level == MemoryPressureLevel::MEMORY_PRESSURE_CRITICAL) {
    pressure_level =
        base::MemoryPressureListener::MEMORY_PRESSURE_LEVEL_CRITICAL;
  }

  m_webview->NotifyMemoryPressure(pressure_level);
}

void WebViewBase::SetVisible(bool visible) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetVisible(visible);
}

void WebViewBase::SetVisibilityState(WebPageVisibilityState visibilityState) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetVisibilityState(
      static_cast<blink::WebPageVisibilityState>(visibilityState));
}

void WebViewBase::DeleteWebStorages(const std::string& identifier) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->DeleteWebStorages(identifier);
}

std::string WebViewBase::DocumentTitle() const {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->DocumentTitle();
}

void WebViewBase::SuspendWebPageDOM() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SuspendDOM();
}

void WebViewBase::ReplaceBaseURL(const std::string& newUrl,
                                 const std::string& oldUrl) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  if (newUrl == oldUrl)
    return;

  m_webview->ReplaceBaseURL(GURL(newUrl));
}

void WebViewBase::ResumeWebPageDOM() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->ResumeDOM();
}

void WebViewBase::SuspendWebPageMedia() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SuspendMedia();
}

void WebViewBase::ResumeWebPageMedia() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->ResumeMedia();
}

void WebViewBase::SuspendPaintingAndSetVisibilityHidden() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SuspendPaintingAndSetVisibilityHidden();
}

void WebViewBase::ResumePaintingAndSetVisibilityVisible() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->ResumePaintingAndSetVisibilityVisible();
}

const std::string& WebViewBase::GetUrl() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->GetUrl();
}

void WebViewBase::RunJavaScript(const std::string& jsCode) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->RunJavaScript(jsCode);
}

void WebViewBase::RunJavaScriptInAllFrames(const std::string& jsCode) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->RunJavaScriptInAllFrames(jsCode);
}

void WebViewBase::Reload() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->Reload();
}

int WebViewBase::RenderProcessPid() const {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->RenderProcessPid();
}

void WebViewBase::SetFocus(bool focus) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetFocus(focus);
}

void WebViewBase::SetZoomFactor(double factor) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetZoomFactor(factor);
}

void WebViewBase::SetDoNotTrack(bool dnt) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetDoNotTrack(dnt);
}

void WebViewBase::ForwardWebOSEvent(WebOSEvent* event) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->ForwardWebOSEvent(event);
}

bool WebViewBase::CanGoBack() const {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->CanGoBack();
}

void WebViewBase::RequestGetCookies(const std::string& url) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->RequestGetCookies(url);
}

bool WebViewBase::IsKeyboardVisible() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->IsKeyboardVisible();
}

bool WebViewBase::IsInputMethodActive() {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);return m_webview->IsInputMethodActive();
}

void WebViewBase::SetHardwareResolution(int width, int height) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetHardwareResolution(width, height);
}

void WebViewBase::SetEnableHtmlSystemKeyboardAttr(bool enable) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->SetEnableHtmlSystemKeyboardAttr(enable);
}

void WebViewBase::DropAllPeerConnections(DropPeerConnectionReason reason) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);m_webview->DropAllPeerConnections(reason);
}

//WebPreferences
void WebViewBase::SetAllowRunningInsecureContent(bool on) {
  fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::AllowRunningInsecureContent, on);
}

void WebViewBase::SetAllowScriptsToCloseWindows(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::AllowScriptsToCloseWindows, on);
}

void WebViewBase::SetAllowUniversalAccessFromFileUrls(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::AllowUniversalAccessFromFileUrls, on);
}

void WebViewBase::SetSuppressesIncrementalRendering(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::SuppressesIncrementalRendering, on);
}

void WebViewBase::SetDisallowScrollbarsInMainFrame(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::DisallowScrollbarsInMainFrame, on);
}

void WebViewBase::SetDisallowScrollingInMainFrame(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::DisallowScrollingInMainFrame, on);
}

void WebViewBase::SetJavascriptCanOpenWindows(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::JavascriptCanOpenWindows, on);
}

void WebViewBase::SetSpatialNavigationEnabled(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::SpatialNavigationEnabled, on);
}

void WebViewBase::SetSupportsMultipleWindows(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::SupportsMultipleWindows, on);
}

void WebViewBase::SetCSSNavigationEnabled(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::CSSNavigationEnabled, on);
}

void WebViewBase::SetV8DateUseSystemLocaloffset(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::V8DateUseSystemLocaloffset, on);
}

void WebViewBase::SetAllowLocalResourceLoad(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::AllowLocalResourceLoad, on);
}

void WebViewBase::SetLocalStorageEnabled(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::LocalStorageEnabled, on);
}

void WebViewBase::SetWebSecurityEnabled(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::WebSecurityEnabled, on);
}

void WebViewBase::SetFixedPositionCreatesStackingContext(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::FixedPositionCreatesStackingContext, on);
}

void WebViewBase::SetKeepAliveWebApp(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::KeepAliveWebApp, on);
}

void WebViewBase::SetAdditionalFontFamilyEnabled(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::AdditionalFontFamilyEnabled, on);
}

void WebViewBase::SetDatabaseIdentifier(const std::string& identifier) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetDatabaseIdentifier(identifier);
}

void WebViewBase::SetBackHistoryAPIDisabled(const bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::BackHistoryAPIDisabled, on);
}

void WebViewBase::SetForceVideoTexture(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::ForceVideoTexture, on);
}

void WebViewBase::SetNotifyFMPDirectly(const bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::NotifyFMPDirectly, on);
}

void WebViewBase::SetNetworkStableTimeout(const double timeout) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferencesAttribute(
      WebView::Attribute::NetworkStableTimeout, timeout);
}

//FontFamily
void WebViewBase::SetStandardFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::StandardFont, font);
}

void WebViewBase::SetFixedFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::FixedFont, font);
}

void WebViewBase::SetSerifFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::SerifFont, font);
}

void WebViewBase::SetSansSerifFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::SansSerifFont, font);
}

void WebViewBase::SetCursiveFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::CursiveFont, font);
}

void WebViewBase::SetFantasyFontFamily(const std::string& font) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetFontFamily(WebView::FontFamily::FantasyFont, font);
}

void WebViewBase::SetFontHinting(WebViewBase::FontRenderParams hinting) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  switch (hinting) {
    case WebViewBase::FontRenderParams::HINTING_NONE :
      m_webview->SetFontHintingNone();
      return;
    case WebViewBase::FontRenderParams::HINTING_SLIGHT :
      m_webview->SetFontHintingSlight();
      return;
    case WebViewBase::FontRenderParams::HINTING_MEDIUM :
      m_webview->SetFontHintingMedium();
      return;
    case WebViewBase::FontRenderParams::HINTING_FULL :
      m_webview->SetFontHintingFull();
      return;
    default :
      m_webview->SetFontHintingNone();
      return;
  }
}

void WebViewBase::UpdatePreferences() {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->UpdatePreferences();
}

void WebViewBase::SetAudioGuidanceOn(bool on) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetAudioGuidanceOn(on);
}

void WebViewBase::ResetStateToMarkNextPaintForContainer() {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
#if defined(USE_SPLASH_SCREEN)
  m_webview->ResetStateToMarkNextPaintForContainer();
#endif
}

void WebViewBase::SetTrustLevel(const std::string& trust_level) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetTrustLevel(trust_level);
}

void WebViewBase::SetAppPath(const std::string& app_path) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetAppPath(app_path);
}

void WebViewBase::SetSSLCertErrorPolicy(SSLCertErrorPolicy policy) {fprintf(stderr, "[%d] %s %s %d\r\n", (int)getpid(), __FILE__, __FUNCTION__, __LINE__);
  m_webview->SetSSLCertErrorPolicy(policy);
}

} //namespace webos
