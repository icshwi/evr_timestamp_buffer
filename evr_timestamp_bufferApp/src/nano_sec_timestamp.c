#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>

#include <sys/time.h>



static int nano_second_timestamp(aSubRecord *prec) {
 
    /* INPA and OUTA fields are accessed by precord->a and precord->vala*/
    /* epicsInt64 or epicsUInt64 */
    epicsTimeStamp tick;
    
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    unsigned long time_in_sec = te.tv_sec; 
    unsigned long time_in_usec = te.tv_usec;
    

    if(!dbGetTimeStamp(&(prec->inpa),&tick)){
	/* Add constant (20*365.25*24*3600=631152000) to change from Epics epoch to Unix epoch */
        //*(long long *)prec->vala =  (((long long) tick.secPastEpoch) + 631152000) * 1000000000 + (long long) tick.nsec;
	*(long *)prec->vala = tick.secPastEpoch + 631152000; //Unix epoch
        *(long *)prec->valb = tick.nsec;
	*(long *)prec->valc = tick.secPastEpoch; //Epics epoch
	*(long *)prec->vald = time_in_sec; 
	*(long *)prec->vale = time_in_usec; 
	*(long *)prec->valf = (tick.secPastEpoch + 631152000 - time_in_sec) + (tick.nsec/1000L - time_in_usec)/1000000L; 
        //*(epicsInt64 *)prec->vald =  (((epicsInt64) tick.secPastEpoch) + 631152000) * 1000000000 + (epicsInt64) tick.nsec;
	printf("TEpics[sec]: %lld,\t [usec]: %lld\n", *(long long *)prec->vala,  *(long long *)prec->valb);
	printf("TUnix[sec] : %lld,\t [usec]: %lld,\t dt:%lld\n", *(long long *)prec->vald,  *(long long *)prec->vale,  *(long long *)prec->valf);
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
