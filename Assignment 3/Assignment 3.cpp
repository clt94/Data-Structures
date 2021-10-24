// Connor Taylor
// Assignment 3: Implement and operate on a binary search tree. User can search, insert, delete, 
//               display, output descending values, and find the most expensive branch in the tree.

#include <iostream>
#include <iomanip>
#include <math.h>

// Defines class BST to operate on the Binary tree
class BST
{
private:
    // Defines Node which holds the value and point to the left and right values in the tree
    struct Node
    {
        int num;
        Node* left;
        Node* right;

        // Constructor for Node
        Node(int num)
        {
            this->num = num;
            left = right = nullptr;
        }
    };
    // Defines the top of the tree
    Node* root;
    // Precondition: int, Node referenced pointer
    // Inserts a new number into the tree
    // Postcondition: None
    void insert(int, Node*&);
    // Precondition: int, Node referenced pointer
    // Removes an existing number from the tree
    // Postcondition: None
    void remove(int, Node*&);
    // Precondition: Node pointer
    // Prints the tree in a tree format
    // Postcondition: None
    void print(Node*);
    // Precondition: Node pointer, int, int
    // Prints a level of the tree
    // Postcondition: None
    void printLevel(Node*, int, int);
    // Precondition: int
    // Outputs the specified amount of spaces
    // Postcondition: None
    void printSpaces(int);
    // Precondition: Node referenced pointer, int
    // Create an empty tree of the specified height
    // Postcondition: None
    void makeEmptyTree(Node*&, int);
    // Precondition: Node references pointer, Node pointer
    // Copies the values of one tree to another
    // Postcondition: None
    void copyToTree(Node*&, Node*);
    // Precondition: int, Node pointer
    // Sees if a value exists in the tree
    // Postcondition: None
    void find(int, Node*);
    // Precondition: Node pointer
    // Gets the height of the tree
    // Postcondition: int
    int getHeight(Node*);
    // Precondition: Node*
    // Outputs all the nodes of the tree in descending order
    // Postcondition: None
    void descOrder(Node*);
    // Precondition: Node*
    // Finds the highest sum in a branch
    // Postcondition: int
    int maxBranch(Node*);
    // Precondition: Node referenced pointer
    // Destroys the specified tree
    // Postcondition: none
    void destroyTree(Node*&);
public:
    // Constructor: intitializes root
    BST()
    {
        root = nullptr;
    }
    // Precondition: none
    // Inserts a number into the tree
    // Postcondition: none
    void insert();
    // Precondition: none
    // Removes a number from the tree
    // Postcondition: none
    void remove();
    // Precondition: none
    // Outputs the tree in a tree format
    // Postcondition: none
    void print();
    // Precondition: none
    // Checks if a number is in the tree
    // Postcondition: none
    void find();
    // Precondition: none
    // Outputs all values of the tree in descending order
    // Postcondition: none
    void descOrder();
    // Precondition: none
    // Gets the biggest sum from a branch
    // Postcondition: none
    void maxBranch();
};

// Precondition: none
// Removes a number from the tree
// Postcondition: none
void BST::insert()
{
    int num;
    // Gets user input for number to insert
    std::cout << "Enter the number you are inserting: ";
    std::cin >> num;
    // Ensures the number is greater than 0
    while (num < 1 || num > 1000)
    {
        std::cout << "Please enter a number between 1 and 1000: ";
        std::cin >> num;
    }
    insert(num, root);
}

// Precondition: int num, Node referenced pointer node
// Inserts a new number into the tree
// Postcondition: None
void BST::insert(int num, Node*& node)
{
    // if node is empty, creates new node with number
    if (node == nullptr)
    {
        node = new Node(num);
        std::cout << num << " inserted successfully." << std::endl;
    }
    else
    {
        // Traverses tree until empty leaf is found 
        if (node->num > num)
        {
            insert(num, node->left);
        }
        else if (node->num < num)
        {
            insert(num, node->right);
        }
        // prohibits duplicate numbers
        else
        {
            std::cout << num << " already exists!" << std::endl;
        }
    }
}

