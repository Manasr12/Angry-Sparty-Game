/**
 * @file FoeCounter.h
 * @author Trey Cosnowski
 *
 * Class that counts the amount of foes
 */

#ifndef PROJECT_1_FOECOUNTER_H
#define PROJECT_1_FOECOUNTER_H

#include "ItemVisitor.h"

/**
 * Class for counting foes
 * Derived from ItemVisitor
 */
class FoeCounter : public ItemVisitor{
private:
    int mNumFoes = 0;

public:
    int GetNumFoes() { return mNumFoes; }

    void VisitFoe(Foe* foe);
};


#endif //PROJECT_1_FOECOUNTER_H
