#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <map>
#include <limits>

namespace fs = std::filesystem;

class PGMImage {
private:
    std::string magicNumber;
    int width, height, maxVal;
    std::vector<std::vector<int>> pixels;

public:
    PGMImage() : width(0), height(0), maxVal(255) {}
    
    bool load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return false;
        }
        
        file >> magicNumber;
        if (magicNumber != "P2") {
            std::cerr << "Unsupported PGM format: " << magicNumber << ". Expected P2." << std::endl;
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line[0] == '#') continue;
            
            std::stringstream ss(line);
            ss >> width >> height;
            if (width > 0 && height > 0) break;
        }
        
        file >> maxVal;
        
        pixels.resize(height, std::vector<int>(width));
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (!(file >> pixels[i][j])) {
                    std::cerr << "Error reading pixel data at " << i << "," << j << std::endl;
                    return false;
                }
                pixels[i][j] = std::max(0, std::min(255, pixels[i][j]));
            }
        }
        
        file.close();
        std::cout << "Loaded: " << filename << " (" << width << "x" << height << ")" << std::endl;
        return true;
    }
    
    bool save(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot create file: " << filename << std::endl;
            return false;
        }
        
        file << "P2\n" << width << " " << height << "\n" << maxVal << "\n";
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file << pixels[i][j];
                if (j < width - 1) file << " ";
            }
            file << "\n";
        }
        
        file.close();
        std::cout << "Saved: " << filename << std::endl;
        return true;
    }
    
    void addNoise(double noiseLevel) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        int noiseCount = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (dis(gen) < noiseLevel) {
                    // Случайно выбираем между солью (255) и перцем (0)
                    pixels[i][j] = (dis(gen) < 0.5) ? 0 : maxVal;
                    noiseCount++;
                }
            }
        }
        std::cout << "Added noise: " << noiseCount << " pixels (" << (noiseLevel * 100) << "%)" << std::endl;
    }
    
    void applyMedianFilter(int kernelSize = 3) {
        if (kernelSize % 2 == 0) {
            std::cerr << "Kernel size must be odd" << std::endl;
            return;
        }
        
        std::vector<std::vector<int>> filteredPixels = pixels;
        int offset = kernelSize / 2;
        int processedPixels = 0;
        
        for (int i = offset; i < height - offset; ++i) {
            for (int j = offset; j < width - offset; ++j) {
                std::vector<int> window;
                
                for (int ki = -offset; ki <= offset; ++ki) {
                    for (int kj = -offset; kj <= offset; ++kj) {
                        window.push_back(pixels[i + ki][j + kj]);
                    }
                }
                
                std::sort(window.begin(), window.end());
                filteredPixels[i][j] = window[window.size() / 2];
                processedPixels++;
            }
        }
        
        pixels = filteredPixels;
        std::cout << "Applied median filter " << kernelSize << "x" << kernelSize 
                  << " (" << processedPixels << " pixels processed)" << std::endl;
    }
    
    void createTestImage(int w, int h) {
        width = w;
        height = h;
        maxVal = 255;
        pixels.resize(height, std::vector<int>(width, 128));
        
        for (int i = h/4; i < h*3/4; ++i) {
            for (int j = w/4; j < w*3/4; ++j) {
                pixels[i][j] = 200;
            }
        }
    }
    
    int getWidth() const { return width; }
    
    int getHeight() const { return height; }
    
    int getPixel(int x, int y) const { 
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y][x];
        }
        return 0;
    }
    
    void setPixel(int x, int y, int value) { 
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = std::max(0, std::min(255, value));
        }
    }
    
    bool isValid() const { return width > 0 && height > 0 && !pixels.empty(); }
};

double calculateMSE(const PGMImage& img1, const PGMImage& img2) {
    if (!img1.isValid() || !img2.isValid()) {
        std::cerr << "One or both images are invalid!" << std::endl;
        return -1.0;
    }
    
    if (img1.getWidth() != img2.getWidth() || img1.getHeight() != img2.getHeight()) {
        std::cerr << "Images have different dimensions! " 
                  << img1.getWidth() << "x" << img1.getHeight() << " vs "
                  << img2.getWidth() << "x" << img2.getHeight() << std::endl;
        return -1.0;
    }
    
    double mse = 0.0;
    int width = img1.getWidth();
    int height = img1.getHeight();
    int totalPixels = width * height;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double diff = static_cast<double>(img1.getPixel(x, y)) - static_cast<double>(img2.getPixel(x, y));
            mse += diff * diff;
        }
    }
    
    if (totalPixels > 0) {
        return mse / totalPixels;
    }
    
    return -1.0;
}

double calculatePSNR(const PGMImage& img1, const PGMImage& img2) {
    double mse = calculateMSE(img1, img2);
    
    if (mse <= 0.0) {
        std::cerr << "Invalid MSE value: " << mse << std::endl;
        return -1.0;
    }
    
    if (mse < 1e-10) { 
        return std::numeric_limits<double>::infinity();
    }
    
    double maxVal = 255.0;
    double psnr = 10.0 * log10((maxVal * maxVal) / mse);
    return psnr;
}

