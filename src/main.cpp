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

    void OnSomeAction(wxCommandEvent &);
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

void MyFrame::OnSomeAction(wxCommandEvent &)
{
    wxMessageBox("Some Action!");
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

    this->Bind(wxEVT_MENU, &MyFrame::OnSomeAction, this,
               customMenu->Append(wxID_ANY, "Some &Action...\tCtrl-Alt-A")->GetId());

    customMenu->AppendSeparator();
    customMenu->AppendCheckItem(wxID_ANY, "Check Item &One\tCtrl-1");
    customMenu->AppendCheckItem(wxID_ANY, "Check Item &Two\tCtrl-2");
    customMenu->AppendSeparator();

    wxMenu *customMenuOptionsSubmenu = new wxMenu();

    customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option One");
    customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Two");
    customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Three");

    customMenu->AppendSubMenu(customMenuOptionsSubmenu, "&Options");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(customMenu, "&Custom");

    SetMenuBar(menuBar);
}
