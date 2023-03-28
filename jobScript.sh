#!/bin/sh

OUTDIR=${1}

FLUX_FILE=${2}
HIST_NAME=${3}

source /cvmfs/nova.opensciencegrid.org/novasoft/slf6/novasoft/setup/setup_nova.sh -s -r S22-09-15

if [ "$OUTDIR" = "-t" ];
then
    gevgen -r 777 -n 20000 -p 14 -t 1000260560 -e 0,40 -f ${FLUX_FILE},${HIST_NAME} --seed 777 --cross-sections $GENIEXSECFILE --tune $GENIE_XSEC_TUNE

else

gevgen -r $[$CLUSTER+$PROCESS] -n 20000 -p 14 -t 1000260560 -e 0,40 -f ${CONDOR_DIR_INPUT}/${FLUX_FILE},${HIST_NAME} --seed $[$CLUSTER+$PROCESS] --cross-sections $GENIEXSECFILE --tune $GENIE_XSEC_TUNE

for f in gntp.*.root
do
    ifdh cp ${f} ${OUTDIR}/${f}
done

fi
