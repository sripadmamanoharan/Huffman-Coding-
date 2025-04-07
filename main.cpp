#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

// Node structure for Huffman tree
struct Node {
    char data;          // Character data for leaf nodes
    int freq;           // Frequency of occurrence
    Node* left;         // Pointer to the left child
    Node* right;        // Pointer to the right child

    // Constructor for leaf nodes
    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    // Constructor for internal nodes
    Node(int freq) : data('\0'), freq(freq), left(nullptr), right(nullptr) {}

    // Destructor to free memory
    ~Node() {
        delete left;
        delete right;
    }
};

// Function to build Huffman tree from given codes
void buildHuffmanTree(std::unordered_map<std::string, char>& codes, Node** root) {
    *root = new Node(0);
    // Iterate through the codes
    for (const auto& pair: codes) {
        std::cout << pair.second << std::endl;  // Debugging: print the character for each code
    }
    // Iterate through the codes again to build the tree
    for (const auto& pair : codes) {
        Node* current = *root;
        for (char bit : pair.first) {
            if (bit == '0') {
                if (!current->left) {
                    current->left = new Node(0);
                }
                current = current->left;
            } else if (bit == '1') {
                if (!current->right) {
                    current->right = new Node(0);
                }
                current = current->right;
            } else {
                std::cerr << "Error: Invalid Huffman code encountered: " << pair.first << std::endl;
                return;
            }
        }
        // Assign the character to leaf node
        if (current->data != '\0') {
            std::cerr << "Error: Huffman code collision detected: " << pair.first << std::endl;
            return;
        }
        current->data = pair.second;
    }
}

// Function to decode the compressed text using Huffman tree
void decodeText(Node* root, std::ifstream& input, std::ofstream& output, int originalSize) {
    Node* current = root;
    int totalDecoded = 0;
    while (totalDecoded < originalSize) {
        if (!input.good()) {
            std::cerr << "Error: Unexpected end of input file." << std::endl;
            return;
        }
        char bit;
        input.get(bit);
        if (bit == '0') {
            if (current->left) {
                current = current->left;
                std::cout << "0";  // Debugging: print the decoded bit
            }
        } else if (bit == '1') {
            if (current->right) {
                current = current->right;
                std::cout << "1";  // Debugging: print the decoded bit
            }
        } else {
            std::cerr << "Error: Invalid character encountered in input file." << std::endl;
            return;
        }
        if (!current) {
            std::cerr << "Error: Invalid Huffman code encountered." << std::endl;
            return;
        }
        // Check if leaf node is reached
        if (current->left == nullptr && current->right == nullptr) {
            if (current->data == '#') {
                output.put('\n');  // Special handling for newline character
            } else if (current->data == '|') {
                output.put(' ');  // Special handling for space character
            } else {
                output.put(current->data);  // Output the decoded character
            }
            std::cout << "  ";  // Debugging: print spacing for readability
            current = root;  // Reset current pointer to root for next character
            totalDecoded++;  // Increment total decoded characters
        }
    }
}

// Function to perform Huffman decompression
void huffmanDecompression(const std::string& inputFilename, const std::string& outputFilename) {
    // Open the compressed file
    std::ifstream input(inputFilename, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Error opening compressed file." << std::endl;
        return;
    }

    // Check for the magic word indicating Huffman compression
    std::string magicWord;
    if (!std::getline(input, magicWord) || magicWord != "HUFFMAN") {
        std::cerr << "Error: Not a valid Huffman compressed file." << std::endl;
        return;
    }

    // Read the code table from the compressed file
    std::unordered_map<std::string, char> codes;
    std::string line;
    while (std::getline(input, line)) {
        // Check for the delimiter indicating the end of the code table
        if (line == "=== ORIGINAL SIZE ===") {
            break;
        }
        // Extract the character and code from the line
        char c;
        std::string code;
        std::istringstream iss(line);
        iss >> c >> code;  // Use std::quoted to handle special characters
        // Store the code in the map
        codes[code] = c;
    }

    // Read the original size of the text from the compressed file
    std::string originalSizeStr;
    if (!std::getline(input, originalSizeStr)) {
        std::cerr << "Error reading original size from compressed file." << std::endl;
        return;
    }

    // Convert the string to an integer
    int originalSize = std::stoi(originalSizeStr);

    // Build the Huffman tree from the codes
    Node* root = nullptr;
    buildHuffmanTree(codes, &root);

    // Decompress the text
    std::ofstream output(outputFilename);
    if (!output.is_open()) {
        std::cerr << "Error creating decompressed file." << std::endl;
        delete root;
        return;
    }

    decodeText(root, input, output, originalSize);

    // Cleanup
    input.close();
    output.close();
    delete root;

    std::cout << "Huffman decompression completed. Output saved to '" << outputFilename << "'" << std::endl;
}

// Main function to parse command line arguments and initiate decompression
int main(int argc, char* argv[]) {
    // Check for correct number of command line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " -f input.hzip [-o output.txt]" << std::endl;
        return 1;
    }

    // Initialize input and output filenames
    std::string inputFilename;
    std::string outputFilename = "output.txt";

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-f" && i + 1 < argc) {
            inputFilename = argv[i + 1];
        } else if (std::string(argv[i]) == "-o" && i + 1
