/**
 * @file HelmetSparty.h
 * @author Trey Cosnowski
 *
 */

#ifndef PROJECT_1_HELMETSPARTY_H
#define PROJECT_1_HELMETSPARTY_H
#include "Angry.h"

/**
 * Class for HelmetSparty
 */
class HelmetSparty : public Angry{
private:
    /// Gruff image file
    std::wstring mHelmetImageFile;

    /// Bool to ensure that HelmetSparty is drawn properlly
    bool mOrderDraw = true;

public:
    HelmetSparty(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    HelmetSparty() = delete;

    /// Copy constructor (disabled)
    HelmetSparty(const HelmetSparty &) = delete;

    /// Assignment operator
    void operator=(const HelmetSparty &) = delete;

    void XmlItem(wxXmlNode *node) override;


    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    b2Vec2 GetPoint() override;
    void SetPoint(b2Vec2 point) override;

    void SetOrderDraw(bool isDraw) override;
    void ReDraw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InAir() override {}

};


#endif //PROJECT_1_HELMETSPARTY_H
