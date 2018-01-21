

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Jan 14 18:19:23 2011
 */
/* Compiler settings for .\MJPegCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MJPegCtrlidl_h__
#define __MJPegCtrlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMJPegCtrl_FWD_DEFINED__
#define ___DMJPegCtrl_FWD_DEFINED__
typedef interface _DMJPegCtrl _DMJPegCtrl;
#endif 	/* ___DMJPegCtrl_FWD_DEFINED__ */


#ifndef ___DMJPegCtrlEvents_FWD_DEFINED__
#define ___DMJPegCtrlEvents_FWD_DEFINED__
typedef interface _DMJPegCtrlEvents _DMJPegCtrlEvents;
#endif 	/* ___DMJPegCtrlEvents_FWD_DEFINED__ */


#ifndef __MJPegCtrl_FWD_DEFINED__
#define __MJPegCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MJPegCtrl MJPegCtrl;
#else
typedef struct MJPegCtrl MJPegCtrl;
#endif /* __cplusplus */

#endif 	/* __MJPegCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MJPegCtrlLib_LIBRARY_DEFINED__
#define __MJPegCtrlLib_LIBRARY_DEFINED__

/* library MJPegCtrlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_MJPegCtrlLib;

#ifndef ___DMJPegCtrl_DISPINTERFACE_DEFINED__
#define ___DMJPegCtrl_DISPINTERFACE_DEFINED__

/* dispinterface _DMJPegCtrl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DMJPegCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EC0AB74A-D271-4947-A737-B311F760A345")
    _DMJPegCtrl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMJPegCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMJPegCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMJPegCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMJPegCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMJPegCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMJPegCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMJPegCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMJPegCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMJPegCtrlVtbl;

    interface _DMJPegCtrl
    {
        CONST_VTBL struct _DMJPegCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMJPegCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMJPegCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMJPegCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMJPegCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMJPegCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMJPegCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMJPegCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMJPegCtrl_DISPINTERFACE_DEFINED__ */


#ifndef ___DMJPegCtrlEvents_DISPINTERFACE_DEFINED__
#define ___DMJPegCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMJPegCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DMJPegCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CC1A542C-D1BD-45F1-B596-912AF4048AD4")
    _DMJPegCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMJPegCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMJPegCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMJPegCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMJPegCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMJPegCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMJPegCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMJPegCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMJPegCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMJPegCtrlEventsVtbl;

    interface _DMJPegCtrlEvents
    {
        CONST_VTBL struct _DMJPegCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMJPegCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMJPegCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMJPegCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMJPegCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMJPegCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMJPegCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMJPegCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMJPegCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MJPegCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("26AE4DED-0D11-45A5-B3D4-3ACA21305850")
MJPegCtrl;
#endif
#endif /* __MJPegCtrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


