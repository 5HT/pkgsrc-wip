$NetBSD$

--- headless/lib/browser/headless_request_context_manager.cc.orig	2020-07-08 21:40:44.000000000 +0000
+++ headless/lib/browser/headless_request_context_manager.cc
@@ -26,7 +26,7 @@ namespace headless {
 
 namespace {
 
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) || defined(OS_BSD)) && !defined(OS_CHROMEOS)
 constexpr char kProductName[] = "HeadlessChrome";
 #endif
 
@@ -56,7 +56,7 @@ net::NetworkTrafficAnnotationTag GetProx
   return traffic_annotation;
 }
 
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) || defined(OS_BSD)) && !defined(OS_CHROMEOS)
 ::network::mojom::CryptConfigPtr BuildCryptConfigOnce(
     const base::FilePath& user_data_path) {
   static bool done_once = false;
@@ -213,7 +213,7 @@ HeadlessRequestContextManager::HeadlessR
     proxy_config_monitor_ = std::make_unique<HeadlessProxyConfigMonitor>(
         base::ThreadTaskRunnerHandle::Get());
   }
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) || defined(OS_BSD)) && !defined(OS_CHROMEOS)
   auto crypt_config = BuildCryptConfigOnce(user_data_path_);
   if (crypt_config)
     content::GetNetworkService()->SetCryptConfig(std::move(crypt_config));
