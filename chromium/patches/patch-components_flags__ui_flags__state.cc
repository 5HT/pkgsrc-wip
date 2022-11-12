$NetBSD$

--- components/flags_ui/flags_state.cc.orig	2020-07-08 21:40:39.000000000 +0000
+++ components/flags_ui/flags_state.cc
@@ -684,7 +684,7 @@ int FlagsState::GetCurrentPlatform() {
   return kOsWin;
 #elif defined(OS_CHROMEOS)  // Needs to be before the OS_LINUX check.
   return kOsCrOS;
-#elif defined(OS_LINUX) || defined(OS_OPENBSD)
+#elif defined(OS_LINUX) || defined(OS_BSD)
   return kOsLinux;
 #elif defined(OS_ANDROID)
   return kOsAndroid;
