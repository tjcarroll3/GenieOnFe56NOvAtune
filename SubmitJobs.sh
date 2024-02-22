
if [ "$#" -ne 4 ]; then
    echo "Illegal number of parameters"
    exit 1
fi

Number_of_Jobs=${1}
PDG_PARTICLE=${2}
FLUX_FILE=${3}
HIST_NAME=${4}

OUTDIR=/pnfs/minos/scratch/users/tcarroll/MINOSgenie_$(date +"%Y_%m_%d_%I_%M_%p")

COUNT=`ls -d ${OUTDIR}*/ 2>/dev/null|wc -l`


OUTDIR=${OUTDIR}_${COUNT}

mkdir -p ${OUTDIR}



cat <<EOF >${OUTDIR}/inputs.txt
Number of jobs: ${1}
Particle PDG ID: ${2}
Flux file: ${3}
Histogram name: ${4}
EOF

FLUX_FILE_ARG=`basename ${FLUX_FILE}`

jobsub_submit -G minos -Q -N ${Number_of_Jobs} --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC,OFFSITE --memory=2GB --expected-lifetime=60m --site=FermiGrid,FNAL,Caltech,BNL,Michigan,BU,Clemson,Colorado,Cornell,Hyak_CE,MIT,Nebraska,NotreDame,Stampede,HOSTED_STANFORD,SU-ITS,TTU,UCSD,Wisconsin --lines '+FERMIHTC_AutoRelease=True' --lines '+FERMIHTC_GraceLifetime=1800' -f dropbox://${FLUX_FILE} --use-pnfs-dropbox file://jobScript.sh ${OUTDIR} ${PDG_PARTICLE} ${FLUX_FILE_ARG} ${HIST_NAME}
