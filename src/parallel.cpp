#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

cv::Mat parallellBlur(const cv::Mat& input_image, int kernel_size, int num_threads) {
    if (kernel_size <= 0 || kernel_size % 2 == 0) {
        std::cerr << "Core's size must to be positive and odd" << std::endl;
    }

    cv::Mat output_image = cv::Mat::zeros(input_image.size(), input_image.type());

    int border = kernel_size / 2; //half core's size

	//iterate over gotten rows of image

    //iterate over rows of image

    auto blur_part = [&](int start_row, int end_row) {
        for (int y = start_row; y < end_row; ++y) {
            if (y < border || y >= input_image.rows - border) continue;
            for (int x = border; x < input_image.cols - border; ++x) {
                cv::Vec3d sum_channels = { 0.0, 0.0, 0.0 };
                for (int ky = -border; ky <= border; ++ky) {
                    for (int kx = -border; kx <= border; ++kx) {
                        cv::Vec3b pixel = input_image.at<cv::Vec3b>(y + ky, x + kx);
                        sum_channels[0] += pixel[0]; // B - this order is classic for opencv
                        sum_channels[1] += pixel[1]; // G
                        sum_channels[2] += pixel[2]; // R 
                    }
                }
                double total_pixels_in_kernel = kernel_size * kernel_size;
                cv::Vec3b avg_pixel;
                avg_pixel[0] = static_cast<uchar>(sum_channels[0] / total_pixels_in_kernel);
                avg_pixel[1] = static_cast<uchar>(sum_channels[1] / total_pixels_in_kernel);
                avg_pixel[2] = static_cast<uchar>(sum_channels[2] / total_pixels_in_kernel);

                output_image.at<cv::Vec3b>(y, x) = avg_pixel; //putting average in output image core
            }
        }
        };

    std::vector<std::thread> threads;
    int rows_per_thread = input_image.rows / num_threads;
    int extra_rows = input_image.rows % num_threads;
    int current_row = 0;

    for (int i = 0; i < num_threads; ++i) {
        int start_row = current_row;
        int end_row = start_row + rows_per_thread + (i < extra_rows ? 1 : 0);
        threads.emplace_back(blur_part, start_row, end_row);
        current_row = end_row;
    }

    for (auto& t : threads) {
        t.join();
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

    int blur_kernel_size = 7;

    // Определяем количество потоков
    int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4; // запасной вариант

    auto start_time = std::chrono::high_resolution_clock::now();

    cv::Mat blurred_image = parallellBlur(image, blur_kernel_size, num_threads);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    std::cout << "Execution time of parallellBlur " << blur_kernel_size << "x" << blur_kernel_size
        << ", threads: " << num_threads << " : " << duration.count() << " ms" << std::endl;

    cv::imshow("Original Image", image);
    cv::imshow("Blurred Image Parallel", blurred_image);

    cv::waitKey(0);

    return 0;
}
