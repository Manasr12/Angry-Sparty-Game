/**
 * @file ItemShape.h
 * @author Trey Cosnowski
 *
 * Class the describes items that will be hit
 */

#ifndef PROJECT_1_ITEMSHAPE_H
#define PROJECT_1_ITEMSHAPE_H

#include "Item.h"
/**
 * Class for Itemshape
 * Derived from Item
 */
class ItemShape : public Item{
private:
    /// Friction for this block
    double mFriction = .5;

    /// Restitution for this block
    double mRestituation = .5;

    /// Density for this block
    double mDensity = 1.0;

    /// Body of this block
    b2Body* mBody = nullptr;

public:
    /**
    * constructor
    * @param level
    */
    ItemShape(Level *level);
    /// Default constructor (disabled)
    ItemShape() = delete;
    /// Copy constructor (disabled)
    ItemShape(const ItemShape &) = delete;

    /// Assignment operator
    void operator=(const ItemShape &) = delete;
     /**
     * XmlItem function for load
     * @param node
     */
    void XmlItem(wxXmlNode *node);
    /**
     * pass attributes of body to Item
     * @param physics
     * @param shape
     */
    void PassAttributes(std::shared_ptr<Physics> physics,b2PolygonShape* shape) ;

    /**
     * Set body of angry to Item body
     * @param body
     */
    void SetBody( b2Body* body) {mBody = body;}

    /**
     * Get body of Item
     * @return mBody
     */
    b2Body* GetBody() { return mBody; }
};


#endif //PROJECT_1_ITEMSHAPE_H
