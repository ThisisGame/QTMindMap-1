#include <gtest/gtest.h>
#include <fstream>
#include <windows.h>
#include "GUIPresentationModel.h"
#include "MindMapModel.h"
#include "ConstVariables.h"

namespace MindMapTest
{
    class GUIPresentationModelTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                CreateDirectory(L"testData", NULL);
                _model = new MindMapModel();
                _pModel = new GUIPresentationModel(_model);
                _rootComputer = new Root(0, "Computer");
                _nodeNetwork = new Node(1, "Network");
                _nodeIPV4 = new Node(2, "IPV4");
                _nodeIPV6 = new Node(3, "IPV6");
                _nodeOS = new Node(4, "OS");
                _nodeMicrosoft = new Node(5, "Microsoft");
                _nodeWin7 = new Node(6, "Win7");
                _nodeWin8 = new Node(7, "Win8");
                _nodeOSX = new Node(8, "OSX");
                _rootComputer->addChild(_nodeNetwork);
                _rootComputer->addChild(_nodeOS);
                _nodeNetwork->addChild(_nodeIPV4);
                _nodeNetwork->addChild(_nodeIPV6);
                _nodeOS->addChild(_nodeMicrosoft);
                _nodeOS->addChild(_nodeOSX);
                _nodeMicrosoft->addChild(_nodeWin7);
                _nodeMicrosoft->addChild(_nodeWin8);
                _model->doInsertNode(_rootComputer);
                _model->doInsertNode(_nodeNetwork);
                _model->doInsertNode(_nodeIPV4);
                _model->doInsertNode(_nodeIPV6);
                _model->doInsertNode(_nodeOS);
                _model->doInsertNode(_nodeMicrosoft);
                _model->doInsertNode(_nodeWin7);
                _model->doInsertNode(_nodeWin8);
                _model->doInsertNode(_nodeOSX);
            }
            virtual void TearDown()
            {
                delete _model;
                delete _pModel;
                remove("testData\\test_file1.mm");
                RemoveDirectory(L"testData");
            }
            Root* _rootComputer;
            Node* _nodeNetwork;
            Node* _nodeIPV4;
            Node* _nodeIPV6;
            Node* _nodeOS;
            Node* _nodeMicrosoft;
            Node* _nodeWin7;
            Node* _nodeWin8;
            Node* _nodeOSX;
            MindMapModel* _model;
            GUIPresentationModel* _pModel;
    };

    TEST_F(GUIPresentationModelTest, testGetSaveMindMapActionEnable)
    {
        ASSERT_FALSE(_pModel->getSaveMindMapActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetEditNodeActionEnable)
    {
        ASSERT_FALSE(_pModel->getEditNodeActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetDeleteNodeActionEnable)
    {
        ASSERT_FALSE(_pModel->getDeleteNodeActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetInsertChildActionEnable)
    {
        ASSERT_FALSE(_pModel->getInsertChildActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetInsertSiblingActionEnable)
    {
        ASSERT_FALSE(_pModel->getInsertSiblingActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetInsertParentActionEnable)
    {
        ASSERT_FALSE(_pModel->getInsertParentActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testGetCopyActionEnbale)
    {
        ASSERT_FALSE(_pModel->getCopyActionEnbale());
    }

    TEST_F(GUIPresentationModelTest, testGetCutActionEnbale)
    {
        ASSERT_FALSE(_pModel->getCutActionEnbale());
    }

    TEST_F(GUIPresentationModelTest, testGetPasteActionEnable)
    {
        ASSERT_FALSE(_pModel->getPasteActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testSaveAndLoadMindMap)
    {
        MindMapModel model;
        GUIPresentationModel pModel(&model);
        pModel.saveMindMap("testData\\test_file1.mm");
        ASSERT_STREQ(ERROR_SAVE, pModel.getMessage().c_str());
        _pModel->saveMindMap("");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
        _pModel->saveMindMap("testData\\test_file1.mm");
        _pModel->loadMindMap("");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
        _pModel->loadMindMap("testData\\test_file1.mm");
        ASSERT_TRUE(_pModel->getSaveMindMapActionEnable());
        ASSERT_FALSE(_pModel->getPasteActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testSelectComponent)
    {
        _pModel->selectComponent(0);
        ASSERT_TRUE(_pModel->getEditNodeActionEnable());
        ASSERT_FALSE(_pModel->getDeleteNodeActionEnable());
        ASSERT_TRUE(_pModel->getInsertChildActionEnable());
        ASSERT_FALSE(_pModel->getInsertSiblingActionEnable());
        ASSERT_FALSE(_pModel->getInsertParentActionEnable());
        ASSERT_FALSE(_pModel->getPasteActionEnable());
        ASSERT_FALSE(_pModel->getCutActionEnbale());
        ASSERT_FALSE(_pModel->getCopyActionEnbale());
        _pModel->selectComponent(1);
        ASSERT_TRUE(_pModel->getEditNodeActionEnable());
        ASSERT_TRUE(_pModel->getDeleteNodeActionEnable());
        ASSERT_TRUE(_pModel->getInsertChildActionEnable());
        ASSERT_TRUE(_pModel->getInsertSiblingActionEnable());
        ASSERT_TRUE(_pModel->getInsertParentActionEnable());
        ASSERT_FALSE(_pModel->getPasteActionEnable());
        ASSERT_TRUE(_pModel->getCutActionEnbale());
        ASSERT_TRUE(_pModel->getCopyActionEnbale());
    }

    TEST_F(GUIPresentationModelTest, testDeleteComponent)
    {
        _pModel->selectComponent(1);
        _pModel->deleteComponent();
        ASSERT_FALSE(_pModel->getEditNodeActionEnable());
        ASSERT_FALSE(_pModel->getDeleteNodeActionEnable());
        ASSERT_FALSE(_pModel->getInsertChildActionEnable());
        ASSERT_FALSE(_pModel->getInsertSiblingActionEnable());
        ASSERT_FALSE(_pModel->getInsertParentActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testEditDescription)
    {
        _pModel->selectComponent(1);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
        _pModel->editDescription("Computer", false);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
        _pModel->editDescription("", true);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
        _pModel->editDescription("", false);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
        _pModel->editDescription("network", true);
        ASSERT_STREQ("network", _model->getSelectComponent()->getDescription().c_str());
    }

    TEST_F(GUIPresentationModelTest, testCreateMindMap)
    {
        MindMapModel model;
        GUIPresentationModel pModel(&model);
        pModel.createMindMap("", false);
        ASSERT_EQ(0, model.getNodeList().size());
        pModel.createMindMap("", true);
        ASSERT_EQ(0, model.getNodeList().size());
        ASSERT_EQ(0, model.getNodeList().size());
        pModel.createMindMap("test", false);
        ASSERT_EQ(0, model.getNodeList().size());
        pModel.createMindMap("MindMap", true);
        ASSERT_EQ(1, model.getNodeList().size());
    }

    TEST_F(GUIPresentationModelTest, testInsertNode)
    {
        _pModel->selectComponent(1);
        ASSERT_EQ(9, _model->getNodeList().size());
        _pModel->insertNode('b', "Computer", false);
        ASSERT_EQ(9, _model->getNodeList().size());
        _pModel->insertNode('c', "", true);
        ASSERT_EQ(9, _model->getNodeList().size());
        _pModel->insertNode('b', "", false);
        ASSERT_EQ(9, _model->getNodeList().size());
        _pModel->insertNode('b', "IP", true);
        ASSERT_EQ(10, _model->getNodeList().size());
    }

    TEST_F(GUIPresentationModelTest, testdisableSelected)
    {
        _pModel->disableSelected();
        ASSERT_FALSE(_pModel->getEditNodeActionEnable());
        ASSERT_FALSE(_pModel->getDeleteNodeActionEnable());
        ASSERT_FALSE(_pModel->getInsertChildActionEnable());
        ASSERT_FALSE(_pModel->getInsertSiblingActionEnable());
        ASSERT_FALSE(_pModel->getInsertParentActionEnable());
        ASSERT_FALSE(_pModel->getCutActionEnbale());
        ASSERT_FALSE(_pModel->getCopyActionEnbale());
    }

    TEST_F(GUIPresentationModelTest, testCopyComponent)
    {
        _pModel->selectComponent(1);
        _pModel->copyComponent();
        ASSERT_TRUE(_pModel->getPasteActionEnable());
    }

    TEST_F(GUIPresentationModelTest, testCutComponent)
    {
        _pModel->selectComponent(2);
        _pModel->cutComponent();
        ASSERT_TRUE(_pModel->getPasteActionEnable());;
    }

    TEST_F(GUIPresentationModelTest, testPasteComponent)
    {
        _pModel->selectComponent(3);
        _pModel->copyComponent();
        _pModel->pasteComponent();
        ASSERT_TRUE(_pModel->getPasteActionEnable());
    }
}