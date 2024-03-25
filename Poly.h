/**
 * @file Poly.h
 * @author Trey Cosnowski
 *
 * Class that initializes a poly
 */

#ifndef PROJECT_1_POLY_H
#define PROJECT_1_POLY_H

#include "AngrySpartyView.h"
#include "Item.h"
#include <b2_world.h>
#include <wx/graphics.h>
#include "ItemShape.h"

/**
 * Class for Poly
 */
class Poly : public ItemShape{
private:
    /// Vertices
   b2Vec2 mVertices[3];
    /// Poly image file
    std::wstring mPolyImageFile;


    /// Center of rotation X
    double mCenterRoationX = 0;

    /// Center of rotation Y
    double mCenterRoationY = 0;

    /// First of vert X
    double mFirstVertX = 0;

    /// First of vert Y
    double mFirstVertY = 0;
    /// Width of poly
    double mWidth = 0;
    /// Hieght of poly
    double mHeight = 0;

public:
    Poly(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    Poly() = delete;

    /// Copy constructor (disabled)
    Poly(const Poly &) = delete;

    /// Assignment operator
    void operator=(const Poly &) = delete;
    /**
     * Draw the poly
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * xml item to load the poly
     * @param node
     */
    void XmlItem(wxXmlNode *node) override;
    /**
     * installing the physics for poly
     * @param physics
     */
    void InstallPhysics(std::shared_ptr<Physics> physics) override;
    /**
* Accept a visitor
* @param visitor The visitor we accept
*/
    void Accept(ItemVisitor* visitor) override { visitor->VisitPoly(this); }
};


#endif //PROJECT_1_POLY_H
