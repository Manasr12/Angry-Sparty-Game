/**
 * @file Block.h
 * @author Trey Cosnowski
 *
 * Class that initializes a block
 */

#ifndef PROJECT1LIB_BLOCK_H
#define PROJECT1LIB_BLOCK_H

#include "AngrySpartyView.h"
#include "Item.h"
#include <string>
#include "Physics.h"
#include "ItemShape.h"

/**
 * A block
 */
class Block : public ItemShape{
private:

    /// Block image file
    std::wstring mBlockImageFile;


    double mRepeatX = 1; /// How many times to repeat block

    double mWidth = 0; /// Width of block

    double mHeight = 0; /// Hieght of block


public:

    Block(Level *level);

    void SetImage(const std::wstring& file) override;
    /// Default constructor (disabled)
    Block() = delete;

    /// Copy constructor (disabled)
    Block(const Block &) = delete;

    /// Assignment operator
    void operator=(const Block &) = delete;

    void XmlItem(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void InstallPhysics(std::shared_ptr<Physics> physics) override;
    /**
* Accept a visitor
* @param visitor The visitor we accept
*/
    void Accept(ItemVisitor* visitor) override { visitor->VisitBlock(this); }


};


#endif //PROJECT1LIB_BLOCK_H
