project(Project1Lib)

set(wxBUILD_PRECOMP OFF )
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

Set(SOURCE_FILES MainFrame.h MainFrame.cpp ids.h Block.cpp Block.h Item.h Item.cpp pch.h AngrySpartyView.cpp AngrySpartyView.h AngrySparty.cpp AngrySparty.h Scoreboard.cpp Scoreboard.h Slingshot.cpp Slingshot.h Poly.cpp Poly.h Consts.h Foe.cpp Foe.h Level.cpp Level.h Images.cpp Images.h Goalpost.cpp Goalpost.h Physics.cpp Physics.h Background.cpp Background.h Angry.cpp Angry.h GruffSparty.cpp GruffSparty.h HelmetSparty.cpp HelmetSparty.h DebugDraw.cpp DebugDraw.h ItemShape.cpp ItemShape.h ItemVisitor.h FoeVisitor.cpp FoeVisitor.h FoeCounter.cpp FoeCounter.h DiveSparty.cpp DiveSparty.h SpartysVisitor.cpp SpartysVisitor.h)


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} box2d)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories(${box2d_SOURCE_DIR}/include/box2d)


