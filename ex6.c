//Ex6 
//Jonathan Djerassi 303013098

#include "ex6.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_BUFFER 128

//function for help
// Removes leading and trailing spaces, tabs, and carriage returns from a given string.
// Reads a dynamically sized input string from the user, trims whitespace, and returns the result.
// Safely reads an integer from user input, validates it, and prompts again for invalid input.
// Duplicates a given string by allocating memory and copying the content. Returns NULL if allocation fails.
// Returns the string name of a given PokemonType enum value. Defaults to "UNKNOWN" for invalid types.
// Calculates and returns the number of nodes in a circular linked list of owners. Returns 0 if the list is empty.
void trimWhitespace(char *str) {
    // Remove leading spaces/tabs/\r
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;

    if (start > 0) {
        int idx = 0;
        while (str[start])
            str[idx++] = str[start++];
        str[idx] = '\0';
    }

    // Remove trailing spaces/tabs/\r
    int len = (int) strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}
char *getDynamicInput() {
    char *input = NULL;
    size_t size = 0, capacity = 1;
    input = (char *) malloc(capacity);
    if (!input) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (size + 1 >= capacity) {
            capacity *= 2;
            char *temp = (char *) realloc(input, capacity);
            if (!temp) {
                printf("Memory reallocation failed.\n");
                free(input);
                return NULL;
            }
            input = temp;
        }
        input[size++] = (char) c;
    }
    input[size] = '\0';

    // Trim any leading/trailing whitespace or carriage returns
    trimWhitespace(input);

    return input;
}
int readIntSafe(const char *prompt) {
    char buffer[INT_BUFFER];
    int value;
    int success = 0;

    while (!success) {
        printf("%s", prompt);

        // If we fail to read, treat it as invalid
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Invalid input.\n");
            clearerr(stdin);
            continue;
        }

        // 1) Strip any trailing \r or \n
        //    so "123\r\n" becomes "123"
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';
        if (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
            buffer[--len] = '\0';

        // 2) Check if empty after stripping
        if (len == 0) {
            printf("Invalid input.\n");
            continue;
        }

        // 3) Attempt to parse integer with strtol
        char *endptr;
        value = (int) strtol(buffer, &endptr, 10);

        // If endptr didn't point to the end => leftover chars => invalid
        // or if buffer was something non-numeric
        if (*endptr != '\0') {
            printf("Invalid input.\n");
        } else {
            // We got a valid integer
            success = 1;
        }
    }
    return value;
}
char *myStrdup(const char *src) {
    if (!src)
        return NULL;
    size_t len = strlen(src);
    char *dest = (char *) malloc(len + 1);
    if (!dest) {
        printf("Memory allocation failed in myStrdup.\n");
        return NULL;
    }
    strcpy(dest, src);
    return dest;
}
const char *getTypeName(PokemonType type) {
    switch (type) {
        case GRASS:
            return "GRASS";
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case BUG:
            return "BUG";
        case NORMAL:
            return "NORMAL";
        case POISON:
            return "POISON";
        case ELECTRIC:
            return "ELECTRIC";
        case GROUND:
            return "GROUND";
        case FAIRY:
            return "FAIRY";
        case FIGHTING:
            return "FIGHTING";
        case PSYCHIC:
            return "PSYCHIC";
        case ROCK:
            return "ROCK";
        case GHOST:
            return "GHOST";
        case DRAGON:
            return "DRAGON";
        case ICE:
            return "ICE";
        default:
            return "UNKNOWN";
    }
}
int getOwnerListSize() {
    if (ownerHead == NULL) {
        return 0; // The list is empty
    }

    int count = 1; // Start counting from the head
    OwnerNode *current = ownerHead->next;

    while (current != NULL && current != ownerHead) {
        count++;
        current = current->next;
    }

    return count;
}

