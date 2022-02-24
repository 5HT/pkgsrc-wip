# $NetBSD: options.mk,v 1.5 2020/12/09 10:33:04 jaapb Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.ocaml
PKG_SUPPORTED_OPTIONS=	pic flambda
PKG_SUGGESTED_OPTIONS=	pic
PLIST_VARS+=	pic flambda ocaml-native

.include "../../mk/bsd.prefs.mk"
.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mpic)
CONFIGURE_ARGS+=	--with-pic
.else
CONFIGURE_ARGS+=	--without-pic
.endif

.if !empty(PKG_OPTIONS:Mflambda)
CONFIGURE_ARGS+=	--enable-flambda
.else
CONFIGURE_ARGS+=	--disable-flambda
.endif
