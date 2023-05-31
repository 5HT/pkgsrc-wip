--- build/unix/stdc++compat/stdc++compat.cpp.orig	2023-05-13 20:47:48.708400730 +0200
+++ build/unix/stdc++compat/stdc++compat.cpp	2023-05-13 20:52:07.029007269 +0200
@@ -24,6 +24,7 @@
    GLIBCXX_3.4.27 is from gcc 10
    GLIBCXX_3.4.28 is from gcc 10
    GLIBCXX_3.4.29 is from gcc 11
+   GLIBCXX_3.4.30 is from gcc 12
 
 This file adds the necessary compatibility tricks to avoid symbols with
 version GLIBCXX_3.4.20 and bigger, keeping binary compatibility with
@@ -69,6 +70,18 @@
 }  // namespace std
 #endif
 
+#if _GLIBCXX_RELEASE >= 12
+namespace std {
+/* This avoids the GLIBCXX_3.4.30 symbol version. */
+void __attribute__((weak))
+__glibcxx_assert_fail(const char* __file, int __line, const char* __function,
+		      const char* __condition) {
+  MOZ_CRASH();
+}
+
+}  // namespace std
+#endif
+
 /* While we generally don't build with exceptions, we have some host tools
  * that do use them. libstdc++ from GCC 5.0 added exception constructors with
  * char const* argument. Older versions only have a constructor with
