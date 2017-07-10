// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME UVeventDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TPoly3.h"
#include "TOnePadDisplay.h"
#include "TBandedLE.h"
#include "TZigZag.h"
#include "TSplineFit.h"
#include "Calibration.h"
#include "UVevent.h"
#include "Analysis.h"
#include "Parameter.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TPoly3(void *p = 0);
   static void *newArray_TPoly3(Long_t size, void *p);
   static void delete_TPoly3(void *p);
   static void deleteArray_TPoly3(void *p);
   static void destruct_TPoly3(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TPoly3*)
   {
      ::TPoly3 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TPoly3 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TPoly3", ::TPoly3::Class_Version(), "TPoly3.h", 10,
                  typeid(::TPoly3), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TPoly3::Dictionary, isa_proxy, 4,
                  sizeof(::TPoly3) );
      instance.SetNew(&new_TPoly3);
      instance.SetNewArray(&newArray_TPoly3);
      instance.SetDelete(&delete_TPoly3);
      instance.SetDeleteArray(&deleteArray_TPoly3);
      instance.SetDestructor(&destruct_TPoly3);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TPoly3*)
   {
      return GenerateInitInstanceLocal((::TPoly3*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TPoly3*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TOnePadDisplay(void *p = 0);
   static void *newArray_TOnePadDisplay(Long_t size, void *p);
   static void delete_TOnePadDisplay(void *p);
   static void deleteArray_TOnePadDisplay(void *p);
   static void destruct_TOnePadDisplay(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TOnePadDisplay*)
   {
      ::TOnePadDisplay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TOnePadDisplay >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TOnePadDisplay", ::TOnePadDisplay::Class_Version(), "TOnePadDisplay.h", 7,
                  typeid(::TOnePadDisplay), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TOnePadDisplay::Dictionary, isa_proxy, 4,
                  sizeof(::TOnePadDisplay) );
      instance.SetNew(&new_TOnePadDisplay);
      instance.SetNewArray(&newArray_TOnePadDisplay);
      instance.SetDelete(&delete_TOnePadDisplay);
      instance.SetDeleteArray(&deleteArray_TOnePadDisplay);
      instance.SetDestructor(&destruct_TOnePadDisplay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TOnePadDisplay*)
   {
      return GenerateInitInstanceLocal((::TOnePadDisplay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TOnePadDisplay*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TBandedLE(void *p = 0);
   static void *newArray_TBandedLE(Long_t size, void *p);
   static void delete_TBandedLE(void *p);
   static void deleteArray_TBandedLE(void *p);
   static void destruct_TBandedLE(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TBandedLE*)
   {
      ::TBandedLE *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TBandedLE >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TBandedLE", ::TBandedLE::Class_Version(), "TBandedLE.h", 6,
                  typeid(::TBandedLE), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TBandedLE::Dictionary, isa_proxy, 4,
                  sizeof(::TBandedLE) );
      instance.SetNew(&new_TBandedLE);
      instance.SetNewArray(&newArray_TBandedLE);
      instance.SetDelete(&delete_TBandedLE);
      instance.SetDeleteArray(&deleteArray_TBandedLE);
      instance.SetDestructor(&destruct_TBandedLE);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TBandedLE*)
   {
      return GenerateInitInstanceLocal((::TBandedLE*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TBandedLE*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TZigZag(void *p = 0);
   static void *newArray_TZigZag(Long_t size, void *p);
   static void delete_TZigZag(void *p);
   static void deleteArray_TZigZag(void *p);
   static void destruct_TZigZag(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TZigZag*)
   {
      ::TZigZag *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TZigZag >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TZigZag", ::TZigZag::Class_Version(), "TZigZag.h", 7,
                  typeid(::TZigZag), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TZigZag::Dictionary, isa_proxy, 4,
                  sizeof(::TZigZag) );
      instance.SetNew(&new_TZigZag);
      instance.SetNewArray(&newArray_TZigZag);
      instance.SetDelete(&delete_TZigZag);
      instance.SetDeleteArray(&deleteArray_TZigZag);
      instance.SetDestructor(&destruct_TZigZag);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TZigZag*)
   {
      return GenerateInitInstanceLocal((::TZigZag*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TZigZag*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TSplineFit(void *p = 0);
   static void *newArray_TSplineFit(Long_t size, void *p);
   static void delete_TSplineFit(void *p);
   static void deleteArray_TSplineFit(void *p);
   static void destruct_TSplineFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSplineFit*)
   {
      ::TSplineFit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSplineFit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSplineFit", ::TSplineFit::Class_Version(), "TSplineFit.h", 23,
                  typeid(::TSplineFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSplineFit::Dictionary, isa_proxy, 4,
                  sizeof(::TSplineFit) );
      instance.SetNew(&new_TSplineFit);
      instance.SetNewArray(&newArray_TSplineFit);
      instance.SetDelete(&delete_TSplineFit);
      instance.SetDeleteArray(&deleteArray_TSplineFit);
      instance.SetDestructor(&destruct_TSplineFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSplineFit*)
   {
      return GenerateInitInstanceLocal((::TSplineFit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSplineFit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *Calibration_Dictionary();
   static void Calibration_TClassManip(TClass*);
   static void *new_Calibration(void *p = 0);
   static void *newArray_Calibration(Long_t size, void *p);
   static void delete_Calibration(void *p);
   static void deleteArray_Calibration(void *p);
   static void destruct_Calibration(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Calibration*)
   {
      ::Calibration *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Calibration));
      static ::ROOT::TGenericClassInfo 
         instance("Calibration", "Calibration.h", 35,
                  typeid(::Calibration), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Calibration_Dictionary, isa_proxy, 4,
                  sizeof(::Calibration) );
      instance.SetNew(&new_Calibration);
      instance.SetNewArray(&newArray_Calibration);
      instance.SetDelete(&delete_Calibration);
      instance.SetDeleteArray(&deleteArray_Calibration);
      instance.SetDestructor(&destruct_Calibration);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Calibration*)
   {
      return GenerateInitInstanceLocal((::Calibration*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Calibration*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Calibration_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Calibration*)0x0)->GetClass();
      Calibration_TClassManip(theClass);
   return theClass;
   }

   static void Calibration_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_UVevent(void *p = 0);
   static void *newArray_UVevent(Long_t size, void *p);
   static void delete_UVevent(void *p);
   static void deleteArray_UVevent(void *p);
   static void destruct_UVevent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UVevent*)
   {
      ::UVevent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::UVevent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("UVevent", ::UVevent::Class_Version(), "UVevent.h", 19,
                  typeid(::UVevent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::UVevent::Dictionary, isa_proxy, 4,
                  sizeof(::UVevent) );
      instance.SetNew(&new_UVevent);
      instance.SetNewArray(&newArray_UVevent);
      instance.SetDelete(&delete_UVevent);
      instance.SetDeleteArray(&deleteArray_UVevent);
      instance.SetDestructor(&destruct_UVevent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UVevent*)
   {
      return GenerateInitInstanceLocal((::UVevent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UVevent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Waveform(void *p = 0);
   static void *newArray_Waveform(Long_t size, void *p);
   static void delete_Waveform(void *p);
   static void deleteArray_Waveform(void *p);
   static void destruct_Waveform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Waveform*)
   {
      ::Waveform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Waveform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Waveform", ::Waveform::Class_Version(), "UVevent.h", 64,
                  typeid(::Waveform), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Waveform::Dictionary, isa_proxy, 4,
                  sizeof(::Waveform) );
      instance.SetNew(&new_Waveform);
      instance.SetNewArray(&newArray_Waveform);
      instance.SetDelete(&delete_Waveform);
      instance.SetDeleteArray(&deleteArray_Waveform);
      instance.SetDestructor(&destruct_Waveform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Waveform*)
   {
      return GenerateInitInstanceLocal((::Waveform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Waveform*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *Analysis_Dictionary();
   static void Analysis_TClassManip(TClass*);
   static void *new_Analysis(void *p = 0);
   static void *newArray_Analysis(Long_t size, void *p);
   static void delete_Analysis(void *p);
   static void deleteArray_Analysis(void *p);
   static void destruct_Analysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Analysis*)
   {
      ::Analysis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Analysis));
      static ::ROOT::TGenericClassInfo 
         instance("Analysis", "Analysis.h", 37,
                  typeid(::Analysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Analysis_Dictionary, isa_proxy, 4,
                  sizeof(::Analysis) );
      instance.SetNew(&new_Analysis);
      instance.SetNewArray(&newArray_Analysis);
      instance.SetDelete(&delete_Analysis);
      instance.SetDeleteArray(&deleteArray_Analysis);
      instance.SetDestructor(&destruct_Analysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Analysis*)
   {
      return GenerateInitInstanceLocal((::Analysis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Analysis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Analysis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Analysis*)0x0)->GetClass();
      Analysis_TClassManip(theClass);
   return theClass;
   }

   static void Analysis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Parameter_Dictionary();
   static void Parameter_TClassManip(TClass*);
   static void *new_Parameter(void *p = 0);
   static void *newArray_Parameter(Long_t size, void *p);
   static void delete_Parameter(void *p);
   static void deleteArray_Parameter(void *p);
   static void destruct_Parameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Parameter*)
   {
      ::Parameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Parameter));
      static ::ROOT::TGenericClassInfo 
         instance("Parameter", "Parameter.h", 37,
                  typeid(::Parameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Parameter_Dictionary, isa_proxy, 4,
                  sizeof(::Parameter) );
      instance.SetNew(&new_Parameter);
      instance.SetNewArray(&newArray_Parameter);
      instance.SetDelete(&delete_Parameter);
      instance.SetDeleteArray(&deleteArray_Parameter);
      instance.SetDestructor(&destruct_Parameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Parameter*)
   {
      return GenerateInitInstanceLocal((::Parameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Parameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Parameter_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Parameter*)0x0)->GetClass();
      Parameter_TClassManip(theClass);
   return theClass;
   }

   static void Parameter_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TPoly3::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TPoly3::Class_Name()
{
   return "TPoly3";
}

//______________________________________________________________________________
const char *TPoly3::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TPoly3*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TPoly3::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TPoly3*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TPoly3::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TPoly3*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TPoly3::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TPoly3*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TOnePadDisplay::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TOnePadDisplay::Class_Name()
{
   return "TOnePadDisplay";
}

//______________________________________________________________________________
const char *TOnePadDisplay::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOnePadDisplay*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TOnePadDisplay::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOnePadDisplay*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TOnePadDisplay::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOnePadDisplay*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TOnePadDisplay::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOnePadDisplay*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TBandedLE::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TBandedLE::Class_Name()
{
   return "TBandedLE";
}

//______________________________________________________________________________
const char *TBandedLE::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBandedLE*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TBandedLE::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBandedLE*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TBandedLE::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBandedLE*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TBandedLE::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBandedLE*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TZigZag::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TZigZag::Class_Name()
{
   return "TZigZag";
}

//______________________________________________________________________________
const char *TZigZag::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TZigZag*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TZigZag::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TZigZag*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TZigZag::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TZigZag*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TZigZag::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TZigZag*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TSplineFit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSplineFit::Class_Name()
{
   return "TSplineFit";
}

//______________________________________________________________________________
const char *TSplineFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSplineFit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSplineFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSplineFit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSplineFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSplineFit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSplineFit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSplineFit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr UVevent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *UVevent::Class_Name()
{
   return "UVevent";
}

//______________________________________________________________________________
const char *UVevent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UVevent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int UVevent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UVevent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *UVevent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UVevent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *UVevent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UVevent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Waveform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Waveform::Class_Name()
{
   return "Waveform";
}

//______________________________________________________________________________
const char *Waveform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Waveform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Waveform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Waveform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Waveform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Waveform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Waveform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Waveform*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TPoly3::Streamer(TBuffer &R__b)
{
   // Stream an object of class TPoly3.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TPoly3::Class(),this);
   } else {
      R__b.WriteClassBuffer(TPoly3::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TPoly3(void *p) {
      return  p ? new(p) ::TPoly3 : new ::TPoly3;
   }
   static void *newArray_TPoly3(Long_t nElements, void *p) {
      return p ? new(p) ::TPoly3[nElements] : new ::TPoly3[nElements];
   }
   // Wrapper around operator delete
   static void delete_TPoly3(void *p) {
      delete ((::TPoly3*)p);
   }
   static void deleteArray_TPoly3(void *p) {
      delete [] ((::TPoly3*)p);
   }
   static void destruct_TPoly3(void *p) {
      typedef ::TPoly3 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TPoly3

//______________________________________________________________________________
void TOnePadDisplay::Streamer(TBuffer &R__b)
{
   // Stream an object of class TOnePadDisplay.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TOnePadDisplay::Class(),this);
   } else {
      R__b.WriteClassBuffer(TOnePadDisplay::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TOnePadDisplay(void *p) {
      return  p ? new(p) ::TOnePadDisplay : new ::TOnePadDisplay;
   }
   static void *newArray_TOnePadDisplay(Long_t nElements, void *p) {
      return p ? new(p) ::TOnePadDisplay[nElements] : new ::TOnePadDisplay[nElements];
   }
   // Wrapper around operator delete
   static void delete_TOnePadDisplay(void *p) {
      delete ((::TOnePadDisplay*)p);
   }
   static void deleteArray_TOnePadDisplay(void *p) {
      delete [] ((::TOnePadDisplay*)p);
   }
   static void destruct_TOnePadDisplay(void *p) {
      typedef ::TOnePadDisplay current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TOnePadDisplay

//______________________________________________________________________________
void TBandedLE::Streamer(TBuffer &R__b)
{
   // Stream an object of class TBandedLE.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TBandedLE::Class(),this);
   } else {
      R__b.WriteClassBuffer(TBandedLE::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TBandedLE(void *p) {
      return  p ? new(p) ::TBandedLE : new ::TBandedLE;
   }
   static void *newArray_TBandedLE(Long_t nElements, void *p) {
      return p ? new(p) ::TBandedLE[nElements] : new ::TBandedLE[nElements];
   }
   // Wrapper around operator delete
   static void delete_TBandedLE(void *p) {
      delete ((::TBandedLE*)p);
   }
   static void deleteArray_TBandedLE(void *p) {
      delete [] ((::TBandedLE*)p);
   }
   static void destruct_TBandedLE(void *p) {
      typedef ::TBandedLE current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TBandedLE

//______________________________________________________________________________
void TZigZag::Streamer(TBuffer &R__b)
{
   // Stream an object of class TZigZag.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TZigZag::Class(),this);
   } else {
      R__b.WriteClassBuffer(TZigZag::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TZigZag(void *p) {
      return  p ? new(p) ::TZigZag : new ::TZigZag;
   }
   static void *newArray_TZigZag(Long_t nElements, void *p) {
      return p ? new(p) ::TZigZag[nElements] : new ::TZigZag[nElements];
   }
   // Wrapper around operator delete
   static void delete_TZigZag(void *p) {
      delete ((::TZigZag*)p);
   }
   static void deleteArray_TZigZag(void *p) {
      delete [] ((::TZigZag*)p);
   }
   static void destruct_TZigZag(void *p) {
      typedef ::TZigZag current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TZigZag

//______________________________________________________________________________
void TSplineFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSplineFit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSplineFit::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSplineFit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSplineFit(void *p) {
      return  p ? new(p) ::TSplineFit : new ::TSplineFit;
   }
   static void *newArray_TSplineFit(Long_t nElements, void *p) {
      return p ? new(p) ::TSplineFit[nElements] : new ::TSplineFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSplineFit(void *p) {
      delete ((::TSplineFit*)p);
   }
   static void deleteArray_TSplineFit(void *p) {
      delete [] ((::TSplineFit*)p);
   }
   static void destruct_TSplineFit(void *p) {
      typedef ::TSplineFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSplineFit

namespace ROOT {
   // Wrappers around operator new
   static void *new_Calibration(void *p) {
      return  p ? new(p) ::Calibration : new ::Calibration;
   }
   static void *newArray_Calibration(Long_t nElements, void *p) {
      return p ? new(p) ::Calibration[nElements] : new ::Calibration[nElements];
   }
   // Wrapper around operator delete
   static void delete_Calibration(void *p) {
      delete ((::Calibration*)p);
   }
   static void deleteArray_Calibration(void *p) {
      delete [] ((::Calibration*)p);
   }
   static void destruct_Calibration(void *p) {
      typedef ::Calibration current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Calibration

//______________________________________________________________________________
void UVevent::Streamer(TBuffer &R__b)
{
   // Stream an object of class UVevent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(UVevent::Class(),this);
   } else {
      R__b.WriteClassBuffer(UVevent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_UVevent(void *p) {
      return  p ? new(p) ::UVevent : new ::UVevent;
   }
   static void *newArray_UVevent(Long_t nElements, void *p) {
      return p ? new(p) ::UVevent[nElements] : new ::UVevent[nElements];
   }
   // Wrapper around operator delete
   static void delete_UVevent(void *p) {
      delete ((::UVevent*)p);
   }
   static void deleteArray_UVevent(void *p) {
      delete [] ((::UVevent*)p);
   }
   static void destruct_UVevent(void *p) {
      typedef ::UVevent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UVevent

//______________________________________________________________________________
void Waveform::Streamer(TBuffer &R__b)
{
   // Stream an object of class Waveform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Waveform::Class(),this);
   } else {
      R__b.WriteClassBuffer(Waveform::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Waveform(void *p) {
      return  p ? new(p) ::Waveform : new ::Waveform;
   }
   static void *newArray_Waveform(Long_t nElements, void *p) {
      return p ? new(p) ::Waveform[nElements] : new ::Waveform[nElements];
   }
   // Wrapper around operator delete
   static void delete_Waveform(void *p) {
      delete ((::Waveform*)p);
   }
   static void deleteArray_Waveform(void *p) {
      delete [] ((::Waveform*)p);
   }
   static void destruct_Waveform(void *p) {
      typedef ::Waveform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Waveform

namespace ROOT {
   // Wrappers around operator new
   static void *new_Analysis(void *p) {
      return  p ? new(p) ::Analysis : new ::Analysis;
   }
   static void *newArray_Analysis(Long_t nElements, void *p) {
      return p ? new(p) ::Analysis[nElements] : new ::Analysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_Analysis(void *p) {
      delete ((::Analysis*)p);
   }
   static void deleteArray_Analysis(void *p) {
      delete [] ((::Analysis*)p);
   }
   static void destruct_Analysis(void *p) {
      typedef ::Analysis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Analysis

namespace ROOT {
   // Wrappers around operator new
   static void *new_Parameter(void *p) {
      return  p ? new(p) ::Parameter : new ::Parameter;
   }
   static void *newArray_Parameter(Long_t nElements, void *p) {
      return p ? new(p) ::Parameter[nElements] : new ::Parameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_Parameter(void *p) {
      delete ((::Parameter*)p);
   }
   static void deleteArray_Parameter(void *p) {
      delete [] ((::Parameter*)p);
   }
   static void destruct_Parameter(void *p) {
      typedef ::Parameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Parameter

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_UVeventDict_Impl() {
    static const char* headers[] = {
"TPoly3.h",
"TOnePadDisplay.h",
"TBandedLE.h",
"TZigZag.h",
"TSplineFit.h",
"Calibration.h",
"UVevent.h",
"Analysis.h",
"Parameter.h",
0
    };
    static const char* includePaths[] = {
"/home/mhattawy/software/Root/build-root/include",
"/home/mhattawy/work/mcp-PMTs/MCPs_PHYs_HEP/mcpanalysis_v3/analysis/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "UVeventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Handling of 3rd order polynoms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TPoly3.h")))  TPoly3;
class __attribute__((annotate(R"ATTRDUMP(Class for displaying results on one pad)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TOnePadDisplay.h")))  TOnePadDisplay;
class __attribute__((annotate(R"ATTRDUMP(CERN program F406 DBEQN translated to C++)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TBandedLE.h")))  TBandedLE;
class __attribute__((annotate(R"ATTRDUMP(Labelling of points such that point i+1 always near from point i)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TZigZag.h")))  TZigZag;
class __attribute__((annotate(R"ATTRDUMP(General Handling of Spline fits)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TSplineFit.h")))  TSplineFit;
class __attribute__((annotate("$clingAutoload$Calibration.h")))  Calibration;
class __attribute__((annotate("$clingAutoload$UVevent.h")))  UVevent;
class __attribute__((annotate("$clingAutoload$UVevent.h")))  Waveform;
class __attribute__((annotate("$clingAutoload$Analysis.h")))  Analysis;
class __attribute__((annotate("$clingAutoload$Parameter.h")))  Parameter;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "UVeventDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TPoly3.h"
#include "TOnePadDisplay.h"
#include "TBandedLE.h"
#include "TZigZag.h"
#include "TSplineFit.h"
#include "Calibration.h"
#include "UVevent.h"
#include "Analysis.h"
#include "Parameter.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Analysis", payloadCode, "@",
"Calibration", payloadCode, "@",
"Parameter", payloadCode, "@",
"TBandedLE", payloadCode, "@",
"TOnePadDisplay", payloadCode, "@",
"TPoly3", payloadCode, "@",
"TSplineFit", payloadCode, "@",
"TZigZag", payloadCode, "@",
"UVevent", payloadCode, "@",
"Waveform", payloadCode, "@",
"gOneDisplay", payloadCode, "@",
"gSplineFit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("UVeventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_UVeventDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_UVeventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_UVeventDict() {
  TriggerDictionaryInitialization_UVeventDict_Impl();
}
