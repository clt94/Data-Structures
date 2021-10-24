// Connor Taylor
// Assignment 5: Takes text input of followers and users then implements them into a graph.
//               Allows user to see some statistics and to see how users are connected.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <utility>

// Precondition: vector<list<int>> by reference, ifstream by reference
// Implements the graph from the text file
// Postcondition: none
void createGraph(std::vector<std::list<int>>&, std::ifstream&);

// Precondition: vector<list<int>> by reference
// Outputs the complete graph
// Postcondition: none
void printGraph(std::vector<std::list<int>>&);

// Precondition: vector<list<int>> by reference, vector<pair<int, int>> by reference
// Creates a vector of pairs that has the count of all the users followers
// Postcondition: none
void createUsers(std::vector<std::list<int>>&, std::vector<std::pair<int, int>>&);

// Precondition: vector<pair<int, int>> by reference, int, int
// Sorts the users with the most followers at the top of the list by a quicksort
// Postcondition: none
void quickSort(std::vector<std::pair<int, int>>&, int, int);

// Precondition: int by reference, int by reference
// Utility function to swap to ints
// Postcondition: none
void swap(int&, int&);

// Precondition: vector<list<int>> by reference, int, int, size_t, vector<int> by reference, vector<int> by reference
// Does a breadth first search of the graph
// Postcondition: True if the value is found
bool BFS(std::vector<std::list<int>>&, int, int, size_t, std::vector<int>&, std::vector<int>&);

// Precondition: vector<list<int>> by reference, int, int, size_t
// Finds the shortest distance between two users
// Postcondition: none
void shortestDistance(std::vector<std::list<int>>&, int, int, size_t);

// Precondition: vector<list<int>> by reference, int
// Gets the index of a specified user
// Postcondition: int index of the user
int getUserIndex(std::vector<std::list<int>>&, int);

int main()
{
    std::ifstream file;
    // opens file
    file.open("github-graph_V1.0.txt");
    // checks if file is open, if not exits program
    if (!file.is_open())
    {
        std::cout << "The file failed to open. Ending program." << std::endl;
        return -1;
    }

    // defines graph and users with info for each user
    std::vector<std::list<int>> graph;
    std::vector<std::pair<int, int>> users;
    createGraph(graph, file);
    createUsers(graph, users);

    int choice = 0;
    int user1Index = 0;
    int user2Index = 0;
    while (choice != 7)
    {
        // displays menu and prompts the user for their choice
        std::cout << "1. Top 10 most connected users\n";
        std::cout << "2. Median number of followers\n";
        std::cout << "3. Average number of followers\n";
        std::cout << "4. Shortest path between two users\n";
        std::cout << "5. Print all users\n";
        std::cout << "6. Print graph\n";
        std::cout << "7. Quit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        while (choice < 1 || choice > 7)
        {
            std::cout << "Choice must be betwen 1 and 5.\nChoice: ";
            std::cin >> choice;
        }
        std::cout << std::endl;

        size_t count = 0;
        switch (choice)
        {
        case 1:
            // Outputs the top 10 most followed users
            for (size_t i = 0; i < 10; ++i)
            {
                std::cout << i + 1 << ". User " << users[i].first << " has " << users[i].second << " followers." << std::endl;
            }
            break;
        case 2:
            // Outputs the median number of followers for users
            std::cout << "Median: " << users[(users.size() - 1) / 2].second << " followers." << std::endl;
            break;
        case 3:
            // Outputs the average number of followers for users
            for (size_t i = 0; i < users.size(); ++i)
            {
                count += users[i].second;
            }

            std::cout << "Average: " << count / users.size() << " followers." << std::endl;
            break;
        case 4:
            // Searches how two users may be connected
            int user1;  
            int user2;
            do 
            {
                std::cout << "First user (-1 to exit): ";
                std::cin >> user1;
                if(user1 != -1)
                { 
                    // Verifies the user does exist
                    user1Index = getUserIndex(graph, user1);
                    if (user1Index == -1)
                    {
                        std::cout << "That user does not exist." << std::endl;
                    }
                }
            } while (user1Index == -1);

            // Enters as long as the user did not intend to exit 
            if (user1 != -1)
            {
                do
                {
                    std::cout << "Second user (-1 to exit): ";
                    std::cin >> user2;
                    if (user2 != -1)
                    {
                        // verifies the user does exist
                        user2Index = getUserIndex(graph, user2);
                        if (user2Index == -1)
                        {
                            std::cout << "That user does not exist." << std::endl;
                        }
                        // ensures both users are not the same
                        else if (user2Index == user1Index)
                        {
                            std::cout << "Users cannot be the same." << std::endl;
                            user2Index = -1;
                        }
                    }
                } while (user2Index == -1);
            }

            // gets the distance between the two users
            if (user1Index != -1 && user2Index != -1 && user1 != -1 && user2 != -1)
            {
                shortestDistance(graph, user1Index, user2Index, graph.size());
            }
            break;
        case 5:
            // outputs all users
            std::cout << "Users\n";
            for (size_t i = 0; i < users.size(); ++i)
            {
                std::cout << users[i].first << '\n';
            }
            break;
        case 6:
            // outputs all users and their followers
            printGraph(graph);
            break;
        case 7:
            std::cout << "Ending program." << std::endl;
            break;
        default:
            std::cout << "Try again." << std::endl;
            break;
        }
        std::cout << std::endl;
    }
    
    // closes file
    file.close();

    return 0;
}

