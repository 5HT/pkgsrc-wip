$NetBSD$

--- components/viz/host/host_display_client.h.orig	2020-07-08 21:40:41.000000000 +0000
+++ components/viz/host/host_display_client.h
@@ -43,7 +43,7 @@ class VIZ_HOST_EXPORT HostDisplayClient 
       mojo::PendingReceiver<mojom::LayeredWindowUpdater> receiver) override;
 #endif
 
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) || defined(OS_BSD)) && !defined(OS_CHROMEOS)
   void DidCompleteSwapWithNewSize(const gfx::Size& size) override;
 #endif
 
