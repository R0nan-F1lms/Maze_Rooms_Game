#include "splashkit.h"
#include <stdio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct room_data *room_ptr;

// Define the structure for path data
struct path_data {
    string description;
    room_ptr destination;
};

// Define the structure for room data
struct room_data {
    string title;
    string description;
    vector<path_data> paths; // Vector to store possible paths from the current room
};

// Function to prompt the user to choose an option and move to the selected room
room_ptr move_player(const room_data &current_room_data) {
    while (true) { // Keep prompting until a valid option is chosen
        printf("Available options:\n");
        for (size_t i = 0; i < current_room_data.paths.size(); ++i) {
            printf("%lu - %s\n", i, current_room_data.paths[i].description.c_str());
        }
        
        printf("Choose an option: ");
        int option = convert_to_integer(read_line()); // Get user's choice

        if (option >= 0 && option < static_cast<int>(current_room_data.paths.size())) { // Check if option is valid
            return current_room_data.paths[option].destination; // Return the pointer to the selected room
        } else {
            printf("Invalid option or path unavailable. Please choose again.\n");
        }
    }
}

int main() {
    // Define room data
    room_data room1, room2, room3;
    room1.title = "Room 1";
    room1.description = "This is room 1, it is empty nothing is in here, just like me";
    room2.title = "Room 2";
    room2.description = "This is room 2 it's just like room 1 but called room 2 it is also empty";
    room3.title = "Room 3";
    room3.description = "This is room 3 it's just like room 2 but called room 3 it is also empty";

    // Define room paths
    path_data path1, path2, path3;
    path1.description = "A Door to Room 2";
    path1.destination = &room2;
    path2.description = "Yet another Door to Room 3";
    path2.destination = &room3;
    path3.description = "A Door back to Room 1";
    path3.destination = &room1;

    room1.paths.push_back(path1);
    room2.paths.push_back(path2);
    room3.paths.push_back(path3);

    // Start in Room 1
    room_ptr current_room = &room1;

    // Move the player through the maze
    while (true) {
        printf("%s\n-----\n%s\n", current_room->title.c_str(), current_room->description.c_str());
        current_room = move_player(*current_room);
    }

    return 0;
}
