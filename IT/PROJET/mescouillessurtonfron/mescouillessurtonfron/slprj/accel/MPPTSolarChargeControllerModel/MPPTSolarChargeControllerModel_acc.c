#include <math.h>
#include "MPPTSolarChargeControllerModel_acc.h"
#include "MPPTSolarChargeControllerModel_acc_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T MPPTSolarChargeControllerModel_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T
numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ;
} testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay
<= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
MPPTSolarChargeControllerModel_acc_rt_TDelayInterpolate ( real_T tMinusDelay
, real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz , int_T *
lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T
discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout
, t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && (
tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart )
return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
SimStruct * S , void * diag ) { if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) {
_ssSet_slErrMsg ( S , diag ) ; } else { _ssDiscardDiagnostic ( S , diag ) ; }
} void rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag ) {
_ssReportDiagnosticAsWarning ( S , diag ) ; } static void mdlOutputs (
SimStruct * S , int_T tid ) { real_T B_11_90_0 ;
B_MPPTSolarChargeControllerModel_T * _rtB ;
DW_MPPTSolarChargeControllerModel_T * _rtDW ;
P_MPPTSolarChargeControllerModel_T * _rtP ;
PrevZCX_MPPTSolarChargeControllerModel_T * _rtZCE ;
X_MPPTSolarChargeControllerModel_T * _rtX ; real_T rtb_B_11_0_0 ; real_T
rtb_B_11_12_0 ; real_T rtb_B_11_15_0 ; real_T rtb_B_11_16_0 ; real_T
rtb_B_11_17_0 ; real_T rtb_B_11_1_0 ; real_T rtb_B_11_27_0 ; real_T
rtb_B_11_2_0 ; real_T rtb_B_11_33_0 ; real_T rtb_B_11_38_0 ; real_T
rtb_B_11_40_0 ; int32_T isHit ; boolean_T rtb_B_11_118_0 ; boolean_T
rtb_B_11_34_0 ; boolean_T rtb_B_11_99_0 ; boolean_T rtb_B_11_9_0 ;
ZCEventType zcEvent ; _rtDW = ( ( DW_MPPTSolarChargeControllerModel_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( (
PrevZCX_MPPTSolarChargeControllerModel_T * ) _ssGetPrevZCSigState ( S ) ) ;
_rtX = ( ( X_MPPTSolarChargeControllerModel_T * ) ssGetContStates ( S ) ) ;
_rtP = ( ( P_MPPTSolarChargeControllerModel_T * ) ssGetModelRtp ( S ) ) ;
_rtB = ( ( B_MPPTSolarChargeControllerModel_T * ) _ssGetModelBlockIO ( S ) )
; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_11_0_0 =
_rtDW -> itinit1_PreviousInput ; rtb_B_11_1_0 = _rtP -> P_62 * _rtDW ->
itinit1_PreviousInput ; rtb_B_11_2_0 = 1.000001 * rtb_B_11_1_0 *
0.96711798839458663 / 0.9999 ; } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_11_3_0 = _rtP -> P_63 * _rtDW ->
Currentfilter_states ; _rtB -> B_11_5_0 = ( _rtB -> B_11_3_0 >
MPPTSolarChargeControllerModel_rtC ( S ) -> B_11_0_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_6_0 = _rtDW ->
itinit_PreviousInput ; } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit !=
0 ) { if ( _rtDW -> inti_IC_LOADING != 0 ) { _rtDW -> inti_DSTATE = _rtB ->
B_11_6_0 ; if ( _rtDW -> inti_DSTATE >= _rtP -> P_68 ) { _rtDW -> inti_DSTATE
= _rtP -> P_68 ; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_69 ) { _rtDW
-> inti_DSTATE = _rtP -> P_69 ; } } } if ( ( _rtB -> B_11_5_0 > 0.0 ) && (
_rtDW -> inti_PrevResetState <= 0 ) ) { _rtDW -> inti_DSTATE = _rtB ->
B_11_6_0 ; if ( _rtDW -> inti_DSTATE >= _rtP -> P_68 ) { _rtDW -> inti_DSTATE
= _rtP -> P_68 ; } else { if ( _rtDW -> inti_DSTATE <= _rtP -> P_69 ) { _rtDW
-> inti_DSTATE = _rtP -> P_69 ; } } } if ( _rtDW -> inti_DSTATE >= _rtP ->
P_68 ) { _rtDW -> inti_DSTATE = _rtP -> P_68 ; } else { if ( _rtDW ->
inti_DSTATE <= _rtP -> P_69 ) { _rtDW -> inti_DSTATE = _rtP -> P_69 ; } }
_rtB -> B_11_8_0 = _rtP -> P_70 * _rtDW -> inti_DSTATE ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_11_9_0 = ( _rtB ->
B_11_8_0 > rtb_B_11_1_0 ) ; } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if (
isHit != 0 ) { if ( _rtB -> B_11_8_0 < _rtB -> B_11_5_0_c ) { _rtB ->
B_11_11_0 = _rtB -> B_11_5_0_c ; } else { _rtB -> B_11_11_0 = _rtB ->
B_11_8_0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
rtb_B_11_9_0 ) { rtb_B_11_12_0 = rtb_B_11_1_0 ; } else { rtb_B_11_12_0 = _rtB
-> B_11_11_0 ; } if ( rtb_B_11_2_0 <= rtb_B_11_12_0 ) { rtb_B_11_12_0 =
rtb_B_11_1_0 ; } rtb_B_11_15_0 = - 5.2689686539396151E-5 * rtb_B_11_0_0 / (
rtb_B_11_0_0 - rtb_B_11_12_0 ) * rtb_B_11_12_0 ; rtb_B_11_16_0 = - _rtB ->
B_11_5_0 * 5.2689686539396151e-5 * _rtB -> B_11_3_0 * rtb_B_11_0_0 / (
rtb_B_11_0_0 - rtb_B_11_12_0 ) ; rtb_B_11_17_0 = _rtP -> P_71 * rtb_B_11_0_0
; if ( ! ( _rtB -> B_11_8_0 > rtb_B_11_17_0 ) ) { rtb_B_11_1_0 = -
rtb_B_11_17_0 * 0.999 * 0.1 * 0.9999 ; if ( _rtB -> B_11_8_0 < rtb_B_11_1_0 )
{ rtb_B_11_17_0 = rtb_B_11_1_0 ; } else { rtb_B_11_17_0 = _rtB -> B_11_8_0 ;
} } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_11_22_0 = ( _rtB -> B_11_3_0 < MPPTSolarChargeControllerModel_rtC ( S ) ->
B_11_1_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
switch ( ( int32_T ) _rtB -> B_11_6_0_k ) { case 1 : rtb_B_11_27_0 = - ( _rtB
-> B_11_10_0 * _rtB -> B_11_22_0 ) * 5.2689686539396151e-5 * ( _rtB ->
B_11_10_0 * _rtB -> B_11_3_0 ) * ( 1881.8799999999951 / ( _rtB -> B_11_10_0 *
rtb_B_11_17_0 + 188.18799999999953 ) ) ; break ; case 2 : rtb_B_11_27_0 =
_rtB -> B_11_7_0 * rtb_B_11_0_0 ; rtb_B_11_27_0 = - ( _rtB -> B_11_7_0 * _rtB
-> B_11_22_0 ) * 5.2689686539396151e-5 * ( _rtB -> B_11_7_0 * _rtB ->
B_11_3_0 ) * rtb_B_11_27_0 / ( _rtB -> B_11_7_0 * rtb_B_11_17_0 +
rtb_B_11_27_0 * 0.1 ) ; break ; case 3 : rtb_B_11_27_0 = - ( _rtB -> B_11_9_0
* _rtB -> B_11_22_0 ) * 5.2689686539396151e-5 * ( _rtB -> B_11_9_0 * _rtB ->
B_11_3_0 ) * ( 1881.8799999999951 / ( muDoubleScalarAbs ( _rtB -> B_11_9_0 *
rtb_B_11_17_0 ) + 188.18799999999953 ) ) ; break ; default : rtb_B_11_27_0 =
- ( _rtB -> B_11_8_0_c * _rtB -> B_11_22_0 ) * 5.2689686539396151e-5 * ( _rtB
-> B_11_8_0_c * _rtB -> B_11_3_0 ) * ( 1881.8799999999951 / (
muDoubleScalarAbs ( _rtB -> B_11_8_0_c * rtb_B_11_17_0 ) + 188.18799999999953
) ) ; break ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_11_28_0 = _rtDW -> DiscreteTimeIntegrator_DSTATE ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { switch ( ( int32_T ) _rtB
-> B_11_11_0_b ) { case 1 : rtb_B_11_33_0 = _rtB -> B_11_28_0 ; break ; case
2 : if ( rtb_B_11_12_0 > _rtP -> P_52 ) { rtb_B_11_17_0 = _rtP -> P_52 ; }
else if ( rtb_B_11_12_0 < _rtP -> P_53 ) { rtb_B_11_17_0 = _rtP -> P_53 ; }
else { rtb_B_11_17_0 = rtb_B_11_12_0 ; } rtb_B_11_33_0 = muDoubleScalarExp (
- 0.033550520276183986 * rtb_B_11_17_0 ) * 1.0748923271905391 ; break ; case
3 : rtb_B_11_33_0 = _rtB -> B_11_28_0 ; break ; default : rtb_B_11_33_0 =
_rtB -> B_11_28_0 ; break ; } rtb_B_11_33_0 = ( ( ( ( rtb_B_11_15_0 +
rtb_B_11_16_0 ) + rtb_B_11_27_0 ) + rtb_B_11_33_0 ) + - 0.0 * rtb_B_11_12_0 )
+ _rtB -> B_11_2_0 ; rtb_B_11_34_0 = ( rtb_B_11_33_0 > _rtB -> B_11_3_0_m ) ;
} isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_35_0
= _rtDW -> Memory2_PreviousInput ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { if ( rtb_B_11_34_0 ) { _rtB -> B_11_37_0 = _rtB ->
B_11_3_0_m ; } else if ( rtb_B_11_33_0 < _rtB -> B_11_35_0 ) { _rtB ->
B_11_37_0 = _rtB -> B_11_35_0 ; } else { _rtB -> B_11_37_0 = rtb_B_11_33_0 ;
} } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { rtb_B_11_38_0 =
_rtDW -> Delay_x_DSTATE ; _rtB -> B_11_39_0 = _rtP -> P_76 * _rtDW ->
Delay_x_DSTATE ; rtb_B_11_40_0 = _rtDW -> Delay_x_DSTATE_g ; _rtB ->
B_11_41_0 = _rtP -> P_78 * _rtDW -> Delay_x_DSTATE_g ; } ssCallAccelRunBlock
( S , 11 , 42 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_11_43_0 = _rtB -> B_11_42_0
* _rtB -> B_11_1_0 ; _rtB -> B_11_44_0 = _rtP -> P_79 * _rtB -> B_11_43_0 ;
_rtB -> B_11_45_0 = _rtB -> B_11_24_0 * _rtB -> B_11_44_0 ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_47_0 = _rtB ->
B_11_54_0_m - _rtDW -> UnitDelay_DSTATE ; } ssCallAccelRunBlock ( S , 11 ,
_rtDW -> Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { rtb_B_11_0_0 = ( 1.0 - rtb_B_11_12_0 / ( _rtP -> P_81 * rtb_B_11_0_0 ) )
* 100.0 ; if ( rtb_B_11_0_0 > _rtP -> P_82 ) { _rtB -> B_11_51_0 = _rtP ->
P_82 ; } else if ( rtb_B_11_0_0 < _rtP -> P_83 ) { _rtB -> B_11_51_0 = _rtP
-> P_83 ; } else { _rtB -> B_11_51_0 = rtb_B_11_0_0 ; } } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_52_0 = _rtP ->
P_84 * _rtB -> B_0_7_0 [ 5 ] ; _rtB -> B_11_53_0 = _rtP -> P_85 * _rtB ->
B_11_52_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_11_54_0 = _rtB -> B_11_37_0 - _rtB -> B_11_53_0 ; ssCallAccelRunBlock (
S , 11 , 55 , SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 11 , 56 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0
) { _rtB -> B_11_66_0 = _rtB -> B_0_14_0 * _rtB -> B_0_10_0 ; }
ssCallAccelRunBlock ( S , 11 , 67 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S ,
11 , 68 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_11_81_0 = ( ( real_T ) ( _rtB ->
B_11_52_0 < MPPTSolarChargeControllerModel_rtC ( S ) -> B_11_2_0 ) * _rtP ->
P_86 - _rtB -> B_11_28_0 ) * muDoubleScalarAbs ( _rtB -> B_11_52_0 ) * _rtP
-> P_87 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_11_82_0 = _rtP -> P_88 * rtb_B_11_12_0 ; } isHit = ssIsSampleHit ( S , 3 ,
0 ) ; if ( isHit != 0 ) { _rtB -> B_11_83_0 = _rtP -> P_89 * _rtB ->
B_11_52_0 ; _rtB -> B_11_87_0 = muDoubleScalarAbs ( _rtB -> B_11_52_0 ) ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 11 , 88 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_11_89_0 = _rtX ->
integrator_CSTATE ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_91 ; B_11_90_0 =
MPPTSolarChargeControllerModel_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 ,
* tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_92 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_11_92_0 = _rtP -> P_93 ; } rtb_B_11_9_0 = ( ssGetT ( S ) >= _rtB ->
B_11_92_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_11_94_0 = _rtDW -> Memory_PreviousInput ; } if ( rtb_B_11_9_0 ) { _rtB
-> B_11_96_0 = ( _rtB -> B_11_89_0 - B_11_90_0 ) * _rtP -> P_54 ; } else {
_rtB -> B_11_96_0 = _rtB -> B_11_94_0 ; } _rtB -> B_11_97_0 = _rtP -> P_95 *
_rtB -> B_11_96_0 ; ssCallAccelRunBlock ( S , 11 , 98 , SS_CALL_MDL_OUTPUTS )
; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_11_99_0 = (
_rtB -> B_11_51_0 < _rtB -> B_11_16_0 ) ; } isHit = ssIsSampleHit ( S , 3 , 0
) ; if ( isHit != 0 ) { if ( _rtB -> B_11_66_0 - _rtDW -> PK1_DSTATE > _rtP
-> P_98 ) { if ( _rtB -> B_0_14_0 - _rtDW -> VK1_DSTATE > _rtP -> P_55 ) {
rtb_B_11_12_0 = _rtB -> B_11_14_0 ; } else { rtb_B_11_12_0 = _rtB ->
B_11_13_0 ; } } else if ( _rtB -> B_0_14_0 - _rtDW -> VK1_DSTATE > _rtP ->
P_56 ) { rtb_B_11_12_0 = _rtB -> B_11_13_0 ; } else { rtb_B_11_12_0 = _rtB ->
B_11_14_0 ; } rtb_B_11_0_0 = rtb_B_11_12_0 + _rtDW -> DK1_PreviousInput ; if
( rtb_B_11_0_0 > _rtP -> P_100 ) { _rtB -> B_11_109_0 = _rtP -> P_100 ; }
else if ( rtb_B_11_0_0 < _rtP -> P_101 ) { _rtB -> B_11_109_0 = _rtP -> P_101
; } else { _rtB -> B_11_109_0 = rtb_B_11_0_0 ; } } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_112_0 = ( real_T ) ( _rtB ->
B_11_54_0 <= _rtB -> B_11_15_0 ) * _rtB -> B_11_109_0 * ( real_T )
rtb_B_11_99_0 ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_EnableDisableFloatStage_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_EnableDisableFloatStage_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_11_112_0 + 0 ) ;
} } { if ( _rtDW -> TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK . AQHandles , ssGetTaskTime
( S , 1 ) , ( char * ) & _rtB -> B_11_97_0 + 0 ) ; } } } isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PK_at_outport_0_PWORK . AQHandles && ssGetLogOutput
( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PK_at_outport_0_PWORK . AQHandles , ssGetTaskTime (
S , 3 ) , ( char * ) & _rtB -> B_11_66_0 + 0 ) ; } } } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_117_0 = _rtB -> B_11_54_0 *
_rtB -> B_11_87_0 / _rtB -> B_11_66_0 ; rtb_B_11_118_0 = ( _rtB -> B_11_112_0
!= MPPTSolarChargeControllerModel_rtC ( S ) -> B_11_3_0 ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_120_0 = _rtP
-> P_102 ; } rtb_B_11_0_0 = ssGetT ( S ) + _rtB -> B_11_120_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_11_122_0 = _rtP
-> P_103 ; } _rtB -> B_11_124_0 = _rtP -> P_104 * muDoubleScalarRem (
rtb_B_11_0_0 , _rtB -> B_11_122_0 ) ; _rtB -> B_11_126_0 = ( ( 2.0 * _rtB ->
B_11_124_0 - 1.0 ) + 1.0 ) * 0.5 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode = ( _rtB -> B_11_112_0 >= _rtB -> B_11_126_0 ) ; }
_rtB -> B_11_129_0 = ( rtb_B_11_118_0 && _rtDW -> RelationalOperator_Mode ) ;
zcEvent = rt_ZCFcn ( ANY_ZERO_CROSSING , & _rtZCE -> HitCrossing_Input_ZCE ,
_rtB -> B_11_124_0 - _rtP -> P_105 ) ; if ( _rtDW -> HitCrossing_MODE == 0 )
{ if ( zcEvent != NO_ZCEVENT ) { _rtB -> B_11_130_0 = ! _rtB -> B_11_130_0 ;
_rtDW -> HitCrossing_MODE = 1 ; } else if ( _rtB -> B_11_130_0 ) { _rtB ->
B_11_130_0 = ( ( ! ( _rtB -> B_11_124_0 != _rtP -> P_105 ) ) && _rtB ->
B_11_130_0 ) ; } else { _rtB -> B_11_130_0 = ( ( _rtB -> B_11_124_0 == _rtP
-> P_105 ) || _rtB -> B_11_130_0 ) ; } } else { _rtB -> B_11_130_0 = ( ( ! (
_rtB -> B_11_124_0 != _rtP -> P_105 ) ) && _rtB -> B_11_130_0 ) ; _rtDW ->
HitCrossing_MODE = 0 ; } } isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_11_136_0 = _rtP -> P_106 * rtb_B_11_40_0 + _rtP -> P_107 *
_rtB -> B_0_8_0 ; _rtB -> B_11_142_0 = _rtP -> P_108 * rtb_B_11_38_0 + _rtP
-> P_109 * _rtB -> B_0_12_0 ; } ssCallAccelRunBlock ( S , 11 , 172 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID4 ( SimStruct * S , int_T tid ) {
B_MPPTSolarChargeControllerModel_T * _rtB ;
P_MPPTSolarChargeControllerModel_T * _rtP ; real_T rtb_B_11_18_0 ; real_T
rtb_B_11_33_0 ; _rtP = ( ( P_MPPTSolarChargeControllerModel_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_MPPTSolarChargeControllerModel_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_11_0_0 [ 0 ] = _rtP -> P_110 [ 0 ] ;
_rtB -> B_11_0_0 [ 1 ] = _rtP -> P_110 [ 1 ] ; _rtB -> B_11_0_0 [ 2 ] = _rtP
-> P_110 [ 2 ] ; _rtB -> B_11_0_0 [ 3 ] = _rtP -> P_110 [ 3 ] ; _rtB ->
B_11_1_0 = _rtP -> P_111 ; _rtB -> B_11_2_0 = _rtP -> P_112 ; _rtB ->
B_11_3_0_m = _rtP -> P_113 ; _rtB -> B_11_4_0 = _rtP -> P_114 ; _rtB ->
B_11_5_0_c = _rtP -> P_115 ; _rtB -> B_11_6_0_k = _rtP -> P_116 ; _rtB ->
B_11_7_0 = _rtP -> P_117 ; _rtB -> B_11_8_0_c = _rtP -> P_118 ; _rtB ->
B_11_9_0 = _rtP -> P_119 ; _rtB -> B_11_10_0 = _rtP -> P_120 ; _rtB ->
B_11_11_0_b = _rtP -> P_121 ; _rtB -> B_11_12_0 = _rtP -> P_122 ; _rtB ->
B_11_13_0 = _rtP -> P_123 ; _rtB -> B_11_14_0 = _rtP -> P_124 * _rtB ->
B_11_13_0 ; _rtB -> B_11_15_0 = _rtP -> P_125 ; _rtB -> B_11_16_0 = _rtP ->
P_126 ; rtb_B_11_18_0 = _rtB -> B_11_12_0 + _rtP -> P_127 ; _rtB -> B_11_24_0
= ( ( rtb_B_11_18_0 - _rtP -> P_128 ) * _rtP -> P_129 + _rtP -> P_130 ) *
_rtP -> P_131 ; _rtB -> B_11_25_0 = _rtP -> P_132 ; rtb_B_11_33_0 =
rtb_B_11_18_0 / _rtP -> P_137 ; _rtB -> B_11_41_0_p = muDoubleScalarExp (
_rtP -> P_139 - ( ( rtb_B_11_18_0 - _rtP -> P_134 ) * _rtP -> P_135 + _rtP ->
P_133 ) * _rtP -> P_136 / ( _rtP -> P_140 * rtb_B_11_18_0 ) ) * ( _rtP ->
P_138 * muDoubleScalarPower ( rtb_B_11_33_0 , 3.0 ) ) ; _rtB -> B_11_42_0_c =
_rtP -> P_141 ; _rtB -> B_11_43_0_f = _rtP -> P_142 ; _rtB -> B_11_44_0_g =
_rtP -> P_143 * rtb_B_11_33_0 ; _rtB -> B_11_45_0_g = _rtP -> P_144 ; if (
muDoubleScalarAbs ( _rtP -> P_146 ) > _rtP -> P_150 ) { rtb_B_11_18_0 = _rtP
-> P_146 ; } else if ( muDoubleScalarSign ( _rtP -> P_146 ) > _rtP -> P_149 )
{ rtb_B_11_18_0 = _rtP -> P_147 ; } else { rtb_B_11_18_0 = _rtP -> P_148 ; }
_rtB -> B_11_54_0_m = _rtP -> P_145 / rtb_B_11_18_0 ; _rtB -> B_11_55_0 =
_rtP -> P_151 ; _rtB -> B_11_56_0 = _rtP -> P_152 ; UNUSED_PARAMETER ( tid )
; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_MPPTSolarChargeControllerModel_T * _rtB ;
DW_MPPTSolarChargeControllerModel_T * _rtDW ;
P_MPPTSolarChargeControllerModel_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_MPPTSolarChargeControllerModel_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_MPPTSolarChargeControllerModel_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_MPPTSolarChargeControllerModel_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
itinit1_PreviousInput = _rtB -> B_11_4_0 ; } isHit = ssIsSampleHit ( S , 3 ,
0 ) ; if ( isHit != 0 ) { _rtDW -> Currentfilter_states = ( _rtB -> B_11_52_0
- _rtP -> P_64 [ 1 ] * _rtDW -> Currentfilter_states ) / _rtP -> P_64 [ 0 ] ;
} isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
itinit_PreviousInput = _rtB -> B_11_82_0 ; } isHit = ssIsSampleHit ( S , 3 ,
0 ) ; if ( isHit != 0 ) { _rtDW -> inti_IC_LOADING = 0U ; _rtDW ->
inti_DSTATE += _rtP -> P_67 * _rtB -> B_11_52_0 ; if ( _rtDW -> inti_DSTATE
>= _rtP -> P_68 ) { _rtDW -> inti_DSTATE = _rtP -> P_68 ; } else { if ( _rtDW
-> inti_DSTATE <= _rtP -> P_69 ) { _rtDW -> inti_DSTATE = _rtP -> P_69 ; } }
if ( _rtB -> B_11_5_0 > 0.0 ) { _rtDW -> inti_PrevResetState = 1 ; } else if
( _rtB -> B_11_5_0 < 0.0 ) { _rtDW -> inti_PrevResetState = - 1 ; } else if (
_rtB -> B_11_5_0 == 0.0 ) { _rtDW -> inti_PrevResetState = 0 ; } else { _rtDW
-> inti_PrevResetState = 2 ; } _rtDW -> DiscreteTimeIntegrator_DSTATE += _rtP
-> P_72 * _rtB -> B_11_81_0 ; _rtDW -> Memory2_PreviousInput = _rtB ->
B_11_83_0 ; _rtDW -> Delay_x_DSTATE = _rtB -> B_11_142_0 ; _rtDW ->
Delay_x_DSTATE_g = _rtB -> B_11_136_0 ; _rtDW -> UnitDelay_DSTATE = _rtB ->
B_11_54_0_m ; ssCallAccelRunBlock ( S , 0 , 7 , SS_CALL_MDL_UPDATE ) ; } {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
MPPTSolarChargeControllerModel_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_91 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_11_89_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW
-> Memory_PreviousInput = _rtB -> B_11_96_0 ; } isHit = ssIsSampleHit ( S , 3
, 0 ) ; if ( isHit != 0 ) { _rtDW -> VK1_DSTATE = _rtB -> B_0_14_0 ; _rtDW ->
PK1_DSTATE = _rtB -> B_11_66_0 ; _rtDW -> DK1_PreviousInput = _rtB ->
B_11_109_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID4 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
B_MPPTSolarChargeControllerModel_T * _rtB ;
XDot_MPPTSolarChargeControllerModel_T * _rtXdot ; _rtXdot = ( (
XDot_MPPTSolarChargeControllerModel_T * ) ssGetdX ( S ) ) ; _rtB = ( (
B_MPPTSolarChargeControllerModel_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot
-> integrator_CSTATE = _rtB -> B_11_117_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_MPPTSolarChargeControllerModel_T * _rtB ;
DW_MPPTSolarChargeControllerModel_T * _rtDW ;
P_MPPTSolarChargeControllerModel_T * _rtP ;
ZCV_MPPTSolarChargeControllerModel_T * _rtZCSV ; _rtDW = ( (
DW_MPPTSolarChargeControllerModel_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = (
( ZCV_MPPTSolarChargeControllerModel_T * ) ssGetSolverZcSignalVector ( S ) )
; _rtP = ( ( P_MPPTSolarChargeControllerModel_T * ) ssGetModelRtp ( S ) ) ;
_rtB = ( ( B_MPPTSolarChargeControllerModel_T * ) _ssGetModelBlockIO ( S ) )
; ssCallAccelRunBlock ( S , 11 , 42 , SS_CALL_MDL_ZERO_CROSSINGS ) ; _rtZCSV
-> RelationalOperator_RelopInput_ZC = _rtB -> B_11_112_0 - _rtB -> B_11_126_0
; _rtZCSV -> HitCrossing_Input_ZC = _rtB -> B_11_124_0 - _rtP -> P_105 ; if (
_rtDW -> HitCrossing_MODE == 0 ) { _rtZCSV -> HitCrossing_Output_ZC = ( (
_rtB -> B_11_124_0 - _rtP -> P_105 ) * ( real_T ) _rtB -> B_11_130_0 != 0.0 )
; } else { _rtZCSV -> HitCrossing_Output_ZC = ssGetT ( S ) -
ssGetTimeOfLastOutput ( S ) ; } } static void mdlInitializeSizes ( SimStruct
* S ) { ssSetChecksumVal ( S , 0 , 1075500118U ) ; ssSetChecksumVal ( S , 1 ,
1821452714U ) ; ssSetChecksumVal ( S , 2 , 1579113547U ) ; ssSetChecksumVal (
S , 3 , 2388589001U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "10.2" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_MPPTSolarChargeControllerModel_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_MPPTSolarChargeControllerModel_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_MPPTSolarChargeControllerModel_T ) ) { static char msg [ 256 ] ; sprintf (
msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & MPPTSolarChargeControllerModel_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
MPPTSolarChargeControllerModel_rtInvariant ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; ( ( P_MPPTSolarChargeControllerModel_T * ) ssGetModelRtp ( S ) )
-> P_53 = rtMinusInf ; ( ( P_MPPTSolarChargeControllerModel_T * )
ssGetModelRtp ( S ) ) -> P_69 = rtMinusInf ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID4 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
