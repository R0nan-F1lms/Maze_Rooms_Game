#include "splashkit.h"
#include <stdio.h>
#include <string>
#include <vector> // Include the vector library for dynamic arrays

using std::string;
using std::vector;

typedef struct room_struct *room_ptr;

typedef struct path_struct
{
    string description;
    room_ptr destination;
} path_data;

typedef struct room_struct
{
    string title;
    string description;
    vector<path_data> paths; // Change to dynamic array using vector
} room_data;

// Forward declarations
room_data new_room(string title, string description);
path_data new_path(string description, room_ptr destination);
void print_path(int idx, const path_data &path);
void print_room(const room_data &room); // Modified function signature
void move_player(room_ptr &current_room, int option, room_data &current_room_data); // Modified function signature
int read_integer(const string &prompt);

int main()
{
    room_data r1 = new_room("Room 1", "This is room 1, it is empty nothing is in here, just like me");
    room_data r2 = new_room("Room 2", "This is room 2 it's just like room 1 but called room 2 it is also empty");
    room_data r3 = new_room("Room 3", "This is room 3 this one is like room 2 and 1 but is called room 3 this is not empty this as you in it");

    r1.paths.push_back(new_path("A Door", &r2)); // Push paths into dynamic array
    r1.paths.push_back(new_path("Yet another Door", &r3));

    room_ptr current_room = &r1;

    while (1)
    {
        print_room(*current_room); // Pass room_data by reference
        for (int i = 0; i < current_room->paths.size(); ++i) // Loop through paths
        {
            print_path(i, current_room->paths[i]);
        }

        int option = read_integer("Option: ");

        if (option >= 0 && option < current_room->paths.size()) // Check if option is valid
        {
            move_player(current_room, option, r1); // Pass room_data by reference
        }
        else
        {
            printf("Invalid option or path unavailable. Please choose again.\n");
        }

        // Check if the user wants to quit
        int answer = read_integer("Do you want to continue (0 to quit, 1 to continue): ");
        if (answer == 0)
        {
            break;
        }
    }

    return 0;
}

// create new room with title and description
room_data new_room(string title, string description)
{
    room_data result = {title, description};
    return result;
}

// create new path with description and destination room
path_data new_path(string description, room_ptr destination)
{
    path_data result = {description, destination};
    return result;
}

// Prints the path
void print_path(int idx, const path_data &path)
{
    printf("%d - %s\n", idx, path.description.c_str());
}

// Output the room's title and description to the terminal.
void print_room(const room_data &room)
{
    printf("%s\n-----\n%s\n", room.title.c_str(), room.description.c_str());
}

// Move the player through the selected path, setting the player's current room
//  to the destination of the path.
void move_player(room_ptr &current_room, int option, room_data &current_room_data)
{
    current_room = current_room_data.paths[option].destination;
}

// Reads an integer value from the user. If the user enters a non-integer value,
// the function will continue to prompt the user until they enter a valid value.
int read_integer(const string &prompt)
{
    int result = 0;

    printf("%s", prompt.c_str());
    try
    {
        result = convert_to_integer(read_line());
    }
    catch (...)
    {
        printf("Please enter a whole number.\n");
    }

    return result;
}
