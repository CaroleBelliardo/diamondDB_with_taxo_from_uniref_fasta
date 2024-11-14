#!/bin/bash
#SBATCH --job-name=extract_ids        # Nom du job
#SBATCH --output=extract_ids.out      # Fichier de sortie
#SBATCH --error=extract_ids.err       # Fichier d'erreurs
#SBATCH --ntasks=1                    # Nombre de tâches (ici, une seule commande)
#SBATCH --cpus-per-task=4             # Nombre de CPU par tâche (ajustez selon les besoins)
#SBATCH --time=24:00:00               # Temps maximal d'exécution (ici 1 heure, ajustez selon vos besoins)
#SBATCH --mem=64G                     # Mémoire par nœud (ajustez selon les besoins)
#SBATCH -p workq 



./extract_ids uniref90.fasta uniref90_map.txt

##-- Run 
sbatch run_extract_ids.txt
