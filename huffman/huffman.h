// Read all the lines from stdin into a single in-memory string.
char *read_data(void);

// A node in the tree.
struct node;

// The tree type = pointer to a node.
typedef struct node* tree_t;

// The struct definition.
struct node {
    char letter;
    int value;

    tree_t left, right;
};

// Make a new tree node from the specified values.
tree_t make_tree(char letter, int value, tree_t left, tree_t right);

// Produces an example tree.
tree_t fixed_tree(void);

// Special character used to load/print trees.
#define SPECIAL_CHAR '~'

// Convert the representation of a tree into a tree.
tree_t load_tree(char* input);

// Output the representation of a tree.
void print_tree(tree_t);

// Count the number of nodes in the tree.
int count_tree(tree_t);

// The frequency table type.
typedef tree_t frequency_table_t[256];

// Create a frequency table from the input data.
frequency_table_t* compute_frequencies(char* input_data);

// Compute a Huffman tree from a frequency table.
tree_t compute_tree(frequency_table_t* freqs);

// Free Huffman tree.
void free_tree(tree_t tree);

// The encoding table type.
typedef struct {
    int code_length;
    int bin_encoding;
    int encoding;
    char letter;
} code;

// The encoding table maps characters to their encoding.
typedef code encoding_table_t[256];

// Convert a tree to an encoding table.
encoding_table_t* compute_code_table(tree_t);

// Free code table.
void free_code_table(encoding_table_t* table);

// Output a representation of an encoding table.
int print_code(code);
void print_code_table(encoding_table_t* table);

// Translate the input data using the encoding table.
void encode_data(encoding_table_t* table, char* input_data, int* num_encoded, int* num_printed);
