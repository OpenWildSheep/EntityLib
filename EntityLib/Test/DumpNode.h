#pragma once

#include <EntityLib/EntVisitor.h>

namespace Ent
{

    class DumpNode : public NodeVisitor
    {
        Cursor& expl;
        nlohmann::json result;
        std::stack<nlohmann::json*, std::vector<nlohmann::json*>> jsonNode{};

        nlohmann::json& _getNode()
        {
            return *jsonNode.top();
        }

    public:
        using json = nlohmann::json;

        json const& getResult() const
        {
            return result;
        }

        DumpNode(Cursor& _expl)
            : expl(_expl)
            , jsonNode({&result})
        {
        }

        void inObject() override
        {
            _getNode() = json::object();
        }
        void inObjectField(char const* key, Cursor const&) override
        {
            jsonNode.push(&(_getNode()[key]));
        }
        void outObjectField() override
        {
            jsonNode.pop();
        }
        void outObject() override
        {
            // jsonNode.pop();
        }
        void inUnion(char const* type) override
        {
            auto unionNameField = expl.getSchema()->getUnionNameField();
            _getNode()[unionNameField] = type;
        }
        void outUnion() override
        {
            // jsonNode.pop();
        }
        void inMap() override
        {
        }
        void outMap() override
        {
        }
        void inMapElement(char const* key) override
        {
            _getNode().push_back(json::array());
            jsonNode.push(&_getNode());
            _getNode().push_back(key);
            jsonNode.push(&_getNode().emplace_back());
        }
        void inMapElement(int64_t key) override
        {
            _getNode().push_back(json::array());
            jsonNode.push(&_getNode());
            _getNode().push_back(key);
            jsonNode.push(&_getNode().emplace_back());
        }
        void outMapElement() override
        {
            jsonNode.pop(); // return to pair
            jsonNode.pop(); // return to map
        }
        void inPrimSet(Ent::DataType) override
        {
            _getNode() = json::array();
        }
        virtual void inArrayElement(size_t)
        {
            jsonNode.push(&_getNode().emplace_back());
        }
        virtual void outArrayElement()
        {
            jsonNode.pop(); // return to array
        }
        virtual void key(char const* _key)
        {
            _getNode() = _key;
        }
        virtual void key(int64_t _key)
        {
            _getNode() = _key;
        }
        void outPrimSet() override
        {
        }
        void inUnionSet() override
        {
            _getNode() = json::array();
        }
        void inUnionSetElement([[maybe_unused]] char const* key) override
        {
            jsonNode.push(&_getNode().emplace_back());
        }
        void outUnionSetElement() override
        {
            jsonNode.pop();
        }
        void outUnionSet() override
        {
        }
        void inObjectSet() override
        {
            _getNode() = json::array();
        }
        void outObjectSet() override
        {
        }
        void inObjectSetElement([[maybe_unused]] char const* key) override
        {
            jsonNode.push(&_getNode().emplace_back());
        }
        void inObjectSetElement([[maybe_unused]] int64_t key) override
        {
            jsonNode.push(&_getNode().emplace_back());
        }
        void outObjectSetElement() override
        {
            jsonNode.pop();
        }
        void inArray() override
        {
            _getNode() = json::array();
        }
        void outArray() override
        {
        }
        void nullNode() override
        {
            _getNode() = json();
        }
        void boolNode() override
        {
            _getNode() = expl.getBool();
        }
        void intNode() override
        {
            _getNode() = expl.getInt();
        }
        void floatNode() override
        {
            _getNode() = expl.getFloat();
        }
        void stringNode() override
        {
            _getNode() = expl.getString();
        }
        void entityRefNode() override
        {
            _getNode() = expl.getEntityRef().entityPath;
        }
    };
} // namespace Ent
