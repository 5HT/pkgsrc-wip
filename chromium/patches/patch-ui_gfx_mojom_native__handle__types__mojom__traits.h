$NetBSD$

--- ui/gfx/mojom/native_handle_types_mojom_traits.h.orig	2020-07-15 18:56:34.000000000 +0000
+++ ui/gfx/mojom/native_handle_types_mojom_traits.h
@@ -14,13 +14,13 @@
 #include "mojo/public/cpp/system/platform_handle.h"
 #include "ui/gfx/mojom/native_handle_types.mojom-shared.h"
 
-#if defined(OS_LINUX) || defined(USE_OZONE)
+#if defined(OS_LINUX) || defined(USE_OZONE) || defined(OS_BSD)
 #include "ui/gfx/native_pixmap_handle.h"
 #endif
 
 namespace mojo {
 
-#if defined(OS_LINUX) || defined(USE_OZONE)
+#if defined(OS_LINUX) || defined(USE_OZONE) || defined(OS_BSD)
 template <>
 struct COMPONENT_EXPORT(GFX_NATIVE_HANDLE_TYPES_SHARED_MOJOM_TRAITS)
     StructTraits<gfx::mojom::NativePixmapPlaneDataView,
@@ -48,7 +48,7 @@ struct COMPONENT_EXPORT(GFX_NATIVE_HANDL
     return pixmap_handle.planes;
   }
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   static uint64_t modifier(const gfx::NativePixmapHandle& pixmap_handle) {
     return pixmap_handle.modifier;
   }
