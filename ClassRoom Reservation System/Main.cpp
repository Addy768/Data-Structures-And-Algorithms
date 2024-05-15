// #include <iostream>
// #include <string>
// #include <sstream>
// #include "Roomsboard.h"


// using namespace std;

// int main() {
//     RoomsBoard board;
//     int choice;
//     string roomID, courseID;
//     string time;

//     do {
//         cout << "\nMenu:\n1. Add new room\n2. Remove all occurrences of a room\n3. Remove all rooms except a room\n4. Clear the RoomsBoard\n5. Split the list of rooms\n6. Display RoomsBoard\n7. Display reservations of a room\n8. Exit\nEnter your choice: ";
//         cin >> choice;

//         switch (choice) {
//         case 1:
//             cout << "Enter roomID, courseID, and time (format HH:MM): ";
//             cin >> roomID >> courseID >> time;
//             {
//                 int hours, minutes;
//                 char colon;
//                 stringstream(time) >> hours >> colon >> minutes;
//                 int t = hours * 100 + minutes;
//                 if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
//                     cout << "Invalid time. Please enter a valid time (HH:MM).\n";
//                 } else {
//                     board.add(ReservedRoom(roomID, courseID, t));
//                 }
//             }
//             break;
//         case 2:
//             cout << "Enter roomID to remove: ";
//             cin >> roomID;
//             board.remove(roomID);
//             break;
//         case 3:
//             cout << "Enter roomID to keep: ";
//             cin >> roomID;
//             board.remove_all_but(roomID);
//             break;
//         case 4:
//             board.removeAll();
//             cout << "RoomsBoard cleared.\n";
//             break;
//         case 5: {
//             RoomsBoard board1, board2;
//             board.split(board1, board2);
//             cout << "List of rooms before 12:00:" << endl;
//             board1.listRooms();
//             cout << "\nList of rooms after 12:00:" << endl;
//             board2.listRooms();
//         }
//                 break;
//         case 6:
//             if (board.isEmpty()) {
//                 cout << "RoomsBoard is empty.\n";
//             } else {
//                 board.listRooms();
//             }
//             break;
//         case 7:
//             cout << "Enter roomID to display reservations: ";
//             cin >> roomID;
//             board.listReservations(roomID);
//             break;
//         case 8:
//             cout << "Exiting program.\n";
//             break;
//         default:
//             cout << "Invalid choice. Please enter a number between 1 and 8.\n";
//         }
//     } while (choice != 8);

//     return 0;
// }


#include <iostream>
#include <string>
#include "Roomsboard.h"

int main() {
    RoomsBoard board;
    int choice;
    std::string roomID, courseID, time;

    do {
        std::cout << "\nMenu:\n1. Add new room\n2. Remove all occurrences of a room\n3. Remove all rooms except a room\n4. Clear the RoomsBoard\n5. Split the list of rooms\n6. Display RoomsBoard\n7. Display reservations of a room\n8. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter roomID, courseID, and time (format HH:MM): ";
                std::cin >> roomID >> courseID >> time;
                if (time.size() != 5 || time[2] != ':') {
                    std::cout << "Invalid time format. Please enter time in HH:MM format.\n";
                } else {
                    int hours = std::stoi(time.substr(0, 2));
                    int minutes = std::stoi(time.substr(3, 2));
                    if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
                        std::cout << "Invalid time. Please enter a valid time (HH:MM).\n";
                    } else {
                        int t = hours * 100 + minutes;
                        board.add(ReservedRoom(roomID, courseID, t));
                    }
                }
                break;
            case 2:
                std::cout << "Enter roomID to remove: ";
                std::cin >> roomID;
                board.remove(roomID);
                break;
            case 3:
                std::cout << "Enter roomID to keep: ";
                std::cin >> roomID;
                board.remove_all_but(roomID);
                break;
            case 4:
                board.removeAll();
                std::cout << "RoomsBoard cleared.\n";
                break;
            case 5: {
                RoomsBoard board1, board2;
                board.split(board1, board2);
                std::cout << "List of rooms before 12:00:" << std::endl;
                board1.listRooms();
                std::cout << "\nList of rooms after 12:00:" << std::endl;
                board2.listRooms();
            }
            break;
            case 6:
                if (board.isEmpty()) {
                    std::cout << "RoomsBoard is empty.\n";
                } else {
                    board.listRooms();
                }
                break;
            case 7:
                std::cout << "Enter roomID to display reservations: ";
                std::cin >> roomID;
                board.listReservations(roomID);
                break;
            case 8:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}