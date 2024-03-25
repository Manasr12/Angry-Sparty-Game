/**
 * @file Level.cpp
 * @author Trey Cosnowski
 *
 * Base class for a level
 */

#include "pch.h"
#include "Level.h"
#include "AngrySparty.h"
#include "Block.h"
#include "Poly.h"
#include "Foe.h"
#include "Goalpost.h"
#include "Background.h"
#include "Angry.h"
#include "GruffSparty.h"
#include "HelmetSparty.h"
#include "Slingshot.h"
#include "FoeCounter.h"
#include "FoeVisitor.h"
#include "SpartysVisitor.h"
#include "DiveSparty.h"

using namespace std;
void Level::XmlLevel(wxXmlNode *root)
{
    double width, height;
    root->GetAttribute(L"width", L"0").ToDouble(&width);
    root->GetAttribute(L"height", L"0").ToDouble(&height);
    mWidth = width;
    mHeight = height;
}

Level::Level(AngrySparty *angrySparty) : mAngrySparty(angrySparty)
{

}

/**
 * Deconstructor
 */
Level::~Level() {

}

void Level::XmlItems(wxXmlNode *node)
{
    Clear();
    auto child = node->GetChildren();

    for( ; child; child = child->GetNext())
    {
        auto name = child->GetName();
        shared_ptr<Item> item;
        ///Pushing
        if (name == L"background")
        {
            item = make_shared<Background>(this);
        }

        else if (name == L"block")
        {
            item = make_shared<Block>(this);
        }

        else if(name == L"poly")
        {
            item = make_shared<Poly>(this);
        }

        else if(name == L"foe")
        {
            item = make_shared<Foe>(this);
        }

        else if (name == L"slingshot")
        {
            item = make_shared<Slingshot>(this);
        }

        else if (name == L"goalposts")
        {
            item = make_shared<Goalpost>(this);
        }




        if (item != nullptr)
        {

            Add(item);
            item->XmlItem(child);
        }
    }


}


void Level::XmlAngrys(wxXmlNode *node)
{
    ///Pushing
    auto child = node->GetChildren();
    shared_ptr<Angry> angry;
    angry = make_shared<Angry>(this);

    for( ; child; child = child->GetNext())
    {
        auto name = child->GetName();
        ///Pushing
        if (name == L"gruff-sparty")
        {
            angry = make_shared<GruffSparty>(this);
        }

        else if (name == L"helmet-sparty")
        {
            angry = make_shared<HelmetSparty>(this);
        }
        else if (name == L"dive-sparty")
        {
            angry = make_shared<DiveSparty>(this);
        }


        if (angry != nullptr)
        {

            Add(angry);
            AddToNumSpartys();
            angry->XmlItem(child);
            mAngrys.push_back(angry);
        }
    }
}





void Level::Add(shared_ptr<Item> item)
{
    mItems.push_back(item);
}

void Level::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item: mItems)
    {
        if (item != nullptr)
        {
            item->Draw(graphics);
        }
    }
};

double Level::GetWidth()
{
    return mWidth;
}

double Level::GetHeight()
{
    return mHeight;
}



void Level::Clear()
{
    mItems.clear();
}

void Level::InstallPhysics(std::shared_ptr<Physics> physics)
{
    for(auto item: mItems)
    {
        item->InstallPhysics(physics);
    }
}


/**
 * Loads the current angry to be shot
 *
 * @return The current Angry that is loaded
 */
std::shared_ptr<Angry> Level::LoadAngry()
{

    std::shared_ptr<Angry> currAngry = nullptr;
    if (!mAngrys.empty()) {
        currAngry = mAngrys[mTraverseAngry];
    }

    mAngry = currAngry;

    return currAngry;
}
void Level::Remove(Foe *foe)
{
    for (auto position = std::begin(mItems); position != std::end(mItems); position++)
    {

        if (position->get() == foe)
        {
            mItems.erase(position);
        }

    }

}
void Level::Remove(Angry *angry)
{
    for (auto position = std::begin(mItems); position != std::end(mItems); position++)
    {

        if (position->get() == angry)
        {
            mItems.erase(position--);
            break;
        }

    }

}
void Level::Accept(ItemVisitor* visitor)
{
    for (auto item: mItems) {
        if (item !=nullptr)
        {
            item->Accept(visitor);
        }

    }
}

double Level::CheckSpartys()
{
    FoeCounter visitor;
    Accept(&visitor);
    int cnt = visitor.GetNumFoes();
    if(mTraverseAngry != -1)
    {

        if (cnt == 0)
        {
            return 1; ///Go to next level
        }
        else
        {
            return 3; ///Continue level
        }
    }
    else
    {
        if (cnt == 0)
        {
            return 1; ///Go to next level
        }
        else
        {
            return 2; ///Restart level
        }
    }

}
/**
 * calls the foe vistor and the visitor should handle the killing of the foe
 * @return
 */
double Level::KillFoe()
{
    FoeVisitor visitor(mAngrySparty);
    Accept(&visitor);
    double FoeKills = visitor.FoeKills();
    return FoeKills;

}
/**
 * calls the angry vistor and the visitor should handle the killing of the angry
 */
void Level::KillAngry()
{
    SpartysVisitor visitor(mAngrySparty);
    Accept(&visitor);
}

/**
 * Removes the active Angry in the game and loads the next one
 */
void Level::RemoveActiveAngry()
{
    if (mTraverseAngry != -1)
    {
        SpartysVisitor visitor(mAngrySparty);
        Accept(&visitor);
        //mAngrys[mTraverseAngry]->Reset();
        mTraverseAngry -= 1;
        //KillAngry();
    }

    if (mTraverseAngry != -1)
    {
        LoadAngry();
    }
}

/**
 * Sets the starter point for the traversal of the angrys
 */
void Level::SetTraversal()
{
    mTraverseAngry = mAngrys.size() - 1;

    if (mAngrys.empty())
    {
        /*
        for (auto a : mAngrys)
        {
            a->Reset();
        }
         */
    }
}