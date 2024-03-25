/**
 * @file Foe.h
 * @author Alex Bocchi
 *
 *
 * Base class for the Foe class
 */

#pragma once

#include <string>
#include <memory>

#ifndef PROJECT_1_FOE_H
#define PROJECT_1_FOE_H

#include "Item.h"
#include "ItemShape.h"
#include "ItemVisitor.h"
#include "AngrySparty.h"

/**
 * Class for Foe
 */
class Foe : public ItemShape{
private:

    /// Foe image file
    std::wstring mFoeImageFile;
    /// Possible Foe states
    //std::shared_ptr<Image> mPicture;
    bool mFoeState = true;

    /// Radius of the foe
    double mRadius = 1;

    /// Down factor of foe
    double mDown = 1;


public:


    virtual ~Foe();

    Foe(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    Foe() = delete;

    /// Copy constructor (disabled)
    Foe(const Foe &) = delete;

    /// Assignment operator
    void operator=(const Foe &) = delete;

    void XmlItem(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void InstallPhysics(std::shared_ptr<Physics> physics) override;
    bool TestDown();
    double GetDown(){return mDown;}
    /**
* Accept a visitor
* @param visitor The visitor we accept
*/
    void Accept(ItemVisitor* visitor) override { visitor->VisitFoe(this); }
    bool FoeCheck()const{return mFoeState;}
    void SetAlive(bool alive, std::shared_ptr<Physics> physics);

    bool GetState(){ return mFoeState; }


};

#endif //PROJECT_1_FOE_H
