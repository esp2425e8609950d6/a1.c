/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Include for isalpha function, inspired by "https://www.programiz.com/c-programming/library-function/ctype.h/isalpha"
#define NUM_CANDIDATES 5

// Structure definition for each candidate with an ID, votes, and percentage of total votes.
// Structure reference based on C basics from "cplusplus.com" [source: https://cplusplus.com/doc/tutorial/structures/]
struct Candidate {
    char id;
    int votes;
    float percentage;
};

// Function prototypes
void inputCandidateIDs(struct Candidate candidates[]); // Used to enter IDs for each candidate
void inputCandidateVotes(struct Candidate candidates[]); // Used to enter votes for each candidate
void calculateResults(struct Candidate candidates[]); // Used to calculate the percentage of votes each candidate got
void displayResults(struct Candidate candidates[]); // Display the results in detail
void displayWinners(struct Candidate candidates[]); // Announce the winners

int main() {
    struct Candidate candidates[NUM_CANDIDATES]; // Array of 5 candidates

    // Greet the user (because who doesnt like a friendly election simulator?)
    printf("Welcome to the worlds greatest Election Simulator!\n");

    // 1. Input candidate IDs and votes, all nicely wrapped in functions
    inputCandidateIDs(candidates);
    inputCandidateVotes(candidates);

    // 2. Calculate and display the results
    calculateResults(candidates);
    displayResults(candidates);

    // 3. Announce the winners
    displayWinners(candidates);

    // End message
    printf("\nThank you for using the worlds greatest Election Simulator!\n");
    return 0;
}

// Function to input unique IDs for each candidate, ensuring only letters are allowed
void inputCandidateIDs(struct Candidate candidates[]) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int valid = 0;
        while (!valid) {
            printf("Please enter an ID for candidate %d (single letter only): ", i + 1);
            scanf(" %c", &candidates[i].id);

            // Check if ID is a letter and if it's unique
            valid = isalpha(candidates[i].id); // Ensure input is a letter
            if (!valid) {
                printf("[Error] Invalid input! Only letters are allowed.\n");
                continue;
            }

            // Checking for unique IDs (based on a simple approach on Stack Overflow [source: https://stackoverflow.com/questions/14090530/])
            for (int j = 0; j < i; j++) {
                if (candidates[i].id == candidates[j].id) {
                    printf("[Error] This ID is already in use/not available!\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
}

// Function to input votes for each candidate
void inputCandidateVotes(struct Candidate candidates[]) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int valid = 0;
        while (!valid) {
            printf("Please enter the amount of votes for candidate \"%c\" (1 to 1000): ", candidates[i].id);

            // Ensure the user enters a number, not a letter
            if (scanf("%d", &candidates[i].votes) != 1) {
                // Handle invalid input (non-numeric input)
                printf("[Error] Invalid input! Please enter a valid number for votes.\n");
                // Clear input buffer to avoid infinite loop; inspired by "https://stackoverflow.com/questions/36021987/infinite-loop-when-trying-to-clear-the-input-buffer"
                while(getchar() != '\n');
                continue;  // Restart the loop for this candidate
            }

            // Validate vote range
            if (candidates[i].votes < 1 || candidates[i].votes > 1000) {
                printf("[Error] Votes must be between 1 and 1000. Please try again.\n");
                continue;  // Ask for input again if votes are out of range
            }

            valid = 1;  // Valid input, move to the next candidate
        }
    }
    
    // Now, after all votes have been entered, ask for confirmation
    int confirmVotes = 0;
    while (confirmVotes != 1) {
        printf("\nAre you sure these inputs are correct? Press 1 to confirm, or 2 to re-enter all votes: ");
        // Confirm function concept: "https://codeforwin.org/c-programming/if-else-programming-practice" and "Assignment 1 Intro - Coding TU Graz"
        scanf("%d", &confirmVotes);
        
        if (confirmVotes == 2) {
            printf("\nLet's re-enter the votes for all candidates.\n");
            // Re-enter all votes if the user chooses 2 (no confirmation)
            inputCandidateVotes(candidates);
        } else if (confirmVotes != 1) {
            printf("[Error] Invalid selection. Please press 1 or 2.\n");
        }
    }
}

// Calculate each candidate's percentage of the total vote
void calculateResults(struct Candidate candidates[]) {
    int totalVotes = 0;
    // Summing up votes, based on an example on Tutorialspoint [source: https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm]
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        totalVotes += candidates[i].votes;
    }
    // Calculating percentages (inspired by examples of basic arithmetic on Stack Overflow [source: https://stackoverflow.com/questions/2992605/])
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        candidates[i].percentage = ((float)candidates[i].votes / totalVotes) * 100;
    }
}

// Function to display the election results
void displayResults(struct Candidate candidates[]) {
    printf("\nThe results of the election are:\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        // Displaying formatted output, inspired by "printf" examples on cplusplus.com [source: https://cplusplus.com/reference/cstdio/printf/]
        printf(" - Candidate \"%c\": %.2f%% (%d votes).\n", candidates[i].id, candidates[i].percentage, candidates[i].votes);
    }
}

// Function to announce the winner(s)
void displayWinners(struct Candidate candidates[]) {
    int maxVotes = 0;
    int numWinners = 0;

    // Determine highest vote count
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
        }
    }

    // Count how many candidates received the max vote count (for ties)
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        if (candidates[i].votes == maxVotes) {
            numWinners++;
        }
    }

    // Announce the winners (single or tied)
    printf("\nPlease congratulate the winner(s) of the election:\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        if (candidates[i].votes == maxVotes) {
            printf(" - Candidate \"%c\"!\n", candidates[i].id);
        }
    }

    // Handle tie announcement
    if (numWinners > 1) {
        printf("\nThat's a %d-way tie! The drama is real.\n", numWinners);
    }
}


