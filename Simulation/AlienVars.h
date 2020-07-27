//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_ALIENVARS_H
#define GLYNTH_ALIENVARS_H


class AlienVariables {

public:
    AlienVariables() {}

    void Set(std::string name, int value) {
        map[name] = value;
    }

    int Get(std::string name) {
        return map[name];
    }

private:
    std::map<std::string, int> map;
};


#endif //GLYNTH_ALIENVARS_H
