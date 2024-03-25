/**
 * @file Images.h
 * @author Trey Cosnowski
 *
 * Base class for saving images
 */

#ifndef PROJECT_1_IMAGES_H
#define PROJECT_1_IMAGES_H
#include <wx/graphics.h>

/**
 * Class for Images
 */
class Images {
private:

    std::shared_ptr<wxImage> mImage; /// Saving the image
    wxGraphicsBitmap mBitmap; /// Saving the bitmap
    //std::wstring mName;

public:

    /**
     * Getter for Image
     * @return mImage
     */
    std::shared_ptr<wxImage> GetImage(){ return mImage; }

    /**
    * Getter for Bitmap
    * @return mBitmap
    */
    wxGraphicsBitmap GetBitmap(){ return mBitmap; }

    /**
     * Setter for Image
     * @param image the image to save
     */
     void SetImage(std::shared_ptr<wxImage> image){ mImage = image; }

    /**
    * Setter for Bitmap
    * @param bitmap the image to save
    */
    void SetBitmap(wxGraphicsBitmap bitmap){ mBitmap = bitmap; }

};


#endif //PROJECT_1_IMAGES_H
