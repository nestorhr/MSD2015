#include "__cf_test_plotblock.h"
#include <math.h>
#include "test_plotblock_acc.h"
#include "test_plotblock_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { pm1eehbhlo * _rtB ;
g4qmwopn25 * _rtP ; fvijcbvdjk * _rtDW ; _rtDW = ( ( fvijcbvdjk * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( g4qmwopn25 * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( pm1eehbhlo * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { memcpy ( & _rtB -> kwxzsnrcgi [ 0 ] , & _rtP -> P_0 [ 0 ] ,
sizeof ( real_T ) << 3U ) ; _rtB -> ayawsc4skp = _rtP -> P_1 ; _rtB ->
pt1f5nnhuo = _rtP -> P_2 ; memcpy ( & _rtB -> jjd5bwvjyc [ 0 ] , & _rtDW ->
i0nxsobupg [ 0 ] , 1317060U * sizeof ( uint8_T ) ) ; } if ( ssIsSampleHit ( S
, 2 , 0 ) ) { _rtB -> cphmwz42pm [ 0 ] = _rtP -> P_3 [ 0 ] ; _rtB ->
cphmwz42pm [ 1 ] = _rtP -> P_3 [ 1 ] ; _rtB -> cphmwz42pm [ 2 ] = _rtP -> P_3
[ 2 ] ; _rtB -> otwf3jqmtj [ 0 ] = _rtP -> P_4 [ 0 ] ; _rtB -> otwf3jqmtj [ 1
] = _rtP -> P_4 [ 1 ] ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER
( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { char_T * sErr ;
pm1eehbhlo * _rtB ; fvijcbvdjk * _rtDW ; _rtDW = ( ( fvijcbvdjk * )
ssGetRootDWork ( S ) ) ; _rtB = ( ( pm1eehbhlo * ) _ssGetBlockIO ( S ) ) ; if
( ssIsSampleHit ( S , 1 , 0 ) ) { sErr = GetErrorBuffer ( & _rtDW ->
efqz2rzpvb [ 0U ] ) ; LibUpdate_Video ( & _rtDW -> efqz2rzpvb [ 0U ] , & _rtB
-> jjd5bwvjyc [ 0U ] , GetNullPointer ( ) , GetNullPointer ( ) , 810 , 542 )
; if ( * sErr != 0 ) { ssSetErrorStatus ( S , sErr ) ; ssSetStopRequested ( S
, 1 ) ; } memcpy ( & _rtDW -> i0nxsobupg [ 0 ] , & _rtB -> plmu21xpdu [ 0 ] ,
1317060U * sizeof ( uint8_T ) ) ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3354365021U
) ; ssSetChecksumVal ( S , 1 , 1020452563U ) ; ssSetChecksumVal ( S , 2 ,
4235432891U ) ; ssSetChecksumVal ( S , 3 , 194574494U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.5" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( fvijcbvdjk ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( pm1eehbhlo ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
g4qmwopn25 ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & lrrbys4r2m ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
