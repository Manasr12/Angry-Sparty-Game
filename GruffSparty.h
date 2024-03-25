/**
 * @file GruffSparty.h
 * @author Trey Cosnowski
 *
 */

#ifndef PROJECT_1_GRUFFSPARTY_H
#define PROJECT_1_GRUFFSPARTY_H

#include "Angry.h"
#include "box2d.h"

/**
 * Class for GruffSparty
 */
class GruffSparty : public Angry{
private:
    /// Gruff image file
    std::wstring mGruffImageFile;

    /// Bool to ensure that GruffSparty is drawn properlly
    bool mOrderDraw = true;

public:
    GruffSparty(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    GruffSparty() = delete;

    /// Copy constructor (disabled)
    GruffSparty(const GruffSparty &) = delete;

    /// Assignment operator
    void operator=(const GruffSparty &) = delete;

    void XmlItem(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void ReDraw(std::shared_ptr<wxGraphicsContext> graphics) override;


    void SetPoint(b2Vec2 point) override;
    b2Vec2 GetPoint() override;

    void SetOrderDraw(bool isDraw) override;

    void InAir() override {}

};


#endif //PROJECT_1_GRUFFSPARTY_H
