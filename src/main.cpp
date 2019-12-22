#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include<findballon.h>

using namespace cv;
using namespace std;

 int main(int argc, char const *argv[])
 {
    Mat src,dst2,dst;
    Findballon find;
    VideoCapture cap; 
	cap.open("4.mp4");
      if (!cap.isOpened())   
    {  
       cout << "Cannot open the camera" << endl;  
       return -1;  
    } 
	  while (1)  
    {   
        cap>>src;
       if (src.empty()){  
          cout << "Cannot read a frame from video stream" << endl;  
          break;  } 

    dst = find.Denoising(src);
    dst2 = src.clone();
    find.getPoint(dst,src);
    cv::Point2f P=find.getPoint(dst,src);
    cout<<P.x<<endl;
    bool haveballon =  find.scale_test(dst2);
    cout<<"+++++++++"<<haveballon<<endl;
    waitKey(1);
    }
    return 0;
}
