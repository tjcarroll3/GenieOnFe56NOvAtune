
source /cvmfs/nova.opensciencegrid.org/novasoft/slf6/novasoft/setup/setup_nova.sh -r S22-09-15

unsetup genie_xsec
unsetup genie_phyopt

setup genie_xsec v3_00_06 -qN1810j0211a:e1000:k250:resfixfix

setup genie_phyopt v3_00_06 -qdkcharmtau:resfixfix
