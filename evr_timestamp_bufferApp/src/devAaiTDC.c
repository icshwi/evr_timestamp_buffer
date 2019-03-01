#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alarm.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "devSup.h"
#include "cantProceed.h"
#include "menuYesNo.h"
#include "aaiRecord.h"
#include "epicsExport.h"

/* Create the dset for devAaiTDC */
static long init_record();
static long read_aai();

struct {
    long      number;
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN read_aai;
} devAaiTDC = {
    5,
    NULL,
    NULL,
    init_record,
    NULL,
    read_aai
};
epicsExportAddress(dset,devAaiTDC);

static long init_record(aaiRecord *prec)
{
    /* INP must be a CONSTANT or a PV_LINK or a DB_LINK or a CA_LINK*/
    switch (prec->inp.type) {
    case CONSTANT:
        prec->nord = 0;
        break;
    case PV_LINK:
    case DB_LINK:
    case CA_LINK:
	break;
    default :
	recGblRecordError(S_db_badField, (void *)prec,
	    "devAaiSoft (init_record) Illegal INP field");
	return(S_db_badField);
    }
    return 0;
}

static long read_aai(aaiRecord *prec)
{
    long nRequest = prec->nelm;

    if (dbGetLink(prec->simm == menuYesNoYES ? &prec->siol : &prec->inp,
        prec->ftvl, prec->bptr, 0, &nRequest) == 0) {
        if (nRequest >= 0) {
            prec->nord = nRequest;
            prec->udf=FALSE;
            if (prec->tsel.type == CONSTANT &&
                prec->tse == epicsTimeEventDeviceTime)
                dbGetTimeStamp(&prec->inp, &prec->time);
        }
    }

    return 0;
}
