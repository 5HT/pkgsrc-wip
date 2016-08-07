$NetBSD$

--- src/VBox/Runtime/r0drv/netbsd/semeventmulti-r0drv-netbsd.c.orig	2016-08-07 02:47:37.581049530 +0000
+++ src/VBox/Runtime/r0drv/netbsd/semeventmulti-r0drv-netbsd.c
@@ -0,0 +1,320 @@
+/* : semeventmulti-r0drv-freebsd.c 57358 2015-08-14 15:16:38Z vboxsync $ */
+/** @file
+ * IPRT - Multiple Release Event Semaphores, Ring-0 Driver, FreeBSD.
+ */
+
+/*
+ * Copyright (c) 2007 knut st. osmundsen <bird-src-spam@anduin.net>
+ *
+ * Permission is hereby granted, free of charge, to any person
+ * obtaining a copy of this software and associated documentation
+ * files (the "Software"), to deal in the Software without
+ * restriction, including without limitation the rights to use,
+ * copy, modify, merge, publish, distribute, sublicense, and/or sell
+ * copies of the Software, and to permit persons to whom the
+ * Software is furnished to do so, subject to the following
+ * conditions:
+ *
+ * The above copyright notice and this permission notice shall be
+ * included in all copies or substantial portions of the Software.
+ *
+ * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
+ * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
+ * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
+ * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
+ * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
+ * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
+ * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
+ * OTHER DEALINGS IN THE SOFTWARE.
+ */
+
+
+/*********************************************************************************************************************************
+*   Header Files                                                                                                                 *
+*********************************************************************************************************************************/
+#define RTSEMEVENTMULTI_WITHOUT_REMAPPING
+#include "the-freebsd-kernel.h"
+#include "internal/iprt.h"
+#include <iprt/semaphore.h>
+
+#include <iprt/assert.h>
+#include <iprt/asm.h>
+#include <iprt/err.h>
+#include <iprt/mem.h>
+#include <iprt/lockvalidator.h>
+
+#include "sleepqueue-r0drv-freebsd.h"
+#include "internal/magics.h"
+
+
+/*********************************************************************************************************************************
+*   Defined Constants And Macros                                                                                                 *
+*********************************************************************************************************************************/
+/** @name fStateAndGen values
+ * @{ */
+/** The state bit number. */
+#define RTSEMEVENTMULTIBSD_STATE_BIT        0
+/** The state mask. */
+#define RTSEMEVENTMULTIBSD_STATE_MASK       RT_BIT_32(RTSEMEVENTMULTIBSD_STATE_BIT)
+/** The generation mask. */
+#define RTSEMEVENTMULTIBSD_GEN_MASK         ~RTSEMEVENTMULTIBSD_STATE_MASK
+/** The generation shift. */
+#define RTSEMEVENTMULTIBSD_GEN_SHIFT        1
+/** The initial variable value. */
+#define RTSEMEVENTMULTIBSD_STATE_GEN_INIT   UINT32_C(0xfffffffc)
+/** @}  */
+
+
+/*********************************************************************************************************************************
+*   Structures and Typedefs                                                                                                      *
+*********************************************************************************************************************************/
+/**
+ * FreeBSD multiple release event semaphore.
+ */
+typedef struct RTSEMEVENTMULTIINTERNAL
+{
+    /** Magic value (RTSEMEVENTMULTI_MAGIC). */
+    uint32_t volatile   u32Magic;
+    /** The object state bit and generation counter.
+     * The generation counter is incremented every time the object is
+     * signalled. */
+    uint32_t volatile   fStateAndGen;
+    /** Reference counter. */
+    uint32_t volatile   cRefs;
+} RTSEMEVENTMULTIINTERNAL, *PRTSEMEVENTMULTIINTERNAL;
+
+
+RTDECL(int)  RTSemEventMultiCreate(PRTSEMEVENTMULTI phEventMultiSem)
+{
+    return RTSemEventMultiCreateEx(phEventMultiSem, 0 /*fFlags*/, NIL_RTLOCKVALCLASS, NULL);
+}
+
+
+RTDECL(int)  RTSemEventMultiCreateEx(PRTSEMEVENTMULTI phEventMultiSem, uint32_t fFlags, RTLOCKVALCLASS hClass,
+                                     const char *pszNameFmt, ...)
+{
+    PRTSEMEVENTMULTIINTERNAL pThis;
+
+    AssertReturn(!(fFlags & ~RTSEMEVENTMULTI_FLAGS_NO_LOCK_VAL), VERR_INVALID_PARAMETER);
+    pThis = (PRTSEMEVENTMULTIINTERNAL)RTMemAlloc(sizeof(*pThis));
+    if (pThis)
+    {
+        pThis->u32Magic     = RTSEMEVENTMULTI_MAGIC;
+        pThis->fStateAndGen = RTSEMEVENTMULTIBSD_STATE_GEN_INIT;
+        pThis->cRefs        = 1;
+
+        *phEventMultiSem = pThis;
+        return VINF_SUCCESS;
+    }
+    return VERR_NO_MEMORY;
+}
+
+
+/**
+ * Retain a reference to the semaphore.
+ *
+ * @param   pThis       The semaphore.
+ */
+DECLINLINE(void) rtR0SemEventMultiBsdRetain(PRTSEMEVENTMULTIINTERNAL pThis)
+{
+    uint32_t cRefs = ASMAtomicIncU32(&pThis->cRefs);
+    Assert(cRefs && cRefs < 100000);
+}
+
+
+/**
+ * Release a reference, destroy the thing if necessary.
+ *
+ * @param   pThis       The semaphore.
+ */
+DECLINLINE(void) rtR0SemEventMultiBsdRelease(PRTSEMEVENTMULTIINTERNAL pThis)
+{
+    if (RT_UNLIKELY(ASMAtomicDecU32(&pThis->cRefs) == 0))
+    {
+        Assert(pThis->u32Magic != RTSEMEVENTMULTI_MAGIC);
+        RTMemFree(pThis);
+    }
+}
+
+
+RTDECL(int)  RTSemEventMultiDestroy(RTSEMEVENTMULTI hEventMultiSem)
+{
+    /*
+     * Validate input.
+     */
+    PRTSEMEVENTMULTIINTERNAL pThis = (PRTSEMEVENTMULTIINTERNAL)hEventMultiSem;
+    if (pThis == NIL_RTSEMEVENTMULTI)
+        return VINF_SUCCESS;
+    AssertPtrReturn(pThis, VERR_INVALID_PARAMETER);
+    AssertMsgReturn(pThis->u32Magic == RTSEMEVENTMULTI_MAGIC, ("%p u32Magic=%RX32\n", pThis, pThis->u32Magic), VERR_INVALID_PARAMETER);
+    Assert(pThis->cRefs > 0);
+
+    /*
+     * Invalidate it and signal the object just in case.
+     */
+    ASMAtomicWriteU32(&pThis->u32Magic, ~RTSEMEVENTMULTI_MAGIC);
+    ASMAtomicAndU32(&pThis->fStateAndGen, RTSEMEVENTMULTIBSD_GEN_MASK);
+    rtR0SemBsdBroadcast(pThis);
+    rtR0SemEventMultiBsdRelease(pThis);
+    return VINF_SUCCESS;
+}
+
+
+RTDECL(int)  RTSemEventMultiSignal(RTSEMEVENTMULTI hEventMultiSem)
+{
+    uint32_t fNew;
+    uint32_t fOld;
+
+    /*
+     * Validate input.
+     */
+    PRTSEMEVENTMULTIINTERNAL pThis = (PRTSEMEVENTMULTIINTERNAL)hEventMultiSem;
+    if (!pThis)
+        return VERR_INVALID_PARAMETER;
+    AssertPtrReturn(pThis, VERR_INVALID_PARAMETER);
+    AssertMsgReturn(pThis->u32Magic == RTSEMEVENTMULTI_MAGIC, ("%p u32Magic=%RX32\n", pThis, pThis->u32Magic), VERR_INVALID_PARAMETER);
+    rtR0SemEventMultiBsdRetain(pThis);
+
+    /*
+     * Signal the event object.  The cause of the parnoia here is racing to try
+     * deal with racing RTSemEventMultiSignal calls (should probably be
+     * forbidden, but it's relatively easy to handle).
+     */
+    do
+    {
+        fNew = fOld = ASMAtomicUoReadU32(&pThis->fStateAndGen);
+        fNew += 1 << RTSEMEVENTMULTIBSD_GEN_SHIFT;
+        fNew |= RTSEMEVENTMULTIBSD_STATE_MASK;
+    }
+    while (!ASMAtomicCmpXchgU32(&pThis->fStateAndGen, fNew, fOld));
+
+    rtR0SemBsdBroadcast(pThis);
+    rtR0SemEventMultiBsdRelease(pThis);
+    return VINF_SUCCESS;
+}
+
+
+RTDECL(int)  RTSemEventMultiReset(RTSEMEVENTMULTI hEventMultiSem)
+{
+    /*
+     * Validate input.
+     */
+    PRTSEMEVENTMULTIINTERNAL pThis = (PRTSEMEVENTMULTIINTERNAL)hEventMultiSem;
+    if (!pThis)
+        return VERR_INVALID_PARAMETER;
+    AssertPtrReturn(pThis, VERR_INVALID_PARAMETER);
+    AssertMsgReturn(pThis->u32Magic == RTSEMEVENTMULTI_MAGIC, ("%p u32Magic=%RX32\n", pThis, pThis->u32Magic), VERR_INVALID_PARAMETER);
+    rtR0SemEventMultiBsdRetain(pThis);
+
+    /*
+     * Reset it.
+     */
+    ASMAtomicAndU32(&pThis->fStateAndGen, ~RTSEMEVENTMULTIBSD_STATE_MASK);
+
+    rtR0SemEventMultiBsdRelease(pThis);
+    return VINF_SUCCESS;
+}
+
+
+/**
+ * Worker for RTSemEventMultiWaitEx and RTSemEventMultiWaitExDebug.
+ *
+ * @returns VBox status code.
+ * @param   pThis           The event semaphore.
+ * @param   fFlags          See RTSemEventMultiWaitEx.
+ * @param   uTimeout        See RTSemEventMultiWaitEx.
+ * @param   pSrcPos         The source code position of the wait.
+ */
+static int rtR0SemEventMultiBsdWait(PRTSEMEVENTMULTIINTERNAL pThis, uint32_t fFlags, uint64_t uTimeout,
+                                    PCRTLOCKVALSRCPOS pSrcPos)
+{
+    uint32_t    fOrgStateAndGen;
+    int         rc;
+
+    /*
+     * Validate the input.
+     */
+    AssertPtrReturn(pThis, VERR_INVALID_PARAMETER);
+    AssertMsgReturn(pThis->u32Magic == RTSEMEVENTMULTI_MAGIC, ("%p u32Magic=%RX32\n", pThis, pThis->u32Magic), VERR_INVALID_PARAMETER);
+    AssertReturn(RTSEMWAIT_FLAGS_ARE_VALID(fFlags), VERR_INVALID_PARAMETER);
+    rtR0SemEventMultiBsdRetain(pThis);
+
+    /*
+     * Is the event already signalled or do we have to wait?
+     */
+    fOrgStateAndGen = ASMAtomicUoReadU32(&pThis->fStateAndGen);
+    if (fOrgStateAndGen & RTSEMEVENTMULTIBSD_STATE_MASK)
+        rc = VINF_SUCCESS;
+    else
+    {
+        /*
+         * We have to wait.
+         */
+        RTR0SEMBSDSLEEP Wait;
+        rc = rtR0SemBsdWaitInit(&Wait, fFlags, uTimeout, pThis);
+        if (RT_SUCCESS(rc))
+        {
+            for (;;)
+            {
+                /* The destruction test. */
+                if (RT_UNLIKELY(pThis->u32Magic != RTSEMEVENTMULTI_MAGIC))
+                    rc = VERR_SEM_DESTROYED;
+                else
+                {
+                    rtR0SemBsdWaitPrepare(&Wait);
+
+                    /* Check the exit conditions. */
+                    if (RT_UNLIKELY(pThis->u32Magic != RTSEMEVENTMULTI_MAGIC))
+                        rc = VERR_SEM_DESTROYED;
+                    else if (ASMAtomicUoReadU32(&pThis->fStateAndGen) != fOrgStateAndGen)
+                        rc = VINF_SUCCESS;
+                    else if (rtR0SemBsdWaitHasTimedOut(&Wait))
+                        rc = VERR_TIMEOUT;
+                    else if (rtR0SemBsdWaitWasInterrupted(&Wait))
+                        rc = VERR_INTERRUPTED;
+                    else
+                    {
+                        /* Do the wait and then recheck the conditions. */
+                        rtR0SemBsdWaitDoIt(&Wait);
+                        continue;
+                    }
+                }
+                break;
+            }
+
+            rtR0SemBsdWaitDelete(&Wait);
+        }
+    }
+
+    rtR0SemEventMultiBsdRelease(pThis);
+    return rc;
+}
+
+
+RTDECL(int)  RTSemEventMultiWaitEx(RTSEMEVENTMULTI hEventMultiSem, uint32_t fFlags, uint64_t uTimeout)
+{
+#ifndef RTSEMEVENT_STRICT
+    return rtR0SemEventMultiBsdWait(hEventMultiSem, fFlags, uTimeout, NULL);
+#else
+    RTLOCKVALSRCPOS SrcPos = RTLOCKVALSRCPOS_INIT_NORMAL_API();
+    return rtR0SemEventMultiBsdWait(hEventMultiSem, fFlags, uTimeout, &SrcPos);
+#endif
+}
+RT_EXPORT_SYMBOL(RTSemEventMultiWaitEx);
+
+
+RTDECL(int)  RTSemEventMultiWaitExDebug(RTSEMEVENTMULTI hEventMultiSem, uint32_t fFlags, uint64_t uTimeout,
+                                        RTHCUINTPTR uId, RT_SRC_POS_DECL)
+{
+    RTLOCKVALSRCPOS SrcPos = RTLOCKVALSRCPOS_INIT_DEBUG_API();
+    return rtR0SemEventMultiBsdWait(hEventMultiSem, fFlags, uTimeout, &SrcPos);
+}
+RT_EXPORT_SYMBOL(RTSemEventMultiWaitExDebug);
+
+
+RTDECL(uint32_t) RTSemEventMultiGetResolution(void)
+{
+    return rtR0SemBsdWaitGetResolution();
+}
+RT_EXPORT_SYMBOL(RTSemEventMultiGetResolution);
+
