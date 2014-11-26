#include <gtest/gtest.h>
#include <list>
#include "Node.h"
#include "Root.h"
#include "Composite.h"
using namespace std;

namespace MindMapTest
{
    class CompositeTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _newNode = new Node(2);
            }
            virtual void TearDown()
            {
                delete _root;
            }
            void init()
            {
            }
            Root* _root;
            Node* _node;
            Node* _newNode;
    };

    TEST_F(CompositeTest, testAddChild)
    {
        ASSERT_EQ(0, _root->getNodeList().size());
        _root->addChild(_node);
        ASSERT_EQ(1, _root->getNodeList().size());
        _root->addChild(_newNode);
        ASSERT_EQ(2, _root->getNodeList().size());
        _root->addChild(_node);
        ASSERT_EQ(2, _root->getNodeList().size());
    }

    TEST_F(CompositeTest, testClearNodeList)
    {
        _root->addChild(_node);
        _root->addChild(_newNode);
        ASSERT_EQ(2, _root->getNodeList().size());
        _root->clearNodeList();
        ASSERT_EQ(0, _root->getNodeList().size());
    }

    TEST_F(CompositeTest, testAddChilds)
    {
        list<Component*> childs;
        ASSERT_EQ(0, _root->getNodeList().size());
        childs.push_back(_node);
        childs.push_back(_newNode);
        _root->addChilds(childs);
        ASSERT_EQ(2, _root->getNodeList().size());
    }

    TEST_F(CompositeTest, testDeleteNodeByNode)
    {
        _root->addChild(_node);
        _root->addChild(_newNode);
        _root->deleteNodeByNode(_node);
        ASSERT_EQ(1, _root->getNodeList().size());
        _root->deleteNodeByNode(_newNode);
        ASSERT_EQ(0, _root->getNodeList().size());
    }

    TEST_F(CompositeTest, testDisplay)
    {
        string content;
        string correctOutput;
        stringstream outputstream(content);
        stringstream correntDisplay(correctOutput);
        Root* rootComputer = new Root(0, "Computer");
        Node* nodeNetwork = new Node(1, "Network");
        Node* nodeIPV4 = new Node(2, "IPV4");
        Node* nodeIPV6 = new Node(3, "IPV6");
        Node* nodeOS = new Node(4, "OS");
        Node* nodeMicrosoft = new Node(5, "Microsoft");
        Node* nodeWin7 = new Node(6, "Win7");
        Node* nodeWin8 = new Node(7, "Win8");
        Node* nodeOSX = new Node(8, "OSX");
        rootComputer->addChild(nodeNetwork);
        rootComputer->addChild(nodeOS);
        nodeNetwork->addChild(nodeIPV4);
        nodeNetwork->addChild(nodeIPV6);
        nodeOS->addChild(nodeMicrosoft);
        nodeOS->addChild(nodeOSX);
        nodeMicrosoft->addChild(nodeWin7);
        nodeMicrosoft->addChild(nodeWin8);
        rootComputer->display(outputstream, "", true);
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-Network(Node, ID: 1)" << endl;
        correntDisplay << "  | +-IPV4(Node, ID: 2)" << endl;
        correntDisplay << "  | +-IPV6(Node, ID: 3)" << endl;
        correntDisplay << "  +-OS(Node, ID: 4)" << endl;
        correntDisplay << "    +-Microsoft(Node, ID: 5)" << endl;
        correntDisplay << "    | +-Win7(Node, ID: 6)" << endl;
        correntDisplay << "    | +-Win8(Node, ID: 7)" << endl;
        correntDisplay << "    +-OSX(Node, ID: 8)" << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), outputstream.str().c_str());
        delete rootComputer;
    }

    TEST_F(CompositeTest, testSetGetPoint)
    {
        _root->setPoint(10, 20);
        ASSERT_EQ(10, _root->getPoint()[0]);
        ASSERT_EQ(20, _root->getPoint()[1]);
        _root->setPoint(60, 5);
        ASSERT_EQ(60, _root->getPoint()[0]);
        ASSERT_EQ(5, _root->getPoint()[1]);
    }
}