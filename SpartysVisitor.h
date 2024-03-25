/**
 * @file SpartysVisitor.h
 * @author ihcco
 *
 *
 */

#ifndef PROJECT_1_SPARTYSVISITOR_H
#define PROJECT_1_SPARTYSVISITOR_H

#include "ItemVisitor.h"
#include "Angry.h"
class AngrySparty;

/**
 * Class for visting sparty and deleting sparty
 * Derived from ItemVisitor
 */
class SpartysVisitor : public ItemVisitor{
private:
    AngrySparty* mAngrySparty;
public:
    SpartysVisitor(AngrySparty *angrySparty);

    void VisitAngrySparty(Angry *angry) override;
};

#endif //PROJECT_1_SPARTYSVISITOR_H
