/**
 * @file Level.h
 * @author Trey Cosnowski
 *
 * Main class for the levels
 */

#ifndef PROJECT_1_LEVEL_H
#define PROJECT_1_LEVEL_H

#include "Item.h"
#include "Angry.h"


class AngrySparty;

/**
 * Class for Level
 */
class Level {
private:

    AngrySparty *mAngrySparty; /// The game this level is in

    double mWidth = 0; /// Width of level

    double mHeight = 0; ///Height of level

    int mNumOfSpartys = -1;

    /// Collection of items
    std::vector<std::shared_ptr<Item> > mItems;

    /// Collection of the anrgys
    std::vector<std::shared_ptr<Angry> > mAngrys;

    /// Int to go through mAngrys
    int mTraverseAngry = -1;

    /// Current angry
    std::shared_ptr<Angry> mAngry = nullptr;
    //bool mFoeState = true;
    /// Current score of the level
    int mLevelScore = 0;

public:
    ///  Default constructor (disabled)
    Level() = delete;

    ///  Copy constructor (disabled)
    Level(const Level &) = delete;
    Level(AngrySparty *angrySparty);

    /**
     * Destructor
    */
    virtual ~Level();
    /**
     * Getter for angry sparty
     * return AngrySparty pointer
     */
    AngrySparty* GetAngrySparty(){ return mAngrySparty; }

    /**
     * Getter for current angry
     * @return pointer to the current angry
     */
    std::shared_ptr<Angry> GetAngry() { return mAngry; }

    void XmlLevel(wxXmlNode *root);
    virtual void XmlItems(wxXmlNode *node);
    void Add(std::shared_ptr<Item> item);

    void Update(double frameRate);



    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void XmlAngrys(wxXmlNode *node);
    /**
     * Getter for items
     * @return mItems a collection of items
     */
    std::vector<std::shared_ptr<Item> > GetItems(){ return mItems; }

    /**
    *  Returns the number of spatys for spacing
    * @return num of spatrys
    */
    int GetNumSpartys() {return mNumOfSpartys;}

    void AddToNumSpartys() {mNumOfSpartys++;}

    double GetWidth();

    double GetHeight();

    void Clear();

    void InstallPhysics(std::shared_ptr<Physics>);
    void Remove(Foe *foe);
    void Remove(Angry *angry);

    void Accept(ItemVisitor *visitor);
    std::shared_ptr<Angry> LoadAngry();

    void RemoveActiveAngry();
    std::shared_ptr<Angry> GetActiveAngry() {return mAngry;};

    double CheckSpartys();
    
    double KillFoe();

    void KillAngry();

    void SetTraversal();
};


#endif //PROJECT_1_LEVEL_H
