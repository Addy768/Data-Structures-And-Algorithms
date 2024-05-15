#ifndef RESERVEDROOM_H
#define RESERVEDROOM_H

#include <string>
#include <sstream>

class ReservedRoom {
private:
    std::string roomID;
    std::string courseID;
    int time;

public:
    ReservedRoom(std::string r, std::string c, int t);

    std::string getRoom() const;
    std::string getCourse() const;
    int getTime() const;
    std::string toString() const;
};

#endif /* RESERVEDROOM_H */
