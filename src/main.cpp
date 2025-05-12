#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

cv::Mat sequentialBlur(const cv::Mat& input_image, int kernel_size) {
    if (kernel_size <= 0 || kernel_size % 2 == 0) {
        std::cerr << "Core's size must to be positive and odd" << std::endl;
    }

    cv::Mat output_image = cv::Mat::zeros(input_image.size(), input_image.type());

    int border = kernel_size / 2; //half core's size

	//iterate over rows of image
    for (int y = border; y < input_image.rows - border; ++y) {
        for (int x = border; x < input_image.cols - border; ++x) {

            cv::Vec3d sum_channels = { 0.0, 0.0, 0.0 }; //store sum for channels

            //iterate over rows of core
			for (int ky = -border; ky <= border; ++ky) {
                for (int kx = -border; kx <= border; ++kx) {
                    // Получаем пиксель из входного изображения в окне ядра
                    cv::Vec3b pixel = input_image.at<cv::Vec3b>(y + ky, x + kx);

                    sum_channels[0] += pixel[0]; // B - this order is classic for opencv
                    sum_channels[1] += pixel[1]; // G
                    sum_channels[2] += pixel[2]; // R 
                }
            }

            double total_pixels_in_kernel = kernel_size * kernel_size;
            cv::Vec3b avg_pixel;
            avg_pixel[0] = static_cast<uchar>(sum_channels[0] / total_pixels_in_kernel); //B
            avg_pixel[1] = static_cast<uchar>(sum_channels[1] / total_pixels_in_kernel); //G
            avg_pixel[2] = static_cast<uchar>(sum_channels[2] / total_pixels_in_kernel); //R

            output_image.at<cv::Vec3b>(y, x) = avg_pixel; //putting average in output image core
        }
    }
    return output_image;
}

int main() {
    std::string image_path = "building.jpg";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "No image found for this path: " << image_path << std::endl;
        return -1;
    }

    std::cout << "Image's been downloaded successfuly. Dimensions: " << image.cols << "x" << image.rows << std::endl;
    std::cout << "Amount of channels: " << image.channels() << std::endl;

    int blur_kernel_size = 5;

    auto start_time = std::chrono::high_resolution_clock::now();

    cv::Mat blurred_image = sequentialBlur(image, blur_kernel_size);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    std::cout << "Execution time of sequentialBlur (" << blur_kernel_size << "x" << blur_kernel_size << "): " << duration.count() << " ms" << std::endl;

    cv::imshow("Original Image", image);
    cv::imshow("Blurred Image (Sequential)", blurred_image);

    cv::waitKey(0);

    return 0;
}
