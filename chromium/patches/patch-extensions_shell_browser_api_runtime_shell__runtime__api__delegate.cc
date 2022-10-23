$NetBSD$

--- extensions/shell/browser/api/runtime/shell_runtime_api_delegate.cc.orig	2020-07-08 21:40:43.000000000 +0000
+++ extensions/shell/browser/api/runtime/shell_runtime_api_delegate.cc
@@ -45,7 +45,7 @@ void ShellRuntimeAPIDelegate::OpenURL(co
 bool ShellRuntimeAPIDelegate::GetPlatformInfo(PlatformInfo* info) {
 #if defined(OS_CHROMEOS)
   info->os = api::runtime::PLATFORM_OS_CROS;
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_BSD)
   info->os = api::runtime::PLATFORM_OS_LINUX;
 #endif
   return true;
