#ifndef EX6_H
#define EX6_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. `createQueue`: Creates a new empty queue and returns a pointer to it.
// 2. `enqueue`: Adds a new node to the rear of the queue.
// 3. `dequeue`: Removes and returns the front node from the queue.
// 4. `isQueueEmpty`: Checks if the queue is empty and returns a boolean value.
// 5. `trimWhitespace`: Removes leading and trailing whitespace from a string.
// 6. `myStrdup`: Duplicates a string and returns a pointer to the new string.
// 7. `readIntSafe`: Safely reads an integer input from the user with a prompt.
// 8. `getDynamicInput`: Reads a string input from the user dynamically.
// 9. `getTypeName`: Returns the string representation of a given Pokémon type.
// 10. `createPokemonNode`: Creates a new Pokémon node with the provided data.
// 11. `createPokemeonDataPtr`: Creates a new pointer to a Pokémon data structure.
// 12. `printExistingPokedex`: Displays the current existing Pokédex.
// 13. `getOwnerNodeByIndex`: Retrieves an owner node from the list by index.
// 14. `isNameAlreadyTaken`: Checks if a given name is already taken by an owner.
// 15. `calculateScore`: Calculates the score of a Pokémon based on its data.
// 16. `findPokemonById`: Finds a Pokémon in the tree by its ID using a breadth-first search.
// 17. `getPokemonById`: Retrieves a Pokémon's data by its ID.
// 18. `countNodes`: Counts the number of nodes in the Pokémon tree.
// 19. `deletePokedex`: Deletes the Pokédex.
// 20. `findOwnerIndexByName`: Finds the index of an owner by their name.
// 21. `createOwner`: Creates a new owner with the specified name and a starter Pokémon.
// 22. `freePokemonNode`: Frees the memory of a Pokémon node and its sub-nodes recursively.
// 23. `freeOwnerNode`: Frees the memory of an owner node.
// 24. `insertPokemonNode`: Inserts a Pokémon node into the binary search tree.
// 25. `searchPokemonBFS`: Searches for a Pokémon node by ID using breadth-first search.
// 26. `removeNodeBST`: Removes a node from the binary search tree.
// 27. `removePokemonByID`: Removes a Pokémon by its ID.
// 28. `BFSGeneric`: Performs a breadth-first traversal of a Pokémon tree, applying a visit function to each node.
// 29. `preOrderGeneric`: Performs a pre-order traversal of a Pokémon tree, applying a visit function.
// 30. `inOrderGeneric`: Performs an in-order traversal of a Pokémon tree, applying a visit function.
// 31. `postOrderGeneric`: Performs a post-order traversal of a Pokémon tree, applying a visit function.
// 32. `printPokemonNode`: Prints the details of a Pokémon node.
// 33. `initNodeArray`: Initializes an array to store Pokémon nodes with a given capacity.
// 34. `addNode`: Adds a Pokémon node to the node array.
// 35. `collectAll`: Collects all nodes in a Pokémon tree into a node array.
// 36. `compareByNameNode`: Compares two Pokémon nodes by their name for sorting purposes.
// 37. `displayAlphabetical`: Displays the Pokémon nodes in alphabetical order.
// 38. `displayBFS`: Displays Pokémon nodes using breadth-first traversal.
// 39. `preOrderTraversal`: Performs and displays pre-order traversal of the Pokémon tree.
// 40. `inOrderTraversal`: Performs and displays in-order traversal of the Pokémon tree.
// 41. `postOrderTraversal`: Performs and displays post-order traversal of the Pokémon tree.
// 42. `pokemonFight`: Simulates a Pokémon fight for the given owner.
// 43. `evolvePokemon`: Evolves the Pokémon of the given owner.
// 44. `addPokemon`: Adds a Pokémon to the owner's Pokédex.
// 45. `freePokemon`: Frees all memory allocated for the owner's Pokémon.
// 46. `displayMenu`: Displays the menu for a given owner.
// 47. `sortOwners`: Sorts the owners by name in alphabetical order.
// 48. `swapOwnerData`: Swaps the data of two owners.
// 49. `linkOwnerInCircularList`: Links a new owner to the circular linked list of owners.
// 50. `findOwnerByName`: Finds an owner by their name.
// 51. `enterExistingPokedexMenu`: Displays the menu for entering an existing Pokédex.
// 52. `insertNewPokedex`: Allows inserting a new Pokédex.
// 53. `freeOwnerNode`: Frees the memory allocated for an owner node.
// 54. `mergePokedexMenu`: Allows merging two Pokédexes.
// 55. `printOwnersCircular`: Prints the owners in a circular fashion based on direction and number of prints.
// 56. `freeAllOwners`: Frees the memory of all owners in the list.
// 57. `mainMenu`: Displays the main menu and executes the corresponding action based on the user's choice.

