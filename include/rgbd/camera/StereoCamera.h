/**
 * @file StereoCamera.h
 * @author Yutaka Kondo <yutaka.kondo@youtalk.jp>
 * @date Jul 23, 2014
 */

#pragma once

#include <memory>
#include <opencv2/calib3d/calib3d.hpp>
#include "rgbd/camera/DepthCamera.h"

namespace rgbd {

class StereoCamera: public DepthCamera {
public:
    StereoCamera(std::shared_ptr<Camera> left, std::shared_ptr<Camera> right,
                 const std::string& intrinsics, const std::string& extrinsics);

    virtual ~StereoCamera();

    cv::Size colorSize() const;

    virtual cv::Size colorSizeL() const;

    virtual cv::Size colorSizeR() const;

    cv::Size depthSize() const;

    virtual void start();

    void captureColor(cv::Mat& buffer);

    virtual void captureColorL(cv::Mat& buffer);

    virtual void captureColorR(cv::Mat& buffer);

    virtual void captureVertex(PointXYZVector& buffer);

    virtual void captureColoredVertex(PointXYZRGBVector& buffer);

protected:
    std::shared_ptr<Camera> _lcamera, _rcamera;

    cv::Mat _lcolor, _rcolor;

    cv::StereoSGBM _sgbm;

    void setUpStereoParams();

private:
    cv::Mat _map11, _map12, _map21, _map22;

    cv::Mat _Q;

    void loadInExtrinsics(const std::string& intrinsics, const std::string& extrinsics);

    void reprojectImage(cv::Mat& xyz);
};

}
