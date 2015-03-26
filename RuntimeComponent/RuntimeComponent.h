

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0611 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for C:\Users\drono\AppData\Local\Temp\RuntimeComponent.idl-22deabb9:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0611 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RuntimeComponent_h__
#define __RuntimeComponent_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(__cplusplus)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
#endif


/* Forward Declarations */ 

#ifndef ____x_ABI_CRuntimeComponent_CITestClassFactory_FWD_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClassFactory_FWD_DEFINED__
typedef interface __x_ABI_CRuntimeComponent_CITestClassFactory __x_ABI_CRuntimeComponent_CITestClassFactory;

#ifdef __cplusplus
namespace ABI {
    namespace RuntimeComponent {
        interface ITestClassFactory;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CRuntimeComponent_CITestClassFactory_FWD_DEFINED__ */


#ifndef ____x_ABI_CRuntimeComponent_CITestClassStatics_FWD_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClassStatics_FWD_DEFINED__
typedef interface __x_ABI_CRuntimeComponent_CITestClassStatics __x_ABI_CRuntimeComponent_CITestClassStatics;

#ifdef __cplusplus
namespace ABI {
    namespace RuntimeComponent {
        interface ITestClassStatics;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CRuntimeComponent_CITestClassStatics_FWD_DEFINED__ */


#ifndef ____x_ABI_CRuntimeComponent_CITestClass_FWD_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClass_FWD_DEFINED__
typedef interface __x_ABI_CRuntimeComponent_CITestClass __x_ABI_CRuntimeComponent_CITestClass;

#ifdef __cplusplus
namespace ABI {
    namespace RuntimeComponent {
        interface ITestClass;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CRuntimeComponent_CITestClass_FWD_DEFINED__ */


#ifndef ____x_ABI_CRuntimeComponent_CITestClass2_FWD_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClass2_FWD_DEFINED__
typedef interface __x_ABI_CRuntimeComponent_CITestClass2 __x_ABI_CRuntimeComponent_CITestClass2;

#ifdef __cplusplus
namespace ABI {
    namespace RuntimeComponent {
        interface ITestClass2;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CRuntimeComponent_CITestClass2_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"
#include "Windows.ApplicationModel.Background.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_RuntimeComponent_0000_0000 */
/* [local] */ 

#ifdef __cplusplus
namespace ABI {
namespace RuntimeComponent {
class TestClass;
} /*RuntimeComponent*/
}
#endif

#if !defined(____x_ABI_CRuntimeComponent_CITestClassFactory_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_RuntimeComponent_ITestClassFactory[] = L"RuntimeComponent.ITestClassFactory";
#endif /* !defined(____x_ABI_CRuntimeComponent_CITestClassFactory_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_RuntimeComponent_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CRuntimeComponent_CITestClassFactory_INTERFACE_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClassFactory_INTERFACE_DEFINED__

/* interface __x_ABI_CRuntimeComponent_CITestClassFactory */
/* [uuid][object] */ 



/* interface ABI::RuntimeComponent::ITestClassFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CRuntimeComponent_CITestClassFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace RuntimeComponent {
            
            MIDL_INTERFACE("aba6712e-a962-458c-8f2c-31617488a320")
            ITestClassFactory : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE ActivateInstanceInt( 
                    /* [in] */ INT32 value,
                    /* [out][retval] */ ABI::RuntimeComponent::ITestClass **result) = 0;
                
                virtual HRESULT STDMETHODCALLTYPE ActivateInstanceIntInt( 
                    /* [in] */ INT32 value,
                    /* [in] */ INT32 power,
                    /* [out][retval] */ ABI::RuntimeComponent::ITestClass **result) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ITestClassFactory = __uuidof(ITestClassFactory);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CRuntimeComponent_CITestClassFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateInstanceInt )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [in] */ INT32 value,
            /* [out][retval] */ __x_ABI_CRuntimeComponent_CITestClass **result);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateInstanceIntInt )( 
            __x_ABI_CRuntimeComponent_CITestClassFactory * This,
            /* [in] */ INT32 value,
            /* [in] */ INT32 power,
            /* [out][retval] */ __x_ABI_CRuntimeComponent_CITestClass **result);
        
