$NetBSD$

--- chrome/browser/chrome_content_browser_client.h.orig	2020-07-08 21:41:46.000000000 +0000
+++ chrome/browser/chrome_content_browser_client.h
@@ -381,7 +381,7 @@ class ChromeContentBrowserClient : publi
   void OverridePageVisibilityState(
       content::RenderFrameHost* render_frame_host,
       content::PageVisibilityState* visibility_state) override;
-#if defined(OS_POSIX) && !defined(OS_MACOSX)
+#if defined(OS_POSIX) && !defined(OS_MACOSX) && !defined(OS_BSD)
   void GetAdditionalMappedFilesForChildProcess(
       const base::CommandLine& command_line,
       int child_process_id,
