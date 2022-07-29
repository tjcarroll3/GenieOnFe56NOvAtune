#!/bin/sh

OUTDIR=${1}

source /cvmfs/nova.opensciencegrid.org/novasoft/slf6/novasoft/setup/setup_nova.sh -s

gevgen -r $[$CLUSTER+$PROCESS] -n 20000 -p 14 -t 1000260560 -e 0,40 -f ${CONDOR_DIR_INPUT}/FluxHelperRun12_numu.root,TrueEnergyNuFluxRW_ND --seed $[$CLUSTER+$PROCESS] --cross-sections $GENIEXSECFILE --tune $GENIE_XSEC_TUNE

for f in gntp.*.root
do
    ifdh cp ${f} ${OUTDIR}/${f}
done