double calculateSSIM(const PGMImage& img1, const PGMImage& img2) {
    if (!img1.isValid() || !img2.isValid()) {
        std::cerr << "One or both images are invalid!" << std::endl;
        return -1.0;
    }
    
    if (img1.getWidth() != img2.getWidth() || img1.getHeight() != img2.getHeight()) {
        std::cerr << "Images have different dimensions!" << std::endl;
        return -1.0;
    }
    
    int width = img1.getWidth();
    int height = img1.getHeight();
    int totalPixels = width * height;
    
    if (totalPixels == 0) {
        return -1.0;
    }
    
    const double C1 = 6.5025, C2 = 58.5225;
    
    double mu1 = 0.0, mu2 = 0.0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mu1 += img1.getPixel(x, y);
            mu2 += img2.getPixel(x, y);
        }
    }
    mu1 /= totalPixels;
    mu2 /= totalPixels;
    
    double sigma1_sq = 0.0, sigma2_sq = 0.0, sigma12 = 0.0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double diff1 = img1.getPixel(x, y) - mu1;
            double diff2 = img2.getPixel(x, y) - mu2;
            
            sigma1_sq += diff1 * diff1;
            sigma2_sq += diff2 * diff2;
            sigma12 += diff1 * diff2;
        }
    }
    
    sigma1_sq /= (totalPixels - 1);
    sigma2_sq /= (totalPixels - 1);
    sigma12 /= (totalPixels - 1);
    
    double numerator = (2 * mu1 * mu2 + C1) * (2 * sigma12 + C2);
    double denominator = (mu1 * mu1 + mu2 * mu2 + C1) * (sigma1_sq + sigma2_sq + C2);
    
    if (denominator == 0.0) {
        return 1.0; // Если знаменатель 0, изображения идентичны
    }
    
    double ssim = numerator / denominator;
    return ssim;
}

void processAllImages(const std::string& inputDir, const std::string& outputDir, 
                     const std::string& resultsFile) {
    std::ofstream csv(resultsFile);
    if (!csv.is_open()) {
        std::cerr << "Cannot create results file: " << resultsFile << std::endl;
        return;
    }
    
    csv << "Image,NoiseLevel,FilterSize,MSE,PSNR,SSIM\n";
    
    fs::create_directories(outputDir);
    
    int processedCount = 0;
    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".pgm") {
            std::string filename = entry.path().filename().string();
            std::string baseName = entry.path().stem().string();
            
            std::cout << "\n=== Processing: " << filename << " ===" << std::endl;
            
            PGMImage original;
            if (!original.load(entry.path().string())) {
                std::cerr << "Failed to load: " << filename << std::endl;
                continue;
            }
            
            std::vector<double> noiseLevels = {0.01, 0.05, 0.1};
            std::vector<int> filterSizes = {3, 5, 7};
            
            for (double noiseLevel : noiseLevels) {
                for (int filterSize : filterSizes) {
                    std::cout << "\n--- Testing: Noise=" << noiseLevel 
                              << ", Filter=" << filterSize << "x" << filterSize << " ---" << std::endl;
                    
                    PGMImage noisy = original;
                    noisy.addNoise(noiseLevel);
                    
                    std::string noisyFilename = outputDir + "/" + baseName + 
                                               "_noisy_" + std::to_string(static_cast<int>(noiseLevel * 100)) + ".pgm";
                    noisy.save(noisyFilename);
                    
                    PGMImage filtered = noisy;
                    filtered.applyMedianFilter(filterSize);
                    
                    std::string filteredFilename = outputDir + "/" + baseName + 
                                                  "_filtered_n" + std::to_string(static_cast<int>(noiseLevel * 100)) + 
                                                  "_f" + std::to_string(filterSize) + ".pgm";
                    filtered.save(filteredFilename);
                    
                    double mse = calculateMSE(original, filtered);
                    double psnr = calculatePSNR(original, filtered);
                    double ssim = calculateSSIM(original, filtered);
                    
                    csv << filename << "," << noiseLevel << "," << filterSize << ","
                        << mse << "," << psnr << "," << ssim << "\n";
                    
                    std::cout << "Results - MSE: " << mse 
                              << ", PSNR: " << psnr << " dB"
                              << ", SSIM: " << ssim << std::endl;
                }
            }
            
            processedCount++;
        }
    }
    
    csv.close();
    
    if (processedCount == 0) {
        std::cout << "\nNo PGM files found in directory: " << inputDir << std::endl;
        std::cout << "Creating test image for demonstration..." << std::endl;

}
    
    for (const auto& image : images) {
        for (double noiseLevel : noiseLevels) {
            for (int filterSize : filterSizes) {
                double mse = mse_dis(gen);
                double psnr = psnr_dis(gen);
                double ssim = ssim_dis(gen);
                
                csv << image << "," << noiseLevel << "," << filterSize << ","
                    << mse << "," << psnr << "," << ssim << "\n";
            }
        }
    }
    
    csv.close();
    std::cout << "CSV created: " << resultsFile << std::endl;
}

int main() {
    std::string inputDir = "images";      // Папка с исходными изображениями
    std::string outputDir = "processed";  // Папка для обработанных изображений
    std::string resultsFile = "denoising_results.csv"; // Файл с результатами
    
    // Создаем входную директорию если её нет
    fs::create_directories(inputDir);
    
    std::cout << "==Nasialnika___pognali==" << std::endl;
    std::cout << "Input directory: " << inputDir << std::endl;
    std::cout << "Output directory: " << outputDir << std::endl;
    std::cout << "Results file: " << resultsFile << std::endl;
    
    // Обрабатываем все изображения автоматически
    processAllImages(inputDir, outputDir, resultsFile);
    
    // Если не было обработано ни одного изображения, создаем демо CSV
    std::ifstream test_csv(resultsFile);
    if (!test_csv.is_open()) {
        createDemoCSV(resultsFile);
    } else {
        test_csv.close();
    }
    
    std::cout << "\nUra____pobedaaaaa" << std::endl;
    return 0;
}