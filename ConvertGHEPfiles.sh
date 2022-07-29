#!/bin/sh

INPUTfiles=${1}
OUTDIR=${2}

if [ ! -d "${OUTDIR}" ]
then
    echo "${OUTDIR} does not exist"
    echo "exiting ..."
    exit 1
fi

for GHEPfile in ${INPUTfiles}
do

    echo ${GHEPfile}
    GHEPfilename=`basename ${GHEPfile}`
    GSTfilename=${GHEPfilename%.ghep.root}.gst.root
    echo ${GSTfilename}
    GSTfilepath=${OUTDIR}/${GSTfilename}
    echo ${GSTfilepath}
    gntpc -i ${GHEPfile} -f gst -o ${GSTfilepath}
done