        END_INTERFACE
    } __x_ABI_CRuntimeComponent_CITestClassFactoryVtbl;

    interface __x_ABI_CRuntimeComponent_CITestClassFactory
    {
        CONST_VTBL struct __x_ABI_CRuntimeComponent_CITestClassFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CRuntimeComponent_CITestClassFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CRuntimeComponent_CITestClassFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CRuntimeComponent_CITestClassFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CRuntimeComponent_CITestClassFactory_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CRuntimeComponent_CITestClassFactory_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CRuntimeComponent_CITestClassFactory_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CRuntimeComponent_CITestClassFactory_ActivateInstanceInt(This,value,result)	\
    ( (This)->lpVtbl -> ActivateInstanceInt(This,value,result) ) 

#define __x_ABI_CRuntimeComponent_CITestClassFactory_ActivateInstanceIntInt(This,value,power,result)	\
    ( (This)->lpVtbl -> ActivateInstanceIntInt(This,value,power,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CRuntimeComponent_CITestClassFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_RuntimeComponent_0000_0001 */
/* [local] */ 

#if !defined(____x_ABI_CRuntimeComponent_CITestClassStatics_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_RuntimeComponent_ITestClassStatics[] = L"RuntimeComponent.ITestClassStatics";
#endif /* !defined(____x_ABI_CRuntimeComponent_CITestClassStatics_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_RuntimeComponent_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0001_v0_0_s_ifspec;

#ifndef ____x_ABI_CRuntimeComponent_CITestClassStatics_INTERFACE_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClassStatics_INTERFACE_DEFINED__

/* interface __x_ABI_CRuntimeComponent_CITestClassStatics */
/* [uuid][object] */ 



/* interface ABI::RuntimeComponent::ITestClassStatics */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CRuntimeComponent_CITestClassStatics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace RuntimeComponent {
            
            MIDL_INTERFACE("9d179c2b-28e9-46b2-b9fa-3c2fadb840a4")
            ITestClassStatics : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE TryUnload( void) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ITestClassStatics = __uuidof(ITestClassStatics);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CRuntimeComponent_CITestClassStaticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *TryUnload )( 
            __x_ABI_CRuntimeComponent_CITestClassStatics * This);
        
        END_INTERFACE
    } __x_ABI_CRuntimeComponent_CITestClassStaticsVtbl;

    interface __x_ABI_CRuntimeComponent_CITestClassStatics
    {
        CONST_VTBL struct __x_ABI_CRuntimeComponent_CITestClassStaticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CRuntimeComponent_CITestClassStatics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CRuntimeComponent_CITestClassStatics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CRuntimeComponent_CITestClassStatics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CRuntimeComponent_CITestClassStatics_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CRuntimeComponent_CITestClassStatics_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CRuntimeComponent_CITestClassStatics_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CRuntimeComponent_CITestClassStatics_TryUnload(This)	\
    ( (This)->lpVtbl -> TryUnload(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CRuntimeComponent_CITestClassStatics_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_RuntimeComponent_0000_0002 */
/* [local] */ 

#if !defined(____x_ABI_CRuntimeComponent_CITestClass_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_RuntimeComponent_ITestClass[] = L"RuntimeComponent.ITestClass";
#endif /* !defined(____x_ABI_CRuntimeComponent_CITestClass_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_RuntimeComponent_0000_0002 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0002_v0_0_s_ifspec;

#ifndef ____x_ABI_CRuntimeComponent_CITestClass_INTERFACE_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClass_INTERFACE_DEFINED__

/* interface __x_ABI_CRuntimeComponent_CITestClass */
/* [uuid][object] */ 



/* interface ABI::RuntimeComponent::ITestClass */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CRuntimeComponent_CITestClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace RuntimeComponent {
            
            MIDL_INTERFACE("67214cd3-3c60-4844-aa3b-a234f99f3c47")
            ITestClass : public IInspectable
            {
            public:
                virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Int( 
                    /* [out][retval] */ INT32 *result) = 0;
                
                virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Str( 
                    /* [out][retval] */ HSTRING *result) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ITestClass = __uuidof(ITestClass);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CRuntimeComponent_CITestClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CRuntimeComponent_CITestClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CRuntimeComponent_CITestClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Int )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [out][retval] */ INT32 *result);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Str )( 
            __x_ABI_CRuntimeComponent_CITestClass * This,
            /* [out][retval] */ HSTRING *result);
        
        END_INTERFACE
    } __x_ABI_CRuntimeComponent_CITestClassVtbl;

    interface __x_ABI_CRuntimeComponent_CITestClass
    {
        CONST_VTBL struct __x_ABI_CRuntimeComponent_CITestClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CRuntimeComponent_CITestClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CRuntimeComponent_CITestClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CRuntimeComponent_CITestClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CRuntimeComponent_CITestClass_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CRuntimeComponent_CITestClass_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CRuntimeComponent_CITestClass_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CRuntimeComponent_CITestClass_get_Int(This,result)	\
    ( (This)->lpVtbl -> get_Int(This,result) ) 

#define __x_ABI_CRuntimeComponent_CITestClass_get_Str(This,result)	\
    ( (This)->lpVtbl -> get_Str(This,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CRuntimeComponent_CITestClass_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_RuntimeComponent_0000_0003 */
/* [local] */ 

#if !defined(____x_ABI_CRuntimeComponent_CITestClass2_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_RuntimeComponent_ITestClass2[] = L"RuntimeComponent.ITestClass2";
#endif /* !defined(____x_ABI_CRuntimeComponent_CITestClass2_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_RuntimeComponent_0000_0003 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0003_v0_0_s_ifspec;

#ifndef ____x_ABI_CRuntimeComponent_CITestClass2_INTERFACE_DEFINED__
#define ____x_ABI_CRuntimeComponent_CITestClass2_INTERFACE_DEFINED__

/* interface __x_ABI_CRuntimeComponent_CITestClass2 */
/* [uuid][object] */ 



/* interface ABI::RuntimeComponent::ITestClass2 */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CRuntimeComponent_CITestClass2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace RuntimeComponent {
            
            MIDL_INTERFACE("67214cd3-3c60-4844-aa3b-a234f99f3c49")
            ITestClass2 : public IInspectable
            {
            public:
                virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Long( 
                    /* [out][retval] */ INT64 *result) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ITestClass2 = __uuidof(ITestClass2);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CRuntimeComponent_CITestClass2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Long )( 
            __x_ABI_CRuntimeComponent_CITestClass2 * This,
            /* [out][retval] */ INT64 *result);
        
        END_INTERFACE
    } __x_ABI_CRuntimeComponent_CITestClass2Vtbl;

    interface __x_ABI_CRuntimeComponent_CITestClass2
    {
        CONST_VTBL struct __x_ABI_CRuntimeComponent_CITestClass2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CRuntimeComponent_CITestClass2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CRuntimeComponent_CITestClass2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CRuntimeComponent_CITestClass2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CRuntimeComponent_CITestClass2_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CRuntimeComponent_CITestClass2_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CRuntimeComponent_CITestClass2_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CRuntimeComponent_CITestClass2_get_Long(This,result)	\
    ( (This)->lpVtbl -> get_Long(This,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CRuntimeComponent_CITestClass2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_RuntimeComponent_0000_0004 */
/* [local] */ 

#ifndef RUNTIMECLASS_RuntimeComponent_TestClass_DEFINED
#define RUNTIMECLASS_RuntimeComponent_TestClass_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_RuntimeComponent_TestClass[] = L"RuntimeComponent.TestClass";
#endif


/* interface __MIDL_itf_RuntimeComponent_0000_0004 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RuntimeComponent_0000_0004_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HSTRING_UserSize(     unsigned long *, unsigned long            , HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserMarshal(  unsigned long *, unsigned char *, HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserUnmarshal(unsigned long *, unsigned char *, HSTRING * ); 
void                      __RPC_USER  HSTRING_UserFree(     unsigned long *, HSTRING * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


