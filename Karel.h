#ifndef KAREL_H_INCLUDED
#define KAREL_H_INCLUDED
#include "Bludiste.h"
#include "Navigace.h"
#include <string>
#include <iostream>

class Karel : public Prohledavac {
public:
    Navigace stav[100][100];
    bool start(Bludiste & map) {
        for(int i = 0; i<100; i++) {
            for(int j = 0; j<100; j++) {
                stav[i][j].navstiveno = false;
            }
        }
        stav[0][0].navstiveno = true;
        return true;
    }
    bool start(BludisteOdkryte & map) {
        return true;
    }
    bool stop() {
        return true;
    }
    void krok(Bludiste & map) {
        // std::cout << map.pocet_kroku() << " kroku, poloha [" << map.poloha().x << ";" << map.poloha().y << "]\n";
        int poloha_x = map.poloha().x;
        int poloha_y = map.poloha().y;
        if(map.cil()) return;
        bool pohyb = false;
        if(poloha_x > 0 && !stav[poloha_x-1][poloha_y].navstiveno) {
            stav[poloha_x-1][poloha_y].navstiveno = true;
            if (map.vlevo()) {
                pohyb = true;
            }
        }
        if(!pohyb && !stav[poloha_x][poloha_y+1].navstiveno) {
            stav[poloha_x][poloha_y+1].navstiveno = true;
            if (map.nahoru()) {
                pohyb = true;
            }
        }
        if(!pohyb && !stav[poloha_x+1][poloha_y].navstiveno) {
            stav[poloha_x+1][poloha_y].navstiveno = true;
            if (map.vpravo()) {
                pohyb = true;
            }
        }
        if(!pohyb && poloha_y > 0 && !stav[poloha_x][poloha_y-1].navstiveno) {
            stav[poloha_x][poloha_y-1].navstiveno = true;
            if (map.dolu()) {
                pohyb = true;
            }
        }
        if(pohyb) {
            stav[map.poloha().x][map.poloha().y].predchozibod_x = poloha_x;
            stav[map.poloha().x][map.poloha().y].predchozibod_y = poloha_y;
        } else {
            int predchozibod_x = stav[poloha_x][poloha_y].predchozibod_x;
            int predchozibod_y = stav[poloha_x][poloha_y].predchozibod_y;
            std::cout << "Karel byl nucen vratit se na souradnice [" << predchozibod_x << ";" << predchozibod_y << "]\n";
            if(predchozibod_x != poloha_x) {
                if(predchozibod_x > poloha_x) {
                    map.vpravo();
                } else {
                    map.vlevo();
                }
            } else {
                if(predchozibod_y > poloha_y) {
                    map.nahoru();
                } else {
                    map.dolu();
                }
            }
        }
    }
    void krok(BludisteOdkryte & map) {
    }
    std::string jmeno() {
        return "Karel";
    }
};

#endif
