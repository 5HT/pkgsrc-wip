$NetBSD$

Treat NetBSD like Linux.

--- src/slic3r/GUI/PrintHostDialogs.cpp.orig	2021-12-17 14:00:02.000000000 +0000
+++ src/slic3r/GUI/PrintHostDialogs.cpp
@@ -121,7 +121,7 @@ PrintHostSendDialog::PrintHostSendDialog
     }
     finalize();
 
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
     // On Linux with GTK2 when text control lose the focus then selection (colored background) disappears but text color stay white
     // and as a result the text is invisible with light mode
     // see https://github.com/prusa3d/PrusaSlicer/issues/4532
