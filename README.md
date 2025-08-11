# Repository Description

Repository for personal project development, with the main focus being on developing necessary skills and knowledge required in the field.

## Compression Project

Language: C++
Lines of Code: 1642

Consists of a compression algorithm, a decompression algorithm, and a comparison algorithm.

Compression Algorithm:
The compression algorithm works using simple string compression, not binary compression. It tokenizes an input file into three general token types: Single, String, and Digit. Single tokens include punctuation, whitespace, and special characters, and are not compressed. This is because these types of characters often show up on their own or attached to other words that may be repeated elsewhere, so treating them as single tokens that remain uncompressed increases compression efficiency (maybe). String and digit tokens are both compressed, and represent sequences of characters and numbers, respectively. To compress, the algorithm analyzes the frequency of the String and Digit tokens using an unordered map, then uses a custom-built max heap to organize these tokens by decreasing frequency. Then, going in decreasing order through the Heap, it compresses each token into a smaller character. This works through a combination of a string of the compression characters ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") and a vector tracking indexes. It starts with the vector containing \[0\], the increments to \[len(compression characters)\]. Once it arrives there, it resets to \[0, 0\], then increments the second value to the length of compression characters, then resets at \[1, 0\], and so on and so forth, adding a new integer to the vector once the existing integers have reached the maximum value. To create the compressed string, it simply indexes the compression characters string with the indexes contained in the vector. Lastly, the algorithm steps through the tokenized file and replaces String and Digit tokens with the corresponding compressed version, and writes an unordered map of compressed strings to uncompressed strings at the top of the file.

When working with folders, the compression algorithm analyzes all of the tokens in all of the text-based files in the folder and subfolders, and builds a frequency map and compression map out of all the tokens. It then writes the compression map into its own file named 'map.compression' within the topmost parent directory. Once this is done, the algorithm recursively goes through all the files and subdirectories within the parent directory, recreating each file and folder, compressing text-based files. If the file is not text-based, such as an image, it will simply move the image file to the new directory.

Usage: ./compress \<input file or folder\> \<-f or -d\> \<output file or folder\>
-f : indicates an input file, and to write to an output file
-d : indicates an input file or folder, and to write to an output folder

If the output folder name exists, it will prompt the user if they want to rewrite the content in the existing file or folder.

## Library Project

*No longer in current development*

Was intended as a practice in working with classes and their associated instance variables and methods.

## Budget Project

The budget project is a different way of practicing classes and their associated programming techniques, and the end goal is to build a simple budgeting software. This budgeting software must be able to track expenses and savings, can assign names and categories to each budget, maintain a history of the past budget iterations, have a user-friendly UI, and be an exececutable on the desktop. This project will be done in three phases:

1. Back-end development
2. Front-end UI development
3. Final features and creating the executable

Back-end development includes building the classes and associated methods needed for handling the data the user will input. This also includes a method for saving to and reading from a file to save the data between uses.

Front-end UI development will involve mainly building the UI for the program, and will use Python libraries, the details of which are not yet set.

Lastly, final features will implement any final features that seem relevant to include, and will create a python executable using the relevant libraries so that the program can be run from the desktop, without the use of an IDE.

**Current Progress:** The first phase is almost complete.

## Genome Project

Mostly a fun project, this project aims to analyze a genome, given the base-pair sequence of such. Details are not yet decided upon, but will likely include a frequency analysis, finding any genes and notating them as such, and determining the protein order of the genes.
