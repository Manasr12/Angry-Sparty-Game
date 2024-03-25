/**
 * @file FoeVisitor.h
 *
 * @author Mannan dhillon
 *
 * Foe visitor base class.
 */

#ifndef PROJECT_1_FOEVISITOR_H
#define PROJECT_1_FOEVISITOR_H


#include "ItemVisitor.h"

#include "Foe.h"
class AngrySparty;
/**
 * Class for visting foe and felting it from mitem and physics body
 * Derived from ItemVisitor
 */
class FoeVisitor : public ItemVisitor{
private:


    double mKilledFoes = 0;
    AngrySparty* mAngrySparty;
public:
    /**
    *  Foe vistor aonsttructor
    * @param angrySparty
    */
    FoeVisitor(AngrySparty *angrySparty);
    /**
    *  visit the foe
    * @param foe
    */
    void VisitFoe(Foe *foe) override;
    /**
    * counts up the foe kills and returns them
    * @return mKilledFoes
    */
    int FoeKills(){return mKilledFoes; }
};

#endif //PROJECT_1_FOEVISITOR_H
