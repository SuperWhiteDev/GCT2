#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

namespace Graphics {
    typedef uint64_t ID;

    enum ImDrawFlags
    {
        ImDrawFlags_None = 0,
        ImDrawFlags_Closed = 1 << 0, // PathStroke(), AddPolyline(): specify that shape should be closed (Important: this is always == 1 for legacy reason)
        ImDrawFlags_RoundCornersTopLeft = 1 << 4, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-left corner only (when rounding > 0.0f, we default to all corners). Was 0x01.
        ImDrawFlags_RoundCornersTopRight = 1 << 5, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-right corner only (when rounding > 0.0f, we default to all corners). Was 0x02.
        ImDrawFlags_RoundCornersBottomLeft = 1 << 6, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-left corner only (when rounding > 0.0f, we default to all corners). Was 0x04.
        ImDrawFlags_RoundCornersBottomRight = 1 << 7, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-right corner only (when rounding > 0.0f, we default to all corners). Wax 0x08.
        ImDrawFlags_RoundCornersNone = 1 << 8, // AddRect(), AddRectFilled(), PathRect(): disable rounding on all corners (when rounding > 0.0f). This is NOT zero, NOT an implicit flag!
        ImDrawFlags_RoundCornersTop = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
        ImDrawFlags_RoundCornersBottom = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
        ImDrawFlags_RoundCornersLeft = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft,
        ImDrawFlags_RoundCornersRight = ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight,
        ImDrawFlags_RoundCornersAll = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
        ImDrawFlags_RoundCornersDefault_ = ImDrawFlags_RoundCornersAll, // Default to ALL corners if none of the _RoundCornersXX flags are specified.
        ImDrawFlags_RoundCornersMask_ = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone
    };
    
    typedef bool(__cdecl* _IsGraphicsLibraryLoaded)();
    typedef void(__cdecl* _GetAvailableFonts)();
    typedef void(__cdecl* _AddFont)(const char* fontFile, const char* fontName, int64_t sizePixels);
    typedef ID(__cdecl* _DrawLine)(int64_t x1, int64_t y1, int64_t x2, int64_t y2, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t thickness);
    typedef ID(__cdecl* _DrawRect)(int64_t x, int64_t y, int64_t width, int64_t height, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t rounding, ImDrawFlags flags);
    typedef ID(__cdecl* _DrawGradientRect)(int64_t x, int64_t y, int64_t width, int64_t height, BYTE LeftBottomColorR, BYTE LeftBottomColorG, BYTE LeftBottomColorB, BYTE LeftBottomAlpha, BYTE LeftTopColorR, BYTE LeftTopColorG, BYTE LeftTopColorB, BYTE LeftTopAlpha, BYTE RightTopColorR, BYTE RightTopColorG, BYTE RightTopColorB, BYTE RightTopAlpha, BYTE RightBottomColorR, BYTE RightBottomColorG, BYTE RightBottomColorB, BYTE RightBottomAlpha);
    typedef ID(__cdecl* _DrawTriangle)(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3, BYTE r, BYTE g, BYTE b, BYTE alpha);
    typedef ID(__cdecl* _DrawEllipse)(int64_t x, int64_t y, int64_t radiusX, int64_t radiusY, BYTE r, BYTE g, BYTE b, BYTE alpha, int numSegments);
    typedef ID(__cdecl* _DisplayText)(const char* text, int64_t x, int64_t y, const char* font, int64_t fontSize, BYTE r, BYTE g, BYTE b, BYTE alpha);
    typedef ID(__cdecl* _DrawWatermark)(const char* text, int64_t x, int64_t y, int64_t width, int64_t height, BYTE startColorR, BYTE startColorG, BYTE startColorB, BYTE endColorR, BYTE endColorG, BYTE endColorB, BYTE alpha, const char* font, int64_t fontSize);
    typedef ID(__cdecl* _DrawImage)(const char* file, int64_t x, int64_t y, int64_t width, int64_t height);
    typedef void(__cdecl* _ShowNotification)(const char* text, time_t duration);
    typedef void(__cdecl* _SetGlobalFontSize)(int64_t fontSize);
    typedef void(__cdecl* _SetGlobalFontSizeStr)(const char* fontSize);
    typedef void(__cdecl* _SetElementPosition)(ID id, const int64_t* coords);
    typedef void(__cdecl* _SetElementSize)(ID id, int64_t width, int64_t height);
    typedef void(__cdecl* _SetElementColor)(ID id, BYTE r, BYTE g, BYTE b, BYTE alpha);
    typedef void(__cdecl* _SetElementText)(ID id, const char* text);
    typedef void(__cdecl* _SetElementFont)(ID id, const char* font, int64_t fontSize);
    typedef void(__cdecl* _SetElementExtra)(ID id, const int64_t* extras);
    typedef void(__cdecl* _DeleteElement)(ID id);
    typedef void(__cdecl* _ClearRenderList)();
    typedef int64_t*(__cdecl* _GetDisplaySize)();

