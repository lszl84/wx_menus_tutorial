#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void SetupMainMenu();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxDefaultSize);
    frame->Show(true);
    return true;
}
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    SetupMainMenu();

    this->SetMinSize(this->FromDIP(wxSize(200, 200)));
    this->SetSize(this->FromDIP(wxSize(800, 600)));
}

namespace MenuIds
{
    const int SomeAction = 100;
}

void MyFrame::SetupMainMenu()
{
    wxMenuBar *menuBar = new wxMenuBar();

    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);

    wxMenu *editMenu = new wxMenu();

    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_PASTE);

    wxMenu *customMenu = new wxMenu();

    customMenu->Append(MenuIds::SomeAction, "Some Action...\tRawCtrl-Alt-A");

    menuBar->Append(fileMenu, "File");
    menuBar->Append(editMenu, "Edit");
    menuBar->Append(customMenu, "Custom");

    SetMenuBar(menuBar);
}
