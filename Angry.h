/**
 * @file Angry.h
 * @author Trey Cosnowski
 *
 */

#ifndef PROJECT_1_ANGRY_H
#define PROJECT_1_ANGRY_H

class Level;
#include "box2d.h"
#include <wx/graphics.h>
#include <string>
#include "Physics.h"
#include "Item.h"
#include "ItemShape.h"


/**
 * Class for Angry
 */
class Angry : public ItemShape{


private:
    /// level
    Level *mLevel;

    /// Item location in the AngrySparty Game
    double mX = 0; /// X location for the center of item
    double mY = 0; /// Y location for the center of item

    double mSpacing = 0; /// Spacing between spartys

    double mRadius = 0.25; /// radius of item
    double mAngle = 0; /// angle of item

    /// The item image
    std::shared_ptr<wxImage> mAngryImage;

    /// The item bitmap
    wxGraphicsBitmap mAngryBitmap;

    /// The file for this item
    std::wstring mFile;
    /// Type of block with physics
    std::string mStatic = "dynamic";
    /// b2Vec2 location
    b2Vec2 initLocation = b2Vec2(5.50, 1.35);

    /// Physics that this block uses
    std::shared_ptr<Physics> mPhysics;

    /// Tests to see if angry in air
    bool mAir;

    /// See if angry is deleted
    bool mDeleted = false;
public:
    Angry(Level *level);
    /// Destructor
    virtual ~Angry();
    /// Default constructor (disabled)
    Angry() = delete;

    /// Copy constructor (disabled)
    Angry(const Angry &) = delete;

    /// Assignment operator
    void operator=(const Angry &) = delete;
    /**
     * Draw this item
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;


    void SetImage(const std::wstring& file) override;

    /**
     * Virtural function for xml load
     * @param node the current node
     */
    void XmlItem(wxXmlNode *node) override;

    void InstallPhysics(std::shared_ptr<Physics> physics) override;


    //std::shared_ptr<Angry> HitTest(int x, int y);

    /**
     * Gets the physics of the current angry
     * @return
     */
    std::shared_ptr<Physics> GetPhysics(){ return mPhysics; }

    /**
     * Returns the angle for the item
     * @return Angle of rotation
     */
    double GetAngle(){ return mAngle; }

    // Find out how to fix these functions
    void SetPoint(b2Vec2 point) override;
    /**
     * Returns the point of current angry body
     * @return
     */
    b2Vec2 GetPoint() override { return b2Vec2(0, 0); }
    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitAngrySparty(this); }
    /**
     * Sets the order to draw based on bool is draw
     * @param isDraw wether to draw or not
     */
    void SetOrderDraw(bool isDraw) override {};
    /**
     * Redraw the angry
     * @param graphics
     */
    void ReDraw(std::shared_ptr<wxGraphicsContext> graphics) override {};

    bool IsDynamic();
    void Launch(std::shared_ptr<Physics> physics);
    /**
     * Function for when the sparty is in the air
     */
    virtual void InAir(){}
    //virtual void Bomb(){}

    /**
     * returns true whether angry is in the air or not
     * @return
     */
    bool GetAir(){ return mAir; }


    void Reset();
    /**
     * delete the angry
     * @param physics
     */
    void DeleteAngry(std::shared_ptr<Physics> physics);
    /**
     * returns true if angry gets deleted
     * @return
     */
    bool GetDeleted(){ return mDeleted; }

};


#endif //PROJECT_1_ANGRY_H
