/*
 * Plaque.cpp
 * Copyright (C) 2015 Florian Leprince <floleprince@gmail.com>
 *
 * Distributed under terms of the GNU GPL V2 license.
 */

#include "Plaque.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>

namespace Gaia {
    static int NPlaques = 0;

    Plaque::Plaque(Triangle *root) {
        id = NPlaques++;

        in.push_back(root);
        root->plaque = this;

        Triangle* tmpt = root->GetNeighbor(0);
        if (tmpt->plaque == nullptr) {
            onedge.push_back(tmpt);
        }

        tmpt = root->GetNeighbor(1);
        if (tmpt->plaque == nullptr) {
            onedge.push_back(tmpt);
        }

        tmpt = root->GetNeighbor(2);
        if (tmpt->plaque == nullptr) {
            onedge.push_back(tmpt);
        }

        canGrow = (onedge.size() != 0);
        edgelength = 3;

        color[0] = rand() % 256;
        color[1] = rand() % 256;
        color[2] = rand() % 256;
    }

    Plaque::~Plaque() {
    }

    void Plaque::UseGLColor() {
        glColor3ub(color[0], color[1], color[2]);
    }

    bool Plaque::Step() {
        if (canGrow) {
            Triangle *elu = nullptr;
            int nelu;

            do {
                nelu = rand() % onedge.size();
                elu = onedge[nelu];
                if (elu->plaque != nullptr) {
                    elu = nullptr;
                    onedge.erase(onedge.begin() + nelu);
                    canGrow = (onedge.size() != 0);
                }
            } while (elu == nullptr && canGrow);

            if (canGrow) {
                onedge.erase(onedge.begin() + nelu);
                canGrow = (onedge.size() != 0);
                in.push_back(elu);
                elu->plaque = this;

                Triangle *tmpt = elu->GetNeighbor(0);
                if (tmpt == nullptr)
                    cout << "ERROR nullptr" << endl;
                else if (tmpt->plaque == nullptr)
                    onedge.push_back(tmpt);

                tmpt = elu->GetNeighbor(1);
                if (tmpt == nullptr)
                    cout << "ERROR nullptr" << endl;
                else if (tmpt->plaque == nullptr)
                    onedge.push_back(tmpt);

                tmpt = elu->GetNeighbor(2);
                if (tmpt == nullptr)
                    cout << "ERROR nullptr" << endl;
                else if (tmpt->plaque == nullptr)
                    onedge.push_back(tmpt);
            }
        }

        return canGrow;
    }
}

