
if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters"
    exit 1
fi



OUTDIR=/pnfs/minos/scratch/users/tcarroll/MINOSgenie_$(date +"%Y_%m_%d_%I_%M_%p")

COUNT=`ls -d ${OUTDIR}*/ 2>/dev/null|wc -l`


OUTDIR=${OUTDIR}_${COUNT}

mkdir -p ${OUTDIR}

jobsub_submit -G minos -g -Q -N ${1} --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC,OFFSITE --memory=2GB --expected-lifetime=60m --site=FermiGrid,FNAL,Caltech,BNL,Michigan,BU,Clemson,Colorado,Cornell,Hyak_CE,MIT,Nebraska,NotreDame,Stampede,HOSTED_STANFORD,SU-ITS,TTU,UCSD,Wisconsin --lines '+FERMIHTC_AutoRelease=True' --lines '+FERMIHTC_GraceLifetime=1800' -f dropbox://FluxHelperRun12_numu.root --use-pnfs-dropbox file://jobScriptMINOSxFD.sh ${OUTDIR}
