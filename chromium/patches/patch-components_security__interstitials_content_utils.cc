$NetBSD$

--- components/security_interstitials/content/utils.cc.orig	2020-07-08 21:40:41.000000000 +0000
+++ components/security_interstitials/content/utils.cc
@@ -31,7 +31,7 @@ void LaunchDateAndTimeSettings() {
 #if defined(OS_ANDROID)
   JNIEnv* env = base::android::AttachCurrentThread();
   Java_DateAndTimeSettingsHelper_openDateAndTimeSettings(env);
-#elif defined(OS_LINUX)
+#elif defined(OS_LINUX) || defined(OS_BSD)
   struct ClockCommand {
     const char* const pathname;
     const char* const argument;
