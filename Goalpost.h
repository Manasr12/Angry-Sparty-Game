/**
 * @file Goalpost.h
 * @author Will Gamba
 *
 * Class for the goalpost
 */

#ifndef PROJECT_1_GOALPOST_H
#define PROJECT_1_GOALPOST_H

#include "Item.h"
#include "Level.h"
#include "Angry.h"

/**
 * Class for the goalpost
 */
class Goalpost : public Item{
private:
    /// Current Angry object
    std::shared_ptr<Angry> mAngry;

    /// Current level
    Level *mLevel;

    /// Goalpost image file
    std::wstring mGoalpostImageFile;

    /// The goalpost front image
    std::shared_ptr<wxImage> mFrontImage;

    /// The temporary angry image
    std::shared_ptr<wxImage> mTempAngryImage;

    /// The file for this image
    wxGraphicsBitmap mBitmap;

    double mOffsetY = 1.2; /// The offset for drawing the main goalpost

    /// Initial center of the angry
    b2Vec2 mAngryCenter = b2Vec2(-5.51, 2.56);

    /// Current point of mAngry
    b2Vec2 mCurrPoint = b2Vec2(-5.51, 2.56);


    double mLength; /// Used for testing the length of the vector

    /// Check if the angry has been loaded into the slingshot
    bool mInitLoad = false;

public:
    Goalpost(Level *level);
    /// Default constructor disabled
    Goalpost() = delete;

    /// Copy constructor (disabled)
    Goalpost(const Goalpost &) = delete;



    void SetImage(const std::wstring& file) override;
    void XmlItem(wxXmlNode *node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawBackBand(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawAngry(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawMiddleBand(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawFront(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawFrontBand(std::shared_ptr<wxGraphicsContext> graphics);

    void SetBand(double x, double y);

    /** Used for goalpost DragTest */
    b2Vec2 GetAngryCenter() {return mAngryCenter;} // Check that it's okay to have this for the test
    double GetLength() {return mLength;} /// Test for the goalpost length

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitGoalpost(this); }

};

#endif //PROJECT_1_GOALPOST_H
