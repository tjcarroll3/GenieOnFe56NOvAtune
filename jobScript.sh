#!/bin/sh

OUTDIR=${1}

PDG_PARTICLE=${2}
FLUX_FILE=${3}
HIST_NAME=${4}

source /cvmfs/nova.opensciencegrid.org/novasoft/slf6/novasoft/setup/setup_nova.sh -s -r S22-09-15

unsetup genie_xsec
unsetup genie_phyopt

setup genie_xsec v3_00_06 -qN1810j0211a:e1000:k250:resfixfix

setup genie_phyopt v3_00_06 -qdkcharmtau:resfixfix

if [ "$OUTDIR" = "-t" ];
then
    gevgen -r 777 -n 20000 -p ${PDG_PARTICLE} -t 1000260560 -e 0,40 -f ${FLUX_FILE},${HIST_NAME} --seed 777 --cross-sections $GENIEXSECFILE --tune $GENIE_XSEC_TUNE

else

gevgen -r $[$CLUSTER+$PROCESS] -n 20000 -p ${PDG_PARTICLE} -t 1000260560 -e 0,40 -f ${CONDOR_DIR_INPUT}/${FLUX_FILE},${HIST_NAME} --seed $[$CLUSTER+$PROCESS] --cross-sections $GENIEXSECFILE --tune $GENIE_XSEC_TUNE

for f in gntp.*.root
do
    ifdh cp ${f} ${OUTDIR}/${f}
done

fi
