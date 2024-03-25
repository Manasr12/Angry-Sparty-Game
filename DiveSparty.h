/**
 * @file DiveSparty.h
 * @author Trey Cosnowski
 *
 */

#ifndef PROJECT_1_DIVESPARTY_H
#define PROJECT_1_DIVESPARTY_H

#include "Angry.h"
#include "box2d.h"
/**
 * Class for DiveSparty
 * Derived from Angry
 */
class DiveSparty : public Angry{
private:
    /// Gruff image file
    std::wstring mDiveImageFile;

    /// Bool to ensure that DiveSparty is drawn properlly
    bool mOrderDraw = true;

public:
    DiveSparty(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    DiveSparty() = delete;

    /// Copy constructor (disabled)
    DiveSparty(const DiveSparty &) = delete;

    /// Assignment operator
    void operator=(const DiveSparty &) = delete;

    void XmlItem(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void ReDraw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetPoint(b2Vec2 point) override;
    b2Vec2 GetPoint() override;
    void Accept(ItemVisitor* visitor) override { visitor->VisitDiveSparty(this); }

    void SetOrderDraw(bool isDraw) override;

    void InAir() override;
};


#endif //PROJECT_1_DIVESPARTY_H
