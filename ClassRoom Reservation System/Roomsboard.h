#ifndef RESERVEDROOM_H
#define RESERVEDROOM_H

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class ReservedRoom {
private:
    std::string roomID;
    std::string courseID;
    int time;

public:
    ReservedRoom(std::string r, std::string c, int t) : roomID(r), courseID(c), time(t) {}

    std::string getRoom() const {
        return roomID;
    }

    std::string getCourse() const {
        return courseID;
    }

    int getTime() const {
        return time;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Room: " << roomID << ", Course: " << courseID << ", Time: " << time;
        return ss.str();
    }
};

template<typename E>
class Node {
public:
    E element;
    Node<E>* next;

    Node(E elem, Node<E>* n = nullptr) : element(elem), next(n) {}
};

class RoomsBoard {
private:
    Node<ReservedRoom>* head;
    int count;

public:
    RoomsBoard() : head(nullptr), count(0) {}

    void add(const ReservedRoom& r) {
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

    void remove(const std::string& roomID) {
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

    void remove_all_but(const std::string& roomID) {
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

     void removeAll() { 
         Node<ReservedRoom>* current = head; 
         while (current != nullptr) { 
             Node<ReservedRoom>* temp = current; 
             current = current->next; 
             delete temp; 
         } 
         head = nullptr; 
         count = 0; 
     } 

     void split(RoomsBoard& board1, RoomsBoard& board2) { 
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

     void listRooms() const { 
         Node<ReservedRoom>* current = head; 
         std::cout << "List of reserved rooms:" << std::endl; 
         while (current != nullptr) { 
             std::cout << current->element.toString() << std::endl; 
             current = current->next; 
         } 
     } 

     void listReservations(const std::string& roomID) const { 
         Node<ReservedRoom>* current = head; 
         std::cout << "Reservations for room " << roomID << ":" << std::endl; 
         while (current != nullptr) { 
             if (current->element.getRoom() == roomID) { 
                 std::cout << current->element.toString() << std::endl;  
             }  
             current = current->next;  
          }  
      }  

      int size() const {  
          return count;  
      }  

      bool isEmpty() const {  
          return count == 0;  
      }  

      ~RoomsBoard() {  
          removeAll();  
      }  
  };  

  #endif // ROOMSBOARD_H