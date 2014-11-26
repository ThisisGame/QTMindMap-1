#include "PasteNodeCommand.h"

PasteNodeCommand::PasteNodeCommand(Component* component, MindMapModel* model)
{
    _component = component;
    _model = model;
    _parent = _model->getSelectComponent();
    _oldNodeList = _model->getNodeList();
}

PasteNodeCommand::~PasteNodeCommand()
{
    delete _component;
}

void PasteNodeCommand::execute()
{
    _parent->addChild(_component);
    _model->doPasteNodes(_component);
}

void PasteNodeCommand::unexcute()
{
    _parent->deleteNodeByNode(_component);
    _model->doAddNodes(_oldNodeList);
}