//function for part 1
// Allocates memory for a new PokemonData structure, copies the given data into it, and returns a pointer to
// the allocated structure.
// Allocates memory for a new PokemonNode structure, initializes it with a dynamically created PokemonData pointer,
// and returns the node pointer.
// Creates a new OwnerNode with the given owner name and starter PokemonNode, and returns the pointer to the new node.
// Adds a new owner node into a circular doubly linked list, maintaining proper next and previous pointers.
// Checks if the given owner name already exists in the circular linked list. Returns 1 if the name is taken,
// otherwise 0.
// Handles the process of inserting a new owner and their starter Pokemon into the system. Validates input,
// ensures unique names, and updates the circular linked list.
PokemonData *createPokemeonDataPtr(const PokemonData data) {
    PokemonData *result = (PokemonData *) calloc(1, sizeof(PokemonData));
    result->id = data.id;
    result->TYPE = data.TYPE;
    result->hp = data.hp;
    result->attack = data.attack;
    result->CAN_EVOLVE = data.CAN_EVOLVE;
    result->name = (char *) calloc(strlen(data.name) + 1, sizeof(char));
    strcpy(result->name, data.name);
    return result;
}
PokemonNode *createPokemonNode(const PokemonData data) {
    PokemonNode *result = (PokemonNode *) calloc(1, sizeof(PokemonNode));
    result->data = createPokemeonDataPtr(data);
    return result;
}
OwnerNode *createOwner(char *ownerName, PokemonNode *starter) {
    OwnerNode *result = (OwnerNode *) calloc(1, sizeof(OwnerNode));
    result->ownerName = ownerName;
    result->pokedexRoot = starter;
    return result;
}
void linkOwnerInCircularList(OwnerNode *newOwner) {
    if (ownerHead == NULL) {
        ownerHead = newOwner;
        newOwner->next = newOwner;
        newOwner->prev = newOwner;
        return;
    }

    OwnerNode *last = ownerHead->prev;
    last->next = newOwner;
    newOwner->prev = last;
    newOwner->next = ownerHead;
    ownerHead->prev = newOwner;
}
int isNameAlreadyTaken(const char *name) {
    OwnerNode *current = ownerHead;
    if (current == NULL) return 0;
    do {
        if (strcmp(current->ownerName, name) == 0) {
            return 1;
        }
        current = current->next;
    } while (current != ownerHead);
    return 0;
}
void insertNewPokedex() {
    printf(" Your name:");
    char *name = getDynamicInput();
    if (isNameAlreadyTaken(name)) {
        printf(" Owner '%s' already exists. Not creating a new Pokedex.\n", name);
        free(name);
        return;
    }
    printf(" Choose Starter:\n1. Bulbasaur\n2. Charmander\n3. Squirtle\n");
    int choice = readIntSafe("Your choice:");
    int realPokemon = -1;
    if (choice == 1) {
        realPokemon = 0;
    } else if (choice == 2) {
        realPokemon = 3;
    } else if (choice == 3) {
        realPokemon = 6;
    }
    PokemonNode *pokemonNode = createPokemonNode(pokedex[realPokemon]);
    OwnerNode *ownerNode = createOwner(name, pokemonNode);
    linkOwnerInCircularList(ownerNode);
    printf(" New Pokedex created for %s with starter %s.", name, pokemonNode->data->name);
}

