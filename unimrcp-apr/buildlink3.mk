# $NetBSD$

BUILDLINK_TREE+=	apr

.if !defined(APR_BUILDLINK3_MK)
APR_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.apr+=	apr>=1.5.2
BUILDLINK_ABI_DEPENDS.apr+=	apr>=1.5.2
BUILDLINK_PKGSRCDIR.apr?=	../../wip/unimrcp-apr
.endif	# APR_BUILDLINK3_MK

BUILDLINK_TREE+=	-apr
