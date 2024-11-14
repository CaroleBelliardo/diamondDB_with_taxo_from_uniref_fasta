#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --ntasks=1   # number of processor cores (i.e. tasks)
#SBATCH --cpus-per-task=20     # number of CPU per task #4
#SBATCH --nodes=1   # number of nodes
#SBATCH --mem=124G   # memory per Nodes   #38
#SBATCH -J "dmd mkdb"   # job name
#SBATCH -e slurm-dmd_mkdb-%j.err
#SBATCH -o slurm-dmd_mkdb-%j.out
#SBATCH -p all

# To run this script on genotoul, please load the last version of Diamond module
module load bioinfo/DIAMOND/2.1.9

## -- path and env. variables

map='./TAXONOMY/map.txt'
nodes="./TAXONOMY/nodes.dmp"
names=".//TAXONOMY/names.dmp"

fasta= $1           # fasta input file
dbout= ${fasta}.dmd # db name

diamond makedb --threads $SLURM_JOB_CPUS_PER_NODE --taxonnodes $nodes --taxonnames $names --taxonmap $map --in $fasta -d $dbout

## run : 
# sbatch diamond_makedb.sh <fasta_path> <db_name>
