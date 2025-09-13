# Repository Description

Repository for personal project development, with the main focus being on developing necessary skills and knowledge required in the field.

## Compression Project

Language: C++  
Lines of Code: 1642  
Updated: 8/11/2025

Consists of a compression algorithm, a decompression algorithm, and a comparison algorithm.

Compression Algorithm:  
The compression algorithm works using simple string compression, not binary compression. It tokenizes an input file into three general token types: Single, String, and Digit. Single tokens include punctuation, whitespace, and special characters, and are not compressed. This is because these types of characters often show up on their own or attached to other words that may be repeated elsewhere, so treating them as single tokens that remain uncompressed increases compression efficiency (maybe). String and digit tokens are both compressed, and represent sequences of characters and numbers, respectively. To compress, the algorithm analyzes the frequency of the String and Digit tokens using an unordered map, then uses a custom-built max heap to organize these tokens by decreasing frequency. Then, going in decreasing order through the Heap, it compresses each token into a smaller character. This works through a combination of a string of the compression characters ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") and a vector tracking indexes. It starts with the vector containing \[0\], the increments to \[len(compression characters)\]. Once it arrives there, it resets to \[0, 0\], then increments the second value to the length of compression characters, then resets at \[1, 0\], and so on and so forth, adding a new integer to the vector once the existing integers have reached the maximum value. To create the compressed string, it simply indexes the compression characters string with the indexes contained in the vector. Lastly, the algorithm steps through the tokenized file and replaces String and Digit tokens with the corresponding compressed version, and writes an unordered map of compressed strings to uncompressed strings at the top of the file.

When working with folders, the compression algorithm analyzes all of the tokens in all of the text-based files in the folder and subfolders, and builds a frequency map and compression map out of all the tokens. It then writes the compression map into its own file named 'map.compression' within the topmost parent directory. Once this is done, the algorithm recursively goes through all the files and subdirectories within the parent directory, recreating each file and folder, compressing text-based files. If the file is not text-based, such as an image, it will simply move the image file to the new directory.

Usage: ./compress \<input file or folder\> \<-f or -d\> \<output file or folder\>  
-f : indicates an input file, and to write to an output file  
-d : indicates an input file or folder, and to write to an output folder

If the output file or folder name exists, it will prompt the user if they want to rewrite the content in the existing file or folder.

Decompression Algorithm:  
The decompression algorithm works by again tokenizing the file first, with tokens Single and String. Before tokenizing, it will either read the compression map from the beginning of the file and build its own unordered map mapping the compressed string to the uncompressed string, or read the 'map.compressed' file and build the same. Once the decompression map is built and the file tokenized, it will rebuild the file or the folder by replacing the compressed string with the uncompressed string. It will also move any uncompressed files, such as images, to the new directory. Unlike the compression algorithm, it assumes that if the input is a file, it will output a file. If the input is a folder, it will output a folder.

Usage: ./decompress \<input file or folder\> \<output file or folder\>

Again, if the output folder or file name exists, it will prompt the user if they want to rewrite the content in the existing file or folder.

Comparison Algorithm:  
This algorithm works by reading in two files or folders, and adding all of the text-based content into one huge string. Then, it will prompt the user for an exact character comparison. What this does is go character by character for both input strings, and checks to see if either are a mismatch. If there is a mismatch between characters, it will tell the user that the files or folders do not exactly match, but if there are no mismatches it will tell the user that the files or folders do exactly match. This was intended to ensure that compression was lossless. It will then prompt the user for a size comparison, which will analyze the lengths of the two strings and inform the user which file or folder is smaller, and what percentage the smaller file or folder is of the larger one. For example, it might give a result that says the first file is 63% the size of the second file. This was intended to analyze how much compression actually took place.

Usage: ./compare \<input file or folder 1\> \<input file or folder 2\>


## Java 2D Practice

Language: Java  
Updated: 9/13/2025  

Practice in using Java 2D utilities, as well as practice in the language itself.

## Library Project and Budget Project

*No longer in current development*

Both intended as a practice in using Python and Object Oriented Programming. They have served their purpose.
