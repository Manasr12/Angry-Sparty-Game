/**
 * @file ItemVisitor.h
 *
 * @author Mannan Dhillon
 *
 * item visitor base class.
 */

#ifndef PROJECT_1_ITEMVISITOR_H
#define PROJECT_1_ITEMVISITOR_H
// Forward references to all tile types
class Foe;
class Background;
class Block;
class Poly;
class Slingshot;
class Goalpost;
class GruffSparty;
class Angry;
class DiveSparty;


/** Item visitor base class */
class ItemVisitor
{

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit a foe object
     * @param foe we are visiting
     */
    virtual void VisitFoe(Foe* foe) {}
    /**
     * Visit a background object
     * @param background we are visiting
     */
    virtual void VisitBackground(Background* background) {}
    /**
     * Visit a block object
     * @param block we are visiting
     */
    virtual void VisitBlock(Block* block) {}
    /**
     * Visit a poly object
     * @param poly we are visiting
     */
    virtual void VisitPoly(Poly* poly) {}
    /**
     * Visit a slingshot object
     * @param slingshot we are visiting
     */
    virtual void VisitSlingshot(Slingshot* slingshot) {}
    /**
     * Visit a Goalpost object
     * @param goalpost we are visiting
     */
    virtual void VisitGoalpost(Goalpost* goalpost) {}
    virtual void VisitGruffSparty(GruffSparty* gruffSparty) {}
    virtual void VisitAngrySparty(Angry* angrySparty) {}
    virtual void VisitDiveSparty(DiveSparty* diveSparty) {}



};
#endif //PROJECT_1_ITEMVISITOR_H
