/**
 * @file Slingshot.h
 * @author Will Gamba
 *
 * Class for the slingshot
 */

#ifndef PROJECT_1_SLINGSHOT_H
#define PROJECT_1_SLINGSHOT_H

#include "Item.h"
#include "AngrySparty.h"
#include "Level.h"
#include "Angry.h"
#include "Consts.h"

/**
 * Class for the slingshot
 */
class Slingshot : public Item{
private:
    /// Current Angry object
    std::shared_ptr<Angry> mAngry;

    /// Current level
    Level *mLevel;

    /// Slingshot image file
    std::wstring mSlingshotImageFile;

    /// The slingshot front image
    std::shared_ptr<wxImage> mFrontImage;

    /// The temporary angry image
    std::shared_ptr<wxImage> mTempAngryImage;

    /// The file for this image
    wxGraphicsBitmap mBitmap;

    double mOffsetY = 0.7; /// The offset for drawing the main slingshot

    /// Initial center of the angry
    b2Vec2 mAngryCenter = b2Vec2(-5.50, 1.35);

    /// Current point of mAngry
    b2Vec2 mCurrPoint = b2Vec2(-5.50, 1.35);

    double mLength; /// Used for testing the length of the vector

    /// Check if the angry has been loaded into the slingshot
    bool mInitLoad = false;

public:

    Slingshot(Level *level);

    /// Default constructor disabled
    Slingshot() = delete;

    /// Copy constructor (disabled)
    Slingshot(const Slingshot &) = delete;

    ///Assignment operator
    void operator=(const Slingshot &) = delete;



    void SetImage(const std::wstring& file) override;
    void XmlItem(wxXmlNode *node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawBackBand(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawAngry(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawMiddleBand(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawFront(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawFrontBand(std::shared_ptr<wxGraphicsContext> graphics);

    void SetBand(double x, double y);

    /** Used for SlingshotDragTest */
    b2Vec2 GetCurrPoint() {return mCurrPoint;} // Check that it's okay to have this for the test
    double GetLength() {return mLength;} /// Test for the slingshot length

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSlingshot(this); }

};

#endif //PROJECT_1_SLINGSHOT_H
