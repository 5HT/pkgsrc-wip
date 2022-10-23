$NetBSD$

--- ui/gfx/font_render_params.h.orig	2020-07-15 18:56:34.000000000 +0000
+++ ui/gfx/font_render_params.h
@@ -111,7 +111,7 @@ GFX_EXPORT FontRenderParams GetFontRende
     const FontRenderParamsQuery& query,
     std::string* family_out);
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 // Clears GetFontRenderParams()'s cache. Intended to be called by tests that are
 // changing Fontconfig's configuration.
 GFX_EXPORT void ClearFontRenderParamsCacheForTest();
@@ -121,7 +121,7 @@ GFX_EXPORT void ClearFontRenderParamsCac
 GFX_EXPORT float GetFontRenderParamsDeviceScaleFactor();
 
 #if defined(OS_WIN) || defined(OS_LINUX) || defined(OS_ANDROID) || \
-    defined(OS_FUCHSIA)
+    defined(OS_FUCHSIA) || defined(OS_BSD)
 // Sets the device scale factor for FontRenderParams to decide
 // if it should enable subpixel positioning.
 GFX_EXPORT void SetFontRenderParamsDeviceScaleFactor(
