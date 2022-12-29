$NetBSD$

--- components/safe_browsing/core/resources/gen_file_type_proto.py.orig	2020-07-08 21:40:41.000000000 +0000
+++ components/safe_browsing/core/resources/gen_file_type_proto.py
@@ -31,6 +31,7 @@ def PlatformTypes():
     "android": download_file_types_pb2.DownloadFileType.PLATFORM_ANDROID,
     "chromeos": download_file_types_pb2.DownloadFileType.PLATFORM_CHROME_OS,
     "linux": download_file_types_pb2.DownloadFileType.PLATFORM_LINUX,
+    "netbsd": download_file_types_pb2.DownloadFileType.PLATFORM_LINUX,
     "mac": download_file_types_pb2.DownloadFileType.PLATFORM_MAC,
     "win": download_file_types_pb2.DownloadFileType.PLATFORM_WINDOWS,
   }
@@ -169,7 +170,7 @@ class DownloadFileTypeProtoGenerator(Bin
                       'Outfile must have a %d for version and %s for platform.')
     parser.add_option('-t', '--type',
                       help='The platform type. One of android, chromeos, ' +
-                      'linux, mac, win')
+                      'linux, mac, win, netbsd')
 
   def AddExtraCommandLineArgsForVirtualEnvRun(self, opts, command):
     if opts.type is not None:
