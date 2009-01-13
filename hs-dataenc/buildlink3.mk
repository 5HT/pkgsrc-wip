# $NetBSD: buildlink3.mk,v 1.2 2009/01/13 22:41:35 phonohawk Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
HS_DATAENC_BUILDLINK3_MK:=	${HS_DATAENC_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	hs-dataenc
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nhs-dataenc}
BUILDLINK_PACKAGES+=	hs-dataenc
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}hs-dataenc

.if ${HS_DATAENC_BUILDLINK3_MK} == "+"
BUILDLINK_DEPMETHOD.hs-dataenc?=	build
BUILDLINK_API_DEPENDS.hs-dataenc+=	hs-dataenc>=0.11.1
BUILDLINK_PKGSRCDIR.hs-dataenc?=	../../wip/hs-dataenc
.endif	# HS_DATAENC_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
