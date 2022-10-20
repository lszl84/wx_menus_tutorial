#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);
}

void DrawingCanvas::OnPaint(wxPaintEvent &)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        for (const auto &pointsVector : squiggles)
        {
            if (pointsVector.size() > 1)
            {
                gc->SetPen(wxPen(
                    wxSystemSettings::GetAppearance().IsDark()
                        ? *wxWHITE
                        : *wxBLACK,
                    this->FromDIP(8)));
                gc->StrokeLines(pointsVector.size(), pointsVector.data());
            }
        }

        delete gc;
    }
}

void DrawingCanvas::OnMouseDown(wxMouseEvent &)
{
    squiggles.push_back({});
    isDrawing = true;
}

void DrawingCanvas::OnMouseMove(wxMouseEvent &event)
{
    if (isDrawing)
    {
        auto pt = event.GetPosition();
        auto &currentSquiggle = squiggles.back();

        currentSquiggle.push_back(pt);
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent &)
{
    isDrawing = false;
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &)
{
    isDrawing = false;
}