#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"

const std::string windowName = "ObjectTracker v0.1";

//Is the user selecting a region
bool isSelectingRegion = false;

//Is the application still running?
bool programIsRunning = true;

//Should we be tracking an object?
//TODO
int trackObject = 0;

//Region representation
cv::Rect regionOfInterest;

//Location of where the mouse was clicked
cv::Point mouseClickOrigin;

//Container to hold the image
cv::Mat frame;



//Mouse callback function
static void onMouse(int event, int x, int y, int flags, void* userdata);

//Key handler
void handleWaitKey(char key);


int main(int argc, char** argv)
{
    cv::Mat frame = cv::imread(argv[1]);

    cv::namedWindow(windowName, CV_WINDOW_NORMAL);
    while(programIsRunning)
    {
        cv::imshow(windowName, frame);
        handleWaitKey(static_cast<char>(cv::waitKey(0)));
    }
    return 0;
}

static void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if(isSelectingRegion)
    {
        regionOfInterest.x = MIN(x, mouseClickOrigin.x);
        regionOfInterest.y = MIN(y, mouseClickOrigin.y);
        regionOfInterest.width = std::abs(x - mouseClickOrigin.x);
        regionOfInterest.height = std::abs(y - mouseClickOrigin.y);

        regionOfInterest &= cv::Rect(0, 0, frame.cols, frame.rows);

    }
    switch(event)
    {
        case(cv::EVENT_LBUTTONDOWN):
        {
            mouseClickOrigin = cv::Point(x, y);
            regionOfInterest = cv::Rect(x, y, 0, 0);
            isSelectingRegion = true;
            break;
        }
        case(cv::EVENT_LBUTTONUP):
        {
            isSelectingRegion = false;
            if(regionOfInterest.width > 0 && regionOfInterest.height > 0)
            {
                trackObject = -1;
            }
            break;
        }
    }
}

void handleWaitKey(char key)
{
    switch(key)
    {
        case(27):
        {
            programIsRunning = false;
            break;
        }
        case('q'):
        {
            programIsRunning = false;
            break;
        }
        case('Q'):
        {
            programIsRunning = false;
            break;
        }
        default:
        {
            
            break;
        }
    }
}