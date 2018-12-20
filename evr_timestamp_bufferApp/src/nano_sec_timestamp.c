#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
 
static int nano_second_timestamp(aSubRecord *prec) {
 
    /* INPA and OUTA fields are accessed by precord->a and precord->vala*/
    /* epicsInt64 or epicsUInt64 */
    epicsTimeStamp tick;

    if(!dbGetTimeStamp(&(prec->inpa),&tick)){
	/* Add constant (20*365.25*24*3600=631152000) to change from Epics epoch to Unix epoch */
        *(epicsInt64 *)prec->vala =  (((epicsInt64) tick.secPastEpoch) + 631152000) * 1000000000 + (epicsInt64) tick.nsec;
        //*(long long *)prec->vala =  (((long long) tick.secPastEpoch) + 631152000) * 1000000000 + (long long) tick.nsec;
	*(long *)prec->valb = tick.secPastEpoch;
        *(long *)prec->valc = tick.nsec;
//	printf("Timestamp: %lld \n", *(long long *)prec->vala);
        return 0;
    } else {
        printf("Could not retrieve timestamp \n");
        return -1;
    }
    /*#ifdef DBR_INT64
        printf("Code where Base has INT64 support");
    #else
        printf("Code for older versions");
    #endif*/

}
 
/* Note the function must be registered at the end!*/
epicsRegisterFunction(nano_second_timestamp);
