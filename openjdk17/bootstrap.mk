# $NetBSD: bootstrap.mk,v 1.4 2020/05/09 00:55:44 tnn Exp $


#ONLY_FOR_PLATFORM+=		NetBSD-*-i386
#BOOT.nb7-i386=			bootstrap-jdk-1.11.0.5.8-netbsd-7-i386-20190928.tar.xz
#SITES.${BOOT.nb7-i386}=		${MASTER_SITE_LOCAL:=openjdk11/}
#.if !empty(MACHINE_PLATFORM:MNetBSD-*-i386) || make(distinfo)
#DISTFILES+=			${BOOT.nb7-i386}
#EXTRACT_ONLY+=			${BOOT.nb7-i386}
#.endif

ONLY_FOR_PLATFORM+=		NetBSD-*-x86_64
BOOT.nb10-amd64=		bootstrap-jdk-1.17.0.2.8-netbsd-10-amd64-20220324.tar.xz
#SITES.${BOOT.nb10-amd64}=	${MASTER_SITE_LOCAL:=openjdk17/}
SITES.${BOOT.nb10-amd64}=	https://www.ryoon.net/~ryoon/
.if !empty(MACHINE_PLATFORM:MNetBSD-*-x86_64) || make(distinfo)
DISTFILES+=			${BOOT.nb10-amd64}
EXTRACT_ONLY+=			${BOOT.nb10-amd64}
.endif

#ONLY_FOR_PLATFORM+=		NetBSD-*-aarch64
#BOOT.nb9-aarch64=		bootstrap-jdk-1.11.0.7.10-netbsd-9-aarch64-20200509.tar.xz
#SITES.${BOOT.nb9-aarch64}=	${MASTER_SITE_LOCAL:=openjdk11/}
#.if !empty(MACHINE_PLATFORM:MNetBSD-*-aarch64) || make(distinfo)
#DISTFILES+=			${BOOT.nb9-aarch64}
#EXTRACT_ONLY+=			${BOOT.nb9-aarch64}
#.endif

CONFIGURE_ENV+=		LD_LIBRARY_PATH=${ALT_BOOTDIR}/lib

ALT_BOOTDIR=		${WRKDIR}/bootstrap
