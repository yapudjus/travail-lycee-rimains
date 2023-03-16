#ifndef RTW_HEADER_MPPTSolarChargeControllerModel_acc_h_
#define RTW_HEADER_MPPTSolarChargeControllerModel_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef MPPTSolarChargeControllerModel_acc_COMMON_INCLUDES_
#define MPPTSolarChargeControllerModel_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "MPPTSolarChargeControllerModel_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_11_3_0 ; real_T B_11_5_0 ; real_T B_11_6_0 ; real_T
B_11_8_0 ; real_T B_11_11_0 ; real_T B_11_22_0 ; real_T B_11_28_0 ; real_T
B_11_35_0 ; real_T B_11_37_0 ; real_T B_11_39_0 ; real_T B_11_41_0 ; real_T
B_11_42_0 ; real_T B_11_43_0 ; real_T B_11_44_0 ; real_T B_11_45_0 ; real_T
B_11_49_0 ; real_T B_11_50_0 ; real_T B_11_51_0 ; real_T B_11_52_0 ; real_T
B_11_64_0 ; real_T B_11_79_0 ; real_T B_11_80_0 ; real_T B_11_81_0 ; real_T
B_11_85_0 ; real_T B_11_87_0 ; real_T B_11_90_0 ; real_T B_11_92_0 ; real_T
B_11_94_0 ; real_T B_11_95_0 ; real_T B_11_107_0 ; real_T B_11_110_0 ; real_T
B_11_115_0 ; real_T B_11_118_0 ; real_T B_11_120_0 ; real_T B_11_122_0 ;
real_T B_11_124_0 ; real_T B_11_127_0 ; real_T B_11_134_0 ; real_T B_11_140_0
; real_T B_11_0_0 [ 4 ] ; real_T B_11_1_0 ; real_T B_11_2_0 ; real_T
B_11_3_0_m ; real_T B_11_4_0 ; real_T B_11_5_0_c ; real_T B_11_6_0_k ; real_T
B_11_7_0 ; real_T B_11_8_0_c ; real_T B_11_9_0 ; real_T B_11_10_0 ; real_T
B_11_11_0_b ; real_T B_11_12_0 ; real_T B_11_13_0 ; real_T B_11_14_0 ; real_T
B_11_15_0 ; real_T B_11_16_0 ; real_T B_11_24_0 ; real_T B_11_25_0 ; real_T
B_11_41_0_p ; real_T B_11_42_0_c ; real_T B_11_43_0_f ; real_T B_11_44_0_g ;
real_T B_11_45_0_g ; real_T B_11_46_0 ; real_T B_11_47_0 ; real_T B_0_0_0 ;
real_T B_0_1_0 ; real_T B_0_2_0 ; real_T B_0_3_0 ; real_T B_0_4_0 ; real_T
B_0_5_0 ; real_T B_0_6_0 ; real_T B_0_7_0 [ 7 ] ; real_T B_0_7_1 [ 4 ] ;
real_T B_0_8_0 ; real_T B_0_9_0 ; real_T B_0_10_0 ; real_T B_0_11_0 ; real_T
B_0_12_0 ; real_T B_0_13_0 ; real_T B_0_14_0 ; real_T B_0_15_0 ; boolean_T
B_11_128_0 ; char_T pad_B_11_128_0 [ 7 ] ; }
B_MPPTSolarChargeControllerModel_T ; typedef struct { real_T
Currentfilter_states ; real_T inti_DSTATE ; real_T
DiscreteTimeIntegrator_DSTATE ; real_T Delay_x_DSTATE ; real_T
Delay_x_DSTATE_g ; real_T VK1_DSTATE ; real_T PK1_DSTATE ; real_T
StateSpace_DSTATE [ 3 ] ; real_T itinit1_PreviousInput ; real_T
itinit_PreviousInput ; real_T Memory2_PreviousInput ; real_T
Memory_PreviousInput ; real_T DK1_PreviousInput ; struct { real_T modelTStart
; } TransportDelay_RWORK ; void * FromWs_PWORK [ 3 ] ; void * Scope_PWORK [ 6
] ; void * BatteryScope_PWORK [ 3 ] ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_EnableDisableFloatStage_at_outport_0_PWORK ; struct
{ void * AQHandles ; } TAQSigLogging_InsertedFor_Gain_at_outport_0_PWORK ;
struct { void * AQHandles ; } TAQSigLogging_InsertedFor_PK_at_outport_0_PWORK
; void * Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_AlgLoopData ;
struct { void * AS ; void * BS ; void * CS ; void * DS ; void * DX_COL ; void
* BD_COL ; void * TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ;
void * SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ;
void * XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG
; void * Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } StateSpace_PWORK ; int32_T
TmpAtomicSubsysAtifP0Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtifP0Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun_f ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport5_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport4_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport3_sysIdxToRun_m ; int32_T
TmpAtomicSubsysAtMultiportSwitch1Inport2_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_parentSysIdxToRun ; int_T
FromWs_ZCTimeIndices [ 9 ] ; int_T FromWs_CurZCTimeIndIdx ; int_T
FromWs_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; int_T
StateSpace_IWORK [ 11 ] ; int_T HitCrossing_MODE ; int8_T inti_PrevResetState
; uint8_T inti_IC_LOADING ; uint8_T inti_NumInitCond ; uint8_T
DiscreteTimeIntegrator_NumInitCond ; boolean_T RelationalOperator_Mode ;
char_T pad_RelationalOperator_Mode [ 7 ] ; }
DW_MPPTSolarChargeControllerModel_T ; typedef struct { real_T
integrator_CSTATE ; } X_MPPTSolarChargeControllerModel_T ; typedef struct {
real_T integrator_CSTATE ; } XDot_MPPTSolarChargeControllerModel_T ; typedef
struct { boolean_T integrator_CSTATE ; }
XDis_MPPTSolarChargeControllerModel_T ; typedef struct { real_T
integrator_CSTATE ; } CStateAbsTol_MPPTSolarChargeControllerModel_T ; typedef
struct { real_T integrator_CSTATE ; }
CXPtMin_MPPTSolarChargeControllerModel_T ; typedef struct { real_T
integrator_CSTATE ; } CXPtMax_MPPTSolarChargeControllerModel_T ; typedef
struct { real_T FromWs_repeatedTime_ZC ; real_T
RelationalOperator_RelopInput_ZC ; real_T HitCrossing_Input_ZC ; real_T
HitCrossing_Output_ZC ; } ZCV_MPPTSolarChargeControllerModel_T ; typedef
struct { ZCSigState FromWs_repeatedTime_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE ; ZCSigState HitCrossing_Input_ZCE ;
ZCSigState HitCrossing_Output_ZCE ; }
PrevZCX_MPPTSolarChargeControllerModel_T ; typedef struct { const real_T
B_11_0_0 ; const real_T B_11_1_0 ; const real_T B_11_2_0 ; const real_T
B_11_3_0 ; } ConstB_MPPTSolarChargeControllerModel_T ;
#define MPPTSolarChargeControllerModel_rtC(S) ((ConstB_MPPTSolarChargeControllerModel_T *) _ssGetConstBlockIO(S))
struct P_MPPTSolarChargeControllerModel_T_ { real_T P_0 [ 2 ] ; real_T P_1 [
9 ] ; real_T P_2 [ 2 ] ; real_T P_3 [ 27 ] ; real_T P_4 [ 2 ] ; real_T P_5 [
21 ] ; real_T P_6 [ 2 ] ; real_T P_7 [ 63 ] ; real_T P_8 [ 2 ] ; real_T P_9 [
3 ] ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ;
real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T
P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ;
real_T P_26 [ 2 ] ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ;
real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T
P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ;
real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T
P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ;
real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T
P_58 ; real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ;
real_T P_64 ; real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T
P_69 ; real_T P_70 ; real_T P_71 [ 4 ] ; real_T P_72 ; real_T P_73 ; real_T
P_74 ; real_T P_75 ; real_T P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 ;
real_T P_80 ; real_T P_81 ; real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T
P_85 ; real_T P_86 ; real_T P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ;
real_T P_91 ; real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T
P_96 ; real_T P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101
; real_T P_102 ; real_T P_103 ; real_T P_104 ; real_T P_105 ; real_T P_106 ;
real_T P_107 ; } ; extern P_MPPTSolarChargeControllerModel_T
MPPTSolarChargeControllerModel_rtDefaultP ; extern const
ConstB_MPPTSolarChargeControllerModel_T
MPPTSolarChargeControllerModel_rtInvariant ;
#endif