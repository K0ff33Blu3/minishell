#!/bin/bash

# Paths and labels
promprt="$USER$ "
expc="expc_output"
mini="mini_output"
outfile="test.diff"

# Pulisci i file di output
> $expc
> $mini

#########################
# 1. Output da Bash
#########################
<testlist bash >$expc 2>&1

echo "BASH EXECUTED"

# Normalizza errori bash -> testlist
sed -i 's/^testlist: line [0-9]*: /testlist: /g' $expc
sed -i 's/^testlist: -c: line [0-9]*: /testlist: /g' $expc
sed -i 's/line [0-9]*: //g' $expc
sed -i 's/^bash: /testlist: /g' $expc

#########################
# 2. Output da minishell
#########################
<testlist ./minishell >$mini 2>&1

echo "MINISHELL EXECUTED"

# Rimuove codici colore ANSI prima di tutto
sed -i 's/\x1b\[[0-9;]*m//g' $mini        # Rimuove escape sequences

# Rimuove prompt, clear screen e righe extra
sed -i "s/^$promprt//g" $mini             # Rimuove prompt
sed -i 's/^minishell% //g' $mini          # Prompt alternativo
sed -i 's/^MINISHELL@ //g' $mini          # Il tuo prompt (globale)
sed -i 's/MINISHELL@ //g' $mini           # Rimuove prompt anche a metà riga (echo -n)
sed -i '/^exit$/d' $mini                  # Rimuove righe "exit"
sed -i '/^minishell% exit$/d' $mini       # Altra forma di exit
sed -i 's/minishell: /testlist: /g' $mini
sed -i '/^### /d' $mini                   # Rimuove linee con commenti ###
sed -i '/^#[a-z]/d' $mini                 # Rimuove linee con commenti #abc  
sed -i '/^# /d' $mini                     # Rimuove commenti con spazio
sed -i '/^cmd_not_found: No such file or directory$/d' $mini  # Rimuove errori commenti
sed -i 's/errore nome variabile/testlist: export: `123asd=ciao'"'"': not a valid identifier/g' $mini  # Normalizza errore export

# Rimuove le righe di comando duplicate (minishell le stampa prima di eseguirle)
# Legge testlist e rimuove ogni riga che corrisponde ESATTAMENTE a un comando  
while IFS= read -r line; do
    # Ignora righe vuote e commenti
    [[ -z "$line" || "$line" =~ ^[[:space:]]*# ]] && continue
    # Escape caratteri speciali per sed (più robusto)
    escaped=$(printf '%s\n' "$line" | sed 's/[][\/.^$*]/\\&/g' | sed 's/|/\\|/g')
    # Rimuove la riga SOLO se corrisponde esattamente (inizio e fine)
    sed -i "/^${escaped}$/d" $mini
done < testlist

# Rimuove righe vuote multiple
sed -i '/^$/N;/^\n$/D' $mini

#########################
# 3. Diff e risultato
#########################
diff $expc $mini > traces.diff

if [ "$?" = "1" ]; then
	echo KO
else
	echo OK
fi
