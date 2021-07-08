#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void makeErrors(FILE *myFile){
    fprintf(myFile,"echo \"Making dir 'errors'\"\n\
mkdir \"$currentDir\"/errors\n\
echo \"------------------- Errors output -------------------\"\n\
for i in $(seq 1 5); do\n\
    diff --color \"$currentDir/testes/$i.out\" \"$currentDir/resul/$i.my\" > \"$currentDir\"/errors/error_$i.my\n\
    exit_code=$?\n\
    if [ $exit_code -eq 1 ]; then\n\
        cat \"$currentDir\"/errors/error_$i.my\n\
    else\n\
        rm \"$currentDir\"/errors/error_$i.my\n\
    fi \n\
done\n\
echo \"-------------------      End      -------------------\"\
\nexistErrors=$(ls errors | wc -l)\n\
existErrors=$(expr $existErrors)\n\
\n\
if [ $existErrors -eq 0 ]; then\n\
    rm -f -r errors\n\
    echo \"0 Erros, deleting dir errors...\"\n\
else\n\
    echo $existErrors \" Errors in dir 'errors'\"\n\
fi\n");
}

void makePattern(FILE *myFile, bool withErrors){
    fprintf(myFile, "currentDir=$(pwd)\n\
\n\
gcc \"$codename\"\".c\" -o \"$codename\";\n\
resulExist=$(find resul -ignore_readdir_race | wc -l);\n\
if [ $resulExist -eq 0 ]\n\
then\n\
    echo \"Making dir of resuls, naming 'resul'\"\n\
    mkdir resul\n\
fi\n\
\n\
quantity_ex=$(ls testes | wc -l)\n\
quantity_ex=$(expr $quantity_ex / 2)\n\
\n\
for i in $(seq 1 $quantity_ex); do \"$currentDir\"/\"$codename\" < \"$currentDir\"/testes/$i.in > \"$currentDir\"/resul/$i.my; done\n\
\n");

    if(withErrors) makeErrors(myFile);
    else fprintf(myFile, "\tfor i in $(seq 1 5); do\n\
    rm -f -r errors\n\
    diff --color \"$currentDir/testes/$i.out\" \"$currentDir/resul/$i.my\"\n\
    done\n");

}


void showHelp(){
    printf("runallex [options]\n");
    printf("\t-h\n\t\t-> Show help.\n\n");
    printf("\t\tWith filename after runallex might be faster...\n\t\t-> runallex filename.\n\n");
    printf("\t-ne\n\t\t->Run with no errors output.\n\n");
    printf("\t\t-> by default it shows all error output and creates the error folder.");
}

void showError(FILE *myFile){
    printf("ERROR: A lot of argumets.\n");
    printf("->\"runallex -h\" for more information.");
    fclose(myFile);
    system("rm run_all_ex.sh");
}

int main(int argc, char *argv[]){
    bool withErrors = true;
    FILE *myFile = fopen("run_all.sh", "w");
    fprintf(myFile, "#!/bin/bash\n");

    if(argc < 2) fprintf(myFile, "\nread -p \"Name of code: \" codename;\n\n");
    else if(argc < 3){
        if(!strcmp(argv[1], "-h")){
            showHelp();
            return 0;
        }
        else if(!strcmp(argv[1], "-ne")){
            fprintf(myFile, "\nread -p \"Name of code: \" codename\n\n");
            withErrors = false;
        }
        else fprintf(myFile, "codename=\"%s\"\n\n", argv[1]);
    }
    else {
       showError(myFile);
       return 1;
    }
    makePattern(myFile, withErrors);
    fclose(myFile);

    system("sh run_all.sh");
    system("rm run_all.sh");

    return 0;
}