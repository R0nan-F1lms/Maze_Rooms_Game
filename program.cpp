#include "splashkit.h"
#include <stdio.h>
#include <string>
#include "dynamic_array.h"


// Define the structure for path data
struct path_data {
    string description;
    struct room_data *destination;
};

// Define the structure for room data
struct room_data {
    string title;
    string description;
    dynamic_array<path_data> paths;
};

// Function to prompt the user to choose an option and move to the selected room
struct room_data* move_player(const struct room_data &current_room_data) {
    while (true) {
        printf("Available options:\n");
        for (int i = 0; i < current_room_data.paths.getSize(); ++i) {
            printf("%d - %s\n", i, current_room_data.paths[i].description.c_str());
        }
        printf("Type 'quit' to exit the program.\n");
        
        printf("Choose an option: ");
        string input = read_line();

        if (input == "quit") {
            return nullptr; // Return nullptr to exit the program
        }

        int option;
        try {
            option = convert_to_integer(input);
        } catch (...) {
            printf("Invalid input. Please choose again.\n");
            continue;
        }

        if (option >= 0 && option < current_room_data.paths.getSize()) {
            return current_room_data.paths[option].destination;
        } else {
            printf("Invalid option or path unavailable. Please choose again.\n");
        }
    }
}

int main() {
    // Define room data
    struct room_data room1, room2, room3, end;
    room1.title = "Room 1";
    room1.description = "This is room 1, it is empty nothing is in here, just like me";
    room2.title = "Room 2";
    room2.description = "This is room 2 it's just like room 1 but called room 2 it is also empty";
    room3.title = "Room 3";
    room3.description = "This is room 3 it's just like room 2 but called room 3 it is also empty";
    end.title = "End";
    end.description = "Congratulations! You've reached the end.";

    // Define room paths
    struct path_data path1, path2, path3, path4;
    path1.description = "A Door to Room 2";
    path1.destination = &room2;
    path2.description = "Yet another Door to Room 3";
    path2.destination = &room3;
    path3.description = "A Door back to Room 1";
    path3.destination = &room1;
    path4.description = "The exit";
    path4.destination = &end;

    room1.paths.append(path1);
    room2.paths.append(path2);
    room3.paths.append(path3);
    room3.paths.append(path4); // Add path to end room

    // Start in Room 1
    struct room_data* current_room = &room1;

    // Move the player through the maze
    while (current_room && current_room != &end) {
        printf("%s\n-----\n%s\n", current_room->title.c_str(), current_room->description.c_str());
        current_room = move_player(*current_room);
    }

    if (current_room == &end) {
        printf("Congratulations! You've reached the end.\n");
    } else {
        printf("Exiting the program.\n");
    }

    return 0;
}