// Precondition: vector<list<int>> by reference, ifstream by reference
// Implements the graph from the text file
// Postcondition: none
void createGraph(std::vector<std::list<int>>& graph, std::ifstream& file)
{
    std::list<int> list;
    std::string line;
    int user, follows;
    user = follows = 0;

    // skips first line
    std::getline(file, line);
    // adds first entry to graph
    std::getline(file, line);
    // finds first space
    std::size_t pos = line.find(' ');
    // converts first number to int
    user = std::stoi(line.substr(0, pos));
    // finds first number after spaces
    follows = std::stoi(line.substr(line.find_first_not_of("0123456789")));

    // initializes first value user and who they are following
    graph.push_back(list);
    graph[0].push_back(user);
    graph[0].push_back(follows);

    // gets every line from file
    while (std::getline(file, line))
    {
        // finds first space
        std::size_t pos = line.find(' ');
        // converts first number to int
        user = std::stoi(line.substr(0, pos));
        // finds first number after spaces
        follows = std::stoi(line.substr(line.find_first_not_of("0123456789")));
        // iterates through graph and populates it with users and who they are following
        size_t size = graph.size();
        bool unique = true;
        for (size_t i = 0; i < size && unique; ++i)
        {
            // if the user already exists, add it to the list of who they are following
            if (user == graph[i].front())
            {
                graph[i].push_back(follows);
                // sets flag unique to false to exit loop and not add new user
                unique = false;
            }
        }
        // if the user does not exist, add the user and who they are following
        if (unique)
        {
            graph.push_back(list);
            size_t i = graph.size() - 1;
            graph[i].push_back(user);
            graph[i].push_back(follows);
        }
    }
}

// Precondition: vector<list<int>> by reference
// Outputs the complete graph
// Postcondition: none
void printGraph(std::vector<std::list<int>>& graph)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (auto j = graph[i].begin(); j != graph[i].end(); ++j)
        {
            std::cout << *j << "->";
        }
        std::cout << std::endl;
    }
}

