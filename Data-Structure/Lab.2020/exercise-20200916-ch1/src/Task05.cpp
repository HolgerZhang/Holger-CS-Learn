// Created by Zhang Hao on 2020/9/16.
// Coding: UTF-8
// File: Task05.cpp
// Task: Page.26, 4(5) Four people want to cross the bridge, and only two people at most can cross this bridge per time.
//                     They are at one end of the bridge, and it was at night so they needed a flashlight but only one.
//                     This means that when two people cross the bridge, one of them has to bring the flashlight back.
//                     Each person walks at a different speed: A takes 1 minute to cross the bridge, B takes 2 minutes,
//                     C takes 5 minutes, D takes 10 minutes. Two people walk at the same speed as the slower one.
//                     Question: How long will it take them to cross the bridge at least?

#include <iostream>

/**
 * Question: How long will it take them to cross the bridge at least?
 * Solution: + Case - the number of people >= 3
 *           Let the fast person to cross the bridge with another people, and let him to bring the flashlight back,
 *           which needs the least time:
 *              `the sum of the time of each person to cross the bridge + (number of people - 3) * the fast one`.
 *           + Case - the number of people = 2
 *           The time of the slower person to cross the bridge.
 *           + Case - the number of people = 1
 *           The time of the only person to cross the bridge.
 * Time Complexity: O(n), n = number of people
 * @param timeOfEachPerson  an array of the time of each person to cross the bridge.
 * @param numberOfPeople    the number of people.
 * @return                  the least time of them all cross the bridge.
 */
int timeOfCrossingBridge(const int timeOfEachPerson[], unsigned numberOfPeople) {
    if (numberOfPeople == 1) {  // Case - the number of people = 1
        return timeOfEachPerson[0];
    } else if (numberOfPeople == 2) {  // Case - the number of people = 2
        return std::max(timeOfEachPerson[0], timeOfEachPerson[1]);
    }
    // Case - the number of people >= 3
    int indexOfMinTimePerson = 0, sumTime = 0;
    for (int i = 0; i < numberOfPeople; ++i) {
        if (timeOfEachPerson[indexOfMinTimePerson] > timeOfEachPerson[i]) { // Find the fast person.
            indexOfMinTimePerson = i;
        }
        sumTime += timeOfEachPerson[i];     // Calculate the sum of the time of each person to cross the bridge.
    }
    sumTime += (numberOfPeople - 3) * timeOfEachPerson[indexOfMinTimePerson];
    return sumTime;
}

int main() {
    int time[4]{1, 2, 5, 10}, result;
    result = timeOfCrossingBridge(time, 4);
    std::cout << "It takes them " << result << " minute(s) to cross the bridge.\n";
    return 0;
}