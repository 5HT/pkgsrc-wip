$NetBSD$

Workaround for disabling PCH.

--- common/lc_findreplacewidget.h.orig	2021-06-05 23:41:42.000000000 +0000
+++ common/lc_findreplacewidget.h
@@ -1,5 +1,7 @@
 #pragma once
 
+#include "lc_global.h"
+
 class lcFindReplaceWidget : public QWidget
 {
 	Q_OBJECT
