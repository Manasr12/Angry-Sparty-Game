/**
 * @file Item.h
 * @author Trey Cosnowski
 *
 * Base class for any item in AngrySparty
 */

#ifndef PROJECT1LIB_ITEM_H
#define PROJECT1LIB_ITEM_H


class Level;
#include "box2d.h"
#include <wx/graphics.h>
#include "Physics.h"
#include "ItemVisitor.h"


/**
 * Base class for any item in AngrySparty
 */
class Item {
protected:
    Item(Level *level);

private:
    /// The level this item is in
    Level *mLevel;

    /// Item location in the AngrySparty Game
    double mX = 0; /// X location for the center of item
    double mY = 0; /// Y location for the center of item

    /// Angle of the item
    double mAngle = 0;

    /// The item image
    std::shared_ptr<wxImage> mItemImage;

    wxGraphicsBitmap mItemBitmap;

    /// The file for this item
    std::wstring mFile;



    std::string mStatic = "dynamic"; /// Type of block with physics


public:
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;
    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const {return mX;}
    /**
  * The Y location of the item
  * @return Y location in pixels
  */
    double GetY() const {return mY;}

    /**
     * Returns the angle for the item
     * @param @return Angle of rotation
     */
    double GetAngle(){ return mAngle; }

    virtual void SetImage(const std::wstring &file);

    /**
     * Virtural function for xml load
     * @param node
     */
    virtual void XmlItem(wxXmlNode *node);
    /**
    * Virtual function for install physics
    * @param std::shared_ptr<Physics>
    */
    virtual void InstallPhysics(std::shared_ptr<Physics>){};
    /**
    * getter for bitmap
    * @param graphics
    */
    wxGraphicsBitmap GetBitmap(std::shared_ptr<wxGraphicsContext> graphics);
    /**
    * Gets the type of block
    * @return mStatic
    */
    std::string GetStatic() { return mStatic; }
    /**
   * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) = 0;
    /**
    * Update function
    * @param frameRate
    */
    void Update(double frameRate);
    /**
    * Sets the point
    * @param point
    */
    virtual void SetPoint(b2Vec2 point) {};
    /**
    * Gets the point
    * @param b2Vec2
    */
    virtual b2Vec2 GetPoint() { return b2Vec2(0, 0); }
    /**
    * Sets the draw order
    * @param isDraw`
    */
    virtual void SetOrderDraw(bool isDraw) {};
    /**
    * reDraws the the graphics
    * @param graphics
    */
    virtual void ReDraw(std::shared_ptr<wxGraphicsContext> graphics) {};

};

#endif //PROJECT1LIB_ITEM_H
