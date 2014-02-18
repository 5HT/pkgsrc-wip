# $NetBSD: buildlink3.mk,v 1.3 2014/02/18 14:29:41 szptvlfn Exp $

BUILDLINK_TREE+=	hs-shake

.if !defined(HS_SHAKE_BUILDLINK3_MK)
HS_SHAKE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-shake+=	hs-shake>=0.11.1
BUILDLINK_PKGSRCDIR.hs-shake?=	../../wip/hs-shake

.include "../../wip/hs-hashable/buildlink3.mk"
.include "../../wip/hs-random/buildlink3.mk"
.include "../../wip/hs-transformers/buildlink3.mk"
.include "../../wip/hs-unordered-containers/buildlink3.mk"
.include "../../wip/hs-utf8-string/buildlink3.mk"
.endif	# HS_SHAKE_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-shake
