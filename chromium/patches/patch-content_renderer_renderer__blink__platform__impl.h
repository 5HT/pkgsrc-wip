$NetBSD$

--- content/renderer/renderer_blink_platform_impl.h.orig	2020-07-08 21:41:48.000000000 +0000
+++ content/renderer/renderer_blink_platform_impl.h
@@ -30,7 +30,7 @@
 #include "third_party/blink/public/mojom/cache_storage/cache_storage.mojom.h"
 #include "third_party/blink/public/mojom/loader/code_cache.mojom.h"
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 #include "components/services/font/public/cpp/font_loader.h"  // nogncheck
 #include "third_party/skia/include/core/SkRefCnt.h"           // nogncheck
 #endif
@@ -218,7 +218,7 @@ class CONTENT_EXPORT RendererBlinkPlatfo
   // Return the mojo interface for making CodeCache calls.
   blink::mojom::CodeCacheHost& GetCodeCacheHost();
 
-#if defined(OS_LINUX) || defined(OS_MACOSX)
+#if defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD)
   std::unique_ptr<blink::WebSandboxSupport> sandbox_support_;
 #endif
 
@@ -239,7 +239,7 @@ class CONTENT_EXPORT RendererBlinkPlatfo
   mojo::PendingRemote<blink::mojom::CodeCacheHost> code_cache_host_remote_;
   mojo::SharedRemote<blink::mojom::CodeCacheHost> code_cache_host_;
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   sk_sp<font_service::FontLoader> font_loader_;
 #endif
 
