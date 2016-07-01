#pragma once

#include "opencv2/highgui/highgui.hpp"

class RegionOfInterest
{
    public:

        RegionOfInterest(const std::string& windowId, cv::Mat inputFrame);

        static void onMouse(int event, int x, int y, int flags, void* params);

        void loadFrame(cv::Mat inputImage)
        {
            m_inputFrame = inputImage;
        }

    private:

        std::string m_windowId;
        bool m_isDragging;
        cv::Point m_topCornerPoint;
        cv::Mat m_inputFrame;
};