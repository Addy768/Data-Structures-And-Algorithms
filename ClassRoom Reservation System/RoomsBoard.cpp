#include "roomsboard.h"

RoomsBoard::RoomsBoard() : head(nullptr), count(0) {}

void RoomsBoard::add(const ReservedRoom& r) {
    Node<ReservedRoom>* newNode = new Node<ReservedRoom>(r);
    if (head == nullptr || r.getTime() < head->element.getTime()) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<ReservedRoom>* current = head;
        Node<ReservedRoom>* prev = nullptr;
        while (current != nullptr && current->element.getTime() <= r.getTime()) {
            prev = current;
            current = current->next;
        }
        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
    count++;
}

void RoomsBoard::remove(const std::string& roomID) {
    Node<ReservedRoom>* current = head;
    Node<ReservedRoom>* prev = nullptr;
    while (current != nullptr) {
        if (current->element.getRoom() == roomID) {
            if (prev == nullptr) {
                head = current->next;
                delete current;
                current = head;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
            count--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void RoomsBoard::remove_all_but(const std::string& roomID) {
    Node<ReservedRoom>* current = head;
    Node<ReservedRoom>* prev = nullptr;
    while (current != nullptr) {
        if (current->element.getRoom() != roomID) {
            if (prev == nullptr) {
                Node<ReservedRoom>* temp = current;
                current = current->next;
                delete temp;
                head = current;
                count--;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
                count--;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void RoomsBoard::removeAll() {
    Node<ReservedRoom>* current = head;
    while (current != nullptr) {
        Node<ReservedRoom>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    count = 0;
}

void RoomsBoard::split(RoomsBoard& board1, RoomsBoard& board2) {
    Node<ReservedRoom>* current = head;
    while (current != nullptr) {
        if (current->element.getTime() < 1200) {
            board1.add(current->element);
        } else {
            board2.add(current->element);
        }
        current = current->next;
    }
}

void RoomsBoard::listRooms() const {
    Node<ReservedRoom>* current = head;
    std::cout << "List of reserved rooms:" << std::endl;
    while (current != nullptr) {
        std::cout << current->element.toString() << std::endl;
        current = current->next;
    }
}

void RoomsBoard::listReservations(const std::string& roomID) const {
    Node<ReservedRoom>* current = head;
    std::cout << "Reservations for room " << roomID << ":" << std::endl;
    while (current != nullptr) {
        if (current->element.getRoom() == roomID) {
            std::cout << current->element.toString() << std::endl;
        }
        current = current->next;
    }
}

int RoomsBoard::size() const {
    return count;
}

bool RoomsBoard::isEmpty() const {
    return count == 0;
}

RoomsBoard::~RoomsBoard() {
    removeAll();
}