// Precondition: vector<list<int>> by reference, vector<pair<int, int>> by reference
// Creates a vector of pairs that has the count of all the users followers
// Postcondition: none
void createUsers(std::vector<std::list<int>>& graph, std::vector<std::pair<int, int>>& users)
{
    // adds each user and sets their follower i to 0
    for (size_t i = 0; i < graph.size(); ++i)
    {
        users.push_back(std::make_pair(graph[i].front(), 0));
    }

    // iterates through graph
    for (size_t i = 0; i < graph.size(); ++i)
    {
        // starts one off to skip main user
        std::list<int>::iterator j = ++graph[i].begin();
        for (j; j != graph[i].end(); ++j)
        {
            bool found = false;
            for (size_t k = 0; k < users.size() && !found; ++k)
            {
                // adds to the users count
                if (users[k].first == *j)
                {
                    found = true;
                    ++users[k].second;
                }
            }
        }
    }

    // sorts users from highest to lowest
    quickSort(users, 0, (int)graph.size() - 1);
}

// Precondition: vector<pair<int, int>> by reference, int, int
// Sorts the users with the most followers at the top of the list by a quicksort
// Postcondition: none
void quickSort(std::vector<std::pair<int, int>>& users, int low, int high)
{
    if (low < high)
    {
        int pivot = users[high].second;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (users[j].second >= pivot)
            {
                ++i;
                swap(users[i].first, users[j].first);
                swap(users[i].second, users[j].second);
            }
        }
        swap(users[static_cast<unsigned __int64>(i) + 1].first, users[high].first);
        swap(users[static_cast<unsigned __int64>(i) + 1].second, users[high].second);

        int part = i + 1;

        quickSort(users, low, part - 1);
        quickSort(users, part + 1, high);
    }
}

// Precondition: int by reference, int by reference
// Utility function to swap to ints
// Postcondition: none
void swap(int& i, int& j)
{
    int temp = i;
    i = j;
    j = temp;
}

// Precondition: vector<list<int>> by reference, int, int, size_t, vector<int> by reference, vector<int> by reference
// Does a breadth first search of the graph
// Postcondition: True if the value is found
bool BFS(std::vector<std::list<int>>& graph, int start, int final, size_t size, std::vector<int>& previous, std::vector<int>& distance)
{
    std::list<int> queue;
    std::vector<bool> visited;
    visited.resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        visited[i] = false;
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    visited[start] = true;
    distance[start] = 0;
    queue.push_back(start);
    while (!queue.empty()) 
    {
        int u = queue.front();
        queue.pop_front();
        for (auto i = graph[u].begin(); i != graph[u].end(); ++i) 
        {
            int index = getUserIndex(graph, *i);
            if (index != -1 && visited[index] == false) 
            {
                visited[index] = true;
                distance[index] = distance[u] + 1;
                previous[index] = u;
                queue.push_back(index);

                if (*i == graph[final].front())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Precondition: vector<list<int>> by reference, int, int, size_t
// Finds the shortest distance between two users
// Postcondition: none
void shortestDistance(std::vector<std::list<int>>& graph, int start, int final, size_t size)
{
    std::vector<int> previous;
    std::vector<int> distance;
    previous.resize(size);
    distance.resize(size);

    if (BFS(graph, start, final, size, previous, distance) == false) 
    {
        std::cout << graph[start].front() << " and " << graph[final].front() << " are not connected." << std::endl;;
        return;
    }

    std::vector<int> path;
    int crawl = final;
    path.push_back(crawl);
    
    while (previous[crawl] != -1) 
    {
        path.push_back(previous[crawl]);
        crawl = previous[crawl];
    }
    
    std::cout << "The length of the shortest path between " << graph[start].front() << " and " << graph[final].front() << " is: " << distance[final] << std::endl;

    std::cout << "The path is: ";
    for (int i = path.size() - 1; i >= 0; --i)
    {
        if (i != 0)
        {
            std::cout << graph[path[i]].front() << "->";
        }
        else
        {
            std::cout << graph[path[i]].front() << std::endl;
        }
    }
}

// Precondition: vector<list<int>> by reference, int
// Gets the index of a specified user
// Postcondition: int index of the user
int getUserIndex(std::vector<std::list<int>>& graph, int user)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        if (graph[i].front() == user)
        {
            return i;
        }
    }
    return -1;
}