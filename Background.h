/**
 * @file Background.h
 * @author Alex Bocchi
 *
 * Class that initializes the background
 */

#ifndef PROJECT_1_BACKGROUND_H
#define PROJECT_1_BACKGROUND_H

#include "AngrySpartyView.h"
#include "Item.h"
#include <string>
class AngrySparty;

/**
 * The background
 */
class Background : public Item{
private:
    /// Background image file
    std::wstring mBackground;


    /// The file for this image
    wxGraphicsBitmap mBitmap;

    /// Height
    double mHeight;
    /// Width
    double mWidth;

public:
    Background(Level *level);

    void SetImage(const std::wstring &file) override;

    /**
     * Set the item size
     * @param x X size in pixels
     * @param y Y size in pixels
     */
    void SetSize(double x, double y) { mWidth = x; mHeight = y; }

    /// Default constructor disabled
    Background() = delete;

    /// Copy Constructor (disabled)
    Background(const Background &) = delete;

    ///Assignment operator
    void operator=(const Background &) = delete;

    void XmlItem(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
* Accept a visitor
* @param visitor The visitor we accept
*/
    void Accept(ItemVisitor* visitor) override { visitor->VisitBackground(this); }


};

#endif //PROJECT_1_BACKGROUND_H
