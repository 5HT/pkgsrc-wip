# $NetBSD$

DISTNAME=	qtquick3d-everywhere-src-${QTVERSION}
PKGNAME=	qt6-qtquick3d-${QTVERSION}
COMMENT=	3d engine for Qt6 quick
CATEGORIES=	graphics
LICENSE=	gnu-gpl-v3

.include "../../wip/qt6-qtbase/Makefile.common"

PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3D.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DAssetImport.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DAssetUtils.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DEffects.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DHelpers.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DIblBaker.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DParticleEffects.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DParticles.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DRuntimeRender.pc
PKGCONFIG_OVERRIDE+=	lib/pkgconfig/Qt6Quick3DUtils.pc

.include "../../multimedia/assimp/buildlink3.mk"
.include "../../wip/qt6-qtbase/buildlink3.mk"
.include "../../wip/qt6-qtdeclarative/buildlink3.mk"
.include "../../wip/qt6-qtquicktimeline/buildlink3.mk"
.include "../../wip/qt6-qtshadertools/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