typedef enum {
    GRASS,
    FIRE,
    WATER,
    BUG,
    NORMAL,
    POISON,
    ELECTRIC,
    GROUND,
    FAIRY,
    FIGHTING,
    PSYCHIC,
    ROCK,
    GHOST,
    DRAGON,
    ICE
} PokemonType;
typedef enum {
    CANNOT_EVOLVE,
    CAN_EVOLVE
} EvolutionStatus;
typedef struct PokemonData {
    int id;
    char *name;
    PokemonType TYPE;
    int hp;
    int attack;
    EvolutionStatus CAN_EVOLVE;
} PokemonData;
typedef struct PokemonNode {
    PokemonData *data;
    struct PokemonNode *left;
    struct PokemonNode *right;
} PokemonNode;
typedef struct OwnerNode {
    char *ownerName; // Owner's name
    PokemonNode *pokedexRoot; // Pointer to the root of the owner's Pokédex
    struct OwnerNode *next; // Next owner in the linked list
    struct OwnerNode *prev; // Previous owner in the linked list
} OwnerNode;
OwnerNode *ownerHead = NULL;
OwnerNode *ownerToMerge = NULL;
typedef struct QueueNode {
    PokemonNode *treeNode;
    struct QueueNode *next;
} QueueNode;
typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;
int getOwnerListSize();
void deletePokedexByIndex(int index);
Queue *createQueue() {
    Queue *q = (Queue *) calloc(1, sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
void enqueue(Queue *q, PokemonNode *treeNode) {
    QueueNode *newNode = (QueueNode *) calloc(1, sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}
PokemonNode *dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    QueueNode *temp = q->front;
    PokemonNode *treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}
int isQueueEmpty(Queue* q) {
 return q->front == NULL;
}
void trimWhitespace(char *str);
char *myStrdup(const char *src);
int readIntSafe(const char *prompt);
char *getDynamicInput(void);
const char *getTypeName(PokemonType type);
PokemonNode *createPokemonNode(PokemonData data);
PokemonData *createPokemeonDataPtr(PokemonData data);
void printExistingPokedex();
OwnerNode *getOwnerNodeByIndex(int index);
int isNameAlreadyTaken(const char *name);
double calculateScore(PokemonData *data);
PokemonNode *findPokemonById(PokemonNode *root, int id);
PokemonData *getPokemonById(int id);
int countNodes(PokemonNode *root);
void deletePokedex();
int findOwnerIndexByName(const char *name);
OwnerNode *createOwner(char *ownerName, PokemonNode *starter);
void freePokemonNode(PokemonNode *node);
void freePokemonNode(PokemonNode *root);
void freeOwnerNode(OwnerNode *owner);
PokemonNode *insertPokemonNode(PokemonNode *root, PokemonNode *newNode);
PokemonNode *searchPokemonBFS(PokemonNode *root, int id);
PokemonNode *removeNodeBST(PokemonNode *root, int id);
PokemonNode *removePokemonByID(PokemonNode *root, int id);
typedef void (*VisitNodeFunc)(PokemonNode *);
void BFSGeneric(PokemonNode *root, VisitNodeFunc visit);
void preOrderGeneric(PokemonNode *root, VisitNodeFunc visit);
void inOrderGeneric(PokemonNode *root, VisitNodeFunc visit);
void postOrderGeneric(PokemonNode *root, VisitNodeFunc visit);
void printPokemonNode(PokemonNode *node);
typedef struct {
    PokemonNode **nodes;
    int size;
    int capacity;
} NodeArray;
void initNodeArray(NodeArray *na, int cap);
void addNode(NodeArray *na, PokemonNode *node);
void collectAll(PokemonNode *root, NodeArray *na);
int compareByNameNode(const void *a, const void *b);
void displayAlphabetical(PokemonNode *root);
void displayBFS(PokemonNode *root);
void preOrderTraversal(PokemonNode *root);
void inOrderTraversal(PokemonNode *root);
void postOrderTraversal(PokemonNode *root);
void pokemonFight(OwnerNode *owner);
void evolvePokemon(OwnerNode *owner);
PokemonNode *addPokemon(PokemonNode *root, PokemonData data,int shouldPrint);
void freePokemon(OwnerNode *owner);
void displayMenu(OwnerNode *owner);
void sortOwners(void);
void swapOwnerData(OwnerNode *a, OwnerNode *b);
void linkOwnerInCircularList(OwnerNode *newOwner);
OwnerNode *findOwnerByName(const char *name);
void enterExistingPokedexMenu(void);
void insertNewPokedex(void);
void freeOwnerNode(OwnerNode *);
void mergePokedexMenu(void);
void printOwnersCircular(void);
void freeAllOwners(void);
void mainMenu(void);
static const PokemonData pokedex[] = {
    {1, "Bulbasaur", GRASS, 45, 49, CAN_EVOLVE},
    {2, "Ivysaur", GRASS, 60, 62, CAN_EVOLVE},
    {3, "Venusaur", GRASS, 80, 82, CANNOT_EVOLVE},
    {4, "Charmander", FIRE, 39, 52, CAN_EVOLVE},
    {5, "Charmeleon", FIRE, 58, 64, CAN_EVOLVE},
    {6, "Charizard", FIRE, 78, 84, CANNOT_EVOLVE},
    {7, "Squirtle", WATER, 44, 48, CAN_EVOLVE},
    {8, "Wartortle", WATER, 59, 63, CAN_EVOLVE},
    {9, "Blastoise", WATER, 79, 83, CANNOT_EVOLVE},
    {10, "Caterpie", BUG, 45, 30, CAN_EVOLVE},
    {11, "Metapod", BUG, 50, 20, CAN_EVOLVE},
    {12, "Butterfree", BUG, 60, 45, CANNOT_EVOLVE},
    {13, "Weedle", BUG, 40, 35, CAN_EVOLVE},
    {14, "Kakuna", BUG, 45, 25, CAN_EVOLVE},
    {15, "Beedrill", BUG, 65, 90, CANNOT_EVOLVE},
    {16, "Pidgey", NORMAL, 40, 45, CAN_EVOLVE},
    {17, "Pidgeotto", NORMAL, 63, 60, CAN_EVOLVE},
    {18, "Pidgeot", NORMAL, 83, 80, CANNOT_EVOLVE},
    {19, "Rattata", NORMAL, 30, 56, CAN_EVOLVE},
    {20, "Raticate", NORMAL, 55, 81, CANNOT_EVOLVE},
    {21, "Spearow", NORMAL, 40, 60, CAN_EVOLVE},
    {22, "Fearow", NORMAL, 65, 90, CANNOT_EVOLVE},
    {23, "Ekans", POISON, 35, 60, CAN_EVOLVE},
    {24, "Arbok", POISON, 60, 85, CANNOT_EVOLVE},
    {25, "Pikachu", ELECTRIC, 35, 55, CAN_EVOLVE},
    {26, "Raichu", ELECTRIC, 60, 90, CANNOT_EVOLVE},
    {27, "Sandshrew", GROUND, 50, 75, CAN_EVOLVE},
    {28, "Sandslash", GROUND, 75, 100, CANNOT_EVOLVE},
    {29, "NidoranF", POISON, 55, 47, CAN_EVOLVE},
    {30, "Nidorina", POISON, 70, 62, CAN_EVOLVE},
    {31, "Nidoqueen", POISON, 90, 92, CANNOT_EVOLVE},
    {32, "NidoranM", POISON, 46, 57, CAN_EVOLVE},
    {33, "Nidorino", POISON, 61, 72, CAN_EVOLVE},
    {34, "Nidoking", POISON, 81, 102, CANNOT_EVOLVE},
    {35, "Clefairy", FAIRY, 70, 45, CAN_EVOLVE},
    {36, "Clefable", FAIRY, 95, 70, CANNOT_EVOLVE},
    {37, "Vulpix", FIRE, 38, 41, CAN_EVOLVE},
    {38, "Ninetales", FIRE, 73, 76, CANNOT_EVOLVE},
    {39, "Jigglypuff", NORMAL, 115, 45, CAN_EVOLVE},
    {40, "Wigglytuff", NORMAL, 140, 70, CANNOT_EVOLVE},
    {41, "Zubat", POISON, 40, 45, CAN_EVOLVE},
    {42, "Golbat", POISON, 75, 80, CAN_EVOLVE},
    {43, "Oddish", GRASS, 45, 50, CAN_EVOLVE},
    {44, "Gloom", GRASS, 60, 65, CAN_EVOLVE},
    {45, "Vileplume", GRASS, 75, 80, CANNOT_EVOLVE},
    {46, "Paras", BUG, 35, 70, CAN_EVOLVE},
    {47, "Parasect", BUG, 60, 95, CANNOT_EVOLVE},
    {48, "Venonat", BUG, 60, 55, CAN_EVOLVE},
    {49, "Venomoth", BUG, 70, 65, CANNOT_EVOLVE},
    {50, "Diglett", GROUND, 10, 55, CAN_EVOLVE},
    {51, "Dugtrio", GROUND, 35, 80, CANNOT_EVOLVE},
    {52, "Meowth", NORMAL, 40, 45, CAN_EVOLVE},
    {53, "Persian", NORMAL, 65, 70, CANNOT_EVOLVE},
    {54, "Psyduck", WATER, 50, 52, CAN_EVOLVE},
    {55, "Golduck", WATER, 80, 82, CANNOT_EVOLVE},
    {56, "Mankey", FIGHTING, 40, 80, CAN_EVOLVE},
    {57, "Primeape", FIGHTING, 65, 105, CANNOT_EVOLVE},
    {58, "Growlithe", FIRE, 55, 70, CAN_EVOLVE},
    {59, "Arcanine", FIRE, 90, 110, CANNOT_EVOLVE},
    {60, "Poliwag", WATER, 40, 50, CAN_EVOLVE},
    {61, "Poliwhirl", WATER, 65, 65, CAN_EVOLVE},
    {62, "Poliwrath", WATER, 90, 95, CANNOT_EVOLVE},
    {63, "Abra", PSYCHIC, 25, 20, CAN_EVOLVE},
    {64, "Kadabra", PSYCHIC, 40, 35, CAN_EVOLVE},
    {65, "Alakazam", PSYCHIC, 55, 50, CANNOT_EVOLVE},
    {66, "Machop", FIGHTING, 70, 80, CAN_EVOLVE},
    {67, "Machoke", FIGHTING, 80, 100, CAN_EVOLVE},
    {68, "Machamp", FIGHTING, 90, 130, CANNOT_EVOLVE},
    {69, "Bellsprout", GRASS, 50, 75, CAN_EVOLVE},
    {70, "Weepinbell", GRASS, 65, 90, CAN_EVOLVE},
    {71, "Victreebel", GRASS, 80, 105, CANNOT_EVOLVE},
    {72, "Tentacool", WATER, 40, 40, CAN_EVOLVE},
    {73, "Tentacruel", WATER, 80, 70, CANNOT_EVOLVE},
    {74, "Geodude", ROCK, 40, 80, CAN_EVOLVE},
    {75, "Graveler", ROCK, 55, 95, CAN_EVOLVE},
    {76, "Golem", ROCK, 80, 120, CANNOT_EVOLVE},
    {77, "Ponyta", FIRE, 50, 85, CAN_EVOLVE},
    {78, "Rapidash", FIRE, 65, 100, CANNOT_EVOLVE},
    {79, "Slowpoke", WATER, 90, 65, CAN_EVOLVE},
    {80, "Slowbro", WATER, 95, 75, CANNOT_EVOLVE},
    {81, "Magnemite", ELECTRIC, 25, 35, CAN_EVOLVE},
    {82, "Magneton", ELECTRIC, 50, 60, CANNOT_EVOLVE},
    {83, "Farfetch'd", NORMAL, 52, 65, CANNOT_EVOLVE},
    {84, "Doduo", NORMAL, 35, 85, CAN_EVOLVE},
    {85, "Dodrio", NORMAL, 60, 110, CANNOT_EVOLVE},
    {86, "Seel", WATER, 65, 45, CAN_EVOLVE},
    {87, "Dewgong", WATER, 90, 70, CANNOT_EVOLVE},
    {88, "Grimer", POISON, 80, 80, CAN_EVOLVE},
    {89, "Muk", POISON, 105, 105, CANNOT_EVOLVE},
    {90, "Shellder", WATER, 30, 65, CAN_EVOLVE},
    {91, "Cloyster", WATER, 50, 95, CANNOT_EVOLVE},
    {92, "Gastly", GHOST, 30, 35, CAN_EVOLVE},
    {93, "Haunter", GHOST, 45, 50, CAN_EVOLVE},
    {94, "Gengar", GHOST, 60, 65, CANNOT_EVOLVE},
    {95, "Onix", ROCK, 35, 45, CANNOT_EVOLVE},
    {96, "Drowzee", PSYCHIC, 60, 48, CAN_EVOLVE},
    {97, "Hypno", PSYCHIC, 85, 73, CANNOT_EVOLVE},
    {98, "Krabby", WATER, 30, 105, CAN_EVOLVE},
    {99, "Kingler", WATER, 55, 130, CANNOT_EVOLVE},
    {100, "Voltorb", ELECTRIC, 40, 30, CAN_EVOLVE},
    {101, "Electrode", ELECTRIC, 60, 50, CANNOT_EVOLVE},
    {102, "Exeggcute", GRASS, 60, 40, CAN_EVOLVE},
    {103, "Exeggutor", GRASS, 95, 95, CANNOT_EVOLVE},
    {104, "Cubone", GROUND, 50, 50, CAN_EVOLVE},
    {105, "Marowak", GROUND, 60, 80, CANNOT_EVOLVE},
    {106, "Hitmonlee", FIGHTING, 50, 120, CANNOT_EVOLVE},
    {107, "Hitmonchan", FIGHTING, 50, 105, CANNOT_EVOLVE},
    {108, "Lickitung", NORMAL, 90, 55, CANNOT_EVOLVE},
    {109, "Koffing", POISON, 40, 65, CAN_EVOLVE},
    {110, "Weezing", POISON, 65, 90, CANNOT_EVOLVE},
    {111, "Rhyhorn", GROUND, 80, 85, CAN_EVOLVE},
    {112, "Rhydon", GROUND, 105, 130, CANNOT_EVOLVE},
    {113, "Chansey", NORMAL, 250, 5, CANNOT_EVOLVE},
    {114, "Tangela", GRASS, 65, 55, CANNOT_EVOLVE},
    {115, "Kangaskhan", NORMAL, 105, 95, CANNOT_EVOLVE},
    {116, "Horsea", WATER, 30, 40, CAN_EVOLVE},
    {117, "Seadra", WATER, 55, 65, CANNOT_EVOLVE},
    {118, "Goldeen", WATER, 45, 67, CAN_EVOLVE},
    {119, "Seaking", WATER, 80, 92, CANNOT_EVOLVE},
    {120, "Staryu", WATER, 30, 45, CAN_EVOLVE},
    {121, "Starmie", WATER, 60, 75, CANNOT_EVOLVE},
    {122, "Mr. Mime", PSYCHIC, 40, 45, CANNOT_EVOLVE},
    {123, "Scyther", BUG, 70, 110, CANNOT_EVOLVE},
    {124, "Jynx", ICE, 65, 50, CANNOT_EVOLVE},
    {125, "Electabuzz", ELECTRIC, 65, 83, CANNOT_EVOLVE},
    {126, "Magmar", FIRE, 65, 95, CANNOT_EVOLVE},
    {127, "Pinsir", BUG, 65, 125, CANNOT_EVOLVE},
    {128, "Tauros", NORMAL, 75, 100, CANNOT_EVOLVE},
    {129, "Magikarp", WATER, 20, 10, CAN_EVOLVE},
    {130, "Gyarados", WATER, 95, 125, CANNOT_EVOLVE},
    {131, "Lapras", WATER, 130, 85, CANNOT_EVOLVE},
    {132, "Ditto", NORMAL, 48, 48, CANNOT_EVOLVE},
    {133, "Eevee", NORMAL, 55, 55, CAN_EVOLVE},
    {134, "Vaporeon", WATER, 130, 65, CANNOT_EVOLVE},
    {135, "Jolteon", ELECTRIC, 65, 65, CANNOT_EVOLVE},
    {136, "Flareon", FIRE, 65, 130, CANNOT_EVOLVE},
    {137, "Porygon", NORMAL, 65, 60, CANNOT_EVOLVE},
    {138, "Omanyte", ROCK, 35, 40, CAN_EVOLVE},
    {139, "Omastar", ROCK, 70, 60, CANNOT_EVOLVE},
    {140, "Kabuto", ROCK, 30, 80, CAN_EVOLVE},
    {141, "Kabutops", ROCK, 60, 115, CANNOT_EVOLVE},
    {142, "Aerodactyl", ROCK, 80, 105, CANNOT_EVOLVE},
    {143, "Snorlax", NORMAL, 160, 110, CANNOT_EVOLVE},
    {144, "Articuno", ICE, 90, 85, CANNOT_EVOLVE},
    {145, "Zapdos", ELECTRIC, 90, 90, CANNOT_EVOLVE},
    {146, "Moltres", FIRE, 90, 100, CANNOT_EVOLVE},
    {147, "Dratini", DRAGON, 41, 64, CAN_EVOLVE},
    {148, "Dragonair", DRAGON, 61, 84, CAN_EVOLVE},
    {149, "Dragonite", DRAGON, 91, 134, CANNOT_EVOLVE},
    {150, "Mewtwo", PSYCHIC, 106, 110, CANNOT_EVOLVE},
    {151, "Mew", PSYCHIC, 100, 100, CANNOT_EVOLVE}
};
#endif // EX6_H
