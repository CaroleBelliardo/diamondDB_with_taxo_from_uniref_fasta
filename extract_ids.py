#!/usr/bin/env python3

"""
Script to extract protein ID (protID) and TaxID from a FASTA file and generate a tab-separated output file.

Usage:
    extract_ids.py <input_fasta> <output_file>

Arguments:
    input_fasta     Path to the input FASTA file.
    output_file     Path to the output tab-separated file.

Example:
    ./extract_ids.py input.fasta output.tsv
"""

import argparse
import re

def extract_protID_taxID(sequence):
    """
    Extract protID and TaxID from a sequence header for all UniRef versions (UniRef50, UniRef90, UniRef100).

    Args:
        sequence (str): Sequence header.

    Returns:
        tuple: (protID, TaxID)
    """
    # Extract protID using regex (for UniRef versions)
    protID_match = re.search(r'UniRef\d+_(\S+)', sequence)
    protID = protID_match.group(1) if protID_match else None

    # Extract TaxID using regex
    taxid_match = re.search(r'TaxID=(\d+)', sequence)
    taxID = taxid_match.group(1) if taxid_match else None

    return protID, taxID

def process_fasta(input_file, output_file):
    """
    Process the input FASTA file and generate the output file.

    Args:
        input_file (str): Path to the input FASTA file.
        output_file (str): Path to the output tab-separated file.
    """
    with open(input_file, 'r') as input_handle, open(output_file, 'w') as output_handle:
        # Write the header to the output file
        output_handle.write("accession.version\ttaxid\n")
        
        # Process each line in the input FASTA file
        for line in input_handle:
            line = line.strip()
            if line.startswith(">"):
                protID, taxID = extract_protID_taxID(line)
                
                # Write only if both protID and taxID are found
                if protID and taxID:
                    output_handle.write(f"{protID}\t{taxID}\n")
                else:
                    print(f"Warning: Missing data for line: {line}")

def main():
    """
    Main function to parse command-line arguments and call the processing function.
    """
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("input_fasta", help="Path to the input FASTA file.")
    parser.add_argument("output_file", help="Path to the output tab-separated file.")
    args = parser.parse_args()

    # Call the processing function with provided arguments
    process_fasta(args.input_fasta, args.output_file)

if __name__ == "__main__":
    main()
