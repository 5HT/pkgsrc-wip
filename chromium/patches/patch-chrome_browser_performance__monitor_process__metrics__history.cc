$NetBSD$

--- chrome/browser/performance_monitor/process_metrics_history.cc.orig	2020-07-08 21:40:34.000000000 +0000
+++ chrome/browser/performance_monitor/process_metrics_history.cc
@@ -47,7 +47,7 @@ void ProcessMetricsHistory::SampleMetric
 #if defined(OS_WIN)
   disk_usage_ = process_metrics_->GetDiskUsageBytesPerSecond();
 #endif
-#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX)
+#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX) || defined(OS_BSD)
   idle_wakeups_ = process_metrics_->GetIdleWakeupsPerSecond();
 #endif
 #if defined(OS_MACOSX)
@@ -90,7 +90,7 @@ void ProcessMetricsHistory::UpdateHistog
           kDiskUsageHistogramMin, kDiskUsageHistogramMax,
           kDiskUsageHistogramBucketCount);
 #endif
-#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX)
+#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX) || defined(OS_BSD)
       UMA_HISTOGRAM_COUNTS_10000(
           "PerformanceMonitor.IdleWakeups.BrowserProcess", idle_wakeups_);
 #endif
@@ -111,7 +111,7 @@ void ProcessMetricsHistory::UpdateHistog
         UMA_HISTOGRAM_BOOLEAN("PerformanceMonitor.HighCPU.RendererProcess",
                               true);
       }
-#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX)
+#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX) || defined(OS_BSD)
       UMA_HISTOGRAM_COUNTS_10000(
           "PerformanceMonitor.IdleWakeups.RendererProcess", idle_wakeups_);
 #endif
@@ -131,7 +131,7 @@ void ProcessMetricsHistory::UpdateHistog
                                   kHistogramBucketCount);
       if (cpu_usage_ > kHighCPUUtilizationThreshold)
         UMA_HISTOGRAM_BOOLEAN("PerformanceMonitor.HighCPU.GPUProcess", true);
-#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX)
+#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_AIX) || defined(OS_BSD)
       UMA_HISTOGRAM_COUNTS_10000("PerformanceMonitor.IdleWakeups.GPUProcess",
                                  idle_wakeups_);
 #endif
