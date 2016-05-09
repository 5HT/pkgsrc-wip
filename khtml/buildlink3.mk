# $NetBSD$

BUILDLINK_TREE+=	khtml

.if !defined(KHTML_BUILDLINK3_MK)
KHTML_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.khtml+=	khtml>=5.21.0
BUILDLINK_PKGSRCDIR.khtml?=	../../wip/khtml

.include "../../graphics/giflib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../wip/kjs/buildlink3.mk"
.include "../../wip/kparts/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# KHTML_BUILDLINK3_MK

BUILDLINK_TREE+=	-khtml
