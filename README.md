

# Workflow

Setup your jobsub environment, then execute SubmitJob*.sh to submit a jobScript*.sh script to the grid. This script is congifured to sample a neutrino energy spectrum from 0 to 40 GeV (`-e 0,40`) and generate numu (PDG code `-p 14`) interactions on Fe56 (`-t 1000260560`). The jobs will produce GHEP files. The `mecTree.C` macro was made using `TTree::MakeClass()`. This macro expects a GENIE summary ntuple format that is generated by the `ConvertGHEPfiles.sh` script.

