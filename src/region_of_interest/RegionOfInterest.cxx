#include "RegionOfInterest.hpp"

RegionOfInterest::RegionOfInterest(const std::string& windowId, cv::Mat inputFrame)
    : m_windowId(windowId)
    , m_inputFrame(inputFrame)
{
    cv::setMouseCallback(m_windowId, onMouse, this);
}


void RegionOfInterest::onMouse(int event, int x, int y, int flags, void* params)
{
        /* user press left button */
    if (event == CV_EVENT_LBUTTONDOWN && !m_isDragging)
    {
        this->m_topCornerPoint = cv::Point(x, y);
        RegionOfInterest.m_isDragging = true;
    }

    /* user drag the mouse */
    if (event == CV_EVENT_MOUSEMOVE && m_isDragging)
    {
        cv::rectangle(m_inputFrame, m_topCornerPoint, cv::Point(x,y), cv::Scalar(255,0,0));
        cv::imshow("Video Feed", m_inputFrame);
    }

    /* user release left button */
    if (event == CV_EVENT_LBUTTONUP && m_isDragging)
    {
        auto rect = cv::rectangle(m_topCornerPoint.x, m_topCornerPoint.y, x - m_topCornerPoint.x, y - m_topCornerPoint.y);
        cv::Mat imageROI = m_inputFrame(rect);

        cv::imshow("RegionOfInterest", imageROI);
        m_isDragging = false;
    }

    /* user click right button: reset all */
    if (event == CV_EVENT_RBUTTONUP)
    {
        m_isDragging = false;
    }
}