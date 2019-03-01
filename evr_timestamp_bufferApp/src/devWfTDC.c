#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alarm.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "dbEvent.h"
#include "recGbl.h"
#include "devSup.h"
#include "waveformRecord.h"
#include "epicsExport.h"

/* Create the dset for devWfTDC */
static long init_record(waveformRecord *prec);
static long read_wf(waveformRecord *prec);

struct {
    long      number;
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN read_wf;
} devWfTDC = {
    5,
    NULL,
    NULL,
    init_record,
    NULL,
    read_wf
};
epicsExportAddress(dset, devWfTDC);

static long init_record(waveformRecord *prec)
{
    /* INP must be CONSTANT, PV_LINK, DB_LINK or CA_LINK*/
    switch (prec->inp.type) {
    case CONSTANT:
        prec->nord = 0;
        break;
    case PV_LINK:
    case DB_LINK:
    case CA_LINK:
        break;
    default:
        recGblRecordError(S_db_badField, (void *)prec,
            "devWfSoft (init_record) Illegal INP field");
        return(S_db_badField);
    }
    return 0;
}

static long read_wf(waveformRecord *prec)
{
    long nRequest = prec->nelm;

    if (dbGetLink(&prec->inp, prec->ftvl, prec->bptr, 0, &nRequest) == 0) {
        if (nRequest >= 0) {
            prec->nord = nRequest;
            if (prec->tsel.type == CONSTANT &&
                prec->tse == epicsTimeEventDeviceTime)
                dbGetTimeStamp(&prec->inp, &prec->time);
        }
    }
    return 0;
}
