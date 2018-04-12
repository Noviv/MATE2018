#ifndef XCVSERIALIZE_H
#define XCVSERIALIZE_H

#include <cassert>
#include <string>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <opencv2/opencv.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(cv::Mat)

namespace boost {
    namespace serialization {
        template <class A>
        void save(A& ar, const cv::Mat& m, const unsigned int version) {
            size_t elemSize = m.elemSize();
            size_t elemType = m.type();

            ar& m.cols;
            ar& m.rows;
            ar& elemSize;
            ar& elemType;

            const size_t dataSize = m.cols * m.rows * m.elemSize();
            for (size_t i = 0; i < dataSize; ++i) {
                ar& m.data[i];
            }
        }

        template <class A>
        void load(A& ar, cv::Mat& m, const unsigned int version) {
            int cols, rows;
            size_t elemSize, elemType;

            ar& cols;
            ar& rows;
            ar& elemSize;
            ar& elemType;

            m.create(rows, cols, static_cast<int>(elemType));
            const size_t dataSize = m.cols * m.rows * elemSize;
            for (size_t i = 0; i < dataSize; ++i) {
                ar& m.data[i];
            }
        }

    } // namespace serialization
} // namespace boost

std::string save(const cv::Mat& mat) {
    std::ostringstream oss;
    boost::archive::text_oarchive toa(oss);
    toa << mat;
    return oss.str();
}

void load(cv::Mat& mat, const char* data_str) {
    std::stringstream ss;
    ss << data_str;
    boost::archive::text_iarchive tia(ss);
    tia >> mat;
}

#endif
