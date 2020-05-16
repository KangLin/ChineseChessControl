

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ChineseChessControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ChineseChessControlidl_h__
#define __ChineseChessControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DChineseChessControl_FWD_DEFINED__
#define ___DChineseChessControl_FWD_DEFINED__
typedef interface _DChineseChessControl _DChineseChessControl;

#endif 	/* ___DChineseChessControl_FWD_DEFINED__ */


#ifndef ___DChineseChessControlEvents_FWD_DEFINED__
#define ___DChineseChessControlEvents_FWD_DEFINED__
typedef interface _DChineseChessControlEvents _DChineseChessControlEvents;

#endif 	/* ___DChineseChessControlEvents_FWD_DEFINED__ */


#ifndef __ChineseChessControl_FWD_DEFINED__
#define __ChineseChessControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChineseChessControl ChineseChessControl;
#else
typedef struct ChineseChessControl ChineseChessControl;
#endif /* __cplusplus */

#endif 	/* __ChineseChessControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ChineseChessControl_0000_0000 */
/* [local] */ 

#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#pragma warning(pop)
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_ChineseChessControl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ChineseChessControl_0000_0000_v0_0_s_ifspec;


#ifndef __ChineseChessControlLib_LIBRARY_DEFINED__
#define __ChineseChessControlLib_LIBRARY_DEFINED__

/* library ChineseChessControlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_ChineseChessControlLib;

#ifndef ___DChineseChessControl_DISPINTERFACE_DEFINED__
#define ___DChineseChessControl_DISPINTERFACE_DEFINED__

/* dispinterface _DChineseChessControl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DChineseChessControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("c66fbdae-fb51-4fb8-b6bc-cd2cbe461bb7")
    _DChineseChessControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DChineseChessControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DChineseChessControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DChineseChessControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DChineseChessControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DChineseChessControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DChineseChessControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DChineseChessControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DChineseChessControl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DChineseChessControlVtbl;

    interface _DChineseChessControl
    {
        CONST_VTBL struct _DChineseChessControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DChineseChessControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DChineseChessControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DChineseChessControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DChineseChessControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DChineseChessControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DChineseChessControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DChineseChessControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DChineseChessControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DChineseChessControlEvents_DISPINTERFACE_DEFINED__
#define ___DChineseChessControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DChineseChessControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DChineseChessControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6757238f-9836-4b8a-9c13-0acc7d6607b5")
    _DChineseChessControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DChineseChessControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DChineseChessControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DChineseChessControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DChineseChessControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DChineseChessControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DChineseChessControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DChineseChessControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DChineseChessControlEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DChineseChessControlEventsVtbl;

    interface _DChineseChessControlEvents
    {
        CONST_VTBL struct _DChineseChessControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DChineseChessControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DChineseChessControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DChineseChessControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DChineseChessControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DChineseChessControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DChineseChessControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DChineseChessControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DChineseChessControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ChineseChessControl;

#ifdef __cplusplus

class DECLSPEC_UUID("23ac49d1-f4fe-4ab0-b5a3-bb3cb22dfed0")
ChineseChessControl;
#endif
#endif /* __ChineseChessControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


