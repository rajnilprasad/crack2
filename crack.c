#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hashString = md5(plaintext, strlen(plaintext)); 
    // Get the MD5 hash of the plaintext

    // Open the hash file
    FILE *file = fopen(hashFilename, "r");
    if (file == NULL) {
        perror("Error opening hash file");
        return NULL; // Error opening file
    }

    // Loop through the hash file, one line at a time.
    char line[HASH_LEN]; // Buffer for each line in the hash file
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the line
        line[strcspn(line, "\n")] = 0; 

    // Attempt to match the hash from the file to the
     if (strcmp(line, hashString) == 0) {
    // hash of the plaintext.
    free(hashString);
    fclose(file);
    // If there is a match, you'll return the hash.
    return strdup(line);
     }
    }
    
     //   Free memory?
    free(hashString);
    //   Close files?
    fclose(file);

     // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    //return "0123456789abcdef0123456789abcdef";
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    //char *found = tryWord("hello", "hashes00.txt");
   // printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (dictFile == NULL) {
        perror("Error opening dictionary file");
        exit(1);
    }

     // Variable to count the number of hashes cracked
    int crackedCount = 0;

    // For each dictionary word, pass it to tryWord, which
    char dictWord[PASS_LEN];
    // will attempt to match it against the hashes in the hash_file.
    while (fgets(dictWord, sizeof(dictWord), dictFile)){
        dictWord[strcspn(dictWord, "\n")] = 0;
    
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    char *result = tryWord(dictWord, argv[1]);
        if (result) {
            printf("%s %s\n", result, dictWord); // Print the found hash and word
            free(result); // Free the duplicated string
            crackedCount++; // Increment the cracked count
        }
    }
    
    // Close the dictionary file.
    fclose(dictFile);

    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!\n", crackedCount);
    
    // Free up any malloc'd memory?
}

