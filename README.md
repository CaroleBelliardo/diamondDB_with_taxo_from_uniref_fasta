# DIAMOND Database Generation with Taxonomic Information
This repository contains scripts to generate a [DIAMOND](https://github.com/bbuchfink/diamond) database with taxonomic information. The resulting database can be used for Last Common Ancestor (LCA) and other taxonomic-related processing, utilising data from the [UNIREF database](https://www.ebi.ac.uk/training/online/courses/uniprot-quick-tour/the-uniprot-databases/uniref/).


## Steps to Generate the DIAMOND Database

### 1. Generate a Correspondence Table from `protID` to `taxID`

This step extracts the `protID` to `taxID` correspondence from the headers of a FASTA file and stores it in a `map.txt` file.

#### Python Script

Run the Python script with the following command:

```bash
module load devel/python/Python-3.11.1 # On Genotoul
python extract_ids.py <input_fasta> <output_file>
```

- `<input_fasta>`: Path to your input FASTA file, such as `uniref90.fasta` or `/work/bank2/ebi/uniref/uniref90/uniref90_2024_05/fasta/uniref90.fasta`.
- `<output_file>`: Path where the output `map.txt` file should be saved, e.g., `./uniref_map.txt`.

Example usage:

```bash
ln -s /work/bank2/ebi/uniref/uniref90/uniref90_2024_05/fasta/uniref90.fasta
python extract_ids.py uniref90.fasta uniref_map.txt
```

#### C++ Version for Large Files

For efficiency with large files, use the C++ version of the script. Compile and run it as follows:

```bash
g++ -std=c++17 extract_ids.cpp -o extract_ids
./extract_ids uniref90.fasta uniref90_map.txt
```

### 2. Run DIAMOND makedb to Build the Database

After generating the `map.txt` file, use the DIAMOND `makedb` tool to create the database. Submit this process on a cluster using the following SLURM script:

```bash
sbatch diamond_makedb.sh <mapFile_path> <fasta_path> <db_name>
```

This SLURM script is intended for the Genotoul server but can be adapted to any cluster with a SLURM job manager.

Alternatively, run the `makedb` process directly from the command line:

```bash
diamond makedb --threads $SLURM_JOB_CPUS_PER_NODE --taxonmap $map --taxonnodes $nodes --taxonnames $names --in $fasta -d $dbout
```

Where:

- `$SLURM_JOB_CPUS_PER_NODE`: Number of CPUs allocated for the job.
- `$map`: Path to the `protID-taxID` correspondence file generated in Step 1.
- `$nodes`: Path to the NCBI `nodes.dmp` file.
- `$names`: Path to the NCBI `names.dmp` file.
- `$fasta`: Path to the input FASTA file.
- `$dbout`: Name for the output DIAMOND database.

**Notes**

- Ensure that the required NCBI files (`nodes.dmp` and `names.dmp`) are available and correctly referenced.
- The scripts are designed for use on the Genotoul server but should work on any SLURM-managed cluster with minor adjustments.
