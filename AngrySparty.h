/**
 * @file AngrySparty.h
 * @author Alex Bocchi
 *
 * Main class for the Angry Sparty game
 */

#ifndef PROJECT_1_ANGRYSPARTY_H
#define PROJECT_1_ANGRYSPARTY_H
#include <wx/wxprec.h>
#include <memory>
#include <map>
#include <tuple>
#include "Scoreboard.h"
#include "Level.h"
#include "Images.h"
#include "Physics.h"
#include "Angry.h"


/**
 * The Angry Sparty game
 */
class AngrySparty {
private:

    /// Map of loaded images
    std::map<const std::wstring, Images> mImageMap;

    /// Width of Background
    int mWidth =  8;

    /// Height of Background
    int mHeight = 8;

    /// Active Level
    std::shared_ptr<Level> mActiveLevel;

    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;

    /// The scoreboard of the game
    Scoreboard mScoreboard;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    ///Collection of all the levels
    std::vector<std::shared_ptr<Level> > mLevels;

    /// X-Offset of the image
    double mXOffset;

    /// Y-Offset of the image
    double mYOffset;

    /// Scale of the image
    double mScale;

    /// Physics that this level uses
    std::shared_ptr<Physics> mPhysics;

    /// Member variable for mouse location
    b2Vec2 mMouseLocation = b2Vec2(0, 0);

    /// Level number
    int mLevelNumber;

    /// Bool to determine if grabbing the active angry
    bool mGrabbingItem = false;

    /// Double for determining the duration the level text has been displayed
    double mLevelTextDuration = 0;

    /// Double for determining the duration since the sparty has been shot
    double mSpartyShotTime = 2;

    /// Bool respresenting if the sparty has been initiallized
    bool mInit = false;

public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Get the directory the images are stored in
     * @return Images directory path
     */
    const std::wstring& GetImagesDirectory() const { return mImagesDirectory; }

    void SetImagesDirectory(const std::wstring& dir);

    void Load(const std::wstring& filename);

    /// Assignment operator
    void operator=(const AngrySparty&) = delete;

    /// Copy constructor (disabled)
    AngrySparty(const AngrySparty&);

    AngrySparty();

    /**
     * Destructor
    */
    virtual ~AngrySparty() = default;

    /**
     * Getter for Image hash map
     * @return Map
     */
    std::map<const std::wstring, Images> GetImageMap() { return mImageMap; }

    /**
     * Setter for ImageMap
     * @param imageMap
     */
    void SetImageMap(const std::wstring filename, Images image);

    void SetLevel(int level);
    /**
     * Update function
     * @param frameRate
     */
    void Update(double frameRate);

    /**
     * Getter for mLevels
     * @return mLevels a collection of levels
     */
    std::vector<std::shared_ptr<Level> > GetLevels() { return mLevels; }

    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    bool HitTest();
    /**
     * updates the level status
     * @param framerate
     */
    void UpdateLevelStatus(double framerate);
    void PrintLevelStatus(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * Loads the levels
     */
    void LoadLevels();
    /**
     * Gets the current level
     * @return mActiveLeveL
     */
    std::shared_ptr<Level> GetCurrentLevel(){ return mActiveLevel;}
    /**
     * Level State function
     */
    void LevelState();
    void ResetLevelVariables();
    /**
     * Gets the physics
     * @return mPhysics
     */
    std::shared_ptr<Physics> GetPhysics(){ return mPhysics; }

};

#endif //PROJECT_1_ANGRYSPARTY_H
