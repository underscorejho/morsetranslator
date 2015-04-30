# morsetranslator

*A program to translate morse code to english text and vice-versa.*

Implented in C, using a binary tree to store -t translations and a 'hash table' to store -m translations.

Using the command line, the format for arguments is as follows:

    (exe name) (input file) (output file) (mode)

ex.

    ./bin/morse txt/text.txt txt/out.txt -m
    
    ./bin/morse txt/morse.txt txt/out.txt -t
    
    
------------------------
### Installing:

1. Clone the repository
2. Run `make` in the current directory to create an executable in `./bin` called `morse`
3. Run `morse` on whatever text you need translated
