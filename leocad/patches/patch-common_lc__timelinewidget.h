$NetBSD$

Workaround for disabling PCH.

--- common/lc_timelinewidget.h.orig	2021-06-05 23:41:42.000000000 +0000
+++ common/lc_timelinewidget.h
@@ -1,5 +1,7 @@
 #pragma once
 
+#include "lc_global.h"
+
 class lcTimelineWidget : public QTreeWidget
 {
 	Q_OBJECT
