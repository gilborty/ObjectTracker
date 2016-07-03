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
bool trackObject = false;

//Region representation
cv::Rect regionOfInterest;

//Location of where the mouse was clicked
cv::Point mouseClickOrigin;

//Container to hold the image
cv::Mat image;



//Mouse callback function
static void onMouse(int event, int x, int y, int flags, void* userdata);

//Key handler
void handleWaitKey(char key);


int main(int argc, char** argv)
{
    cv::VideoCapture cap(0);

    if(argc > 1)
    {
        cv::VideoCapture pathCap(argv[1]);
        cap = pathCap;
    }
    cv::Mat frame;

    if(!cap.isOpened())
    {
        throw std::runtime_error("Could not open capture device");
    }

    cv::namedWindow(windowName, CV_WINDOW_NORMAL);

    //Register our on mouse even
    cv::setMouseCallback(windowName, onMouse, nullptr);
    while(programIsRunning)
    {
        //Get a frame 
        cap >> frame;
        if(frame.empty())
        {
            std::cout << "ERROR: Could not read frame" << std::endl;
            break;
        }
        frame.copyTo(image);
        
        if(trackObject)
        {

        }




        if( isSelectingRegion && regionOfInterest.width > 0 && regionOfInterest.height > 0 )
        {
            cv::Mat roi(image, regionOfInterest);
            bitwise_not(roi, roi);
        }

        cv::imshow(windowName, image);
        handleWaitKey(static_cast<char>(cv::waitKey(10)));
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

        regionOfInterest &= cv::Rect(0, 0, image.cols, image.rows);

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
                trackObject = true;
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
        case('r'):
        {
            trackObject = false;
            break;
        }
        default:
        {
            
            break;
        }
    }
}