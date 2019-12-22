#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
class Findballon{
    public:
	cv::Mat hsv,dst;
    void Denoising(cv::Mat &img);
    /**
     * 
     * 
	 * @param:  
	 * @return:　
     *
     */
	cv::Point2d getPoint(cv::Mat &img);
	/**
	 * 
	 * @param:  
	 * @return:　
	 * 
	 */
	// float measure_distance(cv::Mat &color,cv::Mat depth,cv::Size range,cv::Point2d &Point,rs2::pipeline_profile profile);
	// /**
	//  * 
	//  * @param:  
	//  * @return:
	//  * 
	//  */
    private:

};