// Precondition: none
// Removes a number from the tree
// Postcondition: none
void BST::remove()
{
    // gets user input for number to be deleted
    int num;
    std::cout << "Enter the number you want to delete: ";
    std::cin >> num;
    remove(num, root);
}

// Precondition: int num, Node referenced pointer node
// Removes an existing number from the tree
// Postcondition: None
void BST::remove(int num, Node*& node)
{
    // tree is empty
    if (node == nullptr)
    {
        std::cout << num << " was not found in the tree!" << std::endl;
    }
    // num found
    else if (node->num == num)
    {
        // no children
        if (node->left == nullptr && node->right == nullptr)
        {
            node = nullptr;
        }
        // no left child
        else if (node->left == nullptr)
        {
            node = node->right;
        }
        // no right child
        else if (node->right == nullptr)
        {
            node = node->left;
        }
        // has two children
        else
        {
            Node* temp = node->right;
            node = node->left;
            node->right = temp;
        }
        std::cout << num << " deleted successfully." << std::endl;
    }
    // traverses down tree
    else if(node->num < num)
    {
        remove(num, node->right);
    }
    else
    {
        remove(num, node->left);
    }
}

// Precondition: none
// Outputs the tree in a tree format
// Postcondition: none
void BST::print()
{
    if (root == nullptr)
    {
        std::cout << "The tree is empty!" << std::endl;
        return;
    }
    // Creates empty tree of same height and adds values from main tree
    Node* temp;
    makeEmptyTree(temp, getHeight(root));
    copyToTree(temp, root);
    // outputs tree in tree format
    print(temp);
    // destroys temp tree
    destroyTree(temp);
}

// Precondition: Node pointer node
// Prints the tree in a tree format
// Postcondition: None
void BST::print(Node* node)
{
    int height = getHeight(node);
    // iterates through each level of the tree
    for (int i = 0; i <= getHeight(node); i++)
    {
        // gets spaces for the left most side of the tree
        int initWidth = (int)std::pow(2.0, height + 1) - 1;
        printSpaces(initWidth);
        // gets space between each node in the tree
        int innerWidth = initWidth * 2 - 1;
        // prints the level of the tree
        printLevel(node, i, innerWidth);
        --height;
        std::cout << '\n';
    }
}

// Precondition: Node pointer node, int level, int width
// Prints a level of the tree
// Postcondition: None
void BST::printLevel(Node* node, int level, int width)
{
    // if node is empty exit function
    if (node == nullptr)
    {
        return;
    }
    // if node is "empty" output blank spot
    if (node->num == -1)
    {
        printSpaces(width + 2);
    }
    // outputs node with appropiate space
    if (level == 0)
    {
        if (node->num != -1)
        {
            if (node->num < 100)
            {
                std::cout << ' ';
            }
            std::cout << node->num;
            if (node->num < 10 && node->num > 0)
            {
                std::cout << ' ';
            }
        }
        printSpaces(width);
    }
    // traverses down the tree
    else if (level > 0)
    {
        printLevel(node->left, level - 1, width);
        printLevel(node->right, level - 1, width);
    }
}

// Precondition: int spaces
// Outputs the specified amount of spaces
// Postcondition: None
void BST::printSpaces(int spaces)
{
    // prints amount of spaces specified 
    for (int i = 0; i < spaces; ++i)
    {
        std::cout << ' ';
    }
}

// Precondition: Node referenced pointer node, int height
// Create an empty tree of the specified height
// Postcondition: None
void BST::makeEmptyTree(Node*& node, int height)
{
    // iterates through tree, creating nodes with -1 as value
    if (height >= 0)
    {
        node = new Node(-1);
        makeEmptyTree(node->left, height - 1);
        makeEmptyTree(node->right, height - 1);
    }
}

// Precondition: Node references pointer oldTree, Node pointer newTree
// Copies the values of one tree to another
// Postcondition: None
void BST::copyToTree(Node*& newTree, Node* oldTree)
{
    // if oldTree's node is empty exits function
    if (oldTree == nullptr)
    {
        return;
    }
    else
    {
        // copies value to newTree
        newTree->num = oldTree->num;
        // continues traversing down oldTree
        copyToTree(newTree->left, oldTree->left);
        copyToTree(newTree->right, oldTree->right);
    }
}

