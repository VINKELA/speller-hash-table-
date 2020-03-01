/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
 #include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hashfunc(const char* word);

/**
 * Returns true if word is in dictionary else false.
 */
#define SIZE 17576

// no of words in the dictionary.
int noOfWords;

// declares a struct node.
typedef struct node
{
    char word[LENGTH];
    struct node* next;
}
node;
// declares a hash table
node* hashTable[SIZE];
// function check if a word is in the dictionary
bool check(const char* word)
{

	// gets the hashval of the word.
    int hashVal = hashfunc(word);
    int n = strlen(word);
	// declares the cursor pointer and points it the hashtable
    node* cursor = hashTable[hashVal];
	// gets the length of word
    char temp1 [n + 1];
	// copys the word into temp

	strcpy(temp1, word);
	char* temp = temp1;
	
	// loop changes the letters of the word to small letters
    for(int i = 0; i < n; i++)
    {
		 // if letter is a capital letter change to small letter
        if((temp[i] >= 'A') && (temp[i] <= 'Z'))
        {   
            temp[i] = tolower(temp[i]);
        }
        
    }

    // compare the word with each word in the the row of the hash table
    while(cursor!= NULL)
    {
        // if word is found return true else check next word
        if((strcmp(temp, cursor -> word) == 0))
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }
 	// return false if word is not found..
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // opens the dictionary and assigns a pointer to it
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        printf("couldnt open dictionary");
        return false;
    }
    
    
    while(true)
    {	
		// mallocs a new block of memory
        node* newNode = malloc(sizeof(node));
		// reads a string from dictionary and stores it in the node
        fscanf(file, "%s", newNode -> word);
        if(feof(file))
        {
            free(newNode);
            break;
        }
        //current holds the current word
        const char* current = newNode -> word;
		// gets the hash value of the word from the hash function.
        int hashVal = hashfunc(current);
		// if the hashvalue points to null, create a new row and add the word
        if(hashTable[hashVal] == NULL)
        {
            hashTable[hashVal] = newNode;
            newNode -> next = NULL;
            noOfWords ++;
            
        }
		// check the elements and fix the word at an appropriate positon. 
        else
        {
            node* tcursor = hashTable[hashVal];
   
            while(true)
            {
               if(tcursor -> next == NULL)
              
               {
                    newNode -> next = tcursor -> next;
                    tcursor -> next = newNode;
                    noOfWords ++;
                    break;
               }
               
               else
               {
                    
                    tcursor = tcursor -> next;
               }
               
             
           }
            
          
      }
    }
	// close file
    fclose(file);
	// return true.
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // returns the no of words
    return noOfWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < SIZE; i++)
    {
        node* cursor = hashTable[i];
        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
}


// defines a hash function
// This hash function was derived by me and has alot of potentials
// for possible improvement.
// it assigns 26 rows to each alphabet in the hash table 
// it could be easily be more.
// it uses the first and second letter in the word.
int hashfunc(const char* word)
{
    // get the first word of the word and its corresponding ascii value
    int index = tolower(word[0]) - 'a';
	// gets the first position of the first letter on the hashtable
    int value = index * 676;
    int n = strlen(word);
    if (n == 1 || word[1] == '\'')
    {
        return value;
    
    }
    else
    {
        int index2 = tolower(word[1]) - 'a';
        int value2 = index2 * 26;
        if(n == 2 || word[2] == '\'')
        {
            return (value + value2);
        }
        else
        {
            int index3 = tolower(word[2]) - 'a';
            return (value + value2 + index3);
        }
    }

}