//function for part 2
// Prints the list of existing Pokedexes from the owner list.
// Displays the menu for managing an existing Pokedex of an owner.
// Adds a new Pokemon to the owner's Pokedex based on its ID and data.
// Returns the total number of nodes in the Pokemon tree.
// Displays the menu for displaying the owner's Pokedex using different traversal methods.
// Prints the details of a single Pokemon node.
// Performs a pre-order traversal of the Pokemon tree and applies a function to each node.
// Performs an in-order traversal of the Pokemon tree and applies a function to each node.
// Performs a post-order traversal of the Pokemon tree and applies a function to each node.
// Compares two Pokemon nodes by their names for alphabetical sorting.
// Extracts all Pokemon nodes from the tree into an array for sorting.
// Displays Pokemon in alphabetical order by their names.
// Performs a breadth-first search (BFS) traversal and displays Pokemon nodes.
// Finds and returns a Pokemon node by its ID in the Pokedex.
// Releases (removes) a Pokemon from the owner's Pokedex by its ID.
// Calculates a Pokemon's score based on its attack and HP for the battle.
// Simulates a fight between two Pokemon and determines the winner based on their scores.
// Evolves a Pokemon by changing its evolution status.
void printExistingPokedex() {
    if (ownerHead == NULL) {
        return;
    }
    if (ownerHead->next == NULL) {
        printf("1. %s\n", ownerHead->ownerName);
    } else {
        int counter = 1;
        OwnerNode *ptr = ownerHead;
        while (ptr->next != ownerHead) {
            printf("%d. %s\n", counter, ptr->ownerName);
            counter++;
            ptr = ptr->next;
        }
        printf("%d. %s\n", counter, ptr->ownerName);
    }
}
void enterExistingPokedexMenu() {
    if (ownerHead == NULL) {
        printf(" No existing Pokedexes.\n");
        return;
    }
    printf("\nExisting Pokedexes:\n");

    printExistingPokedex();
    int choice = readIntSafe("Choose a Pokedex by number: \n");


    OwnerNode *ownerNode = getOwnerNodeByIndex(choice);
    if (ownerNode == NULL) {
        printf("No owner found at index %d.\n", choice);
        return;
    }

    printf("\nEntering %s's Pokedex...\n", ownerNode->ownerName);
    int subChoice;
    do {
        printf("\n-- %s's Pokedex Menu --\n", ownerNode->ownerName);
        printf("1. Add Pokemon\n");
        printf("2. Display Pokedex\n");
        printf("3. Release Pokemon (by ID)\n");
        printf("4. Pokemon Fight!\n");
        printf("5. Evolve Pokemon\n");
        printf("6. Back to Main\n");

        subChoice = readIntSafe("Your choice: ");

        switch (subChoice) {
            case 1: {
                int pokemonId = readIntSafe("Enter ID to add:");
                pokemonId--;
                if (pokemonId < 0 || pokemonId > 150) {
                    printf(" Pokemon with ID %d not found.\n", pokemonId);
                } else {
                    PokemonData data = pokedex[pokemonId];
                    ownerNode->pokedexRoot = addPokemon(ownerNode->pokedexRoot, data, 1);
                }
                break;
            }
            case 2:
                displayMenu(ownerNode);
                break;
            case 3:
                freePokemon(ownerNode);
                break;
            case 4:
                pokemonFight(ownerNode);
                break;
            case 5:
                evolvePokemon(ownerNode);
                break;
            case 6:
                printf("Back to Main Menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (subChoice != 6);
}
PokemonNode *addPokemon(PokemonNode *root, PokemonData data, int shouldPrint) {
    if (root == NULL) {
        if (shouldPrint == 1) {
            printf(" Pokemon %s (ID %d) added.\n", data.name, data.id);
        }
        return createPokemonNode(data);
    }

    if (data.id < root->data->id) {
        root->left = addPokemon(root->left, data, shouldPrint);
    } else if (data.id > root->data->id) {
        root->right = addPokemon(root->right, data, shouldPrint);
    } else {
        if (shouldPrint == 1) {
            printf(" Pokemon with ID %d is already in the Pokedex. No changes made.\n", data.id);
        }
    }
    return root;
}
int countNodes(PokemonNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}
void displayMenu(OwnerNode *owner) {
    if (!owner->pokedexRoot) {
        printf("Pokedex is empty.\n");
        return;
    }

    printf("Display:\n");
    printf("1. BFS (Level-Order)\n");
    printf("2. Pre-Order\n");
    printf("3. In-Order\n");
    printf("4. Post-Order\n");
    printf("5. Alphabetical (by name)\n");

    int choice = readIntSafe("Your choice: ");

    switch (choice) {
        case 1:
            displayBFS(owner->pokedexRoot);
            break;
        case 2:
            preOrderTraversal(owner->pokedexRoot);
            break;
        case 3:
            inOrderTraversal(owner->pokedexRoot);
            break;
        case 4:
            postOrderTraversal(owner->pokedexRoot);
            break;
        case 5:
            displayAlphabetical(owner->pokedexRoot);
            break;
        default:
            printf("Invalid choice.\n");
    }
}
void printPokemonNode(PokemonNode *node) {
    if (!node)
        return;
    printf("ID: %d, Name: %s, Type: %s, HP: %d, Attack: %d, Can Evolve: %s\n",
           node->data->id,
           node->data->name,
           getTypeName(node->data->TYPE),
           node->data->hp,
           node->data->attack,
           (node->data->CAN_EVOLVE == CAN_EVOLVE) ? "Yes" : "No");
}
void preOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }

    visit(root);
    preOrderGeneric(root->left, visit);
    preOrderGeneric(root->right, visit);
}
void inOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return; // Base case: empty tree
    }

    inOrderGeneric(root->left, visit); // Recur on the left subtree
    visit(root); // Process the root node
    inOrderGeneric(root->right, visit); // Recur on the right subtree
}
void postOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }

    postOrderGeneric(root->left, visit);
    postOrderGeneric(root->right, visit);
    visit(root);
}
int comparePokemonByName(const void *a, const void *b) {
    PokemonNode *nodeA = *(PokemonNode **) a;
    PokemonNode *nodeB = *(PokemonNode **) b;
    return strcmp(nodeA->data->name, nodeB->data->name);
}
void extractNodesToArray(PokemonNode *root, PokemonNode **array, int *index) {
    if (root == NULL) {
        return;
    }
    extractNodesToArray(root->left, array, index); // Recur on left subtree
    array[(*index)++] = root; // Add the current node to the array
    extractNodesToArray(root->right, array, index); // Recur on right subtree
}
void displayAlphabetical(PokemonNode *root) {
    if (root == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    int totalNodes = countNodes(root);
    PokemonNode **nodeArray = (PokemonNode **) calloc(totalNodes, sizeof(PokemonNode *));
    if (nodeArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int index = 0;
    extractNodesToArray(root, nodeArray, &index);
    qsort(nodeArray, totalNodes, sizeof(PokemonNode *), comparePokemonByName);

    for (int i = 0; i < totalNodes; i++) {
        printPokemonNode(nodeArray[i]);
    }

    // Free the memory allocated for the array
    free(nodeArray);
}
void displayBFS(PokemonNode *root) {
    BFSGeneric(root, printPokemonNode);
}
PokemonNode *findPokemonById(PokemonNode *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data->id == id) {
        return root;
    } else if (id < root->data->id) {
        return findPokemonById(root->left, id);
    } else {
        return findPokemonById(root->right, id);
    }
}
void freePokemon(OwnerNode *owner) {
    if (!owner || !owner->pokedexRoot) {
        printf("No Pokemon to release.\n");
        return;
    }
    int pokemonId = readIntSafe("Enter Pokemon ID to release:");
    PokemonNode *parent = NULL, *current = owner->pokedexRoot;

    while (current && current->data->id != pokemonId) {
        parent = current;
        if (pokemonId < current->data->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (!current) {
        printf(" Pokemon with ID %d not found in the Pokedex.\n", pokemonId);
        return;
    }
    if (!current->left && !current->right) {
        if (!parent) {
            owner->pokedexRoot = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (!current->left || !current->right) {
        PokemonNode *child = current->left ? current->left : current->right;
        if (!parent) {
            owner->pokedexRoot = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        PokemonNode *successorParent = current;
        PokemonNode *successor = current->right;
        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }
        free(current->data->name);
        current->data->id = successor->data->id;
        current->data->TYPE = successor->data->TYPE;
        current->data->hp = successor->data->hp;
        current->data->attack = successor->data->attack;
        current->data->CAN_EVOLVE = successor->data->CAN_EVOLVE;
        current->data->name = myStrdup(successor->data->name);
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        current = successor;
    }
    printf(" Removing Pokemon %s (ID %d).\n", current->data->name, current->data->id);
    free(current->data->name);
    free(current->data);
    free(current);
}
double calculateScore(PokemonData *data) {
    return data->attack * 1.5 + data->hp * 1.2;
}
void pokemonFight(OwnerNode *owner) {
    if (owner->pokedexRoot == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    int id1 = readIntSafe("Enter ID of the first Pokemon:");
    int id2 = readIntSafe(" Enter ID of the second Pokemon: ");
    PokemonNode *pokemon1 = findPokemonById(owner->pokedexRoot, id1);
    PokemonNode *pokemon2 = findPokemonById(owner->pokedexRoot, id2);
    if (pokemon1 == NULL || pokemon2 == NULL) {
        printf("One or both Pokemon IDs not found.\n");
        return;
    }
    double score1 = calculateScore(pokemon1->data);
    double score2 = calculateScore(pokemon2->data);
    printf("Pokemon 1: %s (Score = %.2f)\n", pokemon1->data->name, score1);
    printf("Pokemon 2: %s (Score = %.2f)\n", pokemon2->data->name, score2);
    if (score1 > score2) {
        printf("%s wins!\n", pokemon1->data->name);
    } else if (score2 > score1) {
        printf("%s wins!\n", pokemon2->data->name);
    } else {
        printf("It's a tie!\n");
    }
}
void evolvePokemon(OwnerNode *owner) {
    if (owner->pokedexRoot == NULL) {
        printf("Cannot evolve. Pokedex empty.\n");
        return;
    }

    int oldID = readIntSafe("Enter ID of Pokemon to evolve:");
    PokemonNode *current = owner->pokedexRoot;
    PokemonNode *parent = NULL;

    // Find the Pokémon to evolve
    while (current != NULL && current->data->id != oldID) {
        parent = current;
        if (oldID < current->data->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL || current->data->id >= 152) {
        printf("No Pokemon with ID %d found.\n", oldID);
        return;
    }

    if (current->data->CAN_EVOLVE == CANNOT_EVOLVE) {
        printf("%s (ID %d) cannot evolve.\n", current->data->name, current->data->id);
        return;
    }

    int evolvedID = oldID + 1;
    PokemonNode *evolvedNode = findPokemonById(owner->pokedexRoot, evolvedID);

    if (evolvedNode != NULL) {
        // If the evolved form already exists
        printf("Pokemon evolved from %s (ID %d) to %s (ID %d).\n",
               current->data->name, oldID, evolvedNode->data->name, evolvedID);

        // Remove the base Pokémon (the one being evolved)
        if (parent == NULL) {
            owner->pokedexRoot = (current->left != NULL) ? current->left : current->right;
        } else if (parent->left == current) {
            parent->left = (current->left != NULL) ? current->left : current->right;
        } else {
            parent->right = (current->left != NULL) ? current->left : current->right;
        }

        // Free the base Pokémon
        free(current->data->name);
        free(current->data);
        free(current);
    } else {
        int evolveId = evolvedID - 1;
        if (evolveId < 0 || evolveId > 150) {
            printf("Evolved form for %s (ID %d) not found.\n", current->data->name, current->data->id);
            return;
        }
        PokemonData *evolvedData = createPokemeonDataPtr(pokedex[evolveId]);
        printf("Pokemon evolved from %s (ID %d) to %s (ID %d).\n",
               current->data->name, oldID, evolvedData->name, evolvedID);

        // Update current node with evolved data
        free(current->data->name);
        current->data->id = evolvedData->id;
        current->data->TYPE = evolvedData->TYPE;
        current->data->hp = evolvedData->hp;
        current->data->attack = evolvedData->attack;
        current->data->CAN_EVOLVE = evolvedData->CAN_EVOLVE;
        free(current->data->name);
        current->data->name = (char *) calloc(strlen(evolvedData->name) + 1, sizeof(char));
        strcpy(current->data->name, evolvedData->name);

        free(evolvedData->name);
        free(evolvedData); // Free temporary data
    }
}
void preOrderTraversal(PokemonNode *root) {
    preOrderGeneric(root, printPokemonNode);
}
void inOrderTraversal(PokemonNode *root) {
    inOrderGeneric(root, printPokemonNode);
}
void postOrderTraversal(PokemonNode *root) {
    postOrderGeneric(root, printPokemonNode);
}
OwnerNode *findOwnerByName(const char *name) {
    if (ownerHead == NULL) {
        return NULL;
    }
    OwnerNode *current = ownerHead;
    do {
        if (strcmp(current->ownerName, name) == 0) {
            return current;
        }
        current = current->next;
    } while (current != ownerHead);

    return NULL;
}

//function for part 3
// Recursively frees memory allocated for a Pokemon node and its children nodes.
// Frees memory for an Owner node and its associated Pokedex if it exists.
// Finds and returns an Owner node by its index in the circular linked list of owners.
// Deletes an Owner node's Pokedex by index and frees memory, handling different cases of list structure.
// Deletes a Pokedex from the system after confirming the index, and frees associated memory.
// Merges a Pokemon into an existing owner's Pokedex by adding the Pokemon's data.
// Finds and returns the index of an Owner node by their name, or -1 if not found.
void freePokemonNode(PokemonNode *node) {
    if (node == NULL) {
        return;
    }

    freePokemonNode(node->left);
    freePokemonNode(node->right);


    if (node->data != NULL) {
        free(node->data->name);
        free(node->data);
    }
    free(node);
}
void freeOwnerNode(OwnerNode *node) {
    if (node == NULL) {
        return;
    }

    if (node->pokedexRoot != NULL) {
        freePokemonNode(node->pokedexRoot);
    }

    if (node->ownerName != NULL) {
        free(node->ownerName);
    }
    free(node);
}
OwnerNode *getOwnerNodeByIndex(int index) {
    if (ownerHead == NULL || index < 1) {
        printf("Invalid index.\n");
        return NULL;
    }

    OwnerNode *ptr = ownerHead;
    int count = 1;
    do {
        if (count == index) {
            return ptr;
        }
        ptr = ptr->next;
        count++;
    } while (ptr != ownerHead);

    printf("No owner found at index %d\n", index);
    return NULL;
}
void deletePokedexByIndex(int index) {
    if (ownerHead == NULL) {
        return;
    }

    OwnerNode *current = ownerHead;
    int count = 1;

    do {
        if (count == index) {
            if (current == ownerHead) {
                if (ownerHead->next == ownerHead) {

                    freeOwnerNode(ownerHead);
                    ownerHead = NULL;
                } else {

                    OwnerNode *last = ownerHead->prev;
                    ownerHead = ownerHead->next;
                    last->next = ownerHead;
                    ownerHead->prev = last;
                    freeOwnerNode(current);
                }
            } else {

                current->prev->next = current->next;
                current->next->prev = current->prev;
                freeOwnerNode(current);
            }
            return;
        }
        current = current->next;
        count++;
    } while (current != ownerHead);

    printf("No owner found at index %d\n", index);
}
void deletePokedex() {
    if (ownerHead == NULL) {
        printf(" No existing Pokedexes to delete.\n");
        return;
    }

    printf("\n=== Delete a Pokedex ===\n");
    printExistingPokedex();
    int index = readIntSafe("Choose a Pokedex to delete by number:");

    if (index < 1) {
        printf("Invalid index.\n");
        return;
    }

    OwnerNode *node = getOwnerNodeByIndex(index);
    if (node == NULL) {
        printf("Owner not found at index %d.\n", index);
        return;
    }

    printf(" Deleting %s's entire Pokedex...\n", node->ownerName);
    deletePokedexByIndex(index);
    printf("Pokedex deleted.\n");

    // במקרה שאין יותר Pokedexים
    if (ownerHead == NULL) {
        printf("All Pokedexes deleted.\n");
    }
}
void mergePokdexFunction(PokemonNode *node) {
    PokemonData pokemonData = pokedex[node->data->id - 1];
    ownerToMerge->pokedexRoot = addPokemon(ownerToMerge->pokedexRoot, pokemonData, 0);
}
int findOwnerIndexByName(const char *name) {
    int index = 1;
    OwnerNode *current = ownerHead;

    do {
        if (strcmp(current->ownerName, name) == 0) {
            return index; // Found the match
        }
        current = current->next;
        index++;
    } while (current != ownerHead); // Stop if we've completed a full circle

    return -1; // No match found
}

//function for part 4
// Merges the Pokedexes of two owners by asking for their names, finding them, and applying the merge function.
// Performs a breadth-first search on a Pokemon node, visiting each node and calling the specified function on it.
void mergePokedexMenu() {
    if (ownerHead == NULL) {
        printf(" Not enough owners to merge.\n");
        return;
    }
    printf("\n=== Merge Pokedexes ===\n");
    int listOwnerSize = getOwnerListSize();
    if (listOwnerSize < 2) {
        printf("No more owners available\n");
    }
    printf("Enter name of first owner: ");
    char *firstName = getDynamicInput();
    printf("Enter name of second owner: ");
    char *secondName = getDynamicInput();
    printf("Merging %s and %s...\n", firstName, secondName);
    ownerToMerge = findOwnerByName(firstName);
    OwnerNode *second = findOwnerByName(secondName);
    BFSGeneric(second->pokedexRoot, mergePokdexFunction);
    ownerToMerge = NULL;
    printf("Merge completed.\n");
    int index = findOwnerIndexByName(secondName);
    deletePokedexByIndex(index);
    printf("Owner '%s' has been removed after merging.\n", secondName);
    free(firstName);
    free(secondName);
}
void BFSGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) return;

    Queue *q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        PokemonNode *current = dequeue(q);
        visit(current); // Call the visit function on the current node

        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }
    free(q); // Clean up the queue
}

//function for part 5
// Sorts the owners in ascending order by their names, using a bubble sort approach,
// and swaps their Pokedexes accordingly.
void sortOwners() {
    if (ownerHead == NULL || ownerHead->next == ownerHead) {
        printf(" 0 or 1 owners only => no need to sort.\n");
        return;
    }

    int swapped;
    OwnerNode *current;
    OwnerNode *lastSorted = NULL;

    do {
        swapped = 0;
        current = ownerHead;

        // Traverse until the last unsorted node
        while (current->next != ownerHead && current->next != lastSorted) {
            if (strcmp(current->ownerName, current->next->ownerName) > 0) {
                // Swap the owner names
                char *tempName = current->ownerName;
                current->ownerName = current->next->ownerName;
                current->next->ownerName = tempName;

                // Swap the pokedexRoot pointers
                PokemonNode *tempRoot = current->pokedexRoot;
                current->pokedexRoot = current->next->pokedexRoot;
                current->next->pokedexRoot = tempRoot;

                swapped = 1;
            }
            current = current->next;
        }
        lastSorted = current; // Update the last sorted node
    } while (swapped);

    printf(" Owners sorted by name.\n");
}

//function for part 6
// Prints the names of owners in a circular list, moving either forward or backward based on user input,
// for a specified number of prints.
void printOwnersCircular() {
    if (ownerHead == NULL) {
        printf(" No owners.\n");
        return;
    }

    printf(" Enter direction (F or B): ");
    char *directionInput = getDynamicInput();
    char direction = directionInput[0];
    free(directionInput);

    int numPrints = readIntSafe("How many prints? ");
    if (numPrints <= 0) {
        return;
    }

    OwnerNode *current = ownerHead;

    for (int i = 0; i < numPrints; i++) {
        printf("[%d] %s\n", i + 1, current->ownerName);

        if (direction == 'F' || direction == 'f') {
            current = current->next; // Move forward
        } else if (direction == 'B' || direction == 'b') {
            current = current->prev; // Move backward
        } else {
            printf("Invalid direction! Stopping prints.\n");
            break;
        }
    }
}

// Frees all owners in the circular linked list by repeatedly deleting the first owner.
void freeAllOwners(void) {
    int sizeOfOnwers = getOwnerListSize();
    for (int i = 0; i < sizeOfOnwers; ++i) {
        deletePokedexByIndex(1);
    }
}

// Displays the main menu with options and executes the corresponding function based on the user's choice,
// repeating until the user chooses to exit.
void mainMenu() {
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. New Pokedex\n");
        printf("2. Existing Pokedex\n");
        printf("3. Delete a Pokedex\n");
        printf("4. Merge Pokedexes\n");
        printf("5. Sort Owners by Name\n");
        printf("6. Print Owners in a direction X times\n");
        printf("7. Exit\n");
        choice = readIntSafe("Your choice:");

        switch (choice) {
            case 1:
                insertNewPokedex();
                break;
            case 2:
                enterExistingPokedexMenu();
                break;
            case 3:
                deletePokedex();
                break;
            case 4:
                mergePokedexMenu();
                break;
            case 5:
                 sortOwners();
                break;
            case 6:
                printOwnersCircular();
                break;
            case 7:
                printf(" Goodbye!\n");
                break;
            default:
                printf("Invalid.\n");
        }
    } while (choice != 7);
}

// Calls the main menu function and then frees all owners before exiting the program.
int main() {
    mainMenu();
    freeAllOwners();
    return 0;
}
