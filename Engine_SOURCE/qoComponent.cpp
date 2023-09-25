#include "qoComponent.h"


namespace qo
{
    Component::Component(COMPONENTTYPE type)
        : mType(type)
        , mOwner(nullptr)
    {
    }

    Component::~Component()
    {
    }
}