// Precondition: none
// Checks if a number is in the tree
// Postcondition: none
void BST::find()
{
    // takes user input for value to find in the tree
    int num;
    std::cout << "Enter the number you are seaching for: ";
    std::cin >> num;
    find(num, root);
}

// Precondition: int num, Node pointer node
// Sees if a value exists in the tree
// Postcondition: None
void BST::find(int num, Node* node)
{
    // if the node is empty is empty num does not exist
    if (node == nullptr)
    {
        std::cout << num << " does not exist!" << std::endl;
    }
    // num is found
    else if (node->num == num)
    {
        std::cout << num << " found in tree!" << std::endl;
    }
    // continues traversal down tree
    else if (node->num < num)
    {
        find(num, node->right);
    }
    else
    {
        find(num, node->left);
    }
}

// Precondition: Node pointer node
// Gets the height of the tree
// Postcondition: int
int BST::getHeight(Node* node)
{
    // Returns -1 for an empty tree
    if (node == nullptr)
    {
        return -1;
    }

    // gets height for each side 
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    // adds max height
    if (leftHeight > rightHeight)
    {
        return (leftHeight + 1);
    }
    else
    {
        return (rightHeight + 1);
    }
}

// Precondition: none
// Outputs all values of the tree in descending order
// Postcondition: none
void BST::descOrder()
{
    if (root == nullptr)
    {
        std::cout << "The tree is empty!" << std::endl;
        return;
    }
    descOrder(root);
    std::cout << std::endl;
}

// Precondition: Node* node
// Outputs all the nodes of the tree in descending order
// Postcondition: None
void BST::descOrder(Node* node)
{
    // exits function if node is empty
    if (node == nullptr)
    {
        return;
    }
    
    // outputs the node in RNL order
    descOrder(node->right);
    std::cout << node->num << ' ';
    descOrder(node->left);
}

// Precondition: none
// Gets the biggest sum from a branch
// Postcondition: none
void BST::maxBranch()
{
    std::cout << "The sum of the most expensive branch is: " << maxBranch(root) << std::endl;
}

// Precondition: Node* node
// Finds the highest sum in a branch
// Postcondition: int
int BST::maxBranch(Node* node)
{
    // returns 0 if tree is empty
    if (node == nullptr)
    {
        return 0;
    }

    // iterates through each branch
    int left = maxBranch(node->left);
    int right = maxBranch(node->right);

    // finds the largest branch
    if (left > right)
    {
        return left + node->num;
    }
    else
    {
        return right + node->num;
    }
}

// Precondition: Node referenced pointer node
// Destroys the specified tree
// Postcondition: none
void BST::destroyTree(Node*& node)
{
    if (node == nullptr)
    {
        return;
    }

    // traverses down the tree and deletes each node
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main()
{
    BST tree; 
    int choice = 0;
    while (choice != 7)
    {
        // outputs menu
        std::cout << "1. Search for a node" << std::endl;
        std::cout << "2. Insert a new node" << std::endl;
        std::cout << "3. Delete an existing node" << std::endl;
        std::cout << "4. Display tree" << std::endl;
        std::cout << "5. Display nodes in descending order" << std::endl;
        std::cout << "6. Display cost of most expensive branch" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        // ensures number is between 1 and 7
        while (choice < 1 || choice > 7)
        {
            std::cout << "Please enter a number between 1 and 7: ";
            std::cin >> choice;
        }
        // calls function based on users choice
        switch (choice)
        {
        case 1:
            tree.find();
            break;
        case 2:
            tree.insert();
            break;
        case 3:
            tree.remove();
            break;
        case 4:
            tree.print();
            break;
        case 5:
            tree.descOrder();
            break;
        case 6:
            tree.maxBranch();
            break;
        case 7:
            std::cout << "Ending progam..." << std::endl;
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }

    return 0;
}
