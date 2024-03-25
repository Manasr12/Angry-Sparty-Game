/**
 * @file FoeCounter.cpp
 * @author Trey Cosnowski
 */

#include "pch.h"
#include "FoeCounter.h"
#include "Foe.h"


/**
* Visit the Foe object
 * @param foe Foe we are visiting
*/

void FoeCounter::VisitFoe(Foe *foe)
{
    if(foe->GetState())
    {
        mNumFoes++;
    }

}