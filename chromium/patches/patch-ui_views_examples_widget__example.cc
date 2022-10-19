$NetBSD$

--- ui/views/examples/widget_example.cc.orig	2020-07-15 18:56:34.000000000 +0000
+++ ui/views/examples/widget_example.cc
@@ -79,7 +79,7 @@ void WidgetExample::CreateExampleView(Vi
               DIALOG);
   BuildButton(container, GetStringUTF16(IDS_WIDGET_MODAL_BUTTON_LABEL),
               MODAL_DIALOG);
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // Windows does not support TYPE_CONTROL top-level widgets.
   BuildButton(container, GetStringUTF16(IDS_WIDGET_CHILD_WIDGET_BUTTON_LABEL),
               CHILD);