    bool InitGraphics();
    bool IsGraphicsLibraryLoaded();
    void GetAvailableFonts();
    void AddFont(const char* fontFile, const char* fontName, int64_t sizePixels);
    ID DrawLine(int64_t x1, int64_t y1, int64_t x2, int64_t y2, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t thickness);
    ID DrawRect(int64_t x, int64_t y, int64_t width, int64_t height, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t rounding, ImDrawFlags flags);
    ID DrawGradientRect(int64_t x, int64_t y, int64_t width, int64_t height, BYTE LeftBottomColorR, BYTE LeftBottomColorG, BYTE LeftBottomColorB, BYTE LeftBottomAlpha, BYTE LeftTopColorR, BYTE LeftTopColorG, BYTE LeftTopColorB, BYTE LeftTopAlpha, BYTE RightTopColorR, BYTE RightTopColorG, BYTE RightTopColorB, BYTE RightTopAlpha, BYTE RightBottomColorR, BYTE RightBottomColorG, BYTE RightBottomColorB, BYTE RightBottomAlpha);
    ID DrawTriangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3, BYTE r, BYTE g, BYTE b, BYTE alpha);
    ID DrawEllipse(int64_t x, int64_t y, int64_t radiusX, int64_t radiusY, BYTE r, BYTE g, BYTE b, BYTE alpha, int numSegments);
    ID DisplayText(const char* text, int64_t x, int64_t y, const char* font, int64_t fontSize, BYTE r, BYTE g, BYTE b, BYTE alpha);
    ID DrawWatermark(const char* text, int64_t x, int64_t y, int64_t width, int64_t height, BYTE startColorR, BYTE startColorG, BYTE startColorB, BYTE endColorR, BYTE endColorG, BYTE endColorB, BYTE alpha, const char* font, int64_t fontSize);
    ID DrawImage(const char* file, int64_t x, int64_t y, int64_t width, int64_t height);
    void ShowNotification(const char* text, time_t duration);
    void SetGlobalFontSize(int64_t fontSize);
    void SetGlobalFontSizeStr(const char* fontSize);
    void SetElementPosition(ID id, const int64_t* coords);
    void SetElementSize(ID id, int64_t width, int64_t height);
    void SetElementColor(ID id, BYTE r, BYTE g, BYTE b, BYTE alpha);
    void SetElementText(ID id, const char* text);
    void SetElementFont(ID id, const char* font, int64_t fontSize);
    void SetElementExtra(ID id, const int64_t* extras);
    void DeleteElement(ID id);
    void ClearRenderList();
    int64_t* GetDisplaySize();

    bool IsGraphicsLibAvailable();

    class Line {
        Graphics::ID ElementID;
    public:
        Line(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha, int thickness);
        void SetPosition(int x1, int y1, int x2, int y2);
        void SetColor(int red, int green, int blue, int alpha);
        void SetThickness(int thickness);
    };

    class Rect {
        Graphics::ID ElementID;
    public:
        Rect(int x, int y, int width, int height, int red, int green, int blue, int alpha, int rounding);
        void SetPosition(int x1, int y1, int x2, int y2);
        void SetSize(int width, int height);
        void SetColor(int red, int green, int blue, int alpha);
        void SetRounding(int rounding);
        void SetFlags(int flags);
    };

    class GradientRect {
        Graphics::ID ElementID;
    public:
        GradientRect(int x, int y, int width, int height,
            int left_bottom_red, int left_bottom_green, int left_bottom_blue, int left_bottom_alpha,
            int left_top_red, int left_top_green, int left_top_blue, int left_top_alpha,
            int right_top_red, int right_top_green, int right_top_blue, int right_top_alpha,
            int right_bottom_red, int right_bottom_green, int right_bottom_blue, int right_bottom_alpha);
        void SetPosition(int x1, int y1);
        void SetSize(int width, int height);
        void SetColor(int left_bottom_red, int left_bottom_green, int left_bottom_blue, int left_bottom_alpha,
            int left_top_red, int left_top_green, int left_top_blue, int left_top_alpha,
            int right_top_red, int right_top_green, int right_top_blue, int right_top_alpha,
            int right_bottom_red, int right_bottom_green, int right_bottom_blue, int right_bottom_alpha);
    };

    class Triangle {
        Graphics::ID ElementID;
    public:
        Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue, int alpha);
        void SetPosition(int x1, int y1, int x2, int y2, int x3, int y3);
        void SetColor(int red, int green, int blue, int alpha);
    };

    class Ellipse {
        Graphics::ID ElementID;
    public:
        Ellipse(int x, int y, int radius_x, int radius_y, int red, int green, int blue, int alpha);
        void SetPosition(int x, int y);
        void SetRadius(int radius_x, int radius_y);
        void SetColor(int red, int green, int blue, int alpha);
        void SetSegmentsCount(int segments);
    };

    class Text {
        Graphics::ID ElementID;
    public:
        Text(const std::string& text, int x, int y, int r, int g, int b, int alpha, const std::string& font, int font_size);
        void SetPosition(int x, int y);
        void SetLabel(const std::string& text);
        void SetFont(const std::string& font, int font_size);
        void SetColor(int red, int green, int blue, int alpha);
    };

    class Watermark {
        Graphics::ID ElementID;
    public:
        Watermark(const std::string& text, int x, int y, int width, int height, int start_r, int start_g, int start_b, int end_r, int end_g, int end_b, int alpha, const std::string& font, int font_size);
        void SetPosition(int x, int y);
        void SetSize(int width, int height);
        void SetLabel(const std::string& text);
        void SetFont(const std::string& font, int font_size);
        void SetStartColor(int red, int green, int blue, int alpha);
        void SetEndColor(int red, int green, int blue, int alpha);
    };

    class Image {
        Graphics::ID ElementID;
    public:
        Image(const std::string& image_file, int x, int y, int width, int height);
        void SetPosition(int x, int y);
        void SetSize(int width, int height);
        void Hide();
        void Show();
    };

    class Notification {
    public:
        Notification(const std::string& message);
    };
}