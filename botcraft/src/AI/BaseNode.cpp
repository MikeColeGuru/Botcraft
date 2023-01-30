#include "botcraft/AI/BaseNode.hpp"

namespace Botcraft
{
    BaseNode::BaseNode(const std::string& name_) : name(name_)
    {

    }

    BaseNode::~BaseNode()
    {

    }

    std::string BaseNode::GetFullDescriptor() const
    {
        return this->name.empty() ? GetClassName() : ("\"" + this->name + "\" (" + GetClassName() + ")");
    }

    const std::string& BaseNode::GetName() const
    {
        return name;
    }

    std::string BaseNode::GetClassName() const
    {
        return typeid(*this).name();
    }
} // namespace Botcraft
