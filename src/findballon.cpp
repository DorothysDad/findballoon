#include"findballon.h"
#include "line2Dup.h"
using namespace cv;
cv::Mat Findballon::Denoising(cv::Mat &img){
    
   GaussianBlur(img,img,Size(3,3),3,3);    
   cvtColor(img,hsv,CV_BGR2HSV);
//    imshow("1",hsv);
   inRange(hsv,Scalar(H_L,S_L,V_L),Scalar(H_H,S_H,V_H), dst);
   medianBlur(dst,dst,3);
   imshow("2",dst);
   return dst;
}
cv::Point2f Findballon::getPoint(cv::Mat &img,cv::Mat &src){
   findContours(dst,contours,hierarchy, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE);

    int indexOfBalloon = 0;
  	
   if(contours.size()!=0)
    {   cout<<"There are contours!"<<endl;
        for(;indexOfBalloon>=0;indexOfBalloon=hierarchy[indexOfBalloon][0])
		{   
            double area = contourArea(contours[indexOfBalloon]);
            if(area > 100)
            {
              
                drawContours(dst,contours,indexOfBalloon,Scalar(0),2);
                contours_Rect=minAreaRect(Mat(contours[indexOfBalloon]));
                contours_Rect.points(vertex);
                for(int i=0;i<4;i++){
                    line(src,vertex[i],vertex[(i+1)%4],Scalar(180,60,255),2);
                }
                P1.x = contours_Rect.center.x;
                P1.y = contours_Rect.center.y;
            }
		} 
        // cout<<"中心坐标："<<P1<<endl;
    }
    else {
    //    cout<<"No contours"<<endl;
       P1.x=320.0;
       P1.y=240.0;
    }

//    cout<<"图像大小："<<src.size<<endl;
   imshow("1",src);
  
   return P1;

}
bool Findballon::GetBoxType(cv::Scalar Color){
	int B= std::abs(Color.val[0]);
	int G=std::abs(Color.val[1]);
	int R=std::abs(Color.val[2]);
	if(B>240&&G>240&&R>240)
    return true;
	else 
    return false;
}
cv::Scalar Findballon::GetColor(cv::Mat imgROI,int size){
	cv::Scalar color(0,0,0);
	int r=std::min(imgROI.cols,imgROI.rows);
	srand(time(NULL));
	for(int i=0;i<size;i++){
		int m=rand()%r-(r/2);
		for(int i=0;i<3;i++)
			color.val[i]+=imgROI.at<cv::Vec3b>(imgROI.cols/2+m,imgROI.rows/2+m)[i];
	}
	for(int i=0;i<3;i++)
		color.val[i]/=size;
	return color;
}
bool Findballon::scale_test(cv::Mat &img){
    static bool  flag = false;
    static int num_feature =  60;
    static  std::vector<std::string> ids;
    static line2Dup::Detector detector(num_feature, {4, 8});
    if(!flag){
        ids.push_back("circle1");
        ids.push_back("circle");
        detector.readClasses(ids, "%s_templ.yaml");
        flag = true;
    }
    int stride = 32;
    int n = img.rows/stride;
    int m = img.cols/stride;
    Rect roi(0, 0, stride*m , stride*n);
    cv::Mat matchimg = img(roi).clone();
    auto matches = detector.match(matchimg, 80,ids);
    std::cout << "matches.size(): " << matches.size() << std::endl;
    size_t top5 = 5;
    bool aa;
    if(top5>matches.size()) top5=matches.size();
    for(size_t i=0; i<top5; i++){
        auto match = matches[i];
        auto templ1 = detector.getTemplates("circle",
                                            match.template_id);
        auto templ2 = detector.getTemplates("circle1",
                                            match.template_id);
        int x = -1,y = -1,r = -1;
        if(templ2.size()){
            x =  templ1[0].width/2 + match.x;
            y = templ1[0].height/2 + match.y;
            r = templ1[0].width/2;     
        }else if(templ1.size()){
            x =  templ2[0].width/2 + match.x;
            y = templ2[0].height/2 + match.y;
            r = templ2[0].width/2; 
        }
        // cout<<"x is "<<x<<"y is "<<y<<"R is "<<r<<endl;
        
        Scalar color(255, rand()%255, rand()%255);

        cv::putText(img, to_string(int(round(match.similarity))),
                    Point(match.x+r-10, match.y-3), FONT_HERSHEY_PLAIN, 2, color);
        cv::circle(img, {x, y}, r, color, 2);
        cv::Scalar white=GetColor(img(cv::Rect(x-r/4,y-r/4,
			r/2,r/2)));
        aa=GetBoxType(white);
        // cout<<"+++++"<<aa<<endl;
    }
    cv::imshow("3",img);
    return matches.size()>0&&aa;
}

