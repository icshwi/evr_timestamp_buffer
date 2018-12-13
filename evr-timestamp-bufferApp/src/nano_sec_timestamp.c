#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
 
static int nano_second_timestamp_asub(aSubRecord *prec) {
 
    /* INPA and OUTA fields are accessed by precord->a and precord->vala*/
    /* epicsInt64 or epicsUInt64 */
    epicsTimeStamp tick;

    if(!dbGetTimestamp(&(prec->inpa),&tick)){
	/* Add constant (20*365.25*24*3600=631152000) to change from Epics epoch to Unix epoch */
        *(long long *)prec->vala =  (long long) (tick.secPastEpoch+631152000)*1000000000 + (long long) tick.nsec;
	*(long *)prec->valb = tick.secPastEpoch;
        *(long *)prec->valc = tick.nsec;
        return 0;
    } else {
        printf("Could not retrieve timestamp \n";
        return -1;
    }
}
 
/* Note the function must be registered at the end!*/
epicsRegisterFunction(nano_second_timestamp);
