SU-Assignment-5-DA4007
The 5th assignment for SU DA4007
This is my first Comit 16/10/2026

----------------------------------------------------------------------------
    PROGRAM DESCRIPTION
----------------------------------------------------------------------------
The purpose of this program is to be able to generate text from a training text and then have the program return a specified number of characters.
This program also have the option to use a laplace smoothing function or simply stick to the generated alphabet from the training text.

It's so far the situation that laplace smoothing doesn't generate as a cohesive text as the non-smoothing option


This program contains 6 files (7 with the .gitignore)

These are the class files and their respective headers
LanguageModel.h
LanguageModel.cpp

TextGenerator.h
TextGenerator.cpp

This is the main program file that combines the functions of each class by including each head files:

main.cpp


This file compiles these 5 files above into a function called ./sml:

Makefile


we also include a .gitignore to make sure that generated files like objects and executables are not comitted

----------------------------------------------------------------------------
    File Descriptions
----------------------------------------------------------------------------
1. LanguageModel.h
Defines the LanguageModel class, including its variables and function declarations. It specifies how the model stores k-gram frequencies, character transitions, the alphabet, and pseudocount settings.

2. LanguageModel.cpp
Implements the LanguageModel class. It trains the model on input text, counts k-grams and following characters, and calculates transition probabilities, including optional pseudocount/laplace smoothing.

Short:
You therefore have the option to include laplace smoothing in your requested text generation in addition to how many characters you want generated. The smoothing option allows for the appearance of characters that did not appear in the training text. This is why you are more likely to see random charcters in a smoothing generation (i.e., in this case the probability of a character isn't zero despite not appearing in the training text)

3. TextGenerator.h
Defines the TextGenerator class and declares its text-generation function. It connects a trained language model to the random number generator used to produce text.

4. TextGenerator.cpp
Implements text generation. It randomly selects a starting k-gram based on its frequency, samples subsequent characters according to transition probabilities, and continues until the requested length is reached or no next character is available.

Short:
TextGenrator.cpp and .h uses the class LanguageModel to generate text and thus generates text based on a trained alphabet "no smoothing" or uses a pseudo count that assigns a non-zero probability to other characters that doesn't appear in the training text

5. main.cpp
The main.cpp file contains the main() function, which controls the program. It reads and validates command-line arguments, handles the optional pseudocount (-a), opens the training text file, creates and trains the LanguageModel, and uses TextGenerator to generate and print the requested number of characters. It also catches exceptions and prints descriptive error messages if something goes wrong.

Short:
This is the program that combines the classes and handles the input from the user

6. Main 
This file compiles the program in its correct order

7. gitignore
This file prevents generated executables or objects from being committed

----------------------------------------------------------------------------
 The main program
----------------------------------------------------------------------------

code structure:

./slm k file.txt requested_number_of_generated_characters

./slm = runs the compiles program called slm "small language Model"

k = is the k-grams size

file.txt = is the training text

requested_number_of_generated_characters = is the number of characters we want generated from the small language model

with pseudocount smoothing/laplace smoothing:

./slm -a 0.01 k file.txt requested_number_of_generated_characters

-a 0.01 = sets the smoothing parametre alpha to 0.01


----------------------------------------------------------------------------
Code to run:
----------------------------------------------------------------------------

To compile the whole program:

make

for the file a modest proposal.txt:

without smoothing:

for the file a modest proposal.txt

./slm 3 a_modest_proposal.txt 100

./slm 5 a_modest_proposal.txt 500

with smoothing

./slm -a 0.01 3 a_modest_proposal.txt 100


----------------------------------------------------------------------------
Test-files for the Language Model [SML_test_files]

    "please note that these files are only for me to check my Work hence their location in SML_test_files"
----------------------------------------------------------------------------

File: LanguageModel.cpp
test_file: test_language_model-cpp

NOTE:
This test whether the constructor rejects an invalid k-grams size and 
if the training text is too short to contain k-grams and a following character

code to compile and run:

g++ -std=c++17 -Wall -Wextra -pedantic -Isrc \
    src/test_language_model.cpp src/LanguageModel.cpp \
    -o test_language_model

./test_language_model

expected output:

PASS: Invalid k rejected
PASS: Short text rejected


----------------------------------------------------------------------------

File: LanguageModel.h
test_file: test_language_model_header.cpp

NOTE:
This checks if another c++ file can include the file and if it
can use the functions that are public and if constructor, training and getter functions are accessible and work together

code to compile and run:

g++ -std=c++17 -Wall -Wextra -pedantic -Isrc \
    test_language_model_header.cpp src/LanguageModel.cpp \
    -o test_language_model_header

./test_language_model_header

expected output:

PASS: LanguageModel.h interface works

----------------------------------------------------------------------------
Test Files for the Text Generator
----------------------------------------------------------------------------

File:LanguageModel.cpp
Test_file: test_text_generator.cpp 

NOTE:
This tests verifier that the generator rejects an output length smaller than k and reports an error when the model hasn't been trained.
it checks for invalid arguments and run time error

code to compile and run:

g++ -std=c++17 -Wall -Wextra -pedantic -Isrc \
    test_text_generator.cpp src/LanguageModel.cpp \
    src/TextGenerator.cpp -o test_text_generator

./test_text_generator

Expected Output:
PASS: Short output rejected
PASS: Empty model rejected
----------------------------------------------------------------------------

File: LanguageModel.h
test_File: test_text_generator_header.cpp

NOTE:
This test verifies that the generator can be constructed from a trained language model and that its generate() function returns the asked number of
characters.
it specifically checks the output length and not the exact characters 

code to compile and run:

g++ -std=c++17 -Wall -Wextra -pedantic -Isrc \
    test_text_generator_header.cpp src/LanguageModel.cpp \
    src/TextGenerator.cpp -o test_text_generator_header

./test_text_generator_header

Expected output:

PASS: TextGenerator.h interface works

----------------------------------------------------------------------------
File: main.cpp
test_File; test_main.cpp

NOTE:
This file test the main program file for:

1. Valid arguments
The program accepts valid inputs and generates text.

2. Pseudocount smoothing
The -a 0.01 option works correctly.

3. Invalid k
The program rejects a k-gram size of 0.

4. Invalid output length
The program rejects an output length smaller than k.

5. Missing file
The program reports an error when the training file cannot be opened.

6. Unknown option
The program rejects an unsupported option such as -x.

7. Negative pseudocount
The program rejects a negative smoothing value.

8. Missing pseudocount
The program rejects -a when no value follows it.

9. Training text too short
The program rejects text that contains no k-gram followed by another character.

10. UTF-8 normalization
The program processes text containing curly apostrophes and dashes and checks that the generated output contains only ASCII bytes.


Code to compile and run:

g++ -std=c++17 -Wall -Wextra -pedantic src/test_main.cpp -o test_main

./test_main

Expected output:

PASS: Valid arguments
PASS: Pseudocount smoothing
PASS: Reject k = 0
PASS: Reject output length smaller than k
PASS: Reject missing training file
PASS: Reject unknown option
PASS: Reject negative pseudocount


