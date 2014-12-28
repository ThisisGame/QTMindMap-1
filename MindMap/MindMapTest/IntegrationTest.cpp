#include <gtest/gtest.h>
#include <fstream>
#include "MindMapModel.h"
#include <windows.h>
#include "TextUIPresentationModel.h"
#include "ConstVariables.h"

namespace MindMapTest
{
    class IntegrationTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                fstream outFile;
                CreateDirectory(L"testData", NULL);
                outFile.open("testData\\test_file1.mm", ios::out);
                string data = "0 \"Computer\"  \"Root\" 2 7 \n1 \"windows\"  \"Node\" 5 6 \n2 \"OS\"  \"Node\" 1 3 4 \n3 \"IOS\"  \"Node\" \n4 \"Linux\"  \"Node\" \n5 \"DirectX\"  \"Node\" \n6 \"Microsoft Office\"  \"Node\" \n7 \"Network\"  \"Node\" 8 9 \n8 \"Wireless\"  \"Node\" \n9 \"Cable\"  \"Node\" \n";
                outFile << data;
                outFile.close();
                _model = new MindMapModel();
                _pModel = new TextUIPresentationModel(_model);
            }
            virtual void TearDown()
            {
                remove("testData\\test_file1.mm");
                RemoveDirectory(L"testData");
                delete _model;
                delete _pModel;
            }
            MindMapModel* _model;
            TextUIPresentationModel* _pModel;
    };

    TEST_F(IntegrationTest, testLoadFileNotExist)
    {
        /*
        1. Load the ¡§file_not_exist.erd¡¨ under the ¡§testData¡¨  directory
        2. Assert file not found error
        */
        _pModel->loadMindMap("testData\\file_not_exist.erd");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
    }

    TEST_F(IntegrationTest, testUndoDeleteNode)
    {
        /*
        1. Load the ¡§test_file1.mm¡¨ under the ¡§testData¡¨ directory
        2. Assert the diagram is loaded correctly
        3. Add an Node with text ¡§Test¡¨ under ¡§Linux¡¨
        4. Assert the Node is added correctly
        5. Delete the Node added above
        6. Assert the Node has been deleted
        7. Undo
        8. Assert there is an Node with text ¡§Test¡¨
        */
        _pModel->loadMindMap("testData\\test_file1.mm");
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _pModel->getMessage().c_str());
        _model->selectComponent(4);
        _model->insertNode('b');
        _model->setDescription("Test");
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  |   +-Test(Node, ID: 10)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->selectComponent(10);
        _model->deleteComponent();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->undo();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  |   +-Test(Node, ID: 10)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
    }

    TEST_F(IntegrationTest, testRedoDeleteNode)
    {
        /*
        1. Load the ¡§test_file1.mm¡¨ under the ¡§testData¡¨ directory
        2. Assert the diagram is loaded correctly
        3. Add an Node with text ¡§Test¡¨ under ¡§Cable¡¨
        4. Assert the Node is added correctly
        5. Delete the Node added above
        6. Assert the Node has been deleted
        7. Undo
        8. Assert there is an Node with text ¡§Test¡¨
        9. Redo
        10. Assert Node with text ¡§Test¡¨ is deleted
        */
        _pModel->loadMindMap("testData\\test_file1.mm");
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _pModel->getMessage().c_str());
        _model->selectComponent(9);
        _model->insertNode('b');
        _model->setDescription("Test");
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl ;
        correntDisplay << "      +-Test(Node, ID: 10)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->selectComponent(10);
        _model->deleteComponent();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->undo();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl;
        correntDisplay << "      +-Test(Node, ID: 10)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->redo();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
    }

    TEST_F(IntegrationTest, testChangeNodeParent)
    {
        /*
        1. Load the ¡§test_file1.mm¡¨ under the ¡§testdata¡¨ directory
        2. Assert the diagram is loaded correctly
        3. Change ¡§Windows¡¨ parent form¡¨OS¡¨ to ¡§Microsoft Office¡¨
        4. Assert ¡§Windows¡¨ parent is ¡§Microsoft Office¡¨
        5. Assert ¡§Microsoft Office¡¨ parent is ¡§OS¡¨
        6. Undo
        7. Assert ¡§Windows¡¨ parent is ¡§OS¡¨
        8. Assert ¡§Microsoft Office¡¨ parent is ¡§Windows¡¨
        9. Redo
        10. Assert ¡§Windows¡¨ parent is ¡§Microsoft Office¡¨
        11. Assert ¡§Microsoft Office¡¨ parent is ¡§OS¡¨
        */
        _pModel->loadMindMap("testData\\test_file1.mm");
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _pModel->getMessage().c_str());
        _model->selectComponent(1);
        _model->changeParent(6);
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  |   +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->undo();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  | | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
        _model->redo();
        _model->display();
        correntDisplay.str("");
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-OS(Node, ID: 2)" << endl;
        correntDisplay << "  | +-IOS(Node, ID: 3)" << endl;
        correntDisplay << "  | +-Linux(Node, ID: 4)" << endl;
        correntDisplay << "  | +-DirectX(Node, ID: 5)" << endl;
        correntDisplay << "  | +-Microsoft Office(Node, ID: 6)" << endl;
        correntDisplay << "  |   +-windows(Node, ID: 1)" << endl;
        correntDisplay << "  +-Network(Node, ID: 7)" << endl;
        correntDisplay << "    +-Wireless(Node, ID: 8)" << endl;
        correntDisplay << "    +-Cable(Node, ID: 9)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
    }
}