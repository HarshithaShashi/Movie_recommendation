#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    char title[100];
    char genre[50];
    float rating;
    int release_year;
    struct Movie* next;
};

struct Movie* head;

struct Movie* createMovieNode() {
    struct Movie* newNode = (struct Movie*)malloc(sizeof(struct Movie));

   
    newNode->next = NULL;
    printf("Enter movie title: ");
    scanf(" %s", newNode->title);
    printf("Enter genre: ");
    scanf(" %s", newNode->genre);
    printf("Enter rating (out of 10): ");
    scanf("%f", &newNode->rating);
    if (newNode->rating > 10) {
        printf("Rating should not be greater than 10\n ");
        return NULL;
    }
    else {
        printf("Enter release year: ");
        scanf("%d", &newNode->release_year);
 }
    return newNode;
}


int movieExists(struct Movie* head, char title[]) {
    struct Movie* current = head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}


void addMovie(struct Movie** head) {
    struct Movie* newMovie = createMovieNode();
    if (newMovie == NULL) {
        printf("Movie not added. Please enter valid details.\n");
        return;
    }

    if (movieExists(*head, newMovie->title)) {
        printf("Movie '%s' already exists in the list.\n", newMovie->title);
        free(newMovie);
        return;
    }
struct Movie* current = *head;
    if (*head == NULL) {
        *head = newMovie;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newMovie;
    }
    printf("Movie added successfully!\n");
}

void displayMovies(struct Movie* head) {
    if (head == NULL) {
        printf("Movie list is empty. Please add the movies to continue\n");
        return;
    }

    printf("\n----------- All Movies -----------\n");
    struct Movie* current = head;
    int count = 1;

    while (current != NULL) {
        printf("\nMovie %d:\n", count);
        printf("Title: %s\n", current->title);
        printf("Genre: %s\n", current->genre);
        printf("Rating: %.2f\n", current->rating);
        printf("Release Year: %d\n", current->release_year);
        current = current->next;
        count++;
}
    printf("\n");
}

void recommendMovies(struct Movie* head, char genre[], float minRating) {
    struct Movie* current = head;
    int count = 1;
    int found = 0;

    printf("\n----------- Recommended Movies -----------\n");
    while (current != NULL) {
        if (strcmp(current->genre, genre) == 0 && current->rating >= minRating) {
            printf("\nRecommended Movie %d:\n", count);
            printf("Title: %s\n", current->title);
            printf("Genre: %s\n", current->genre);
            printf("Rating: %.2f\n", current->rating);
            printf("Release Year: %d\n", current->release_year);
            count++;
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No movies found matching your preferences.\n");
    }
    printf("\n");
}


void deleteMovie(struct Movie** head, char title[]) {

    if (*head == NULL) {
        printf("Movie list is empty. No movie to delete.\n");
        return;
    }

    struct Movie* prev = NULL;
    struct Movie* current = *head;

   
    while (current != NULL && strcmp(current->title, title) != 0) {
        prev = current;
        current = current->next;
    }

    
    if (current == NULL) {
        printf("Movie not found in the list.\n");
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    }
    else {
        prev->next = current->next;
    }

    free(current);
    printf("Movie deleted successfully.\n");
}

int main() {
    struct Movie* head = NULL;
    int choice;
    char userGenre[50];
    float userMinRating;

    do {
        printf("------ Movie Recommendation System ------\n");
        printf("1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Recommend Movies\n");
        printf("4. Delete Movies\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMovie(&head);
                break;
            case 2:
                displayMovies(head);
                break;
            case 3:
                printf("Enter your preferred genre: ");
                scanf(" %s", userGenre);
                printf("Enter your minimum rating preference (out of 10): ");
                scanf("%f", &userMinRating);
                recommendMovies(head, userGenre, userMinRating);
                break;
            case 4:
                printf("Enter the movie title to be deleted: ");
                scanf("%s", userGenre);
                deleteMovie(&head, userGenre);
                break;
            case 5:
                printf("Exiting the Movie Recommendation System. Thank you!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

return 0;
}

