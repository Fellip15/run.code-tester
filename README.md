# tester-codes
This code will compile and execute your code, making a folder with the resuls and errors.

# Requiriments
..* A folder with name "testes" in the same dir of code and where you want to put the resuls and the errors.

..* That folder, "testes", must have the file ".in", the file that will make the same thing that a input, and the ".out", the expected output, to compare both of them and show the differences.

..* Compile the "run_all.c" to make the executable file to run the code.

..* [Optional] Make alias:
    1. If you are using bash standart, the alias should be in "\~/.bashrc". In this case you must open this file and put "alias name_command=dir_run_all/run_all.c", where name_command is the name of your command [can be any name] and dir_run_al is the folder of the file "run_all". It's recommended that the file be in the home folder, but it's not necessary.
    2. If you are using something other than bash, you must search where is your source. For example, the source of oh-my-zsh is at "~/.zshrc".
    
# How to use
..* After you create your alias, just go to the folder of your code that you want to compile and run the command. If you don't have alias, just run /dir_run_all/run_all.

..* Don't forget to put a test folder named "testes", with the .in and .out, and the file.c that you want to compile.

..* Isn't necessary to put .c after the filename.

..* The compiler have two flags:

    1. "-h" 
      . Can be run with put -h after the alias or after the /dir_run_all/run_all.
      . Show some informations of the code.
      
    2. "-ne"
      . Can be run with put -h after the alias or after the /dir_run_all/run_all.
      . Run the code withouth errors.
      
..* The code have two ways to run, the first you can put the name of file that you want to compile after the alias or the /dir_run_all/run_all, like "runallex cool_code", with the "cool_code.c" in the same folder, and the second is just run the alias or the /dir_run_all/run_all, after that will appear a message asking to the filename, so, just put the name and finish.

..* Will appear two folders: 

    1. resul: with the results of your code.
    2. errors: the differences between your output and the expected output (.out).
