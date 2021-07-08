#!/bin/bash

read -p "Name of code: " codename;

currentDir=$(pwd)

gcc "$codename"".c" -o "$codename";
resulExist=$(find resul -ignore_readdir_race | wc -l);
if [ $resulExist -eq 0 ]
then
    echo "Making dir of resuls, naming 'resul'"
    mkdir resul
fi

quantity_ex=$(ls testes | wc -l)
quantity_ex=$(expr $quantity_ex / 2)

for i in $(seq 1 $quantity_ex); do "$currentDir"/"$codename" < "$currentDir"/testes/$i.in > "$currentDir"/resul/$i.my; done

echo "Making dir 'errors'"
mkdir "$currentDir"/errors
echo "------------------- Errors output -------------------"
for i in $(seq 1 5); do
    diff --color "$currentDir/testes/$i.out" "$currentDir/resul/$i.my" > "$currentDir"/errors/error_$i.my
    exit_code=$?
    if [ $exit_code -eq 1 ]; then
        cat "$currentDir"/errors/error_$i.my
    else
        rm "$currentDir"/errors/error_$i.my
    fi 
done
echo "-------------------      End      -------------------"
existErrors=$(ls errors | wc -l)
existErrors=$(expr $existErrors)

if [ $existErrors -eq 0 ]; then
    rm -f -r errors
    echo "0 Erros, deleting dir errors..."
else
    echo $existErrors " Errors in dir 'errors'"
fi
