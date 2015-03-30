#include "model.h"

Model::Model(const S32 numberOfStates)
    : state{numberOfStates}
{

}

const State& Model::GetState() const
{
    return state;
}
