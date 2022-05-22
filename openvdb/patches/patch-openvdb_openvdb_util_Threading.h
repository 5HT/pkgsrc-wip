$NetBSD$

Support tbb 2021.3 from
https://github.com/AcademySoftwareFoundation/openvdb/commit/5b0ec82307c603adb147cee4bc1a925d407141f5

--- openvdb/openvdb/util/Threading.h.orig	2021-08-11 09:50:26.288237592 +0000
+++ openvdb/openvdb/util/Threading.h
@@ -0,0 +1,50 @@
+// Copyright Contributors to the OpenVDB Project
+// SPDX-License-Identifier: MPL-2.0
+//
+/// @file Threading.h
+
+#ifndef OPENVDB_UTIL_THREADING_HAS_BEEN_INCLUDED
+#define OPENVDB_UTIL_THREADING_HAS_BEEN_INCLUDED
+
+#include "openvdb/version.h"
+
+/// @note tbb/blocked_range.h is the ONLY include that persists from TBB 2020
+///   to TBB 2021 that itself includes the TBB specific version header files.
+///   In TBB 2020, the version header was called tbb/stddef.h. In 2021, it's
+///   called tbb/version.h. We include tbb/blocked_range.h here to indirectly
+///   access the version defines in a consistent way so that downstream
+///   software doesn't need to provide compile time defines.
+#include <tbb/blocked_range.h>
+#include <tbb/task.h>
+#include <tbb/task_group.h>
+
+namespace openvdb {
+OPENVDB_USE_VERSION_NAMESPACE
+namespace OPENVDB_VERSION_NAME {
+namespace util {
+
+inline bool cancelGroupExecution()
+{
+#if TBB_INTERFACE_VERSION_MAJOR >= 12
+	auto ctx = tbb::task::current_context();
+	return ctx ? ctx->cancel_group_execution() : false;
+#else
+    return tbb::task::self().cancel_group_execution();
+#endif
+}
+
+inline bool isGroupExecutionCancelled()
+{
+#if TBB_INTERFACE_VERSION_MAJOR >= 12
+	auto ctx = tbb::task::current_context();
+	return ctx ? ctx->is_group_execution_cancelled() : false;
+#else
+    return tbb::task::self().is_cancelled();
+#endif
+}
+
+} // namespace util
+} // namespace OPENVDB_VERSION_NAME
+} // namespace openvdb
+
+#endif // OPENVDB_UTIL_THREADING_HAS_BEEN_INCLUDED
